/**
 *
 * \brief BFCP server API
 *
 * Implements BFCP Floor control server  API actions and events   .
 *
 * Create BFCP server with conference ID and floor ID  .
 * The stack is TCP/IP server ( based on \ref BFCPConnection ).
 *
 * \remarks :
 * In the first release , server manage only one conferenceID and one floorID. 
 *
 * In the first release , server can not use active connections .
 *
 * This class include a final state machine based on \ref BFCP_fsm class .
 * You can overide methode and state model of FSM .
 *  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_server.h
 *
 * \version $Revision: 2630 $
 *
 * \date $Date: 2015-11-25 17:47:27 +0100 (Wed, 25 Nov 2015) $
 *
 * \remarks :
 */

/* ==========================================================================*/
/* File identification                                                       */
/* ==========================================================================*/

/* ==========================================================================*/
/* System include(s)                                                         */
/* ==========================================================================*/
#ifndef _BFCP_SERVER_H
#define _BFCP_SERVER_H
#ifndef WIN32
#include <unistd.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BFCPconnection.h"
#include "BFCP_fsm.h"
#include "bfcp_threads.h"
#include "bfcp_messages.h"
#include "bfcp_user_list.h"
#include "bfcp_link_list.h"

/**  \struct  st_bfcp_conference 
 * \brief BFCP Conference instance 
*/
typedef struct  {
	int bfcp_transport;			/**  \brief  TCP/BFCP (0) or TLS/BFCP (1) */
	bfcp_queue *pending;			/**  \brief  The Pending list */
	bfcp_queue *accepted;			/**  \brief  The Accepted list */
	bfcp_queue *granted;			/**  \brief  The Granted list */
	UINT32 conferenceID;		/**  \brief  The BFCP ConferenceID */
	UINT16 floorRequestID;	/**  \brief The base FloorRequestID to increment at each new request */
	bfcp_list_users *user;			/**  \brief  The Users list */
	bfcp_list_floors *floor;		/**  \brief  The Floors list */
	UINT32 chair_wait_request;	/**  \brief  Time in miliseconds that the system will wait for a ChairAction */
	int automatic_accepted_deny_policy;	/**  \brief  Policy for automated responses when a chair is missing (0 = accept request, 1 = reject request) */
} st_bfcp_conference;


/**  \struct  st_bfcp_server 
 * \brief Floor Control Server (FCS) 
*/
typedef struct  {
	UINT16 Actual_number_conference;	/**  \brief  The current number of managed conferences */
	UINT16 Max_number_conference;	/**  \brief  The maximum number of allowed conferences */
	st_bfcp_conference *list_conferences;		/**  \brief  The linked list of currently managed conferences */
} st_bfcp_server;

#define BFCP_SERVER_BASE_CONFID   1
#define BFCP_SERVER_BASE_USERID   1
#define BFCP_SERVER_BASE_FLOORID  1
#define BFCP_SERVER_BASE_STREAMID 0
#define BFCP_MAX_CONF           64                   /** @brief The default max conference by server  */
/**
 * BFCP Floor control server manager class 
 *
 * \class BFCP_Server
 *
 * Floor control servers respond to FloorRequest messages with
 * FloorRequestStatus messages, which provide information about the
 * status of the floor request.  The first FloorRequestStatus message is
 * the response to the FloorRequest message from the client, and
 * therefore has the same Transaction ID as the FloorRequest.
 * 
 * After particpant connection BFCP Floor control server wait a \ref e_bfcp_primitives::e_primitive_Hello  messages and auto reply with the capacity of floor control servers , and confirm that they are alive on reception.
 * Actual server capacity :
 * \li Supported primitive 
 *
 * BFCP hello message \ref e_bfcp_primitives::e_primitive_Hello 
 * 
 * BFCP floor request \ref e_bfcp_primitives::e_primitive_FloorRequest 
 *
 * BFCP floor release \ref e_bfcp_primitives::e_primitive_FloorRelease
 *
 * \li Create  a BFCP server  . \ref BFCP_Server 
 *
 * \li Start TCP thread server and waiting connection. \ref OpenTcpConnection 
 *
 * \li Close all connections and stop  TCP thread server. \ref CloseTcpConnection 
 *
 * \li Add user on Floor Control Server. \ref AddUser  
 *
 * \li Remove user on Floor Control Server .  \ref RemoveUserInConf  
 *
 * \li Check if user id aldready add in Floor Control Server .  \ref isUserInConf
 *
 * \li  Received connections events and BFCP request of participants. \ref ServerEvent::OnBfcpServerEvent 
 *
 * \li  Get conference ID manag by this server  \ref GetConfID 
 *
 * \li  Get floor ID manag by this server  \ref GetFloorID 
 *
 * \li Dump state of floor control server . \ref DumpServer
 *
 * \li Send a Floor Request Respons. \ref FloorRequestRespons
 *
 * \li Send a Floor Status. \ref SendFloorStatus
 *
 * \li return the current state of FCS  \ref GetFloorState
 *
 * \see  
 * \li \ref BFCPConnection  network connection  
 * \warning 
 *
 * You must implement  BFCP_Server::ServerEvent::OnBfcpServerEvent(e_BFCP_ACT p_evt , st_BFCP_fsm_event* p_FsmEvent ) 
 *
 * You must implement  BFCP_Server::Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) 
 *
 */
class BFCP_Server :  public BFCPConnection , public BFCP_fsm , public BFCP_LinkList , public BFCP_UserList
{

public:
    /**
     * Callback for BFCP participants events and request 
     * \class ServerEvent
    */
   class ServerEvent
   {
        public: 
    /**
     *  \brief Floor control server callback for BFCP events and respons 
     *
     * @param p_evt \ref BFCP_fsm::e_BFCP_ACT current event of BFCP server 
     * @param p_FsmEvent \ref  BFCP_fsm::st_BFCP_fsm_event informations struct of events 
     * @return  true success , false failed 
     *
     */
       virtual bool OnBfcpServerEvent(e_BFCP_ACT p_evt , st_BFCP_fsm_event* p_FsmEvent ) = 0 ;
       /**
        * Default destructor 
        * @return void
        */
       virtual ~ServerEvent() {};	
    };

     /**
      * Default destructor 
      * @return void
      */
     ~BFCP_Server();
    /**
     * Create a new server , but don't launch network server .
     * @param Max_conf Number of maximum conference on this server ( futur use ) 
     * @param p_confID Conference ID manage by this server.   \ref BFCP-COMMON-HEADER 
     * @param p_userID First userID manage by this server ( futur use )
     * @param p_floorID Floor ID manage by this server \ref FLOOR-ID
     * @param p_streamID futur use 
     * @param p_ServerEvent listener for ServerEvent \ref ServerEvent
     * @return new instance
     */
    BFCP_Server(UINT8 Max_conf ,UINT32 p_confID ,UINT32 p_userID , UINT32 p_floorID , UINT32 p_streamID ,BFCP_Server::ServerEvent* p_ServerEvent);

    /**
     * \brief start thread for TCP connection . 
     *
     * If the server aldready connect with the same parameters the connection is not modified 
     * else currrents connections are closed and TCP server is restarted. 
     * 
     * @param local_address local IP V4 address,  you can use NULL to listen all interface  
     * @param local_port  local port, if you use 0 you dont bind . 
     * @param remote_address remote ipv4 adress if your are on active mode ( not recommended for server )
     * @param remote_port remote port if your are on active mode ( not recommended for server )
     * @param isServer true == serveur waitting connection of remotes , false serveur launch connection with remote
     * @return true , in passive mode , serveur started and waitting connections , in active mode your are connected at remoteg .
     *
     *
     * @see 
     * OnBfcpServerEvent
     * BFCPConnection::SelLocalConnection
     */
    bool OpenTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isServer);
    
    /**
     * @param p_userID - user ID to be associated with 
     * 
     * @param local_address local IP address to bind
     * - if NULL, local adress of TCP connection will be used. 
     * - if specified, we will try to bind to the specified address.
     * - if empty local adress of TCP connection will be used and address will be returned.
     *
     * @param local_port, local port to use
     *
     **/
    bool OpenUdpConnection(UINT16 p_userID, char * local_address, int local_port);
    
    
    bool GetConnectionInfo(UINT16 p_userID, char * local_address, int * local_port, int * transport);
    
    /**
     * Close all current connection and stop server thread .
     * @return true sucess , false error
     */
    bool CloseTcpConnection() ;    
     /**
     * \brief Virtual log and traces callback , for better traces integration on your process 
     * @param pcFile file reference 
     * @param iLine  line refernce 
     * @param iErrorLevel error level \ref INF debug \ref WAR warning \ref ERR error 
     * @param pcFormat char formated traces 
     */
     
     
    
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) ;
    /**
     * Getter for conference ID of this server 
     * \ref BFCP-COMMON-HEADER
     * @return 
     */
    UINT32              GetConfID( ) { return m_confID ;};
    /**
     * Getter for first user id free on this server ( futur use ) 
     * @return 
     */
    UINT16              GetFirstUserID( ) { return m_FirstUserID ; };
    /**
     * Getter for floor ID of this server 
     * \ref FLOOR-ID
     * @return 
     */
    UINT16              GetFloorID( ) { return m_floorID ;};
    /**
     * Getter for stream ID of this server ( futur use )
     * @return 
     */
    UINT16              GetStreamID( ) { return m_streamID ;};
    
    /**
     * return if user exist on conference 
     * @param userID user to check 
     * @return true user exist on conference , false user not exist .
     */
    bool isUserInConf(UINT16 userID );

    /**
     *  \brief Add a new user on floor control server 
     * \remarks 
     * you must add user before network connection , otherwise \ref e_bfcp_primitives hello are not  confirmed .
     * and all request of this user are unrecognized .
     * @param userID user ID added on conference
     * @param user_URI  user URI ( not mandatory ) 
     * @param user_display_name user display name  ( not mandatory ) 
     * @return rue success , false failed 
     */
    bool AddUser(UINT16 userID, char *user_URI=NULL, char *user_display_name=NULL);
     /**
     * Remove user on FCS
     * \remarks 
     * User are only removed on authorized user list, TCP Connections are not closed .
     * @param userID user ID removed on conference
     * @return true success , false failed 
     */
    bool RemoveUserInConf(UINT16 userID );
    
    /**
     * Dump state of floor control server . 
     */
    void DumpServer();
    
    /**
     * Set the remote address and port (UDP) and send Hello to the remote client
     **/
     bool SendHello(UINT32 p_userID, const char * remoteAddr, UINT16 remotePort, BFCP_SOCKET s = INVALID_SOCKET, int tr = BFCP_OVER_UDP );
    
    /**
     * The floor control server informs floor participants and floor chairs
     * about the status of their floor requests by sending them
     * FloorRequestStatus messages.
     * @param p_userID user id of request 
     * @param p_beneficiaryID  beneficiary of request ( 0 = userID ) \ref BENEFICIARY-ID
     * @param p_TransactionID transaction ID of request \ref BFCP-PROTOCOL-TRANSACTION
     * @param p_floorRequestID floor request ID of request \ref FLOOR-REQUEST-ID
     * @param p_bfcp_status status of request \ref REQUEST-STATUS 
     * @param p_queue_position position on the list \ref REQUEST-STATUS
     * @param p_priority priority of request \ref PRIORITY
     * @param p_InformALL true , all particpant receive a BFCP floor status with the new status of conference and floor ID  
     * @return true = success , false = failed .
     */
    bool FloorRequestRespons(UINT32 p_userID ,  UINT32 p_beneficiaryID , UINT16 p_TransactionID , UINT16 p_floorRequestID , e_bfcp_status p_bfcp_status , UINT16 p_queue_position = 0  ,  e_bfcp_priority p_priority = BFCP_NORMAL_PRIORITY ,  bool p_InformALL = false  );
    /**
     * The floor control server informs floor participants and floor chairs
     * about the status (e.g., the current holder) of a floor by sending
     * them FloorStatus messages.
     * @param p_userID user ID concerned by this status 
     * @param p_TransactionID transaction ID concerned by this status ( TODO check if mandatory )
     * @param p_floorRequestID floor request ID  \ref FLOOR-REQUEST-ID
     * @param node internal FloorRequest information if node is null we send status by FCS state else we use node information 
     * @param p_InformALL true , all particpant execpt user id receive a current state of FCS , false only user id receive the current state , true and user id is null all participant receive a current state of FCS
     * @return 
     */
    bool SendFloorStatus(UINT32 p_userID ,  UINT16 p_TransactionID , UINT16 p_floorRequestID , bfcp_node *node , bool p_InformALL );
    
    
    /**
     * Send a goodback message to the remote party. 
     * @param p_userID
     **/
    bool SendGoodBye(UINT32 p_userID);

    
    bool AnswerGoodByeAck(UINT32 ConferenceID, UINT16 p_userID, UINT16 TransactionID, BFCP_SOCKET sockfd, int transport);
    
    /**
     * return the current state of FCS , and the informations of first request corresponding to this state
     * @param p_bfcp_status current status of FCS 
     * @param p_userID first user id corresponding to this state
     * @param p_beneficiaryID first beneficiary id corresponding to this state
     * @param p_floorRequestID first floor request id corresponding to this state
     * @return true success , false failed 
     */
     
    bool GetFloorState(e_bfcp_status* p_bfcp_status , UINT32* p_userID ,  UINT32* p_beneficiaryID , UINT16* p_floorRequestID  );
    
protected:
    /** \brief  BFCPconnection callback  */
    virtual int ProcessBFCPmessage(bfcp_received_message * m, BFCP_SOCKET s);
    
    virtual bool OnBFCPConnected(BFCP_SOCKET socket, const char * remoteIp , int remotePort);
    virtual bool OnBFCPDisconnected(BFCP_SOCKET socket) ;
    
    /** \brief callback user_list */
    virtual int BFCP_UserList_error_code(UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, char *error_info, bfcp_unknown_m_error_details *details, int sockfd, int i, int transport)
    {
        return bfcp_error_code( conferenceID , userID , TransactionID , code  , error_info,details, sockfd,  i,  transport);
    } ;
    /** \brief callback link_list */
    virtual bfcp_user_information* BFCP_LinkList_show_user_information(lusers list_users, UINT16 userID) {
        return bfcp_show_user_information(list_users, userID);};

  
    /** \brief Virtual FSM exit function */
    bool BFCPFSM_UpdatesBfcpFsmEvent( s_bfcp_msg_event* p_bfcp_evt , e_BFCP_ACT p_evt , e_BFCP_ACT p_st );
    /** \brief FSM transistion */
    virtual bool BFCPFSM_Hello(s_bfcp_msg_event* p_evt) ;
    virtual bool BFCPFSM_PrimitiveNotSupported(s_bfcp_msg_event* p_evt) ;
    virtual bool BFCPFSM_FloorRelease(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorRequest(  s_bfcp_msg_event* p_evt );
    
 

    /* A controller to check timeouts when waiting for a ChairAction watchdog */
#ifdef WIN32
    static unsigned  __stdcall WatchDog(void* st_thread);
#else
    static void* WatchDog(void* st_thread);
#endif
    
private: 
    ServerEvent * m_ServerEvent ; 
    /* Thread- and mutex-related variables */
    bfcp_mutex_t count_mutex;
    st_bfcp_server* 	m_struct_server;	
    UINT32              m_confID ;
    UINT16              m_FirstUserID ;
    UINT16              m_floorID ;
    UINT16              m_streamID ;
    void                initStateMachine(void);
    void                print_requests_list(st_bfcp_server* server, int index, e_bfcp_status status);
    bool FloorStatusRespons(UINT32 p_userID ,  UINT16 p_TransactionID , UINT16 p_floorRequestID , bfcp_node *node , bool p_InformALL );
   
    UINT16		m_trIdGenerator;
    /**************************/
    /* Server-related methods */
    /**************************/
    /** \brief Destroy a currently running Floor Control Server */
    int bfcp_destroy_bfcp_server(st_bfcp_server **serverp);
    /** \brief Create a new BFCP Conference and add it to the FCS */
    int bfcp_initialize_conference_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 Max_Num_Floors, UINT16 Max_Number_Floor_Request, int automatic_accepted_deny_policy, UINT32 chair_wait_request);
    /** \brief Destroy a currently managed BFCP Conference and remove it from the FCS */
    int bfcp_destroy_conference_server(st_bfcp_server *server, UINT32 ConferenceID);
    /** \brief Change the maximum number of allowed conferences in the FCS */
    int bfcp_change_number_bfcp_conferences_server(st_bfcp_server *server, UINT16 Num);
    /** \brief Change the maximum number of users that can be granted this floor at the same time */
    int bfcp_change_number_granted_floor_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 limit_granted_floor);
    /** \brief Change the allowed number of per-floor requests for this list */
    int bfcp_change_user_req_floors_server(st_bfcp_server *server, UINT16 Max_Number_Floor_Request);
    /** \brief Change the automated policy for requests related to floors that have no chair */
    int bfcp_change_chair_policy(st_bfcp_server *server, UINT32 ConferenceID, int automatic_accepted_deny_policy, UINT32 chair_wait_request);
    /** \brief Add a floor to an existing conference */
    int bfcp_add_floor_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 ChairID, int limit_granted_floor);
    /** \brief Remove a floor from an existing conference */
    int bfcp_delete_floor_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID);
    /** \brief Set a participant as chair of a floor */
    int bfcp_add_chair_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID, UINT16 ChairID);
    /** \brief Set no participant as chair for a floor */
    int bfcp_delete_chair_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 FloorID);
    /** \brief Add a participant to the list of users of a BFCP Conference */
    int bfcp_add_user_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, char *user_URI, char *user_display_name);
    /** \brief assign the socket file descriptor and the transpor to the user */
    int bfcp_set_user_sockfd(st_bfcp_server *server, UINT32 conferenceID,UINT16 userID, BFCP_SOCKET p_sockfd, int transport );
    BFCP_SOCKET bfcp_get_user_sockfd(st_bfcp_server *server, UINT32 conferenceID,UINT16 userID, int * p_transport);
    /* Remove a participant from the list of users of a BFCP Conference */
    int bfcp_delete_user_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID);

    /** 
     * Process a goodbye request: notify the application, then remove the user and when under
     * unreliable transport, remove the associated client.
     *
     * @param ConferenceID concerned conference
     * @param UserID user to terminate
     * @param TransactionID BFCP transaction ID
     * @param p_sockfd socket file descriptor on which request has been received.
     * @param transport transport on which message has been received
     */
    void OnGoodBye(UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, BFCP_SOCKET p_sockfd, int transport);

    /******************/
    /* Helper methods */
    /******************/

    /** \brief Create a new 'bfcp_floor_request_information' (bfcp_messages.h) out of a 'pnode' */
    bfcp_floor_request_information *create_floor_request_userID(pnode traverse, lusers users, UINT16 userID, UINT16 request_status, int i);
    /** \brief Create a new 'bfcp_floor_request_information' (bfcp_messages.h) out of a floor */
    bfcp_floor_request_information *create_floor_message(UINT16 floorID, pnode traverse, lusers users, UINT16 request_status, int i);
    /** \brief Prepare the needed arguments for a FloorRequestStatus BFCP message */
    int bfcp_print_information_floor(st_bfcp_conference *conference, UINT16 userID, UINT16 TransactionID, pnode newnode, UINT16 status);
    /** \brief Setup and send a FloorRequestStatus BFCP message */
    int bfcp_show_requestfloor_information(bfcp_list_users *list_users, bfcp_queue *accepted_queue, 
					   UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID,
					   pnode newnode, UINT16 status, BFCP_SOCKET socket, int transport);

    /** \brief Remove all floor requests made by a user from all existing nodes */
    int bfcp_remove_floorrequest_from_all_nodes(st_bfcp_conference *server, UINT16 userID);
    /** \brief Remove all floor requests made by a user from a queue */
    int bfcp_remove_floorrequest_from_a_queue(bfcp_queue *conference, UINT16 userID);
    /** \brief Disable and remove all floor events notifications to an user */
    int bfcp_remove_floorquery_from_all_nodes(bfcp_list_floors *lfloors, UINT16 userID);

    /** \brief Handle an incoming FloorRequest message */
    int bfcp_FloorRequest_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID, pnode newnode, int sockfd, int y, int transport);
    /** \brief Handle an incoming FloorRelease message */
    /** \brief RequestStatus ->Cancelled if the floor had not been previous granted- Released if the floor had been previous granted*/
    int bfcp_FloorRelease_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID, UINT16 userID, UINT16 FloorRequestID, BFCP_SOCKET sockfd, int y, int transport);

    /** \brief Handle an incoming ChairAction message */
    int bfcp_ChairAction_server(st_bfcp_server *server, UINT32 ConferenceID, bfcp_floor *list_floors, UINT16 userID, UINT32 FloorRequestID, int RequestStatus, char *chair_info, UINT16 queue_position, UINT16 TransactionID, int sockfd, int y, int transport);
    /** \brief Handle an incoming Hello message */
    int bfcp_hello_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, BFCP_SOCKET sockfd, int y, int transport);
    /** \brief Handle an incoming UserQuery message */
    int bfcp_userquery_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, UINT16 beneficiaryID, BFCP_SOCKET sockfd, int y, int transport);
    /** \brief Handle an incoming FloorQuery message */
    int bfcp_floorquery_server(st_bfcp_server *server, UINT32 ConferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 TransactionID, int sockfd, int y, int transport);
    /** \brief (??) */
    int bfcp_floor_query_server(bfcp_list_floors *lfloors, bfcp_floor *list_floors, UINT16 userID, int sockfd, int transport);
    /** \brief Handle an incoming FloorRequestQuery message */
    int bfcp_floorrequestquery_server(st_bfcp_server *server, UINT32 ConferenceID, UINT16 TransactionID,    UINT32 FloorRequestID, UINT16 userID, int sockfd, int y, int transport);
    /** \brief Check if it's fine to grant a floor to an accepted request */
    int check_accepted_node(st_bfcp_conference *conference, pnode queue_accepted, UINT16 floorID, char *chair_info);
    /** \brief Check if it's fine to grant a floor to an accepted request (??) */
    int give_free_floors_to_the_accepted_nodes(st_bfcp_conference *conference, bfcp_queue *laccepted, bfcp_list_floors *lfloors, char *chair_info);
    /** \brief Setup and send an Error reply to a participant */
    int bfcp_error_code(UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code,const char *error_info, bfcp_unknown_m_error_details *details, BFCP_SOCKET sockfd, int i, int transport);
    /** \brief Setup and send a floorstatus BFCP message */
    int bfcp_show_floor_information(UINT32 conferenceID, UINT16 TransactionID, UINT16 userID, st_bfcp_conference *conference, UINT16 floorID, int *client, pnode newnode, UINT16 status);
    /** \brief Handle an incoming ChairAction message */
    int bfcp_ChairAction_server(st_bfcp_server *server, UINT32 conferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 floorRequestID, int RequestStatus, char *chair_info, UINT16 queue_position, UINT16 TransactionID, BFCP_SOCKET sockfd, int y, int transport);
    /** \brief Handle an incoming FloorRequestQuery message */
    int bfcp_floorrequestquery_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 TransactionID, UINT16 floorRequestID, UINT16 userID, BFCP_SOCKET sockfd, int y, int transport);
    /** \brief incoming messages */
    bool bfcp_received_msg(bfcp_received_message *recv_msg, BFCP_SOCKET sockfd);     
    
    
public: 
    /* Only for log stack don't use this .
     * @return server log instance 
     */
    BFCP_Server() { /* Just for stack log */ } ;
};


/** \brief Thread handling a specific FloorRequest instance */
typedef struct bfcp_thread {
    BFCP_Server* bfcpServer ;
    st_bfcp_conference *conf;			/** \brief BFCP Conference this thread is related to */
    UINT32 chair_wait_request;	/** \brief Time in milisecons that the thread will wait for a ChairAction */
    UINT16 floorRequestID;	/** \brief Identifier of the FloorRequest this thread is handling */
} bfcp_thread;
/** \brief Pointer to a thread */
typedef bfcp_thread *struct_thread;

#endif

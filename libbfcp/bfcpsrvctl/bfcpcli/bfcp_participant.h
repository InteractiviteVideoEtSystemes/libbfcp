/**
 *
 * \brief BFCP particpant API
 *
 * Implements BFCP particpant API actions and events on Floor control server   .
 * Create BFCP participant endpoint and a receiver remote endpoint or a receiver local endpoint only.
 * The stack is TCP/IP client/server ( based on \ref BFCPConnection ).. A connection usually has an input socket and an
 * output socket. Both are opened for defined ports. Each connection endpoint
 * must be set for an unique socket address. 
 *
 * This class include a final state machine based on \ref BFCP_fsm class .
 * You can overide methode and state model of FSM .
 *
 *
 * \author Philippe Verney 
 *
 * \file bfcp_participant.h
 *
 * \version $Revision: 2493 $
 *
 * \date $Date: 2015-10-27 12:51:00 +0100 (Tue, 27 Oct 2015) $
 *
 * \remarks :
 * In the first release , particpant manage only one conferenceID and one floorID. 
 *
 * \ingroup libbfcp
 *
 */

/* ==========================================================================*/
/* File identification                                                       */
/* ==========================================================================*/

/* ==========================================================================*/
/* System include(s)                                                         */
/* ==========================================================================*/

#ifndef _BFCP_PARTICIPANT_H
#define _BFCP_PARTICIPANT_H

//#define SUPPORT_SSL TRUE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef WIN32
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#endif

#include "bfcp_messages.h"
#include "BFCPconnection.h"
#include "BFCP_fsm.h"
#include "bfcp_threads.h"



/**  \brief    Participant-related Floor information */
typedef struct bfcp_floors_participant {
    UINT16 floorID;			/** \brief Floor Identifier */
    char *sInfo;				/** \brief Status Info (text) */
    struct bfcp_floors_participant *next;
}
st_bfcp_floors_participant;

/** \brief  BFCP Participant */
typedef struct  {
    UINT32 conferenceID;		/** \brief Conference Identifier */
    UINT16 userID;			/** \brief User Identifier (the participant) */
    st_bfcp_floors_participant* pfloors;		/** \brief List of floors this user is aware of */
}
st_bfcp_participant_information;

/**
 * BFCP Floor Participant manager class 
 *
 * \class BFCP_Participant
 *
 * Floor Participant : A logical entity that requests floors, and
 *  possibly information about them, from a floor control server.  An
 *  entity that assumes the logical role of a floor participant for a
 *  given transaction may assume a different role (e.g., a floor chair)
 *  for a different transaction.  The roles of floor participant and
 *  floor chair are defined on a transaction-by-transaction basis. In floor-controlled
 *  conferences, a given floor participant is typically colocated with a
 *  media participant, but it does not need to be.  Third-party floor
 *  requests consist of having a floor participant request a floor for a
 *  media participant when they are not colocated.
 *
 *  \ref BFCP_Participant Create  a BFCP user .
 *
 *  \ref OpenTcpConnection Open TCP connection with Floor Control Server.
 *
 *  \ref CloseTcpConnection Close TCP connection with Floor Control Server.
 *
 *  \ref bfcp_floorRequest_participant Send FloorRequest , to the Floor Control Server.
 *
 *  \ref bfcp_floorRelease_participant Send FloorRelease , to the Floor Control Server.
 *
 */
class BFCP_Participant : public BFCPConnection , public BFCP_fsm {
public:
    /**
      * Callback for BFCP FCS events and status 
     * \class ParticipantEvent
    */
    class ParticipantEvent {
    public:
        /**
         * Participant event callback .
	Used to received Floor Control Server status or respons .
         * @param p_evt current event received .
         * @param p_FsmEvent event informations 
         * @return true success , false failed .
         */
        virtual bool OnBfcpParticipantEvent(e_BFCP_ACT p_evt , st_BFCP_fsm_event* p_FsmEvent ) = 0 ;
        virtual ~ParticipantEvent() {};
    };
    // traces 
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) ;
    /**
     * Default destructor .
     * @return void
     */
    virtual ~BFCP_Participant();
    /**
     * Default constructor , to instanciate BFCP participant
     * @param p_confID BFCP conference ID
     * @param p_userID BFCP userID 
     * @param p_floorID BFCP floorID
     * @param p_streamID BFCP stream ID , not used in the first release .
     * @param p_ParticipantEvent ParticipantEvent class for OnBfcpParticipantEvent callback .
     * @return new instance .
     */
    BFCP_Participant(UINT32 p_confID ,UINT16 p_userID , UINT16 p_floorID , UINT16 p_streamID ,BFCP_Participant::ParticipantEvent* p_ParticipantEvent);

    /**
     * Open a new TCP connection with BFCP server . 
     * if the connection success , api send BFCP hello message .
     * On the hello message this class sets the Conference ID and the Transaction ID in the
     * common header .  
     * API sets the User ID in the common header to the client's identifier.
     * This User ID will be used by the floor control server to authenticate
     * and authorize the request.
     * the respons of Floor control server are recieved on \ref ParticipantEvent::OnBfcpParticipantEvent 
     * @param local_address local ip to use , NULL if you want use all ip interface .
     * @param local_port  local ip port , 0 if you dont want use specific port 
     * @param remote_address  ip adress of distant
     * @param remote_port   port of distant.
     * @param isServer  parameter to specifie if you launch connection with remote or if you waitting remote connection , for participant is recommanded to use false .
     * @return true sucess , if you are on server mode , the server is launched and waitting connection , else on client mode , you are connected of remote server .
     */
    bool OpenTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isServer);
    /**
     * Close current TCP connection .
     * @return true sucess , false failed .
     */
    bool CloseTcpConnection() ;
    /**
     * Check if the request ID is the current request .
     * @param p_FloorRequestID request ID
     * @return true sucess , false failed .
     */
    bool checkFloorRequestID( UINT16 p_FloorRequestID );
    /* FloorRequest */
    /**    FloorRequest 
     * 
     * Create floorRequest to BFCP Floor Control Server  .
     * Floor participants request a floor by sending a FloorRequest message
     * to the floor control server.  BFCP supports third-party floor
     * requests.  That is, the floor participant sending the floor request
     * need not be colocated with the media participant that will get the
     * floor once the floor request is granted.  FloorRequest messages carry
     * the identity of the requester in the User ID field of the common
     * header, and the identity of the beneficiary of the floor (in third-
     * party floor requests) in a BENEFICIARY-ID attribute.
     * FloorRequest messages identify the floor or floors being requested by
     * carrying their 16-bit floor identifiers in FLOOR-ID attributes.  If a
     * FloorRequest message carries more than one floor identifier, the
     * floor control server treats all the floor requests as an atomic
     * package.  That is, the floor control server either grants or denies
     * all the floors in the FloorRequest message.
     * Floor control servers respond to FloorRequest messages with
     * FloorRequestStatus messages, which provide information about the
     * status of the floor request.  The first FloorRequestStatus message is
     * the response to the FloorRequest message from the client, and
     * therefore has the same Transaction ID as the FloorRequest.
     * the respons of Floor control server are recieved on \ref ParticipantEvent::OnBfcpParticipantEvent 
     * @param p_floorID floor ID concerned by request .
     * @return true request send success , false failed .
     */
    int bfcp_floorRequest_participant(UINT16 p_floorID);

    /**
     * FloorRelease , Release current floorrequest 
     * @return true  request send success  , false failed .
     */
    int bfcp_floorRelease_participant();
    
    /** 
      * Retrieve current particpant information 
      *@return pointer on current participant information 
      */
    st_bfcp_participant_information* GetCurrentParticpantInfo ( ) { return  m_bfcp_participant_information ; } ;

    /** \brief BFCP Participant side Messages-related operations */

    /** Hello */
    int bfcp_hello_participant(st_bfcp_participant_information* participant);
    /** FloorRequest */
    int bfcp_floorRequest_participant(st_bfcp_participant_information* participant, UINT16 beneficiaryID, e_bfcp_priority priority, bfcp_floors_participant *list_floors, char *participant_info);
    /** FloorRelease */
    int bfcp_floorRelease_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID);
    /** FloorRequestQuery */
    int bfcp_floorRequestQuery_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID);
    /** UserQuery */
    int bfcp_userQuery_participant(st_bfcp_participant_information* participant, UINT16 beneficiaryID);
    /** FloorQuery */
    int bfcp_floorQuery_participant(st_bfcp_participant_information* participant, bfcp_floors_participant *list_floors);
    /** ChairAction */
    int bfcp_chairAction_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID, char *statusInfo, UINT16 status, bfcp_floors_participant *list_floors, UINT16 queue_position);


    /** Helper operations */

    /** Create a 'bfcp_floors_participant' element */
    st_bfcp_floors_participant *create_floor_list(UINT16 floorID, char *status_info);
    /** Create a 'bfcp_floors_participant' element and add it to an existing list */
    st_bfcp_floors_participant *insert_floor_list(st_bfcp_floors_participant* floor_list, UINT16 floorID, char *status_info);
    /** Destroy a list of 'bfcp_floors_participant' elements */
    int remove_floor_list(st_bfcp_floors_participant* floor_list);
    
protected:
    /**  BFCPconnection class callback */

    /**
     * Callback process a BFCP message is present on socket . 
     * @param p_sock  socket 
     * @return NULL , socket readed  , -1 error on socket.
     */
    virtual int ProcessBFCPmessage(bfcp_received_message * m, BFCP_SOCKET s);
    /**
     * Callback used to prevent success of connection.
     * @param socket socket connected  .
     * @param RemoteIp remote ip connected .
     * @param remotePort remote port .
     * @return FSM status 
     */
    virtual bool OnBFCPConnected(BFCP_SOCKET socket, const char * RemoteIp , int remotePort);

    /**
     * Callback used to prevent disconnection.
     * @param socket socket disconnected  .
     * @param RemoteIp remote ip connected .
     * @param remotePort remote port .
     * @return  FSM status 
     */
    virtual bool OnBFCPDisconnected(BFCP_SOCKET socket) ;

protected:
    // Virtual FSM transition
    virtual bool BFCPFSM_Connected(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_Disconnected(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorStatusAccepted(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorStatusGranted(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorStatusAborted(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorRequestStatusAccepted(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorRequestStatusGranted(  s_bfcp_msg_event* p_evt ) ;
    virtual bool BFCPFSM_FloorRequestStatusAborted(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_FloorReleaseStatusAborted(  s_bfcp_msg_event* p_evt ) ;
    virtual bool BFCPFSM_FloorRelease(  s_bfcp_msg_event* p_evt ) ;
    virtual bool BFCPFSM_FloorRequest(  s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_UpdateHwnd(  s_bfcp_msg_event* p_evt ) ;
    // Virtual FSM exit function
    virtual bool BFCPFSM_UpdatesBfcpFsmEvent( s_bfcp_msg_event* p_bfcp_evt ,e_BFCP_ACT p_evt , e_BFCP_ACT p_st );
    
private:
    UINT16 m_base_transactionID ;	/** \brief TransactionID of the client */
    int m_bfcp_transport;	/** \brief Wheter we use TCP/BFCP or TCP/TLS/BFCP */
    st_bfcp_participant_information* m_bfcp_participant_information ; /** \brief Current participant */
    UINT16 m_currentFloorRequestID ;  /** \brief Current floor request ID */
    bfcp_mutex_t count_mutex; /** \brief mutex used to prevent dual access */
    ParticipantEvent* m_ParticipantEvent ; /** \brief  ParticipantEvent class for OnBfcpParticipantEvent callback  */
    BFCP_SOCKET m_PartSocket ; /** \brief  socket used by this particpant */
    /**
     * Particpant BFCP messages analyse
     * @param recv_msg bfcp message 
     * @return true bfcp message is correct , false error .
     */
    bool bfcp_received_msg(bfcp_received_message *recv_msg);
    
     /**  BFCP Participant  operations */
    /**
     *  Destroy an existing Participant 
     * @param participant 
     * @return 
     */
    int bfcp_destroy_bfcp_participant(st_bfcp_participant_information **participant);
    /** Add a floor to the list of floors the participant will be aware of */
    int bfcp_insert_floor_participant(st_bfcp_participant_information* participant, UINT16 floorID);
    /** Delete a floor from the list of floors the participant is aware of */
    int bfcp_delete_floor_participant(st_bfcp_participant_information* participant, UINT16 floorID);
public:
    /**
     * Only for log stack don't use this .
     * @return particpant log instance 
     */
    BFCP_Participant( )  { /* Just for stack log */} ;

};

#endif

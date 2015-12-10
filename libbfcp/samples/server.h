/**
 *
 *
 * \brief Sample test of BFCP particpant API . 
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file server.h
 *
 * \version $Revision: 2161 $
 *
 * \date $Date: 2014-01-23 11:30:23 +0100 (Thu, 23 Jan 2014) $
 *
 * \remarks 
 *
 * \ingroup libbfcp
 */
#ifndef _BFCP_SERVER_TEST_H_
#define _BFCP_SERVER_TEST_H_
#include "bfcp_server.h"


#ifndef INF
#define INF __FILE__, __LINE__, 0
#endif

#ifndef WAR
#define WAR __FILE__, __LINE__, 1
#endif

#ifndef ERR
#define ERR __FILE__, __LINE__, 2
#endif
#define BFCPAPI_SUCCESS 1
#define BFCPAPI_ERROR 0
/** \enum e_floorctrlMode 
* \brief type of connection 
*/
typedef enum {
    FLOOCTRL_MODE_CLIENT = 0 ,
    FLOOCTRL_MODE_SERVER ,
    FLOOCTRL_MODE_CLIENT_AND_SERVER
}e_floorctrlMode ;

/** \class sampleServer
 * Easy sample of Floor Control Server  implementation \ref server.cpp
 * \warning 
 *
 * You must implement  BFCP_Server::ServerEvent::OnBfcpServerEvent(e_BFCP_ACT p_evt , st_BFCP_fsm_event* p_FsmEvent ) 
 *
 * You must implement  BFCP_Server::Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) 
 *
 * \section SampleManagFCS manage Floor control server 
 * 
 * 
 * Create a new Floor control server instance and start a TCP serveur of FCS  \ref StartServer  
 * 
 * Callback for participants connections and request . \ref sampleServer::OnBfcpServerEvent   
 *
 * \remarks 
 *
 * In the first release on instance of FCS manage one ConferenceID and one floor only .
 *
 * \ref BFCP_Server based on BFCP_Server class 
 */
class sampleServer : public BFCP_Server::ServerEvent {
public:
    /**
    * Floor control server sample constructor 
    * @return 
    */
    sampleServer();
    /**
    * Floor control server sample destructor
    * @return 
    */
    ~sampleServer();
    
    /**
     * Stop TCP thread server, close all actives connections., and destroy instance
     * @return always 1
     */
    int StopServer();
    /**
     * local conference ID setter 
     * @param p_confID \ref BFCP-COMMON-HEADER conference ID managed by this FCS
     */
    void                SetConfID( UINT32 p_confID ) ;
    /**
     * local conference ID getter
     * @return \ref BFCP-COMMON-HEADER conference ID managed by this FCS
     */
    UINT32            GetConfID( ) ;
    void                SetUserID( UINT16 p_userID );
    UINT16            GetUserID( );
    void                SetFloorID( UINT16 p_floorID );
    UINT16            GetFloorID( ) ;
    void                SetStreamID( UINT16 p_streamID );
    UINT16            GetStreamID( );
    void                SetIsPassive( bool p_IsServer );
    bool                GetIsPassive( ) ;
    void                SetFloorctrlMode( e_floorctrlMode pfloorctrlMode ) ;
    e_floorctrlMode GetFloorctrlMode(void) ;
    /**
     * stdout menu to manage floor control server and test API 
     * @param lineptr 
     */
    void                menu(char *lineptr) ;

    /**
     *  \brief Add a new user on floor control server 
     * \remarks 
     * you MUST add user before TCP connection , otherwise \ref e_bfcp_primitives hello are not  confirmed .
     * and all request of this user are unrecognized .
     * @param p_userID user ID added on conference
     * @return true success , false failed 
     */
    bool AddUserIDinConf( UINT16 p_userID );
    /**
     * Remove user on FCS
     * \remarks 
     * User are only removed on authorized user list , TCP Connections are not closed .
     * @param p_userID user ID removed on conference
     * @return true success , false failed 
     */
    bool RemoveUserIDinConf( UINT16 p_userID );


    /**
     *  \brief Floor control server callback for BFCP events and respons 
     *
     * @param p_evt \ref BFCP_fsm::e_BFCP_ACT current event of BFCP server 
     * @param p_FsmEvent \ref  BFCP_fsm::st_BFCP_fsm_event informations struct of events 
     * @return  true success , false failed 
     *
     */
    virtual bool OnBfcpServerEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent );

    /**
     * \brief Virtual log and traces callback , for better traces integration on your process 
     * @param pcFile file reference 
     * @param iLine  line refernce 
     * @param iErrorLevel error level \ref INF debug \ref WAR warning \ref ERR error 
     * @param pcFormat char formated traces 
     */
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) ;

     /**
     * \brief Create a new FCS instance and start thread for TCP connection . 
     *
     * If the server aldready connect with the same parameters the connection is not modified 
     * else currrents connections are closed and TCP server is restarted. 
     * 
     * @param local_address local IP V4 address,  you can use NULL to listen all interface  
     * @param local_port  local port, if you use 0 you dont bind . 
     * @param remote_address remote ipv4 adress if your are on active mode ( not recommended for server )
     * @param remote_port remote port if your are on active mode ( not recommended for server )
     * @param isPassive true == serveur waitting connection of remotes , false serveur launch connection with remote
     * @return true , in passive mode , serveur started and waitting connections , in active mode your are connected at remoteg .
     *
     *
     * @see OnBfcpServerEvent
     */
    int StartServer(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive);

    
private:
    BFCP_Server*        m_BFCP_Server ; /* \brief Floor control server */
    e_floorctrlMode     m_e_floorctrlMode ;  /* \brief Floor control server  connection mode */
    UINT32              m_confID ; /* \brief local conferenceID */
    UINT16              m_userID ; /* \brief local user ID */
    UINT16              m_floorID ; /* \brief local floor ID */
    UINT16              m_streamID ; /* \brief local stream ID , \remarks futur use   */
    bool                  m_IsPassive ;/* \brief local connection mode  */
 };

#endif

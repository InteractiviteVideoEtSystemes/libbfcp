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
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_server.cpp
 *
 * \version $Revision: 2652 $
 *
 * \date $Date: 2015-12-03 22:54:12 +0100 (Thu, 03 Dec 2015) $
 *
 * \remarks :
 */
#include <sstream>
#include "stdafx.h"
#include "BFCPexception.h"
#include "bfcp_server.h"
#include "bfcp_link_list.h"
#include "bfcp_strings.h"

/* Macro to check for errors after sending a BFCP message */

#define BFCP_SEND_CHECK_ERRORS()			\
    if(arguments != NULL)					\
    bfcp_free_arguments(arguments); 		\
    if(message != NULL)					    \
    bfcp_free_message(message);

extern "C" void _ServerLog(char* pcFile, int iLine, int iErrorLevel, char* pcFormat, ...)
{
    static BFCP_Server _p ;
    va_list arg;
    char s[BFCP_STRING_SIZE];
    va_start(arg,pcFormat);
    vsnprintf(s,BFCP_STRING_SIZE,pcFormat,arg);
    va_end(arg);
    return  _p.Log(pcFile, iLine, iErrorLevel, s ) ;
}

BFCP_Server::BFCP_Server(UINT8 Max_conf ,UINT32 p_confID ,UINT32 p_userID , UINT32 p_floorID , UINT32 p_streamID , BFCP_Server::ServerEvent* p_ServerEvent ) {
    m_struct_server = NULL ;
    if(!Max_conf)
        Max_conf = BFCP_MAX_CONF;
    if(!p_confID)
        p_confID = BFCP_SERVER_BASE_CONFID ;
    if ( !p_userID )
        p_userID = BFCP_SERVER_BASE_USERID ;
    if ( !p_floorID )
        p_floorID = BFCP_SERVER_BASE_FLOORID ;
    if (!p_streamID )
        p_streamID = BFCP_SERVER_BASE_STREAMID ;

    m_confID        = p_confID;
    m_FirstUserID   = p_userID;
    m_floorID       = p_floorID;
    m_streamID      = p_streamID;
    setName("Server");
    m_trIdGenerator = 100;
    
    Log(INF,"BFCP_Server:: created Server conferenceID[%d] first userID[%d] floorID[%d] stramID[%d]",
        p_confID , p_userID, p_floorID , p_streamID );
    st_bfcp_server* struct_server;
    st_bfcp_conference* lconferences;

    if(!Max_conf) Max_conf = BFCP_MAX_CONF;

    /*  Allocate  Create the new Floor Control Server */
    struct_server = (st_bfcp_server*)calloc(1, sizeof(st_bfcp_server));
    if(struct_server == NULL)
        throw IllegalArgumentException("BFCP_Server:: Allocate and setup invalid");

    /* Initialize and lock the mutex */
    bfcp_mutex_init(count_mutex, NULL);
    // create the FCS
    lconferences = (st_bfcp_conference*)calloc(Max_conf, sizeof(st_bfcp_conference));
    if(lconferences == NULL) {
        bfcp_mutex_lock(count_mutex);
        free(struct_server);
        struct_server = NULL;
        bfcp_mutex_unlock(count_mutex);
        throw IllegalArgumentException("BFCP_Server:: Allocate and setup invalid");
    }

    memset(lconferences,0,Max_conf * sizeof(st_bfcp_conference));
    struct_server->list_conferences = lconferences;
    struct_server->Actual_number_conference = 0;
    struct_server->Max_number_conference = --Max_conf;
    
    m_ServerEvent = p_ServerEvent  ;
    m_struct_server = struct_server ;

    int chair_automatic_accepted_policy = 0;  // Automated policy when chair is missing: 0 = accept the request / 1 = don't
    UINT32 chair_wait_request = 500 ;
    // Insert a new conference
    if (bfcp_initialize_conference_server(m_struct_server, m_confID, Max_conf, Max_conf, chair_automatic_accepted_policy, chair_wait_request) < 0)
        throw IllegalArgumentException("BFCP_Server:: Couldn't add the conference to the FCS...");

    // Add a new floor
    unsigned short chairID = 0 ; // If a chair will manage this floor, enter its UserID (ChairID, 0 if no chair)
    if(bfcp_add_floor_server(m_struct_server, m_confID, m_floorID, chairID, BFCP_MAX_CONF) < 0)
        throw IllegalArgumentException("BFCP_Server:: Couldn't add the floor to the FCS...");

#if 0

    if(bfcp_add_chair_server(m_struct_server, m_confID, m_floorID, chairID)< 0) {
        Log(ERR,_T("BFCP_Server::AddUser : Couldn't setup the new chair."),userID);
        Status = false ;
    }
#endif


    if(bfcp_change_number_bfcp_conferences_server(m_struct_server, Max_conf) < 0)
        throw IllegalArgumentException("BFCP_Server:: Couldn't change the maximum allowed number of concurrent conferences...");

    initStateMachine();
    BFCP_msg_LogCallback(  _ServerLog  );
}


BFCP_Server::~BFCP_Server(void) 
{
    Log(INF,_T("BFCP destroy server."));
    bfcp_mutex_lock(count_mutex);
    removeSession();
    bfcp_destroy_bfcp_server(&m_struct_server);
    bfcp_mutex_destroy(count_mutex);
}

void BFCP_Server::initStateMachine() {
    // By default init for particpant
    st_BFCP_fsm BFCPStateMachine[BFCP_ACT_LAST][BFCP_ACT_LAST] =
        {
            /* from BFCP_ACT_UNDEFINED */
            {
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_UNDEFINED  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_INITIALIZED */
            {
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_CONNECTED    , &BFCP_fsm::BFCPFSM_Connected                  } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_CONNECTED    , &BFCP_fsm::BFCPFSM_Hello              	       } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_CONNECTED    , &BFCP_fsm::BFCPFSM_HelloAck                   } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               }  /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_DISCONNECTED */
            {
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED   , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_DISCONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_CONNECTED */
            {
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorRequest               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorRelease               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_PrimitiveNotSupported      } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_PrimitiveNotSupported      } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_PrimitiveNotSupported      } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_PrimitiveNotSupported      } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_Hello                      } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_PrimitiveNotSupported      } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorStatusAccepted        } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorStatusAborted         } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorStatusGranted         } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_HelloAck                   } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRequest */
            {
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED   , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction                 } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRelease */
            {
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED   , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRequestQuery */
            {
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED        , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRequestQuery  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_UserQuery */
            {
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_UserQuery  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorQuery */
            {
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected                } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               } ,  /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorQuery  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_ChairAction*/
            {
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_ChairAction  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_Hello*/
            {
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected           } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_Hello  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_Error*/
            {
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected           } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_Error  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRequestStatusAccepted*/
            {
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED                 , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRequestStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRequestStatusAborted */
            {
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED                , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRequestStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorRequestStatusGranted */
            {
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED                , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorRequestStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_UserStatus*/
            {
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_UserStatus  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorStatusAccepted */
            {
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED          , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorStatusAccepted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorStatusAborted */
            {
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED         , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorStatusAborted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_FloorStatusGranted */
            {
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED         , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_FloorStatusGranted  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_ChairActionAck*/
            {
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED     , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_ChairActionAck  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_HelloAck*/
            {
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected              } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_HelloAck  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_SHARE*/
            {
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED, &BFCP_fsm::BFCPFSM_Disconnected           } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            },
            /* from BFCP_ACT_SERVER_SHARE*/
            {
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UNDEFINED */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_INITIALIZED */
                {BFCP_ACT_INITIALIZED   , &BFCP_fsm::BFCPFSM_Disconnected               } , /* BFCP_ACT_DISCONNECTED */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_CONNECTED */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequest */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
                {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
            }
        };
    BFCPFSM_init(BFCPStateMachine);
}


/**
 * Parameter checking function
 * @return -1 - invalid parameter or conference server not initialized
 *         -2 - conference does not exist
 *         -3 - if userID specified, user does not exist
 *         -4 - sockfd of received message does not match sock fd of user
 *         > 0 index to use to access conference
 **/
static int CheckConferenceAndUser(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID, BFCP_SOCKET sockfd, BFCP_SOCKET * asockfd = NULL)
{
    int i;
    
    if (server == NULL || server->list_conferences == NULL) return -1;
    if (conferenceID <= 0) return -1;
    
    int actual_conference = server->Actual_number_conference;
    for(i = 0; i < actual_conference; i++) 
    {
        if (server->list_conferences[i].conferenceID == conferenceID)
	{
	    if (userID > 0)
	    {
		users u;
		if (! server->list_conferences[i].user ) return -3;
			
		for (u = server->list_conferences[i].user->users; u != NULL; u = u->next)
		{
		    if ( u->userID == userID)
		    {
			if (sockfd < 0 || u->sockFd < 0)
			{
				/* we do not check sockfd consistency in case of unasigned sockfd
				 * or if we are asked not to check */
				return i;
		        }
		        else
		        {
			    if (sockfd == u->sockFd)
			    {
			        /* sockfd are valid and consistants */
			        return i;
			    }
			    else
			    {
				/* inconsistant socket */
			        if (asockfd) *asockfd = u->sockFd;
			        return -4;
			    }
			}
		    }
		}

		/* If we are here, this means that we are asked to check if user 
		 * exists and user does not exist
		 s*/
		return -3;
	    }
	    else
	    {
		return i;
	    }
	}
    }
    return -2;
}


bool BFCP_Server::OnBFCPConnected(BFCP_SOCKET socket, const char * remoteIp , int remotePort) 
{
    Log(INF,_T("BFCP server connection callback sock [%d] from/to [%s:%d]"), socket, remoteIp, remotePort);
    s_bfcp_msg_event evt ;
    
    memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
    if ( remoteIp ) 
    {
	strncpy(evt.c_param , remoteIp , BFCP_STRING_SIZE );
	evt.c_param[BFCP_STRING_SIZE-1] = 0;
    }

    if ( remotePort > 0 ) evt.i_parm = remotePort ;
    return FsmCtrlPerform( BFCP_fsm::BFCP_ACT_CONNECTED , &evt ) ;
}

bool BFCP_Server::AddUser(UINT16 userID, char *user_URI, char *user_display_name) {
    bool Status = !isUserInConf( userID );
    if ( Status ) {
        if(bfcp_add_user_server(m_struct_server, m_confID, userID, user_URI, user_display_name) < 0) {
            Log(ERR,_T("BFCP_Server::AddUser : Couldn't add the new user %d"),userID);
            Status = false ;
        } else {
            Log(INF,_T("BFCP_Server::AddUser User %d added."),userID);
        }
    } else {
        Log(INF,_T("BFCP_Server::AddUser : User aldready insert %d"),userID);
    }
    return Status ;
}

bool BFCP_Server::isUserInConf(UINT16 userID ) 
{
    bool Status = false ;
    bfcp_user *user = NULL;
    bfcp_list_users *list_user = NULL;
    for(int i = 0; i < m_struct_server->Actual_number_conference && !Status ; i++) {
        // list of users
        list_user = m_struct_server->list_conferences[i].user;
        if(list_user != NULL) {
            user = list_user->users;
            while(user && !Status ) {
                if (user->userID == userID) {
                    Status = true ;
                }
                user = user->next;
            }
        }
    }
    return Status ;
}

bool BFCP_Server::RemoveUserInConf(UINT16 userID )
{
    bool Status = true ;
    int i = CheckConferenceAndUser(m_struct_server, m_confID, userID, -1);
    if (i >= 0)
    {
	/* Notify remote party that the user is gone ! */
	SendGoodBye(userID);
    }
    
    if( bfcp_delete_user_server(m_struct_server, m_confID, userID) < 0) 
    {
        Log(ERR,_T("BFCP_Server::RemoveUserInConf Couldn't remove the user %d"),userID);
        Status = false ;
    } else
        Log(INF,_T("BFCP_Server::RemoveUserInConf user %d removed."),userID);
    return Status ;
}

bool BFCP_Server::OpenUdpConnection(UINT16 p_userID, char * local_address, int local_port)
{
    if ( isUserInConf(p_userID) )
    {
	int tr = 0;
	BFCP_SOCKET fd = bfcp_get_user_sockfd(m_struct_server, m_confID , p_userID, &tr);
	if ( fd != INVALID_SOCKET)
	{
	    if ( tr == BFCP_OVER_UDP)
	    {
		/* client already open */
		Log(INF, "BFCP_Server::OpenUdpConnection: user %u was alreay associated with UDP connection [%d]", p_userID,
		    fd);
		return true;
	    }
	    else
	    {
		Log(ERR, "BFCP_Server::OpenUdpConnection: user %u was alreay associated with a TCP connection. Killing it", p_userID);
		RemoveClient(fd);
	    }
	}
	
	fd = AddClient(BFCP_OVER_UDP, BFCPConnectionRole::PASSIVE, local_address, local_port );
	
	if ( fd != INVALID_SOCKET )
	{
	    int ret = bfcp_set_user_sockfd(m_struct_server, m_confID , p_userID, fd, BFCP_OVER_UDP);
	    if (ret)
	    {
		Log(ERR, "BFCP_Server::OpenUdpConnection fail to assing FD to user %d in conference ID %d", p_userID, m_confID);
	    }
	    return (ret == 0);
	}
    }
    else
    {
	 Log(ERR,_T("BFCP_Server::OpenUdpConnection user %d is not in conference ID %d"), p_userID, m_confID);
    }
    return false;
}

bool BFCP_Server::GetConnectionInfo(UINT16 p_userID, char * local_address, int * local_port, int * transport)
{
    if ( isUserInConf(p_userID) )
    {
	int tr = 0;
	
	BFCP_SOCKET fd = bfcp_get_user_sockfd(m_struct_server, m_confID , p_userID, &tr);
	
	if ( GetConnectionLocalInfo(fd, local_address, local_port ) )
	{
	    if (transport) *transport = tr;
	    return true;
	}
    }
    else
    {
	 Log(ERR,_T("BFCP_Server::OpenUdpConnection user %d is not in conference ID %d"), p_userID, m_confID);
    }
    return false;
}

bool BFCP_Server::OnBFCPDisconnected(BFCP_SOCKET socket) 
{
    s_bfcp_msg_event evt ;
    memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
    if ( socket == getServerSocket() )
    {
	return FsmCtrlPerform( BFCP_fsm::BFCP_ACT_DISCONNECTED , &evt ) ;
    }
    else
    {
	/* Lookup conference for all user with the same sockfd */
	int i = CheckConferenceAndUser( m_struct_server, m_confID, 0, -1);
	if (i >= 0)
	{
	    UINT16 UserID = find_user_by_sockfd(m_struct_server->list_conferences[i].user, socket);
	    if (UserID > 0)
	    {
		/* Reset the sock fd associated with this user */
		bfcp_set_user_sockfd(m_struct_server, m_confID, UserID, INVALID_SOCKET, BFCP_OVER_TCP);
	    }
	}
    }
    return false ;
}

bool BFCP_Server::CloseTcpConnection() {
    removeSession();
    return true;
}

/* Create a new Participant */
bool BFCP_Server::OpenTcpConnection(const char* local_address,
                                    int local_port,
                                    const char* remote_address,
                                    int remote_port,
                                    bool isServer) {
    bool Status = false ;
    //m_base_transactionID = 1 ;
    if ( !m_struct_server ) {
        Log(ERR,"BFCP_Server:: invalid participant ! ");
        //throw IOException("BFCP_Participant:: Connection connect failed");
    }

    try {
        SelLocalConnection(local_address,local_port,isServer?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE);
        if ( !isServer ) {
            if (remote_address!=NULL && remote_port!=0) {
                if ( setRemoteEndpoint(remote_address,remote_port) ) 
		{
                    if ( connect() )
		    {
                        Log(INF,"BFCP_Server:: connection lauched ");
                        Status = true ;
                    }
		    else
		    {
                        removeSession();
                        Log(ERR,"BFCP_Server:: Connection connect failed ");
                        //throw IOException("BFCP_Participant:: Connection connect failed");
                    }
                } else {
                    Log(ERR,"BFCP_Server setRemoteEndpoint failed ");
                    //throw IOException("BFCP_Participant:: setRemoteEndpoint failed");
                }
            } else {
                Log(ERR,"BFCP_Server invalid address ");
                //throw IOException("BFCP_Participant:: invalid address ");
            }
        } else {
            if ( connect() ) {
                Log(INF,"BFCP_Server connection manager started with success ");
                Status = true ;
            } else {
                removeSession();
                Log(ERR,"BFCP_Server connection manager start failed ");
                //throw IOException("BFCP_Participant:: connect failed ");
            }
        }
    } catch(...) {
        Log(ERR,_T("BFCP_Server error"));
        //throw IllegalArgumentException("BFCP_Participant:: failed ");
    }
    return Status ;
}

/* Destroy a currently running Floor Control Server */
int BFCP_Server::bfcp_destroy_bfcp_server(st_bfcp_server **serverp) {
    if(serverp == NULL)
        return -1;

    int error = 0, i, max_conference;

    st_bfcp_server *server = *serverp;
    max_conference = server->Actual_number_conference -1;

    for(i = 0; i <= max_conference; i++) {
        /* Free all the handled information (floors, users, etc) */
        error = bfcp_remove_request_list(&(server->list_conferences[i].pending));
        if(error == -1) {
            return -1;
        }
        error = bfcp_remove_request_list(&(server->list_conferences[i].accepted));
        if(error == -1) {
            return -1;
        }
        error = bfcp_remove_request_list(&(server->list_conferences[i].granted));
        if(error == -1) {
            return -1;
        }
        error = bfcp_remove_floor_list(&(server->list_conferences[i].floor));
        if(error == -1) {
            return -1;
        }
        error = bfcp_remove_user_list(&(server->list_conferences[i].user));
        if(error == -1) {
            return -1;
        }

        server->list_conferences[i].conferenceID = 0;
        server->list_conferences[i].chair_wait_request = 0;
        server->list_conferences[i].automatic_accepted_deny_policy = 0;
    }

    /* Free the list of active conferences */
    free(server->list_conferences);
    server->list_conferences = NULL;


    /* Free the FCS stuff */
    if(error == 0) {
        free(server);
        server = NULL;
        *serverp = NULL;
    } else {
        return -1;
    }
    return 0;
}

/* Create a new BFCP Conference and add it to the FCS */
int BFCP_Server::bfcp_initialize_conference_server(st_bfcp_server *conference_server, UINT32 conferenceID, UINT16 Max_Num_floors, UINT16 Max_Number_Floor_Request, int automatic_accepted_deny_policy, UINT32 chair_wait_request) 
{
    if(conference_server == NULL)
        return -1;
     if(conference_server->list_conferences == NULL)
        return -1;
    if(conferenceID == 0)
        return -1;

    int i = 0;

    if(Max_Number_Floor_Request <= 0)
        Max_Number_Floor_Request = 1;
    if(Max_Num_floors <= 0)
        Max_Num_floors = 1;
    if((automatic_accepted_deny_policy != 0) && (automatic_accepted_deny_policy != 1))
        automatic_accepted_deny_policy = 0;
    if(chair_wait_request <= 0)
        chair_wait_request = 300; /* By default the FCS will wait 5 minutes for ChairActions */

    /* Initialization the conference */
    i = conference_server->Actual_number_conference;
    if(i > conference_server->Max_number_conference)
        /* The maximum allowed number of active conferences has already been reached */
        return -1;

    bfcp_mutex_lock(count_mutex);

    if (CheckConferenceAndUser(conference_server, conferenceID, 0, -1) >= 0)
    {
	/* A conference with this conferenceID already exists */
        Log(ERR, "Could not create conference: conference ID %u is aready used.");
	bfcp_mutex_unlock(count_mutex);
	return -1;
    }

    /* Create a list for Pending request */
    conference_server->list_conferences[i].pending = bfcp_create_list();
    if(!conference_server->list_conferences[i].pending) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    /* Create a list for Accepted request */
    conference_server->list_conferences[i].accepted = bfcp_create_list();
    if(!conference_server->list_conferences[i].accepted) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    /* Create a list for Granted request */
    conference_server->list_conferences[i].granted = bfcp_create_list();
    if(!conference_server->list_conferences[i].granted) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    conference_server->list_conferences[i].conferenceID = conferenceID;

    /* Create a list for users */
    conference_server->list_conferences[i].user = bfcp_create_user_list(Max_Number_Floor_Request, Max_Num_floors);
    if(!conference_server->list_conferences[i].user) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Create a list for floors */
    conference_server->list_conferences[i].floor = bfcp_create_floor_list(Max_Num_floors);
    if(!conference_server->list_conferences[i].floor) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    conference_server->list_conferences[i].chair_wait_request = chair_wait_request;
    conference_server->list_conferences[i].automatic_accepted_deny_policy = automatic_accepted_deny_policy;
    conference_server->list_conferences[i].floorRequestID = 1;

    /* Both the conference and its list of users inheritate the transport property from the FCS */
    /* Obsolete - transport is handled event by event and associated with sock FD */
    conference_server->list_conferences[i].bfcp_transport = BFCP_OVER_TCP;
    
    /* Obsolete - transport will be associated to the USER, not to the USER LIST */
    //conference_server->list_conferences[i].user->bfcp_transport = BFCP_OVER_TCP;

    conference_server->Actual_number_conference = ++i;

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Destroy a currently managed BFCP Conference and remove it from the FCS */
int BFCP_Server::bfcp_destroy_conference_server(st_bfcp_server *conference_server, UINT32 conferenceID) {
    if(conferenceID <= 0)
        return -1;
    if(conference_server == NULL)
        return -1;

    int error = 0, i, actual_conference;
    st_bfcp_conference* remove_conference ;
    st_bfcp_conference* last_conference;

    bfcp_mutex_lock(count_mutex);

    i = CheckConferenceAndUser(conference_server, conferenceID, 0, -1);
    if (i < 0)
    {
        /* A conference with this conferenceID does NOT exist */
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }    

    actual_conference = conference_server->Actual_number_conference - 1; 
        remove_conference = &conference_server->list_conferences[i];
        last_conference = &conference_server->list_conferences[actual_conference];

        /* We free the list of Pending requests */
        error = bfcp_clean_request_list(remove_conference->pending);
        if(error == 0) {
            free(remove_conference->pending);
            remove_conference->pending = NULL;
        } else {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* We free the list of Accepted requests */
        error = bfcp_clean_request_list(remove_conference->accepted);
        if(error == 0) {
            free(remove_conference->accepted);
            remove_conference->accepted = NULL;
        } else {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* We free the list of Granted requests */
        error = bfcp_clean_request_list(remove_conference->granted);
        if(error == 0) {
            free(remove_conference->granted);
            remove_conference->granted = NULL;
        } else {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* We free the list of floors */
        error = bfcp_remove_floor_list(&(remove_conference->floor));
        if(error == 0) {
            free(remove_conference->floor);
            remove_conference->floor = NULL;
        }
        /* We free the list of users */
        error = bfcp_remove_user_list(&(remove_conference->user));
        if(error == 0) {
            free(remove_conference->user);
            remove_conference->user = NULL;
        }

        remove_conference->conferenceID = 0;
        remove_conference->chair_wait_request = 0;
        remove_conference->automatic_accepted_deny_policy = 0;

        if(i != actual_conference) {
            /* Swap the last element in queue and the one to delete (reorder) */
            remove_conference->pending = last_conference->pending;
            remove_conference->accepted = last_conference->accepted;
            remove_conference->granted = last_conference->granted;
            remove_conference->conferenceID = last_conference->conferenceID;
            remove_conference->user = last_conference->user;
            remove_conference->floor = last_conference->floor;
            remove_conference->chair_wait_request = last_conference->chair_wait_request;
            remove_conference->automatic_accepted_deny_policy = last_conference->automatic_accepted_deny_policy;

            /* Remove the last element of the queue, which now is the one to delete */
            last_conference->pending = NULL;
            last_conference->accepted = NULL;
            last_conference->granted = NULL;
            last_conference->user = NULL;
            last_conference->floor = NULL;
            last_conference->conferenceID = 0;
            last_conference->chair_wait_request = 0;
            last_conference->automatic_accepted_deny_policy = 0;
        }

    conference_server->Actual_number_conference = actual_conference;

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Change the maximum number of allowed conferences in the FCS */
int BFCP_Server::bfcp_change_number_bfcp_conferences_server(st_bfcp_server *server, UINT16 Num) {
    if(server == NULL)
        return -1;
    if(Num == 0)
        Num = 1;

    st_bfcp_conference* lconference;
    int i = 0;

    if((server->Actual_number_conference) > Num) {
        for(i = Num; i < server->Actual_number_conference; i++)
            bfcp_destroy_conference_server(server, server->list_conferences[i].conferenceID);
    }

    lconference = (st_bfcp_conference*)realloc(server->list_conferences, Num*sizeof(st_bfcp_conference));
    if(lconference == NULL)
        return -1;

    server->list_conferences = lconference;

    if((server->Actual_number_conference) > Num)
        server->Actual_number_conference = Num;

    server->Max_number_conference = --Num;

    return 0;
}

/* Change the maximum number of users that can be granted this floor at the same time */
int BFCP_Server::bfcp_change_number_granted_floor_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 floorID, UINT16 limit_granted_floor)
{
    if(floorID <= 0)
        return -1;
    if(limit_granted_floor <= 0)
        return 0;

    int i, value = 0;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, -1);
    if (i >= 0)
    {
        value = bfcp_change_number_granted_floor(server->list_conferences[i].floor, floorID, limit_granted_floor);
        if(value == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Change the allowed number of per-floor requests for this list */
int BFCP_Server::bfcp_change_user_req_floors_server(st_bfcp_server *server, UINT16 Max_Number_Floor_Request) {
    if(server == NULL)
        return -1;
    if(Max_Number_Floor_Request == 0)
        Max_Number_Floor_Request = 1;

    int i = 0, value = 0;

    bfcp_mutex_lock(count_mutex);

    for(i = 0; i <= server->Actual_number_conference; i++) {
        value = bfcp_change_user_req_floors(server->list_conferences[i].user, Max_Number_Floor_Request);
        if(value == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Change the automated policy for requests related to floors that have no chair */
int BFCP_Server::bfcp_change_chair_policy(st_bfcp_server *conference_server, UINT32 conferenceID, int automatic_accepted_deny_policy, UINT32 chair_wait_request)
{
    int i = -1;
 
    if((automatic_accepted_deny_policy < 0) || (automatic_accepted_deny_policy > 1))
        automatic_accepted_deny_policy = 0;

    bfcp_mutex_lock(count_mutex);

    i = CheckConferenceAndUser(conference_server, conferenceID, 0, -1);
    if ( i >= 0 ) 
    {
        if(chair_wait_request != 0)
            conference_server->list_conferences[i].chair_wait_request = chair_wait_request;
        conference_server->list_conferences[i].automatic_accepted_deny_policy = automatic_accepted_deny_policy;
    } else {
        /* A conference with this conferenceID does NOT exist */
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Add a floor to an existing conference */
int BFCP_Server::bfcp_add_floor_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 floorID, UINT16 ChairID, int limit_granted_floor)
{
    int error, i = -1;
    
    if (limit_granted_floor < 0) return -1;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, -1);
    if ( i >=0 )
    {
        /* Check if the chair of the floor is a valid user */
        if((bfcp_existence_user(server->list_conferences[i].user, ChairID) == 0) || (ChairID == 0))
	{
            error = bfcp_insert_floor(server->list_conferences[i].floor, floorID, ChairID);
            if(error == -1) {
		Log(ERR, "bfcp_add_floor_server: could not insert floor ID %d", floorID );
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
            error = bfcp_change_number_granted_floor(server->list_conferences[i].floor, floorID, limit_granted_floor);
            if(error == -1) {
		Log(ERR, "bfcp_add_floor_server: could not set floor limit to %d", limit_granted_floor );
                bfcp_mutex_unlock(count_mutex);
                return -2;
            }
        }
	else
	{
	    Log(ERR, "bfcp_add_floor_server: could not insert floor ID %d becaose chair ID %u is not a valid participant", 
		floorID, ChairID );
	}
    }
    else {
        /* A conference with this conferenceID does NOT exist */
	Log(ERR, "bfcp_add_floor_server: conference ID %u does not exist. ret=%d", conferenceID, i );
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Remove a floor from an existing conference */
int BFCP_Server::bfcp_delete_floor_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 floorID)
{
    int value=0, error, i;
    bfcp_queue *laccepted;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, -1);
    if ( i >=0 )
    {
        /* Find the position of this floor in the floor list */
        value = bfcp_return_position_floor(server->list_conferences[i].floor, floorID);

        /* Remove the floor from the FloorRequests sublist of the user list */
        error = bfcp_delete_a_floor_from_user_list(server->list_conferences[i].user, value);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the floor from the Pending list */
        error = bfcp_delete_node_with_floorID(server->list_conferences[i].conferenceID, server->list_conferences[i].accepted, server->list_conferences[i].pending, floorID, server->list_conferences[i].floor, 1);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* Remove the floor from the Accepted list */
        error = bfcp_delete_node_with_floorID(server->list_conferences[i].conferenceID, server->list_conferences[i].accepted, server->list_conferences[i].accepted, floorID, server->list_conferences[i].floor,0);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* Remove the floor from the Granted list */
        error = bfcp_delete_node_with_floorID(server->list_conferences[i].conferenceID, server->list_conferences[i].accepted, server->list_conferences[i].granted, floorID, server->list_conferences[i].floor,0);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Check if other requests that need this floor are in the Accepted list */
        laccepted = server->list_conferences[i].accepted;
        if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, laccepted, server->list_conferences[i].floor, NULL)== -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the floor from the floor list */
        error = bfcp_delete_floor(server->list_conferences[i].floor, floorID);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    } else {
        /* A conference with this conferenceID does NOT exist */
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Set a participant as chair of a floor */
int BFCP_Server::bfcp_add_chair_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 floorID, UINT16 ChairID)
{
    int error = 0, i = -1;

    bfcp_mutex_lock(count_mutex);

    i = CheckConferenceAndUser(server, conferenceID, ChairID, -1);
    if ( i >=0 )
    {
            error = bfcp_change_chair(server->list_conferences[i].floor, floorID, ChairID);
            if(error == -1) 
	    {
                Log(ERR, "bfcp_add_chair_server: floor ID %u does NOT exist in conferenceID %u ", floorID, conferenceID);
            }
    } 
    else 
    {
	error = i;
	switch(i)
	{
	    case -2:
	        Log(ERR, "bfcp_add_chair_server: conferenceID %u does NOT exist", conferenceID);
		break;

	    case -3:
	        Log(ERR, "bfcp_add_chair_server: user ID %u does NOT exist in conferenceID %u ",ChairID,  conferenceID);
		break;
	    
	    default:
	    case -1:
	       Log(ERR, "bfcp_add_chair_server: confID: %u, floorID: %u, userID: %u - internal error (NULL pointer)");
	       break;
	}
    }

    bfcp_mutex_unlock(count_mutex);
    return error;
}

/* Set no participant as chair for a floor */
int BFCP_Server::bfcp_delete_chair_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 floorID)
{

    int error, i, position_floor = 0;
    bfcp_floor *floor;
    floor_request_query *newrequest;
    pnode traverse;

    i = CheckConferenceAndUser(server, conferenceID, 0, false);
    if (i < 0)
        /* A conference with this conferenceID does NOT exist */
        return -1;

    if (server->list_conferences[i].floor != NULL) 
    {
        position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, floorID);
        if(position_floor == -1)
            return -1;
    } else
        return -1;

    bfcp_mutex_lock(count_mutex);
    /* Check if the chair of the floor is a valid user */
    if(server->list_conferences[i].floor->floors[position_floor].chairID != 0) {
        if(bfcp_existence_user(server->list_conferences[i].user, server->list_conferences[i].floor->floors[position_floor].chairID) == 0) {
            /* Check if the automated response policy is to deny requests */
            if(server->list_conferences[i].automatic_accepted_deny_policy == 1) {
                /* Notify all interested users before cancelling the requests */
                if((server->list_conferences[i].pending!=NULL) && (server->list_conferences[i].pending->head!=NULL)) {
                    traverse = server->list_conferences[i].pending->head;
                    while(traverse != NULL) {
                        floor = traverse->floor;
                        while(floor != NULL) {
                            if(floor->floorID == floorID) {
                                newrequest = traverse->floorrequest;
                                while(newrequest != NULL) {
                                    error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, conferenceID, newrequest->userID,
									       0, traverse, BFCP_CANCELLED, newrequest->fd, newrequest->transport);
                                    if(error == -1) {
                                        bfcp_mutex_unlock(count_mutex);
                                        return -1;
                                    }
                                    newrequest = newrequest->next;
                                }
                            }
                            floor = floor->next;
                        }
                        traverse = traverse->next;
                    }
                }
                /* Remove the floor from the Pending list */
                error = bfcp_delete_node_with_floorID(server->list_conferences[i].conferenceID, server->list_conferences[i].accepted, server->list_conferences[i].pending, floorID, server->list_conferences[i].floor,0);
                if(error == -1) {
                    bfcp_mutex_unlock(count_mutex);
                    return -1;
                }
            }
            if(server->list_conferences[i].automatic_accepted_deny_policy == 0) {
                error = bfcp_accepted_pending_node_with_floorID(server->list_conferences[i].conferenceID, server->list_conferences[i].accepted, server->list_conferences[i].pending, floorID, server->list_conferences[i].floor, 0);
                if(error == -1) {
                    bfcp_mutex_unlock(count_mutex);
                    return -1;
                }

                /* Notify all interested users before accepting the requests */
                if((server->list_conferences[i].accepted != NULL) && (server->list_conferences[i].accepted->head != NULL)) {
                    traverse = server->list_conferences[i].accepted->head;
                    while(traverse != NULL) {
                        floor = traverse->floor;
                        while(floor != NULL) {
                            if(floor->floorID == floorID) {
                                newrequest = traverse->floorrequest;

                                while(newrequest != NULL)
				{
                                    error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, 
									      conferenceID, newrequest->userID, 0, 
									      traverse, BFCP_ACCEPTED, newrequest->fd, newrequest->transport);
                                    if (error == -1) {
                                        bfcp_mutex_unlock(count_mutex);
                                        return -1;
                                    }
                                    newrequest = newrequest->next;
                                }
                            }
                            floor = floor->next;
                        }
                        traverse = traverse->next;
                    }
                }
                /* Check if the node should be in the Granted queue */
                if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, server->list_conferences[i].accepted, server->list_conferences[i].floor, NULL) == -1) {
                    bfcp_mutex_unlock(count_mutex);
                    return -1;
                } else {
                    /*send floor information after accepted all the floors*/
                    if((server->list_conferences[i].granted != NULL) && (server->list_conferences[i].granted->head != NULL)) {
                        traverse = server->list_conferences[i].granted->head;
                        while(traverse != NULL) {
                            floor = traverse->floor;
                            while(floor != NULL) {
                                if(floor->floorID == floorID) {
                                    newrequest = traverse->floorrequest;
                                    while(newrequest != NULL) {
                                        error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, conferenceID, newrequest->userID, 0, traverse, BFCP_GRANTED, newrequest->fd, newrequest->transport);
                                        if(error == -1) {
                                            bfcp_mutex_unlock(count_mutex);
                                            return -1;
                                        }
                                        newrequest = newrequest->next;
                                    }
                                }
                                floor = floor->next;
                            }
                            traverse = traverse->next;
                        }
                    }
                }
            }
            /* Remove the ChairID from the floor list */
            error = bfcp_change_chair(server->list_conferences[i].floor, floorID, 0);
            if(error == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }
    }
    bfcp_mutex_unlock(count_mutex);
    return 0;
}

/* Add a participant to the list of users of a BFCP Conference */
int BFCP_Server::bfcp_add_user_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID, char *user_URI, char *user_display_name)
{

    int error, i;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, false);
    if (i >= 0)
    {
        /* Add a new user to the conference */
        error = bfcp_add_user(server->list_conferences[i].user, userID, user_URI, user_display_name);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    } else {
        /* A conference with this conferenceID does NOT exist */
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

int BFCP_Server::bfcp_set_user_sockfd(st_bfcp_server *server, UINT32 conferenceID,UINT16 userID,BFCP_SOCKET p_sockfd, int p_transport ) 
{
    int error, i;
    Log(INF,"bfcp_set_user_sockfd server[0x%p] sockfd[0x%p] confD[%d] User[%d] ",
        server, p_sockfd , conferenceID , userID ) ;
	
    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, false);
    if (i <= 0) {
        /* Add a new user to the conference */
        error = bfcp_set_user_socket(server->list_conferences[i].user,  userID, p_sockfd, p_transport);
        if(error == -1)
	{
            Log(ERR,"bfcp_set_userSockFd server user list[0x%p] sockfd[0x%p] confD[%d] User[%d] failed",
                server->list_conferences[i].user, p_sockfd , conferenceID , userID ) ;
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    } else {
        /* A conference with this conferenceID does NOT exist */
        Log(ERR,"bfcp_set_user_sockfd A conference with this conferenceID [%d] does NOT exist", conferenceID ) ;
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);
    return 0;
}

BFCP_SOCKET BFCP_Server::bfcp_get_user_sockfd(st_bfcp_server *server, UINT32 conferenceID,UINT16 userID, int * p_transport)
{
    int  i;
    BFCP_SOCKET sockfd = INVALID_SOCKET ;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, 0, -1);
    if ( i >=0 ) 
    {
        /* Add a new user to the conference */
        sockfd = bfcp_get_user_socket(server->list_conferences[i].user, userID, p_transport);
    }
    bfcp_mutex_unlock(count_mutex);
    return sockfd;
}

/* Remove a participant from the list of users of a BFCP Conference */
int BFCP_Server::bfcp_delete_user_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID)
{
    if(userID <= 0) return -1;

    int error, i, y;
    bfcp_queue *laccepted;
    bfcp_list_floors *lfloors;
    pnode traverse;

    bfcp_mutex_lock(count_mutex);

    i = CheckConferenceAndUser(server, conferenceID, userID, -1);
    if ( i >=0 ) 
    {
        /* Remove the user from the FloorRequest list of every node */
        error = bfcp_remove_floorrequest_from_all_nodes(server->list_conferences+i, userID);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* Remove the user from the FloorQuery list */
        error = bfcp_remove_floorquery_from_all_nodes(server->list_conferences[i].floor, userID);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* Checks if the user is chair of any floors */
        if(bfcp_exist_user_as_a_chair(server->list_conferences[i].floor, userID) == 0) {
            /* This user is chair of at least one floor */
            lfloors = server->list_conferences[i].floor;
            for(y = 0; y < lfloors->actual_number_floors; y++) {
                if(lfloors->floors[y].chairID == userID) {
                    error = bfcp_delete_chair_server(server, conferenceID, lfloors->floors[y].floorID);
                    if(error == -1) {
                        bfcp_mutex_unlock(count_mutex);
                        return -1;
                    }
                }
            }
        }

        /* Notify all interested users before cancelling the Pending requests */
        if((server->list_conferences[i].pending != NULL) && (server->list_conferences[i].pending->head != NULL)) {
            traverse = server->list_conferences[i].pending->head;
            while(traverse != NULL) {
                if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                    error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, traverse, BFCP_CANCELLED);
                    if(error == -1) {
                        bfcp_mutex_unlock(count_mutex);
                        return -1;
                    }
                }
                traverse = traverse->next;
            }
        }

        /* Notify all interested users before cancelling the Accepted requests */
        if((server->list_conferences[i].accepted != NULL) && (server->list_conferences[i].accepted->head != NULL)) {
            traverse = server->list_conferences[i].accepted->head;
            while(traverse != NULL) {
                if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                    error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, traverse, BFCP_CANCELLED);
                    if(error == -1) {
                        bfcp_mutex_unlock(count_mutex);
                        return -1;
                    }
                }
                traverse = traverse->next;
            }
        }

        /* Notify all interested users before cancelling the Granted requests */
        if((server->list_conferences[i].granted != NULL) && (server->list_conferences[i].granted->head != NULL)) {
            traverse = server->list_conferences[i].granted->head;
            while(traverse != NULL) {
                if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                    error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, traverse, BFCP_CANCELLED);
                    if(error == -1) {
                        bfcp_mutex_unlock(count_mutex);
                        return -1;
                    }
                }
                traverse = traverse->next;
            }
        }

        /* Remove the user from the Pending requests list */
        error = bfcp_delete_node_with_userID(server->list_conferences[i].pending, userID, server->list_conferences[i].floor);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the user from the Accepted requests list */
        error = bfcp_delete_node_with_userID(server->list_conferences[i].accepted, userID, server->list_conferences[i].floor);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the user from the Granted requests list */
        error = bfcp_delete_node_with_userID(server->list_conferences[i].granted, userID, server->list_conferences[i].floor);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Finally remove the user from the conference */
        error = bfcp_delete_user(server->list_conferences[i].user, userID);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Check if other requests that need the floors freed by the leaving user are in the Accepted list */
        laccepted = server->list_conferences[i].accepted;
        if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, laccepted, server->list_conferences[i].floor, NULL) == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }
    else {
        /* A conference with this conferenceID does NOT exist */
        bfcp_mutex_unlock(count_mutex);
	Log(ERR, "bfcp_delete_user_server: no such user %u or conference %u. err=%d", userID, conferenceID, i);
        return -1; 
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Create a new 'bfcp_floor_request_information' (bfcp_messages.h) out of a 'pnode' */
bfcp_floor_request_information *BFCP_Server::create_floor_request_userID(pnode traverse,lusers users, UINT16 userID, UINT16 request_status, int i) {
    if(traverse == NULL)
        return NULL;
    if(users == NULL)
        return NULL;

    bfcp_user_information *user_info;
    bfcp_user_information *beneficiary_info;
    bfcp_floor *node;
    bfcp_floor_request_information *frqInfo = NULL;
    bfcp_overall_request_status *oRS = NULL;
    bfcp_floor_request_status *fRS_temp = NULL, *fRS = NULL;

    /* If there's a beneficiary, add its information */
    if(traverse->beneficiaryID != 0) {
        beneficiary_info = bfcp_show_user_information(users, traverse->beneficiaryID);
        if(beneficiary_info == NULL) {
            bfcp_free_user_information(beneficiary_info);
            return NULL;
        }
    } else
        beneficiary_info = NULL;
    /* If there's user information, add it */
    if(traverse->userID != 0) {
        user_info = bfcp_show_user_information(users, traverse->userID);
        if(user_info == NULL) {
            bfcp_free_user_information(user_info);
            return NULL;
        }
    } else
        user_info = NULL;

    node = traverse->floor;
    if(node != NULL) {
        fRS = bfcp_new_floor_request_status(node->floorID, request_status, i, node->chair_info);
        if(fRS == NULL)
            return NULL;
        node = node->next;
        while(node != NULL) {
            fRS_temp = bfcp_new_floor_request_status(node->floorID, request_status, i, node->chair_info);
            if(fRS_temp != NULL)
                bfcp_list_floor_request_status(fRS, fRS_temp, NULL);
            node=node->next;
        }
    } else
        return NULL;

    oRS = bfcp_new_overall_request_status(traverse->floorRequestID, request_status, i , traverse->chair_info);

    frqInfo = bfcp_new_floor_request_information(traverse->floorRequestID, oRS, fRS, beneficiary_info, user_info, traverse->priority ,traverse->participant_info);

    return frqInfo;
}

/* Create a new 'bfcp_floor_request_information' (bfcp_messages.h) out of a floor */
bfcp_floor_request_information *BFCP_Server::create_floor_message(UINT16 floorID, pnode traverse, lusers users, UINT16 request_status, int i) {
    if(traverse == NULL)
        return NULL;
    if(users == NULL)
        return NULL;

    bfcp_user_information *user_info;
    bfcp_user_information *beneficiary_info;
    bfcp_floor_request_information *frqInfo = NULL;
    bfcp_floor_request_status *fRS = NULL;
    bfcp_overall_request_status *oRS = NULL;

    /* If there's a beneficiary, add its information */
    if(traverse->beneficiaryID != 0) {
        beneficiary_info = bfcp_show_user_information(users, traverse->beneficiaryID);
        if(beneficiary_info == NULL) {
            bfcp_free_user_information(beneficiary_info);
            return NULL;
        }
    } else
        beneficiary_info = NULL;

    /* If there's user information, add its information */
    if(traverse->userID != 0) {
        user_info = bfcp_show_user_information(users, traverse->userID);
        if(user_info == NULL) {
            bfcp_free_user_information(user_info);
            return NULL;
        }
    } else
        user_info = NULL;

    /* Setup the Floor Request Information by preparing its sub-attributes */
    fRS = bfcp_new_floor_request_status(floorID, request_status, i, NULL);
    oRS = bfcp_new_overall_request_status(traverse->floorRequestID, request_status, i , traverse->chair_info);
    frqInfo = bfcp_new_floor_request_information(traverse->floorRequestID, oRS, fRS, beneficiary_info, user_info, traverse->priority ,traverse->participant_info);

    return frqInfo;
}

/* Setup and send a floorstatus BFCP message */
int BFCP_Server::bfcp_show_floor_information(UINT32 conferenceID, UINT16 TransactionID, UINT16 userID, st_bfcp_conference *conference, UINT16 floorID, int *client, pnode newnode, UINT16 status) 
{
    if(conference == NULL)
        return 0;

    int error, i, transport;
    pnode traverse;
    pfloor floor;
    bfcp_message *message = NULL;
    bfcp_arguments *arguments = NULL;
    bfcp_floor_request_information *frqInfo = NULL, *list_frqInfo = NULL;
    bfcp_floor_id_list *fID;
    BFCP_SOCKET sockfd;
    
    sockfd = bfcp_get_user_socket(conference->user, userID, &transport);
    if (sockfd == INVALID_SOCKET) return -1;
    
    if (TransactionID == 0 && transport == BFCP_OVER_UDP)
    {
	TransactionID = ++m_trIdGenerator;
    }
    
    arguments = bfcp_new_arguments();
    if(!arguments)
        return -1;

    arguments->entity = bfcp_new_entity(conferenceID, TransactionID, userID);
    arguments->primitive = e_primitive_FloorStatus;
    if(floorID != 0)
        fID = bfcp_new_floor_id_list(floorID, 0);
    else
        fID = NULL;

    arguments->fID = fID;

    if((status > BFCP_GRANTED) && (newnode != NULL)) {
        frqInfo = create_floor_message(floorID, newnode, conference->user, status, 0);
        if((frqInfo != NULL) && (list_frqInfo != NULL))
            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
        else if(list_frqInfo == NULL)
            list_frqInfo = frqInfo;
    }

    if(conference->granted != NULL) {
        /* This is the Granted queue */
        traverse = conference->granted->tail;
        while(traverse) {
            if((newnode == NULL) || (status <= BFCP_GRANTED) || ((newnode != NULL) && (newnode->floorRequestID != traverse->floorRequestID))) {
                floor = traverse->floor;
                while(floor) {
                    if(floor->floorID == floorID) {
                        frqInfo = create_floor_message(floorID, traverse, conference->user, 3, 0);
                        if((frqInfo != NULL) && (list_frqInfo != NULL))
                            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                        else if(list_frqInfo == NULL)
                            list_frqInfo = frqInfo;
                    }
                    floor = floor->next;
                }
            }
            traverse = traverse->prev;
        }
    }

    if(conference->accepted != NULL) {
        /* This is the Accepted queue */
        traverse = conference->accepted->tail;
        i = 1;
        while(traverse) {
            if((newnode == NULL) || (status <= BFCP_GRANTED) || ((newnode != NULL) && (newnode->floorRequestID != traverse->floorRequestID))) {
                floor = traverse->floor;
                while(floor) {
                    if(floor->floorID == floorID) {
                        frqInfo = create_floor_message(floorID, traverse, conference->user, 2, i);
                        if((frqInfo != NULL) && (list_frqInfo != NULL))
                            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                        else if(list_frqInfo == NULL)
                            list_frqInfo = frqInfo;
                    }
                    floor = floor->next;
                }
            }
            i = i + 1;
            traverse = traverse->prev;
        }
    }

    if(conference->pending != NULL) {
        /* This is the Accepted queue */
        traverse = conference->pending->tail;
        while(traverse) {
            if((newnode == NULL) || (status <= BFCP_GRANTED) || ((newnode != NULL) && (newnode->floorRequestID != traverse->floorRequestID))) {
                floor = traverse->floor;
                while(floor) {
                    if(floor->floorID == floorID) {
                        frqInfo = create_floor_message(floorID, traverse, conference->user, 1, 0);
                        if((frqInfo != NULL) && (list_frqInfo != NULL))
                            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                        else if(list_frqInfo == NULL)
                            list_frqInfo = frqInfo;
                    }
                    floor = floor->next;
                }
            }
            traverse = traverse->prev;
        }
    }
    bool freeNode = false ;
    pnode tmpnode = NULL ;
    if ( !list_frqInfo ) {
        tmpnode = bfcp_init_request(userID, 0 , BFCP_NORMAL_PRIORITY , NULL , floorID );
        frqInfo = create_floor_message(floorID, tmpnode, conference->user, BFCP_RELEASED  , 0);
        if((frqInfo != NULL) && (list_frqInfo != NULL))
            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
        else if(list_frqInfo == NULL)
            list_frqInfo = frqInfo;
    }

    arguments->frqInfo = list_frqInfo;

    message = bfcp_build_message(arguments);
    if(!message) {
        return -1;
    }
    error = sendBFCPmessage(sockfd, message);
    BFCP_SEND_CHECK_ERRORS();
    if ( freeNode ) {
        if ( tmpnode ) {
            remove_request_list_of_node(tmpnode->floorrequest);
            free(tmpnode->participant_info);
            tmpnode->participant_info = NULL;
            free(tmpnode->chair_info);
            tmpnode->chair_info = NULL;
            free(tmpnode);
            tmpnode = NULL;
        }
        freeNode = false ;
    }
    return 0;
}

/* Prepare the needed arguments for a FloorRequestStatus BFCP message */
int BFCP_Server::bfcp_print_information_floor(st_bfcp_conference *conference, UINT16 userID, UINT16 TransactionID, pnode newnode, UINT16 status) {
    if(conference == NULL)
        return 0;
    if(conference->floor == NULL)
        return 0;
    if(conference->floor->floors == NULL)
        return 0;
    if(status <= 0)
        return -1;
    if(newnode == NULL)
        return 0;

    int error, position;
    floor_query *query;
    pfloor floor;
    floor_request_query *newrequest;
    /* Prepare all floor information needed by interested users */
    floor = newnode->floor;
    while (floor)
    {
        position = bfcp_return_position_floor(conference->floor, floor->floorID);
        if(position >= 0) {
            if(conference->floor->floors != NULL) 
	    {
                query = conference->floor->floors[position].floorquery;
                int cl;
                while(query != NULL) 
		{
                    error = bfcp_show_floor_information(conference->conferenceID, TransactionID, query->userID, conference, floor->floorID, &cl, newnode, status);

                    if(error == -1) {
                        return -1;
                    }
                    query = query->next;
                }
            }
        }
        floor = floor->next;
    }

    newrequest = newnode->floorrequest;

    while(newrequest != NULL) {
        error = bfcp_show_requestfloor_information(conference->user, conference->accepted, conference->conferenceID, newrequest->userID, 0, newnode, status, newrequest->fd, newrequest->transport);
        if(error == -1) {
            return -1;
        }
        newrequest = newrequest->next;
    }
    return 0;
}

/* Setup and send a FloorRequestStatus BFCP message */
int BFCP_Server::bfcp_show_requestfloor_information(bfcp_list_users *list_users, bfcp_queue *accepted_queue, 
						    UINT32 conferenceID, UINT16 userID, UINT16 TransactionID,
						    pnode newnode, UINT16 status, BFCP_SOCKET sockfd, int transport) 
{
    if(newnode == NULL)
        return 0;
    if(status <= 0)
        return 0;
    if(list_users == NULL)
        return 0;

    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;
    bfcp_floor *floorID;
    bfcp_user_information *beneficiary_info, *user_info;
    pnode traverse=NULL;
    bfcp_overall_request_status *oRS = NULL;
    bfcp_floor_request_status *fRS_temp = NULL, *fRS = NULL;
    int i = 0, error = 0;
    
    /* Intermediate BFCP_PENDING and BFCP_GRANTED floor status should NOT be resent */
    bool donotresend = false;

    arguments = bfcp_new_arguments();
    if(!arguments)
        return -1;


    arguments->entity = bfcp_new_entity(conferenceID, TransactionID, userID);
    arguments->primitive = e_primitive_FloorRequestStatus;

    if(newnode->beneficiaryID != 0) {
        beneficiary_info = bfcp_new_user_information(newnode->beneficiaryID, (char *)bfcp_obtain_user_display_name(list_users, newnode->beneficiaryID), (char *)bfcp_obtain_userURI(list_users, newnode->beneficiaryID));
        if(beneficiary_info == NULL) {
            bfcp_free_user_information(beneficiary_info);
            return -1;
        }
    } else
        beneficiary_info = NULL;

    if(newnode->userID != 0) {
        user_info = bfcp_new_user_information(newnode->userID, (char *)bfcp_obtain_user_display_name(list_users, newnode->userID), (char *)bfcp_obtain_userURI(list_users, newnode->userID));
        if(user_info == NULL) {
            bfcp_free_user_information(user_info);
            return -1;
        }
    } else
        user_info = NULL;

    floorID = newnode->floor;
    if(floorID != NULL)
        fRS = bfcp_new_floor_request_status(floorID->floorID, status, 0, floorID->chair_info);
    if(fRS == NULL)
        return -1;
    floorID = floorID->next;
    while(floorID != NULL) {
        fRS_temp = bfcp_new_floor_request_status(floorID->floorID, status, 0, floorID->chair_info);
        if(fRS_temp != NULL)
            bfcp_list_floor_request_status(fRS, fRS_temp, NULL);
        floorID = floorID->next;
    }

    switch(status) {
    case BFCP_PENDING:
        /* Pending request */
        oRS = bfcp_new_overall_request_status(newnode->floorRequestID, status, newnode->priority, newnode->chair_info);
	donotresend = true;
        break;
    case BFCP_ACCEPTED:
        /* Accepted request */
        oRS = bfcp_new_overall_request_status(newnode->floorRequestID, status, 0, newnode->chair_info);
	donotresend = true;
        if(accepted_queue != NULL) {
            traverse = accepted_queue->tail;
            i = 1;
            while(traverse != NULL) {
                if(traverse->floorRequestID == newnode->floorRequestID) {
                    oRS = bfcp_new_overall_request_status(traverse->floorRequestID, status, i , traverse->chair_info);
                    break;
                } else
                    i = i + 1;
                traverse = traverse->prev;
            }
        }
        break;
    default:
        oRS = bfcp_new_overall_request_status(newnode->floorRequestID, status, 0, newnode->chair_info);
        break;
    }

    arguments->frqInfo = bfcp_new_floor_request_information(newnode->floorRequestID, oRS, fRS, beneficiary_info, user_info, BFCP_NORMAL_PRIORITY  ,newnode->participant_info);

    message = bfcp_build_message(arguments);
    if(!message) {
        return -1;
    }
    error = sendBFCPmessage(sockfd ,message, donotresend);
    BFCP_SEND_CHECK_ERRORS();

    return 0;
}

/* Handle a BFCP message a client sent to the FCS */
int BFCP_Server::ProcessBFCPmessage(bfcp_received_message * m, BFCP_SOCKET s)
{
    if (m != NULL)
    {
        /* Trigger the application callback to notify about the new incoming message */
        bfcp_received_msg(m,s);
	return 0;
    }
    else
    {
	return -1;
    }
}

/* Remove all floor requests made by a user from all existing nodes */
int BFCP_Server::bfcp_remove_floorrequest_from_all_nodes(st_bfcp_conference *server, UINT16 userID) {
    int error;

    if(server == NULL)
        return -1;

    error = bfcp_remove_floorrequest_from_a_queue(server->pending, userID);
    if(error == -1)
        return -1;

    error = bfcp_remove_floorrequest_from_a_queue(server->accepted, userID);
    if(error == -1)
        return -1;

    error = bfcp_remove_floorrequest_from_a_queue(server->granted, userID);
    if(error == -1)
        return -1;

    return 0;
}

/* Remove all floor requests made by a user from a queue */
int BFCP_Server::bfcp_remove_floorrequest_from_a_queue(bfcp_queue *conference, UINT16 userID) {
    if(conference == NULL)
        return -1;
    if(userID <= 0)
        return -1;

    pnode traverse;
    int error;

    traverse = conference->head;

    while(traverse) {
        error = remove_request_from_the_node(traverse, userID);
        if(error == -1)
            return -1;

        traverse = traverse->next;
    }

    return 0;
}

/* Disable and remove all floor events notifications to an user */
int BFCP_Server::bfcp_remove_floorquery_from_all_nodes(bfcp_list_floors *lfloors, UINT16 userID) {
    if(lfloors == NULL)
        return 0;
    if(lfloors->floors == NULL)
        return 0;
    if(userID <= 0)
        return -1;

    int i = 0, error = 0;

    for(i = 0; i < lfloors->actual_number_floors; i++) {
        error = remove_request_from_the_floor(lfloors->floors+i, userID);
        if(error == -1)
            return -1;
    }

    return 0;
}

/* A controller to check timeouts when waiting for a ChairAction */
#ifdef WIN32
unsigned  __stdcall BFCP_Server::WatchDog(void* st_thread)
#else
void* BFCP_Server::WatchDog(void* st_thread)
#endif
{
    bfcp_thread *thread = (bfcp_thread *)st_thread;
    BFCP_Server* bfcpServer = thread->bfcpServer ;
    bfcp_mutex_lock(bfcpServer->count_mutex);
    st_bfcp_conference *server;
    pfloor list_floors;
    UINT32 chair_wait_request;
    unsigned short floorRequestID;
    pnode traverse;

    server = thread->conf;
    floorRequestID = thread->floorRequestID;
    chair_wait_request = thread->chair_wait_request;

    bfcp_mutex_unlock(bfcpServer->count_mutex);
    /* Free the thread */
    free(thread);
    thread = NULL;

    BFCP_SLEEP(chair_wait_request*1000);
    /*if the queue is a pending queue*/
    if((server != NULL) && (server->pending != NULL)) {
        traverse = server->pending->tail;
        while(traverse) {
            if((traverse->floorRequestID) == floorRequestID)
                bfcpServer->bfcp_print_information_floor(server, 0, 0, traverse, BFCP_CANCELLED);
            traverse = traverse->prev;
        }
    }

    /* If the request is from the Pending list, remove it */
    list_floors = bfcpServer->bfcp_delete_request(server->pending, floorRequestID, 0);

    /* Free all the elements from the floors list */
    bfcpServer->remove_floor_list(list_floors);
    return NULL;
}

/* Handle an incoming FloorRequest message */
int BFCP_Server::bfcp_FloorRequest_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 TransactionID, pnode newnode, int sockfd, int y, int transport)
{
    if(newnode == NULL)
        return -1;

    int i, position_floor, error;
    UINT16 chairID;
    pfloor tempnode, floor;
    BFCP_THREAD_HANDLE wid = BFCP_NULL_THREAD_HANDLE  ;	/* The thread identifier */
    struct_thread st_thread;
    unsigned short floorRequestID;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, newnode->userID, sockfd);
    if(server->list_conferences[i].floorRequestID <= 0)
        server->list_conferences[i].floorRequestID = 1;
    floorRequestID = server->list_conferences[i].floorRequestID;

    newnode->floorRequestID = floorRequestID;

    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    switch (i)
    {
	case -1:
	default:
	    if (i<0)
	    {
		error = BFCP_GENERIC_ERROR;
		strcpy(errortext, "Server internal error");
	    }
	    break;
	   
	case -2:
	    error = BFCP_CONFERENCE_DOES_NOT_EXIST;
	    sprintf(errortext, "Conference %d does not exist", conferenceID);
	    break;
	   
	case -3:
	    error = BFCP_USER_DOES_NOT_EXIST;
	    sprintf(errortext, "User %d does not exist in Conference %d", newnode->userID, conferenceID);
	    break;
	    
	case -4:
	    error = BFCP_UNAUTHORIZED_OPERATION;
	    sprintf(errortext, "Floor request cannot be performed from this connection");
	    break;
    }
    
    if ( i < 0 ) 
    {
floor_request_report_err:
        bfcp_error_code(conferenceID, newnode->userID, TransactionID, (e_bfcp_error_codes) error, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    if( newnode->beneficiaryID != 0 )
    {
	/* Checks if the beneficiary user exists in the conference */
	if ( bfcp_existence_user(server->list_conferences[i].user, newnode->beneficiaryID) != 0 )
	{
	    sprintf(errortext, "No such beneficiary ID %hu in Conference %d", newnode->beneficiaryID, conferenceID);
	    error = BFCP_USER_DOES_NOT_EXIST;
	    goto floor_request_report_err;
	}
	
	if ( newnode->userID != newnode->beneficiaryID)
	{
	    /* If this FloorRequest has a beneficiaryID, check if the user chairs the conference. Only then the user is allowed to do this operation 
	     * If the user and beneficiary ID are the same we authorize the operation
	     */
	    if ( bfcp_exist_user_as_a_chair(server->list_conferences[i].floor, newnode->userID) != 0 )
	    {
		error = BFCP_UNAUTHORIZED_OPERATION;
		sprintf(errortext, "Third-party FloorRequests (for benificiaty user %u) only allowed for chairs (User %d is not chair of any floor)", 
		        newnode->beneficiaryID, newnode->userID);
		goto floor_request_report_err;
	    }
	}
    }
    if(server->list_conferences[i].floorRequestID <= 0)
        server->list_conferences[i].floorRequestID = 1;
    floorRequestID = server->list_conferences[i].floorRequestID;

    newnode->floorRequestID = floorRequestID;
    if (newnode->floor != NULL) 
    {
        for (tempnode = newnode->floor; tempnode; tempnode = tempnode->next)
	{
            position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
            if(position_floor == -1) 
	    {
                sprintf(errortext, "Floor %d does not exist in Conference %d", tempnode->floorID, conferenceID);
		error = BFCP_INVALID_FLOORID;
		goto floor_request_report_err;
            }

            /* If no chair is present and the policy is to autodeny requests, remove the request node */
            if((server->list_conferences[i].automatic_accepted_deny_policy == 1) && (bfcp_return_chair_floor(server->list_conferences[i].floor, tempnode->floorID) == 0)) {
                error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, server->list_conferences[i].conferenceID, newnode->userID, TransactionID, newnode, BFCP_DENIED, sockfd, transport);
                if(error == -1) {
                    bfcp_mutex_unlock(count_mutex);
                    return -1;
                }

                /* Remove the request node */
                remove_floor_list(newnode->floor);
                remove_request_list_of_node(newnode->floorrequest);
                free(newnode->participant_info);
                newnode->participant_info = NULL;
                free(newnode->chair_info);
                newnode->chair_info = NULL;
                free(newnode);
                newnode = NULL;
                bfcp_mutex_unlock(count_mutex);
                return 0;
            }

            /* Check if this user has already reached the maximum number of ongoing requests for the same floor */
            if(bfcp_is_floor_request_full(conferenceID, TransactionID, server->list_conferences[i].user, newnode->beneficiaryID ? newnode->beneficiaryID : newnode->userID, position_floor, sockfd, y, transport) == -1) {
                /* Remove the request node */
                remove_floor_list(newnode->floor);
                remove_request_list_of_node(newnode->floorrequest);
                free(newnode->participant_info);
                newnode->participant_info = NULL;
                free(newnode->chair_info);
                newnode->chair_info = NULL;
                free(newnode);
                newnode = NULL;
                bfcp_mutex_unlock(count_mutex);
                return 0;
            }
        }
    } else {
        sprintf(errortext, "There are no floors in Conference %d", conferenceID);
        bfcp_error_code(conferenceID, newnode->userID, TransactionID, BFCP_INVALID_FLOORID, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Checks in which position each floor is, and add the request to the user's list */
    position_floor = 0;
    for(tempnode = newnode->floor; tempnode; tempnode = tempnode->next) {
        position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
        if(position_floor != -1) {
            /* If the floor(s) is/are for a beneficiary, add the request to the beneficiary's list */
            if(newnode->beneficiaryID != 0)
                error = bfcp_add_user_request(conferenceID, TransactionID, server->list_conferences[i].user, newnode->beneficiaryID, position_floor, sockfd, y);
            else
                error = bfcp_add_user_request(conferenceID, TransactionID, server->list_conferences[i].user, newnode->userID, position_floor, sockfd, y);
            if(error == -1) {
                /* Remove the node */
                remove_floor_list(newnode->floor);
                remove_request_list_of_node(newnode->floorrequest);
                free(newnode->participant_info);
                newnode->participant_info = NULL;
                free(newnode->chair_info);
                newnode->chair_info = NULL;
                free(newnode);
                newnode = NULL;
                bfcp_mutex_unlock(count_mutex);
                return 0;
            }
        } else {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    /* Handle the Chair part */

    /* For each floor in the request, accept/deny it or ask for the chair's approval */
    if((newnode->floor) != NULL) {
        for(tempnode = newnode->floor; tempnode; tempnode = tempnode->next) {
            /*checks if this floor has a chair*/
            chairID= bfcp_return_chair_floor(server->list_conferences[i].floor, tempnode->floorID);
            /*if it has a chair*/
            if(chairID != 0) {
                /* Allocate a new thread handler */
                st_thread = (struct_thread)calloc(1, sizeof(bfcp_thread));
                if(st_thread == NULL) {
                    bfcp_mutex_unlock(count_mutex);
                    return -1;
                }

                /* Initialize the structure the thread will handle */
                st_thread->conf = server->list_conferences + i;
                st_thread->chair_wait_request = server->list_conferences[i].chair_wait_request;
                st_thread->floorRequestID = floorRequestID;
                st_thread->bfcpServer = this ;

                /* Create the watchdog thread */
                BFCP_THREAD_START( wid , BFCP_Server::WatchDog , (void*)st_thread );
                if ( wid ) {
                    Log(INF, "BFCP  watchdog started [0x%p]",wid);
                }
                /*put the pID in the node*/
                tempnode->pID = wid;
            } else
                /* Change status of the floor to Accepted */
                tempnode->status = BFCP_FLOOR_STATE_ACCEPTED;
        }
    }

    /* Check if the floors are FREE (TODO check state) */
    floor = newnode->floor;
    while(floor != NULL) {
        if(floor->status == 1)
            floor = floor->next;
        else
            break;
    }

    if(floor == NULL) {
        /*put the node in the accept list*/
        /*change the priority of the node to the lowest one*/
        newnode->priority = BFCP_LOWEST_PRIORITY;

        /* Remove the threads handling this node */
        floor = newnode->floor;
        while(floor) {

            if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                BFCP_THREAD_KILL(floor->pID);
                floor->pID = BFCP_NULL_THREAD_HANDLE ;
            }
            floor = floor->next;
        }

        error = bfcp_insert_request(server->list_conferences[i].accepted, newnode, floorRequestID, NULL);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Prepare all floor information needed by interested users */
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_ACCEPTED);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Notify the requester about all the most important information about his request */
        error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, server->list_conferences[i].conferenceID, newnode->userID, TransactionID, newnode, BFCP_ACCEPTED, sockfd, transport);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Check if the node should be moved to the Granted queue */
        if(server->list_conferences[i].floor != NULL) {
            if(server->list_conferences[i].floor->floors != NULL) {
                for (y = (server->list_conferences[i].floor->actual_number_floors-1); 0 <= y; y--) {
                    if(bfcp_return_state_floor(server->list_conferences[i].floor, server->list_conferences[i].floor->floors[y].floorID)<bfcp_return_number_granted_floor(server->list_conferences[i].floor, server->list_conferences[i].floor->floors[y].floorID)) {
                        if(check_accepted_node(server->list_conferences+i, newnode, server->list_conferences[i].floor->floors[y].floorID, NULL) == 0) {
                            /* Notify the requester about all the most important information about his request */
                            error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, server->list_conferences[i].conferenceID, newnode->userID, TransactionID, newnode, BFCP_GRANTED, sockfd, transport);
                            if(error == -1) {
                                bfcp_mutex_unlock(count_mutex);
                                return -1;
                            }
                        }
                    }
                }
            }
        }
    } else {
        /*put the node in the pending list*/
        error = bfcp_insert_request(server->list_conferences[i].pending, newnode, floorRequestID, NULL);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Prepare all floor information needed by interested users */
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_PENDING);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Notify the requester about all the most important information about his request */
        error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, server->list_conferences[i].conferenceID, newnode->userID, TransactionID, newnode, BFCP_PENDING, sockfd, transport);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    server->list_conferences[i].floorRequestID = server->list_conferences[i].floorRequestID + 1;

    /* The requester will constantly be notified about updates concerning his request */
    error = add_request_to_the_node(newnode, newnode->userID, sockfd, transport);
    if(error == -1) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Handle an incoming FloorRelease message */
/* RequestStatus ->Cancelled if the floor had not been previous granted- Released if the floor had been previous granted */
int BFCP_Server::bfcp_FloorRelease_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 TransactionID, UINT16 userID, UINT16 floorRequestID, BFCP_SOCKET sockfd, int y, int transport)
{
    if(server == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(floorRequestID <= 0)
        return -1;

    int i= 0, position_floor= 0, error= 0, status_floor = 0;
    pfloor temp = NULL, list_floors = NULL, floor = NULL;
    pnode newnode = NULL;
    bfcp_queue *laccepted= NULL;

    Log(INF,"bfcp_FloorRelease_server ConfID:[%u] UserID:[%d] floorRequestID:[%d]", conferenceID, userID, floorRequestID);
    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, userID, sockfd);
    
    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    switch (i)
    {
	case -1:
	default:
	    if (i<0)
	    {
		error = BFCP_GENERIC_ERROR;
		strcpy(errortext, "Server internal error");
	    }
	    break;
	   
	case -2:
	    error = BFCP_CONFERENCE_DOES_NOT_EXIST;
	    sprintf(errortext, "Conference %d does not exist", conferenceID);
	    break;
	   
	case -3:
	    error = BFCP_USER_DOES_NOT_EXIST;
	    sprintf(errortext, "User %d does not exist in Conference %d", userID, conferenceID);
	    break;
	    
	case -4:
	    error = BFCP_UNAUTHORIZED_OPERATION; 
	    sprintf(errortext, "This command is not authorized from this IP address");
	    {
		int tr;
		BFCP_SOCKET su = bfcp_get_user_sockfd(m_struct_server, conferenceID, userID, &tr);
		
		Log(ERR, "BFCP message sent to user ID %u associated with sock FD %d but received on sockfd %d",
		    userID, su, sockfd);
	    }
	    break;
    }
    
    if ( i < 0 ) 
    {
        bfcp_error_code(conferenceID, userID, TransactionID, (e_bfcp_error_codes) error, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    /* Check if this request node is in the Accepted list */
    if(bfcp_give_user_of_request(server->list_conferences[i].accepted, floorRequestID) == userID) {
        newnode = bfcp_extract_request(server->list_conferences[i].accepted, floorRequestID);
        status_floor = BFCP_FLOOR_STATE_ACCEPTED;
    }

    if(newnode == NULL) {
        /* First check if the request node is in the Pending list */
        if(bfcp_give_user_of_request(server->list_conferences[i].pending, floorRequestID) == userID) {
            bfcp_kill_threads_request_with_FloorRequestID(server->list_conferences[i].pending, floorRequestID);
            newnode = bfcp_extract_request(server->list_conferences[i].pending, floorRequestID);
            status_floor = BFCP_FLOOR_STATE_ACCEPTED;
        }
        if(newnode == NULL) {
            /* Then check if the request node is in the Granted list */
            if(bfcp_give_user_of_request(server->list_conferences[i].granted, floorRequestID) == userID) {
                newnode = bfcp_extract_request(server->list_conferences[i].granted, floorRequestID);
                status_floor = BFCP_FLOOR_STATE_GRANTED;
            }
            if(newnode == NULL) {
                sprintf(errortext, "FloorRequest %d does not exist in Conference %d", floorRequestID, conferenceID);
                bfcp_error_code(conferenceID, userID, TransactionID, BFCP_FLOORREQUEST_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        } else {
            /* Remove the thread if this request node is in the Pending list */
            floor = newnode->floor;
            while(floor) {
                if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                    BFCP_THREAD_KILL(floor->pID);
                    floor->pID = BFCP_NULL_THREAD_HANDLE;
                }
                floor = floor->next;
            }
        }
    }

    /* Notify the releaser about the floor request information of the released request */
    if(status_floor == BFCP_FLOOR_STATE_ACCEPTED)
        error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, 
						   server->list_conferences[i].conferenceID, userID, TransactionID, 
						   newnode, BFCP_CANCELLED, sockfd, transport);
    else
        error = bfcp_show_requestfloor_information(server->list_conferences[i].user, server->list_conferences[i].accepted, 
						   server->list_conferences[i].conferenceID, userID, TransactionID,
						   newnode, BFCP_RELEASED, sockfd, transport);
    if(error == -1) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    error = remove_request_from_the_node(newnode, userID);
    if(error == -1) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Prepare all floor information needed by interested users */

    if(status_floor == BFCP_FLOOR_STATE_ACCEPTED)
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_CANCELLED);
    else
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_RELEASED);
    if(error == -1) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    list_floors = newnode->floor;

    /* Remove the list of requests */
    remove_request_list_of_node(newnode->floorrequest);

    free(newnode->participant_info);
    newnode->participant_info = NULL;
    free(newnode->chair_info);
    newnode->chair_info = NULL;
    free(newnode);
    newnode = NULL;

    while(list_floors != NULL) {
        position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, list_floors->floorID);

        if(position_floor != -1) {
            if((bfcp_return_state_floor(server->list_conferences[i].floor, server->list_conferences[i].floor->floors[position_floor].floorID) == BFCP_FLOOR_STATE_GRANTED ) && (list_floors->status == 2))
                /* Change state of the floor to available (FREE) */
                bfcp_change_state_floor(server->list_conferences[i].floor, list_floors->floorID, BFCP_FLOOR_STATE_WAITING);

            error = bfcp_deleted_user_request(server->list_conferences[i].user, userID, position_floor);
            if(error == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }

        /* Check if other requests that need this floor are in the Accepted list */
        laccepted = server->list_conferences[i].accepted;

        if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, laccepted, server->list_conferences[i].floor, NULL) == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Destroy the floors list */
        temp = list_floors;
        list_floors = list_floors->next;
        free(temp->chair_info);
        temp->chair_info = NULL;
        free(temp);
        temp = NULL;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* Handle an incoming ChairAction message */
int BFCP_Server::bfcp_ChairAction_server(st_bfcp_server *server, UINT32 conferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 floorRequestID, int RequestStatus, char *chair_info, UINT16 queue_position, UINT16 TransactionID, BFCP_SOCKET sockfd, int y, int transport) 
{
    if(server == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(list_floors == NULL)
        return -1;
    if(userID <= 0)
        return -1;
    if(floorRequestID <= 0)
        return -1;
    if((RequestStatus != BFCP_ACCEPTED) && (RequestStatus != BFCP_DENIED) && (RequestStatus != BFCP_REVOKED))
        return -1;
    if(TransactionID <= 0)
        return -1;

    int actual_conference = 0, i, error, position_floor;
    pfloor floor, next, next_floors, tempnode, free_floors, tempfloors = NULL;
    bfcp_node *newnode = NULL;
    bfcp_floor *node = NULL;
    bfcp_queue *laccepted;
    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;
    size_t dLen;

    actual_conference = server->Actual_number_conference - 1;
    for(i = 0; i < actual_conference; i++) {
        if(server->list_conferences[i].conferenceID == conferenceID)
            break;
    }

    bfcp_mutex_lock(count_mutex);

    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    if(server->list_conferences[i].conferenceID != conferenceID) {
        sprintf(errortext, "Conference %d does not exist", conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_CONFERENCE_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if this user exists */
    if(bfcp_existence_user(server->list_conferences[i].user, userID) != 0) {
        sprintf(errortext, "User %d does not exist in Conference %d", userID, conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if all the floors exist in the conference, otherwise send an error */
    for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
        position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
        if(position_floor == -1) {
            sprintf(errortext, "Floor %d does not exist in Conference %d", tempnode->floorID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_INVALID_FLOORID, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Check if the user is allowed to do this operation */
        if(bfcp_return_chair_floor(server->list_conferences[i].floor, tempnode->floorID) != userID) {
            sprintf(errortext, "User %d is not chair of Floor %hu in Conference %d", userID, tempnode->floorID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_UNAUTHORIZED_OPERATION, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    if(RequestStatus == BFCP_ACCEPTED) {
        /* The chair accepted a request */

        /* First check if the request node is in the Pending list */
        if(bfcp_give_user_of_request(server->list_conferences[i].pending, floorRequestID) == 0) {
            sprintf(errortext, "Pending FloorRequest %d does not exist in Conference %d", floorRequestID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_FLOORREQUEST_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        /* Check if the floors involved in the accepted request exist */
        for(tempnode = list_floors; tempnode != NULL; tempnode = tempnode->next) {
            if(bfcp_change_status(server->list_conferences[i].pending, tempnode->floorID, floorRequestID, BFCP_FLOOR_STATE_ACCEPTED, tempnode->chair_info) != 0) {
                sprintf(errortext, "Floor %d does not exist in Conference %d", tempnode->floorID, conferenceID);
                bfcp_error_code(conferenceID, userID, TransactionID, BFCP_INVALID_FLOORID, errortext, NULL, sockfd, y, transport);
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }

        /* Set the queue_position value if it is needed */
        bfcp_change_queue_position(server->list_conferences[i].pending, floorRequestID, queue_position);

        /* If all the floors in the request have been accepted... */
        if(bfcp_all_floor_status(server->list_conferences[i].pending, floorRequestID, BFCP_FLOOR_STATE_ACCEPTED) == 0) {
            /* Extract the request node from the Pending list */
            newnode = bfcp_extract_request(server->list_conferences[i].pending, floorRequestID);

            /* Remove the threads handling this node */
            floor = newnode->floor;
            while(floor) {
                if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                    BFCP_THREAD_KILL(floor->pID);
                    floor->pID = BFCP_NULL_THREAD_HANDLE ;
                }
                floor = floor->next;
            }

            /* Move the node to the Accepted list */

            newnode->priority = BFCP_LOWEST_PRIORITY;

            error = bfcp_insert_request(server->list_conferences[i].accepted, newnode, floorRequestID, chair_info);
            if(error == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }

            /* Prepare all floor information needed by interested users */
            error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_ACCEPTED);
            if(error == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }

            /* Check if the node should be in the Granted queue */
            laccepted = server->list_conferences[i].accepted;
            if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, laccepted, server->list_conferences[i].floor, chair_info) == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }
    } else if(RequestStatus == BFCP_DENIED) {
        /* The chair denied a pending request */

        /* Extract the request node from the Pending list */
        newnode = bfcp_extract_request(server->list_conferences[i].pending, floorRequestID);
        if(newnode == NULL) {
            sprintf(errortext, "Pending FloorRequest %d does not exist in Conference %d", floorRequestID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_FLOORREQUEST_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* If there's chair-provided text information, add it to the request node */
        if(chair_info != NULL) {
            dLen = strlen(chair_info);
            if(dLen != 0) {
                if(newnode->chair_info != NULL) {
                    free(newnode->chair_info);
                    newnode->chair_info = NULL;
                }
                newnode->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
                memcpy(newnode->chair_info, chair_info, dLen+1);
            }
        }

        /* Remove the threads handling this node */
        floor = newnode->floor;
        while(floor != NULL) {
            if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                BFCP_THREAD_KILL(floor->pID);
                floor->pID = BFCP_NULL_THREAD_HANDLE ;
            }
            floor = floor->next;
        }

        /* Add the chair-provided information to each floor */
        for(tempnode = list_floors; tempnode != NULL; tempnode = tempnode->next) {
            for(node = newnode->floor; node != NULL; node = node->next) {
                if(node->floorID == tempnode->floorID) {
                    /* If there's chair-provided text for this floor, add it */
                    if(tempnode->chair_info != NULL) {
                        dLen = strlen(tempnode->chair_info);
                        if(dLen != 0) {
                            if(node->chair_info != NULL) {
                                free(node->chair_info);
                                node->chair_info = NULL;
                            }
                            node->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
                            memcpy(node->chair_info, tempnode->chair_info, dLen+1);
                        }
                    } else
                        node->chair_info = NULL;
                }
            }
        }
        /* Prepare all floor information needed by interested users */
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_DENIED);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the request node from the Pending list */
        if(newnode != NULL) {
            remove_floor_list(newnode->floor);
            remove_request_list_of_node(newnode->floorrequest);
            free(newnode->participant_info);
            newnode->participant_info = NULL;
            free(newnode->chair_info);
            newnode->chair_info = NULL;
            free(newnode);
            newnode = NULL;
        }
    } else if(RequestStatus == BFCP_REVOKED) {
        /* The chair revoked a previously granted request */

        /* Extract the request node from the Granted list */
        newnode = bfcp_extract_request(server->list_conferences[i].granted, floorRequestID);
        if(newnode == NULL) {
            sprintf(errortext, "Granted FloorRequest %d does not exist in Conference %d", floorRequestID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_FLOORREQUEST_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* If there's chair-provided text information, add it to the request node */
        if(chair_info != NULL) {
            dLen = strlen(chair_info);
            if(dLen != 0) {
                if(newnode->chair_info != NULL)
                    free(newnode->chair_info);
                newnode->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
                memcpy(newnode->chair_info, chair_info, dLen+1);
            }
        }

        /* Add the chair-provided information to each floor */
        for(tempnode = list_floors; tempnode != NULL; tempnode = tempnode->next) {
            for(node = newnode->floor; node != NULL; node = node->next) {
                if(node->floorID == tempnode->floorID) {
                    /* If there's chair-provided text for this floor, add it */
                    if(tempnode->chair_info != NULL) {
                        dLen = strlen(tempnode->chair_info);
                        if(dLen != 0) {
                            if(node->chair_info != NULL) {
                                free(node->chair_info);
                                node->chair_info = NULL;
                            }
                            node->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
                            memcpy(node->chair_info, tempnode->chair_info, dLen+1);
                        }
                    } else
                        node->chair_info = NULL;
                }
            }
        }

        /* Prepare all floor information needed by interested users */
        error = bfcp_print_information_floor(server->list_conferences+i, 0, 0, newnode, BFCP_REVOKED);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Remove the request node from the Granted list */
        if(newnode != NULL) {
            tempfloors = newnode->floor;
            remove_request_list_of_node(newnode->floorrequest);
            free(newnode->participant_info);
            newnode->participant_info = NULL;
            free(newnode->chair_info);
            newnode->chair_info = NULL;
            free(newnode);
            newnode = NULL;
        }

        /* Set the state of the floors to FREE */
        free_floors = tempfloors;
        while(free_floors != NULL) {
            error = bfcp_change_state_floor(server->list_conferences[i].floor, free_floors->floorID, BFCP_FLOOR_STATE_WAITING);
            if(error == -1) {
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
            next = free_floors->next;
            free(free_floors->chair_info);
            free_floors->chair_info = NULL;
            free(free_floors);
            free_floors = NULL;
            free_floors = next;
        }

        laccepted = server->list_conferences[i].accepted;
        if(give_free_floors_to_the_accepted_nodes(server->list_conferences+i, laccepted, server->list_conferences[i].floor, chair_info) == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    } else {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Free the floors list */
    while(list_floors) {
        next_floors = list_floors->next;
        free(list_floors->chair_info);
        list_floors->chair_info = NULL;
        free(list_floors);
        list_floors = NULL;
        list_floors = next_floors;
    }

    /* Send the ChairActionAck to the client */
    arguments = bfcp_new_arguments();
    if(!arguments) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    arguments->entity = bfcp_new_entity(conferenceID,TransactionID,userID);
    arguments->primitive = e_primitive_ChairActionAck;

    message = bfcp_build_message(arguments);
    if(!message) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    bfcp_mutex_unlock(count_mutex);
    error = sendBFCPmessage(sockfd,message);
    BFCP_SEND_CHECK_ERRORS();

    return 0;
}

/* Handle an incoming Hello message */
int BFCP_Server::bfcp_hello_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, BFCP_SOCKET sockfd, int y, int transport) 
{
    if(server == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(userID <= 0)
        return -1;
    if(TransactionID <= 0)
        return -1;

    int i, error;
    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, userID, -1);
    
    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    if (i == -2) 
    {
        Log(ERR,"Conference %d does not exist", conferenceID);
        sprintf(errortext, "Conference %d does not exist", conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_CONFERENCE_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if this user exists */
    if (i == -3) 
    {
        Log(ERR,"User %d does not exist in Conference %d", userID, conferenceID);
        sprintf(errortext, "User %d does not exist in Conference %d", userID, conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    if (i < 0)
    {
	Log(ERR,"Parameter error %d", i);
        sprintf(errortext, "Server error");
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_GENERIC_ERROR, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    arguments = bfcp_new_arguments();
    if (!arguments) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    arguments->entity = bfcp_new_entity(conferenceID,TransactionID,userID);
    arguments->primitive = e_primitive_HelloAck;

    /* Create a list of all the primitives the FCS supports */
    arguments->primitives= bfcp_new_supported_list(e_primitive_FloorRequest,
                           e_primitive_FloorRelease,
                           /* e_primitive_FloorRequestQuery,
                           e_primitive_FloorRequestStatus,
                           e_primitive_UserQuery,
                           e_primitive_UserStatus,
			   */
                           e_primitive_FloorQuery,
                           /*
                           e_primitive_ChairAction,
                           e_primitive_ChairActionAck,*/
			   e_primitive_FloorStatus,
                           e_primitive_Hello,
                           e_primitive_HelloAck,
			   e_primitive_Goodbye,
			   e_primitive_GoodbyeAck,
                           e_primitive_Error, 0);

    /* Create a list of all the attributes the FCS supports */
    arguments->attributes= bfcp_new_supported_list(BENEFICIARY_ID,
                           FLOOR_ID,
                           FLOOR_REQUEST_ID,
                           PRIORITY,
                           REQUEST_STATUS,
                           ERROR_CODE,
                           ERROR_INFO,
                           PARTICIPANT_PROVIDED_INFO,
                           STATUS_INFO,
                           SUPPORTED_ATTRIBUTES,
                           SUPPORTED_PRIMITIVES,
                           USER_DISPLAY_NAME,
                           USER_URI,
                           BENEFICIARY_INFORMATION,
                           FLOOR_REQUEST_INFORMATION,
                           REQUESTED_BY_INFORMATION,
                           FLOOR_REQUEST_STATUS,
                           OVERALL_REQUEST_STATUS,
                           NONCE,
                           DIGEST, 0);

    message = bfcp_build_message(arguments);
    if (!message) 
    {
	Log(ERR,"BFCPServer: Failed to build HelloAck message");
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);
    
    Log(INF,"BFCPServer: sending HelloAck sock fd %d", sockfd);
    error = sendBFCPmessage(sockfd, message);
    
    BFCP_SEND_CHECK_ERRORS();
    if ( error < 0 ) Log(INF,"BFCPServer: failed to send HelloAck. err %d on sockfd %d", error, sockfd);
    return 0;
}

/* Handle an incoming UserQuery message */
int BFCP_Server::bfcp_userquery_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, UINT16 beneficiaryID, BFCP_SOCKET sockfd, int y, int transport)
{
    if(server == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(userID <= 0)
        return -1;

    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;
    bfcp_user_information *beneficiary_info;
    int error, actual_conference = 0, i, j;
    bfcp_floor_request_information *frqInfo = NULL, *list_frqInfo = NULL;
    pnode traverse;

    bfcp_mutex_lock(count_mutex);

    actual_conference = server->Actual_number_conference - 1;
    for(i = 0; i < actual_conference; i++) {
        if(server->list_conferences[i].conferenceID == conferenceID)
            break;
    }

    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    if(server->list_conferences[i].conferenceID != conferenceID) {
        sprintf(errortext, "Conference %d does not exist", conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_CONFERENCE_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if this user exists */
    if(bfcp_existence_user(server->list_conferences[i].user, userID) != 0) {
        sprintf(errortext, "User %hu does not exist in Conference %d", userID, conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    if(beneficiaryID != 0) {
        /* The user requested information about another user, the Beneficiary: */
        /* 	check if this beneficiary exists in the conference */
        if(bfcp_existence_user(server->list_conferences[i].user, beneficiaryID) != 0) {
            sprintf(errortext, "User %hu (beneficiary of the query) does not exist in Conference %d", beneficiaryID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    /* Prepare an UserStatus message */
    arguments = bfcp_new_arguments();
    if(!arguments) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    arguments->entity = bfcp_new_entity(conferenceID,TransactionID,userID);
    arguments->primitive = e_primitive_UserStatus;

    /* Add the Beneficiary information, if needed */
    if(beneficiaryID != 0) {
        beneficiary_info = bfcp_show_user_information(server->list_conferences[i].user, beneficiaryID);
        if(beneficiary_info == NULL) {
            bfcp_free_user_information(beneficiary_info);
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        userID= beneficiaryID;
    } else
        beneficiary_info = NULL;

    arguments->beneficiary = beneficiary_info;

    /*if the queue is a granted queue*/
    if(server->list_conferences[i].granted != NULL) {
        traverse = server->list_conferences[i].granted->tail;
        while(traverse) {
            if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                frqInfo = create_floor_request_userID(traverse,server->list_conferences[i].user, userID, 3, 0);
                if((frqInfo != NULL) && (list_frqInfo != NULL))
                    bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                else if(list_frqInfo == NULL)
                    list_frqInfo = frqInfo;
            }
            traverse = traverse->prev;
        }
    }

    /* Accepted queue */
    if(server->list_conferences[i].accepted != NULL) {
        traverse = server->list_conferences[i].accepted->tail;
        j = 1;
        while(traverse) {
            if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                frqInfo = create_floor_request_userID(traverse,server->list_conferences[i].user, userID, 2, j);
                if((frqInfo != NULL) && (list_frqInfo != NULL))
                    bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                else if(list_frqInfo == NULL)
                    list_frqInfo = frqInfo;
            }
            j = j + 1;
            traverse = traverse->prev;
        }
    }

    /* Pending queue */
    if(server->list_conferences[i].pending != NULL) {
        traverse = server->list_conferences[i].pending->tail;
        while(traverse) {
            if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
                frqInfo = create_floor_request_userID(traverse,server->list_conferences[i].user, userID, 1, 0);
                if((frqInfo != NULL) && (list_frqInfo != NULL))
                    bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
                else if(list_frqInfo == NULL)
                    list_frqInfo = frqInfo;
            }
            traverse = traverse->prev;
        }
    }

    arguments->frqInfo = list_frqInfo;

    message = bfcp_build_message(arguments);
    if(!message) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);
    error = sendBFCPmessage(sockfd,message);

    BFCP_SEND_CHECK_ERRORS();

    return 0;
}

/* Handle an incoming FloorQuery message */
int BFCP_Server::bfcp_floorquery_server(st_bfcp_server *server, UINT32 conferenceID, bfcp_floor *list_floors, UINT16 userID, UINT16 TransactionID, int sockfd, int y, int transport)
{
    if(server == NULL)
        return -1;
    if(server->list_conferences == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(TransactionID <= 0)
        return -1;

    int error, i, position;
    bfcp_floor *next_floors, *tempnode;
    floor_query *query;
    int position_floor;

    bfcp_mutex_lock(count_mutex);

    
    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};
    i = CheckConferenceAndUser(server, conferenceID, userID, -1);
    
    switch (i)
    {
	case -2:
	    sprintf(errortext, "Conference %d does not exist", conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_CONFERENCE_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
	    break;
	    
	case -3:
	    sprintf(errortext, "User %hu does not exist in Conference %d", userID, conferenceID);
            bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
	    break;
	    
	default:
	    break;
    }

    if (i < 0)
    {
	bfcp_mutex_unlock(count_mutex);
	return i;
    }

    error = bfcp_floor_query_server(server->list_conferences[i].floor, list_floors, userID, sockfd, transport);
    if (error < 0)
    {
            bfcp_mutex_unlock(count_mutex);
            return error;
    }
    
    /* Check if all the floors exist in the conference, otherwise send an error */
    if(list_floors != NULL) 
    {
        for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
            position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
            if(position_floor == -1) {
                sprintf(errortext, "Floor %hu does not exist in Conference %d", tempnode->floorID, conferenceID);
                bfcp_error_code(conferenceID, userID, TransactionID, BFCP_INVALID_FLOORID, errortext, NULL, sockfd, y, transport);
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }
    }

    if(list_floors == NULL) 
    {
        /* Remove the user from the list of FloorQueries */
        error = bfcp_remove_floorquery_from_all_nodes(server->list_conferences[i].floor, userID);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        int *client = NULL ;
        error = bfcp_show_floor_information(conferenceID, TransactionID, userID, server->list_conferences+i, 0, client, NULL, 0);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
    }

    while(list_floors) {
        position = bfcp_return_position_floor(server->list_conferences[i].floor, list_floors->floorID);
        if(position >= 0) {
            if(server->list_conferences[i].floor->floors != NULL) {
                query = server->list_conferences[i].floor->floors[position].floorquery;
                while(query != NULL) {
                    if(query->userID == userID) 
		    {
			int cl = 0;

                        error = bfcp_show_floor_information(conferenceID, TransactionID, query->userID, server->list_conferences+i, list_floors->floorID, &cl, NULL, 0);
                        if(error == -1) {
                            bfcp_mutex_unlock(count_mutex);
                            return -1;
                        }
                    }
                    query = query->next;
                }
            }
        }

        /* Remove the floor from the list */
        next_floors = list_floors->next;
        free(list_floors->chair_info);
        list_floors->chair_info = NULL;
        free(list_floors);
        list_floors = NULL;
        list_floors = next_floors;
    }

    bfcp_mutex_unlock(count_mutex);

    return 0;
}

/* (??) */
int BFCP_Server::bfcp_floor_query_server(bfcp_list_floors *lfloors, bfcp_floor *list_floors, UINT16 userID, int sockfd, int transport) 
{
    if(lfloors == NULL)
        return 0;
    if(userID <= 0)
        return -1;

    floor_query *query = NULL;
    floor_query *query_temp = NULL;
    floor_query *newnode = NULL;
    int i = 0, exist_user;

    i = lfloors->actual_number_floors-1;
    while(0 <= i) {
        if((list_floors == NULL) || (lfloors->floors[i].floorID != list_floors->floorID)) {
            query = lfloors->floors[i].floorquery;
            if(query != NULL) {
                if(query->userID == userID) {
                    lfloors->floors[i].floorquery = query->next;
                    query->next = NULL;
                    free(query);
                    query = NULL;
                } else {
                    while(query->next) {
                        if(query->next->userID == userID) {
                            /* Remove the query */
                            query_temp= query->next;
                            query->next = query_temp->next;
                            query_temp->next = NULL;
                            free(query_temp);
                            query_temp = NULL;
                            break;
                        } else
                            query = query->next;
                    }
                }
            }

            if(list_floors == NULL)
                i = i - 1;
            else {
                if(lfloors->floors[i].floorID > list_floors->floorID)
                    i = i - 1;
                else
                    list_floors = list_floors->next;
            }
        } else {
            query = lfloors->floors[i].floorquery;
            /* If the query already exists, don't add it again */
            exist_user = 0;
            while(query) {
                if(query->userID == userID) {
                    exist_user = 1;
                    break;
                }
                query = query->next;
            }
            if(exist_user == 0) {
                /* Allocate a new node */
                newnode = (floor_query *)calloc(1, sizeof(floor_query));
                if(newnode == NULL)
                    return -1;

                query = lfloors->floors[i].floorquery;
                /* Add the new query to the list of requests */
                newnode->userID = userID;
                newnode->fd = sockfd;
                newnode->next = query;
                lfloors->floors[i].floorquery = newnode;
            }

            i = i - 1;
            list_floors = list_floors->next;
        }
    }

    return 0;
}

/* Handle an incoming FloorRequestQuery message */
int BFCP_Server::bfcp_floorrequestquery_server(st_bfcp_server *server, UINT32 conferenceID, UINT16 TransactionID, UINT16 floorRequestID, UINT16 userID, BFCP_SOCKET sockfd, int y, int transport) 
{
    if(server == NULL)
        return -1;
    if(conferenceID <= 0)
        return -1;
    if(userID <= 0)
        return -1;

    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;
    bfcp_floor_request_information *frqInfo, *list_frqInfo = NULL;
    int actual_conference, i, error;
    bfcp_mutex_lock(count_mutex);
    actual_conference = server->Actual_number_conference - 1;
    for(i = 0; i < actual_conference; i++) {
        if(server->list_conferences[i].conferenceID == conferenceID)
            break;
    }

    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    if(server->list_conferences[i].conferenceID != conferenceID) {
        sprintf(errortext, "Conference %d does not exist", conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_CONFERENCE_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if this user exists */
    if(bfcp_existence_user(server->list_conferences[i].user, userID) != 0) {
        sprintf(errortext, "User %hu does not exist in Conference %d", userID, conferenceID);
        bfcp_error_code(conferenceID, userID, TransactionID, BFCP_USER_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    /* Check if the request is in the Pending list */
    if(bfcp_floor_request_query_server(server->list_conferences[i].pending, floorRequestID, userID, sockfd, transport) != 0)
    {
        /* Check if the request is in the Accepted list */
        if(bfcp_floor_request_query_server(server->list_conferences[i].accepted, floorRequestID, userID, sockfd, transport) != 0) {
            /* Check if the request is in the Granted list */
            if(bfcp_floor_request_query_server(server->list_conferences[i].granted, floorRequestID, userID, sockfd, transport) != 0) {
                sprintf(errortext, "FloorRequest %d does not exist in Conference %d", floorRequestID, conferenceID);
                bfcp_error_code(conferenceID, userID, TransactionID, BFCP_FLOORREQUEST_DOES_NOT_EXIST, errortext, NULL, sockfd, y, transport);
                bfcp_mutex_unlock(count_mutex);
                return -1;
            }
        }
    }

    /* Prepare the FloorRequestStatus message */
    arguments = bfcp_new_arguments();
    if(!arguments) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }
    arguments->entity = bfcp_new_entity(conferenceID,TransactionID,userID);
    arguments->primitive = e_primitive_FloorRequestStatus;

    /* Granted list*/
    frqInfo = bfcp_show_floorrequest_information(server->list_conferences[i].granted, server->list_conferences[i].user, floorRequestID, 0);
    if(frqInfo != NULL) {
        if(list_frqInfo != NULL)
            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
        else
            list_frqInfo = frqInfo;
    }

    /* Accepted list*/
    frqInfo = bfcp_show_floorrequest_information(server->list_conferences[i].accepted, server->list_conferences[i].user, floorRequestID, 1);
    if(frqInfo != NULL) {
        if(list_frqInfo != NULL)
            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
        else
            list_frqInfo = frqInfo;
    }

    /* Pending list*/
    frqInfo = bfcp_show_floorrequest_information(server->list_conferences[i].pending, server->list_conferences[i].user, floorRequestID, 2);
    if(frqInfo != NULL) {
        if(list_frqInfo != NULL)
            bfcp_add_floor_request_information_list(list_frqInfo, frqInfo, NULL);
        else
            list_frqInfo = frqInfo;
    }

    arguments->frqInfo = list_frqInfo;

    message = bfcp_build_message(arguments);
    if(!message) {
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    bfcp_mutex_unlock(count_mutex);
    error = sendBFCPmessage(sockfd,message);
    BFCP_SEND_CHECK_ERRORS();
    return 0;
}

/* Check if it's fine to grant a floor to an accepted request */
int BFCP_Server::check_accepted_node(st_bfcp_conference *conference, pnode queue_accepted, UINT16 floorID, char *chair_info)
{
    pfloor accepted_floor;
    pnode newnode;
    int error;
    bfcp_mutex_lock(count_mutex);
    accepted_floor = queue_accepted->floor;
    while(accepted_floor) {
        if((floorID == accepted_floor->floorID) && ((accepted_floor->status == BFCP_FLOOR_STATE_WAITING) || (accepted_floor->status == BFCP_FLOOR_STATE_ACCEPTED))) {
            /* Change state to the floor again */
            bfcp_change_state_floor(conference->floor, accepted_floor->floorID, BFCP_FLOOR_STATE_GRANTED);
            /* Set it as Granted */
            accepted_floor->status = BFCP_FLOOR_STATE_GRANTED;
            accepted_floor = accepted_floor->next;
            break;
        } else if((floorID < accepted_floor->floorID) && (accepted_floor->status == BFCP_FLOOR_STATE_GRANTED))
            accepted_floor = accepted_floor->next;
        else
            break;
    }

    if((accepted_floor == NULL) && (bfcp_all_floor_status(conference->accepted, queue_accepted->floorRequestID,BFCP_FLOOR_STATE_GRANTED) == 0)) {
        /* Extract the request node from the Accepted list */
        newnode = bfcp_extract_request(conference->accepted, queue_accepted->floorRequestID);
        if(newnode == NULL) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Now prepare to move the node to the Granted list */

        /* Change the priority of the request node to the lowest one */
        newnode->priority = BFCP_LOWEST_PRIORITY;
        /* Change the queue_position of the request node to the lowest one */
        newnode->queue_position = 0;
        /* Move the node to the Granted list */
        error = bfcp_insert_request(conference->granted, newnode, newnode->floorRequestID, chair_info);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }

        /* Prepare all floor information needed by interested users */
        error = bfcp_print_information_floor(conference, 0, 0, newnode, BFCP_GRANTED);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return -1;
        }
        bfcp_mutex_unlock(count_mutex);
        return 0;
    } else
        bfcp_mutex_unlock(count_mutex);
    return 1;
}

/* Check if it's fine to grant a floor to an accepted request (??) */
int BFCP_Server::give_free_floors_to_the_accepted_nodes(st_bfcp_conference *conference, bfcp_queue *laccepted, bfcp_list_floors *lfloors, char *chair_info) {
    if(lfloors == NULL)
        return 0;
    if(lfloors->floors == NULL)
        return 0;
    if(laccepted == NULL)
        return 0;

    int i;
    pnode queue_accepted;

    for (i = (lfloors->actual_number_floors - 1); 0 <= i; i--) {
        if(bfcp_return_state_floor(lfloors, lfloors->floors[i].floorID) < bfcp_return_number_granted_floor(lfloors, lfloors->floors[i].floorID)) {
            queue_accepted = laccepted->tail;
            while(queue_accepted) {
                if(check_accepted_node(conference, queue_accepted, lfloors->floors[i].floorID, chair_info) == 1)
                    queue_accepted = queue_accepted->prev;
            }
        }
    }

    return 0;
}

/* Setup and send an Error reply to a participant */
int BFCP_Server::bfcp_error_code(UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, const char *error_info, bfcp_unknown_m_error_details *details, BFCP_SOCKET sockfd, int i, int transport) {
    int error;
    size_t dLen;
    bfcp_arguments *arguments = NULL;
    bfcp_message *message = NULL;
    Log(WAR,"bfcp_error_code UserID[%d] code[%d] msg[%s]",userID,code,error_info?error_info:"");
    arguments = bfcp_new_arguments();
    if(!arguments)
        return -1;

    arguments->entity = bfcp_new_entity(conferenceID, TransactionID, userID);
    arguments->primitive = e_primitive_Error;

    arguments->error = bfcp_new_error(code, NULL);
    if(!arguments->error) {
        /* An error occurred when creating a new Error Code */
        bfcp_free_error(arguments->error);
        return -1;
    }

    if(error_info != NULL) {	/* If there's error text, add it */
        dLen = strlen(error_info);
        if(dLen != 0) {
            arguments->eInfo = (char *)calloc(1, dLen*sizeof(char)+1);
            memcpy(arguments->eInfo, error_info, dLen+1);
        } else
            arguments->eInfo = NULL;
    } else
        arguments->eInfo = NULL;

    message = bfcp_build_message(arguments);
    if(!message) {
        return -1;
    }
    error = sendBFCPmessage(sockfd, message);
    BFCP_SEND_CHECK_ERRORS();
    return 0;
}

/* incoming connections and messages */
bool BFCP_Server::bfcp_received_msg(bfcp_received_message *recv_msg, BFCP_SOCKET sockfd) 
{
    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};
    int error = 0 ;
    if (recv_msg != NULL)
    {
        bfcp_received_message_error* errors;
        bfcp_unknown_m_error_details *error_detail_list;
        bfcp_floor_id_list *parse_floor;
        // bfcp_floor_request_status *parse_floor_id;
        UINT32 conferenceID = recv_msg->entity->conferenceID;
        UINT16 userID = recv_msg->entity->userID;
        UINT16 transactionID = recv_msg->entity->transactionID;
        s_bfcp_msg_event evt ;
        memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
	
	evt.transport 	  = recv_msg->transport;
        evt.Event         = (e_bfcp_primitives)recv_msg->primitive ;
        evt.TransactionID = transactionID ;
        evt.userID        = userID ;
        evt.conferenceID  = conferenceID ;
        evt.sockfd        =  sockfd ;
        if (recv_msg->errors != NULL) 
	{
            errors = recv_msg->errors;
            switch(errors->code)
	    {
		case BFCP_UNKNOWN_PRIMITIVE:
                    Log(INF,"Error: UNKNOWN_PRIMITIVE  [%i]", recv_msg->primitive);
                    sprintf(errortext, "Unknown primitive %i", recv_msg->primitive);
                    bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, recv_msg->entity->transactionID, BFCP_UNKNOWN_PRIMITIVE, errortext, NULL, 
		                    sockfd, 0, recv_msg->transport);
                    break;
		
                case BFCP_UNKNOWN_MANDATORY_ATTRIBUTE:
                    Log(INF,"Error:UNKNOWN_MANDATORY_ATTRIBUTE");
                    error_detail_list = bfcp_new_unknown_m_error_details_list(errors->attribute, 0);
                    errors = errors->next;
                    while(errors) 
		    {
                        if(errors->code == BFCP_UNKNOWN_MANDATORY_ATTRIBUTE)
                            error = bfcp_add_unknown_m_error_details_list(error_detail_list, errors->attribute, 0);
                        if(error == -1) break;
                        errors = errors->next;
                    }
                    if (error != -1)
                    bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, recv_msg->entity->transactionID, BFCP_UNKNOWN_MANDATORY_ATTRIBUTE, 
				    "Unknown Mandatory Attributes in the header", error_detail_list, sockfd,0, recv_msg->transport);
                    break;
		
	        case BFCP_CONFERENCE_DOES_NOT_EXIST:
		    Log(INF,"Error: UNKNOWN_CONFERENCE %u", recv_msg->entity->conferenceID);
		    break;
		
		case BFCP_WRONG_LENGTH:
		    bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, recv_msg->entity->transactionID, BFCP_UNKNOWN_MANDATORY_ATTRIBUTE, 
				    "Incorrect message length specified", NULL, sockfd,0, recv_msg->transport);
		    break;
		  
		
                default:
                    Log(INF,"Error: code[%d]",errors->code);
                    break;
            }
            //evt.Error_codes = (e_bfcp_error_codes)errors->code ;
            //BFCPFSM_FsmEvent( &evt );
        } 
	else
	{
            /* Check the primitive in the message and do what's needed */
            switch(recv_msg->primitive)
	    {
            case e_primitive_Hello:
                Log(INF,"On Socket {%d] Hello:", sockfd);
                if(recv_msg->entity != NULL) {
                    evt.TransactionID = recv_msg->entity->transactionID ;
                    evt.userID        = recv_msg->entity->userID ;
                    evt.conferenceID  = recv_msg->entity->conferenceID ;
                    Log(INF,"TransactionID: %d", evt.TransactionID);
                    Log(INF,"UserID         %d", evt.userID);
                    Log(INF,"ConferenceID:  %d",evt.conferenceID);
                }
                BFCPFSM_FsmEvent( &evt );
                break;
            case e_primitive_ChairAction:
                Log(INF, "ChairAction");
                Log(INF,"TransactionID: %d", transactionID);
                Log(INF,"UserID         %d", userID);
                Log(INF,"ConferenceID:  %d", conferenceID);
                BFCPFSM_FsmEvent( &evt );
#if 0

                if(recv_msg->entity != NULL) {
                    if(recv_msg->arguments != NULL) {
                        if(recv_msg->arguments->frqInfo != NULL) {
                            if(recv_msg->arguments->frqInfo->oRS != NULL) {
                                if(recv_msg->arguments->frqInfo->fRS != NULL) {
                                    parse_floor_id=recv_msg->arguments->frqInfo->fRS;
                                    if(parse_floor_id != NULL) {
                                        Log(INF,"FloorID:       %d", parse_floor_id->fID );
                                        list_floor = create_floor_list(parse_floor_id->fID, BFCP_FLOOR_STATE_WAITING, parse_floor_id->sInfo);
                                        parse_floor_id = parse_floor_id->next;
                                        while(parse_floor_id != NULL) {
                                            list_floor = add_floor_list(list_floor, parse_floor_id->fID, 0, parse_floor_id->sInfo);
                                            parse_floor_id = parse_floor_id->next;
                                        }
                                        error = bfcp_ChairAction_server(m_struct_server, recv_msg->entity->conferenceID, list_floor, recv_msg->entity->userID, recv_msg->arguments->frqInfo->frqID, recv_msg->arguments->frqInfo->oRS->rs->rs, recv_msg->arguments->frqInfo->oRS->sInfo, 0,recv_msg->entity->transactionID, sockfd, 0);
                                        if(error == -1) {
                                            remove_floor_list(list_floor);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
#endif
                break;
            case e_primitive_FloorQuery:
                Log(INF,"On Socket %d FloorQuery", sockfd);
                //BFCPFSM_FsmEvent( &evt );
                if (recv_msg->entity != NULL)
		{
		    pfloor list_floor = NULL;
		    
                    if (recv_msg->arguments != NULL && recv_msg->arguments->fID != NULL) 
		    {
                        parse_floor = recv_msg->arguments->fID;
                        if (parse_floor != NULL) 
			{
                                Log(INF,"FloorID:       %d", parse_floor->ID );
                                list_floor = create_floor_list(parse_floor->ID, BFCP_FLOOR_STATE_WAITING, NULL);
                                parse_floor = parse_floor->next;
                                while (parse_floor != NULL)
				{
                                    list_floor = add_floor_list(list_floor, parse_floor->ID, BFCP_FLOOR_STATE_WAITING, NULL);
                                    parse_floor = parse_floor->next;
                                }
                        }
                    }
		    
		    error = bfcp_floorquery_server(m_struct_server, recv_msg->entity->conferenceID, list_floor, recv_msg->entity->userID, recv_msg->entity->transactionID, sockfd, 0, recv_msg->transport);
                    if (error == -1 && list_floor != NULL) remove_floor_list(list_floor);
                }
                break;

            case e_primitive_UserQuery:
                Log(INF,"UserQuery: NOT SUPPORTED");
                Log(INF,"TransactionID: %d", transactionID);
                Log(INF,"UserID         %d", userID);
                Log(INF,"ConferenceID:  %d", conferenceID);
                BFCPFSM_FsmEvent( &evt );
#if 0

                if(recv_msg->entity != NULL) {
                    if(recv_msg->arguments != NULL)
                        error = bfcp_userquery_server(m_struct_server, recv_msg->entity->conferenceID, recv_msg->entity->userID, recv_msg->entity->transactionID, recv_msg->arguments->bID, sockfd, 0);
                }
#endif
                break;
            case e_primitive_FloorRequestQuery:
                Log(INF,"FloorRequestQuery: NOT SUPPORTED");
                Log(INF,"TransactionID: %d", transactionID);
                Log(INF,"UserID         %d", userID);
                Log(INF,"ConferenceID:  %d", conferenceID);

                BFCPFSM_FsmEvent( &evt );
#if 0

                if(recv_msg->entity != NULL) 
		{
                    if(recv_msg->arguments != NULL && recv_msg->arguments->frqID != 0) 
		    {
                        Log(INF,"FloorID:       %d", recv_msg->arguments->frqID);
                        error = bfcp_floorrequestquery_server(m_struct_server, recv_msg->entity->conferenceID, recv_msg->entity->transactionID, recv_msg->arguments->frqID, recv_msg->entity->userID, sockfd, 0);
                    }
		    else
		    {
			Log(ERR, "FloorRequest does not specify any floor.");
			bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, 
				recv_msg->entity->transactionID, BFCP_INVALID_FLOORID, "No floor id specified for FloorRequestQuery", NULL, sockfd, 0,
				recv_msg->transport);
		    }
                }
#endif
                break;
            case e_primitive_FloorRelease:
                if(recv_msg->entity != NULL) 
		{
                    evt.TransactionID = recv_msg->entity->transactionID ;
                    evt.userID        = recv_msg->entity->userID ;
                    evt.conferenceID  = recv_msg->entity->conferenceID ;
                    if (recv_msg->arguments != NULL && recv_msg->arguments->frqID != 0) 
		    {
                        evt.FloorRequestID = recv_msg->arguments->frqID ;
                        Log(INF,"FloorRelease: FloorRequestID [%d]", recv_msg->arguments->frqID );
                        BFCPFSM_FsmEvent( &evt );
                    }
		    else
		    {
			Log(ERR, "FloorRelease: no floor request ID specified");
			bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, 
				recv_msg->entity->transactionID, BFCP_INVALID_FLOORID, "No floor id specified for FloorRelease", NULL, sockfd, 0,
				recv_msg->transport);
		    }
                }
                break;

            case e_primitive_FloorRequest:
                Log(INF,"On socket [%d] FloorRequest:", sockfd);
                if(recv_msg->entity != NULL) 
		{
                    evt.TransactionID = recv_msg->entity->transactionID ;
                    evt.userID        = recv_msg->entity->userID ;
                    evt.conferenceID  = recv_msg->entity->conferenceID ;
                    Log(INF,"TransactionID: %d", evt.TransactionID);
                    Log(INF,"UserID         %d", evt.userID);
                    Log (INF,"ConferenceID:  %d",evt.conferenceID);
                    if (recv_msg->arguments != NULL && recv_msg->arguments->fID != NULL) 
		    {
			pnode node;
                            //Log(INF,"DEBUG FloorRequest: fID[0x%p]",recv_msg->arguments->fID );
                        parse_floor = recv_msg->arguments->fID;
                            
                                
                        evt.FloorID = parse_floor->ID ;
                        evt.BeneficiaryID = recv_msg->arguments->bID ;
                        evt.Priority = (e_bfcp_priority)recv_msg->arguments->priority ;
                        Log(INF,"FloorID       : %d", parse_floor->ID );
                        Log(INF,"Beneficiary ID: %d",recv_msg->arguments->bID );
                        Log(INF,"Priority      : %d",recv_msg->arguments->priority );
                        Log(INF,"Info          : %s",recv_msg->arguments->pInfo?recv_msg->arguments->pInfo:"" );
			
                        node = bfcp_init_request(recv_msg->entity->userID, recv_msg->arguments->bID, recv_msg->arguments->priority, recv_msg->arguments->pInfo, parse_floor->ID);
                        parse_floor = parse_floor->next;
                        while (parse_floor != NULL)
			{
                            Log(INF,"FloorID next:       %d", parse_floor->ID );
                            error = bfcp_add_floor_to_request(node, parse_floor->ID);
                            if (error != 0) break;
                            parse_floor = parse_floor->next;
                        }
			
                        evt.pt_param = (void*)&node ;
                        BFCPFSM_FsmEvent( &evt );
                    }
		    else
		    {
			Log(ERR, "FloorRequest does not specify any floor.");
			bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, 
				recv_msg->entity->transactionID, BFCP_INVALID_FLOORID, "No floor id specified for FloorRequest", NULL, sockfd, 0,
				recv_msg->transport);
		    }
                }
                break;

	    case e_primitive_Goodbye:
                if(recv_msg->entity != NULL) 
		{
		     OnGoodBye(recv_msg->entity->conferenceID, recv_msg->entity->userID, recv_msg->entity->transactionID, 
			       sockfd, recv_msg->transport);
		}
		break;
	    
	    case e_primitive_GoodbyeAck:
	    case e_primitive_HelloAck:
	    case e_primitive_FloorRequestStatusAck:
	    case e_primitive_FloorStatusAck:
	    case e_primitive_ErrorAck:
		break;

	    case e_primitive_Cisco90:
	    case e_primitive_Cisco91:
	    case e_primitive_Cisco92:
	    case e_primitive_Cisco93:
	    case e_primitive_Cisco94:
	    case e_primitive_Cisco95:
		Log(INF,"CISCO promitive: [%d]", recv_msg->primitive);
		sprintf(errortext, "CISCO primitive %i", recv_msg->primitive);
	        bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, 
				recv_msg->entity->transactionID, BFCP_UNKNOWN_PRIMITIVE, errortext, NULL, sockfd, 0,
				recv_msg->transport);
		break;
		
            default:
                Log(INF,"Unknown primitive:[%d]",recv_msg->primitive);
                Log(INF,"TransactionID: %d", transactionID);
                Log(INF,"UserID         %d", userID);
                Log(INF,"ConferenceID:  %d", conferenceID);

                sprintf(errortext, "Unknown primitive %i", recv_msg->primitive);
                bfcp_error_code(recv_msg->entity->conferenceID, recv_msg->entity->userID, 
				recv_msg->entity->transactionID, BFCP_UNKNOWN_PRIMITIVE, errortext, NULL, sockfd, 0,
				recv_msg->transport);
                break;
            }
        }
    }

    if(recv_msg != NULL)
        bfcp_free_received_message(recv_msg);
    return ( error==0 );
}


void BFCP_Server::DumpServer() {
    bfcp_list_floors *list_floor = NULL;
    bfcp_list_users *list_user = NULL;
    bfcp_user *user = NULL;
    floor_query *query = NULL;
    st_bfcp_server* server = m_struct_server ;

    for(int i = 0; i < server->Actual_number_conference; i++) {
        Log(INF,"CONFERENCE:");
        Log(INF,"ConferenceID: %d", server->list_conferences[i].conferenceID);
        /* Print the list of floors */
        list_floor = server->list_conferences[i].floor;
        if(list_floor != NULL) {
            Log(INF,"Maximum number of floors in the conference: %i", list_floor->number_floors + 1);
            Log(INF,"FLOORS");
            for(int j = 0; j < list_floor->actual_number_floors; j++) {
                Log(INF,"FloorID: %u ", list_floor->floors[j].floorID);
                Log(INF,"ChairID: %u", list_floor->floors[j].chairID);
                if(list_floor->floors[j].floorState == BFCP_FLOOR_STATE_WAITING)
                    Log(INF," state: FREE");
                else if(list_floor->floors[j].floorState == BFCP_FLOOR_STATE_ACCEPTED)
                    Log(INF," state: ACCEPTED");
                else if(list_floor->floors[j].floorState >= BFCP_FLOOR_STATE_GRANTED)
                    Log(INF," state: GRANTED");
                else
                    Log(INF," state: error!");
                Log(INF,"Number of simultaneous granted users:% i", list_floor->floors[j].limit_granted_floor-1);
                query = list_floor->floors[j].floorquery;
                if(query != NULL)
                    Log(INF,"QUERY LIST");
                while(query) {
                    Log(INF,"User: %u",query->userID);
                    query = query->next;
                }
            }
        }
        /* Print the list of users */
        list_user = server->list_conferences[i].user;
        if(list_user != NULL) {
            user = list_user->users;
            Log(INF,"Maximum number of request per floors in the conference: %i", list_user->max_number_floor_request);
            Log(INF,"USERS");
            while(user) {
                Log(INF,"UserID: %hu", user->userID);
                user = user->next;
            }
        }
        /* Print the list of Pending requests */
        print_requests_list(server, i, BFCP_PENDING);
        /* Print the list of Accepted requests */
        print_requests_list(server, i, BFCP_ACCEPTED);
        /* Print the list of Granted requests */
        print_requests_list(server, i, BFCP_GRANTED);
    }
}

void BFCP_Server::print_requests_list(st_bfcp_server* server, int index, e_bfcp_status status) {
    if(!server)
        return;

    bfcp_queue *list = NULL;
    bfcp_node *node = NULL;
    floor_request_query *query_floorrequest = NULL;

    switch(status) {
    case BFCP_PENDING:
        list = server->list_conferences[index].pending;
        break;
    case BFCP_ACCEPTED:
        list = server->list_conferences[index].accepted;
        break;
    case BFCP_GRANTED:
        list = server->list_conferences[index].granted;
        break;
    default:
        break;
    }

    bfcp_floor *FloorID = NULL;

    if(list != NULL) {
        node = list->head;
        if(node)
            Log(INF,"%s LIST  head[0x%p] tail[0x%p] ", getBfcpStatus(status),list->head,list->tail);
        while(node != NULL) {
            Log(INF,"FloorRequestID:[%u] UserID[%u] Priority[%i] Queue_position:[%u] ", node->floorRequestID, node->userID, node->priority, node->queue_position);
            if(node->beneficiaryID != 0)
                Log(INF,"BeneficiaryID:[%u]", node->beneficiaryID);
            FloorID = node->floor;
            while(FloorID) {
                Log(INF,"FloorID: %hu ", FloorID->floorID);
                if(FloorID->chair_info != NULL)
                    Log(INF,"Chair-provided information: %s ", FloorID->chair_info);
                if(FloorID->status == BFCP_FLOOR_STATE_WAITING)
                    Log(INF," state: FREE");
                else if(FloorID->status == BFCP_FLOOR_STATE_ACCEPTED)
                    Log(INF," state: ACCEPTED");
                else if(FloorID->status >= BFCP_FLOOR_STATE_GRANTED)
                    Log(INF," state: GRANTED");
                else
                    Log(INF," state: error!");
                FloorID = FloorID->next;
            }
            query_floorrequest = node->floorrequest;
            while(query_floorrequest) {
                Log(INF,"FloorRequest query by userID: %hu", query_floorrequest->userID);
                query_floorrequest = query_floorrequest->next;
            }
            node = node->next;
            Log(INF,"-----------------");
        }
    }
}

bool BFCP_Server::BFCPFSM_UpdatesBfcpFsmEvent( s_bfcp_msg_event* p_bfcp_evt , e_BFCP_ACT p_evt , e_BFCP_ACT p_st )
{
    Log(INF,_T("BFCPFSM_UpdatesBfcpFsmEvent current  event[%s]  state[%s]"), getBfcpFsmAct(p_evt), getBfcpFsmAct(p_st) );
    st_BFCP_fsm_event bfcpFsmEvt;
    
    bool Status = true ;
    switch ( p_evt ) 
    {
    case BFCP_ACT_UNDEFINED :
        break ;
    case BFCP_ACT_INITIALIZED  :
        break ;
    case BFCP_ACT_DISCONNECTED  :
        Status = true ;
        break ;
    case BFCP_ACT_CONNECTED :
        Status = true ;
        break ;
    case BFCP_ACT_FloorRequest :
        Status = true ;
        break ;
    case BFCP_ACT_FloorRelease  :
        Status = true ;
        break ;
    case BFCP_ACT_FloorRequestQuery :
        break ;
    case BFCP_ACT_UserQuery  :
        break ;
    case BFCP_ACT_FloorQuery  :
        break ;
    case BFCP_ACT_ChairAction  :
        break ;
    case BFCP_ACT_Hello :
        break ;
    case BFCP_ACT_Error :
        Status = true ;
        break ;
    case BFCP_ACT_FloorRequestStatusAccepted :
        break ;
    case BFCP_ACT_FloorRequestStatusAborted :
        break ;
    case BFCP_ACT_FloorRequestStatusGranted  :
        break ;
    case BFCP_ACT_UserStatus :
        break ;
    case BFCP_ACT_FloorStatusAccepted :
        break ;
    case BFCP_ACT_FloorStatusAborted :
        break ;
    case BFCP_ACT_FloorStatusGranted  :
        break ;
    case BFCP_ACT_ChairActionAck :
        break ;
    case BFCP_ACT_HelloAck  :
        Status = true ;
        break ;
    case BFCP_ACT_SHARE :
        Status = true ;
        break ;
    case BFCP_ACT_SERVER_SHARE :
        Status = true ;
        break ;
    default :
        break ;
    }
    
    if ( Status && m_ServerEvent != NULL ) 
    {
	InitFsmEvent(&bfcpFsmEvt, p_st, p_bfcp_evt);
        if ( ! p_bfcp_evt )
	{
            bfcpFsmEvt.FloorID = m_floorID ;
            bfcpFsmEvt.conferenceID = m_confID ;
        }
        m_ServerEvent->OnBfcpServerEvent( p_evt, &bfcpFsmEvt );
    }
    return Status ;
}

bool BFCP_Server::BFCPFSM_Hello(s_bfcp_msg_event* p_evt) 
{
    bool status = false ;
    if ( p_evt )
    {	    
	if ( p_evt->transport != BFCP_OVER_UDP )
	{
	    /*
	     * for connected transport, socket are created by accept() dynamically. The BFCP Hello message is used to associated the socket to the
	     * particicpant ID
	     */
	    int tr;
	    BFCP_SOCKET s = bfcp_get_user_sockfd(m_struct_server, m_confID, p_evt->userID, &tr);
	    if ( s != INVALID_SOCKET && s != p_evt->sockfd )
	    {
		if ( IsClientActive(s) )
		{
		    /* we have already a socket. Check if some connection or data exchange is active */
		    Log(ERR,_T("BFCP_Server::BFCPFSM_Hello: participant %u is already associated with a connected/active socket [%d]. Possible security issue."),
		        p_evt->userID,s);
		    return false;
		}
		else
		{
		    Log(INF, "BFCP_Server::BFCPFSM_Hello: participant %u was associated with inactive socket [%d]. Closing it.",
		        p_evt->userID,s);
		    RemoveClient(s);
		}
	    }
	}
	
	if (bfcp_set_user_sockfd(m_struct_server, m_confID, p_evt->userID,(BFCP_SOCKET)p_evt->sockfd, p_evt->transport ) < 0)
	{
	    Log(ERR, "BFCP_Server::BFCPFSM_Hello: failed to assign sock FD [%d] to participant %u",
		p_evt->userID);
	    return false;
	}
	else
	{
	    Log(INF, "BFCP_Server::BFCPFSM_Hello: assigned sock FD [%d] to participant %u", p_evt->sockfd, p_evt->userID);
	}
	
	if ( bfcp_hello_server(m_struct_server, p_evt->conferenceID, p_evt->userID , p_evt->TransactionID , (BFCP_SOCKET)p_evt->sockfd, 0, p_evt->transport) == -1 ) 
	{
            Log(ERR,"BFCP_Server::BFCPFSM_Hello send  helloAck failed ! ");
        } 
	else 
	{
	    if (p_evt->transport == BFCP_OVER_UDP) SendHello(p_evt->userID, NULL, 0, p_evt->sockfd);
            return FsmCtrlPerform( BFCP_fsm::BFCP_ACT_HelloAck , p_evt ) ;
        }
    }
    return status ;
}

bool BFCP_Server::BFCPFSM_PrimitiveNotSupported(s_bfcp_msg_event* p_evt)
{
    bool status = false ;

    if ( !p_evt ||bfcp_error_code( p_evt->conferenceID, p_evt->userID , p_evt->TransactionID, BFCP_UNKNOWN_PRIMITIVE, (p_evt->c_param[0]!=0)? p_evt->c_param:(char*)"Primitive not supported !", NULL, (BFCP_SOCKET)p_evt->sockfd, 0, p_evt->transport) == -1 ) 
    {
        Log(ERR,"BFCPFSM_PrimitiveNotSupported send  bfcp_error_code failed ! ");
    } else {
        status = true ;
    }
    return status ;
}

bool BFCP_Server::BFCPFSM_FloorRelease(  s_bfcp_msg_event* p_evt )
{
    bool status = false ;

    if ( !p_evt || bfcp_FloorRelease_server(m_struct_server, p_evt->conferenceID, p_evt->TransactionID , p_evt->userID, p_evt->FloorRequestID,(BFCP_SOCKET)p_evt->sockfd, 0, p_evt->transport)== -1 ) {
        Log(ERR,"BFCPFSM_FloorRelease send  BFCPFSM_FloorRelease failed ! ");
    } else {
        status = true ;
    }
    return status ;
}

bool BFCP_Server::BFCPFSM_FloorRequest(  s_bfcp_msg_event* p_evt )
{
    bool status = false ;
    if ( !p_evt )
        return status ;

    st_bfcp_server *server = m_struct_server ;
    UINT32 conferenceID = p_evt->conferenceID ;
    UINT16 TransactionID = p_evt->TransactionID ;
    int y = 0 ;
    pnode newnode ;
    BFCP_SOCKET sockfd = (BFCP_SOCKET)p_evt->sockfd ;
    BFCP_SOCKET s2;
    memcpy( &newnode , p_evt->pt_param , sizeof(pnode));

    int i, position_floor, error;
    pfloor tempnode, floor;
    unsigned short floorRequestID;

    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(server, conferenceID, newnode->userID, sockfd, &s2);
    if(server->list_conferences[i].floorRequestID <= 0)
        server->list_conferences[i].floorRequestID = 1;
    floorRequestID = server->list_conferences[i].floorRequestID;

    newnode->floorRequestID = floorRequestID;

    /* A buffer to compose error text messages when needed */
    char errortext[BFCP_STRING_SIZE]={0};

    /* Check if this conference exists */
    switch (i)
    {
	case -1:
	default:
	    if (i<0)
	    {
		error = BFCP_GENERIC_ERROR;
		strcpy(errortext, "Server internal error");
	    }
	    break;
	   
	case -2:
	    error = BFCP_CONFERENCE_DOES_NOT_EXIST;
	    sprintf(errortext, "Conference %d does not exist", conferenceID);
	    break;
	   
	case -3:
	    error = BFCP_USER_DOES_NOT_EXIST;
	    sprintf(errortext, "User %d does not exist in Conference %d", newnode->userID, conferenceID);
	    break;
	    
	case -4:
	    error = BFCP_UNAUTHORIZED_OPERATION;
	    {
		Log(ERR,"User %u is associated with socket [%d] while request comes from socket [%d]", 
		    newnode->userID, s2, sockfd);
	    }
	    sprintf(errortext, "Floor request cannot be performed from this connection");
	    break;
    }
    
    if ( i < 0 ) 
    {
floor_request_report_err2:
        bfcp_error_code(conferenceID, newnode->userID, TransactionID, (e_bfcp_error_codes) error, errortext, NULL, sockfd, y, p_evt->transport);
        bfcp_mutex_unlock(count_mutex);
        return -1;
    }

    if( newnode->beneficiaryID != 0 )
    {
	/* Checks if the beneficiary user exists in the conference */
	if ( bfcp_existence_user(server->list_conferences[i].user, newnode->beneficiaryID) != 0 )
	{
	    sprintf(errortext, "No such beneficiary ID %hu in Conference %d", newnode->beneficiaryID, conferenceID);
	    error = BFCP_USER_DOES_NOT_EXIST;
	    goto floor_request_report_err2;
	}
	
	/* If this FloorRequest has a beneficiaryID, check if the user is allowed to do this operation */
	if ( newnode->userID != newnode->beneficiaryID)
	{
	    /* If this FloorRequest has a beneficiaryID, check if the user chairs the conference. Only then the user is allowed to do this operation 
	     * If the user and beneficiary ID are the same we authorize the operation
	     */

	    if ( bfcp_exist_user_as_a_chair(server->list_conferences[i].floor, newnode->userID) != 0 )
	    {
	        error = BFCP_UNAUTHORIZED_OPERATION;
	        sprintf(errortext, "Third-party FloorRequests only allowed for chairs (User %d is not chair of any floor)", newnode->userID);
	        goto floor_request_report_err2;
	    }
	}
    }

    /* Check if all the floors exist in the conference, otherwise send an error */
    if( newnode->floor != NULL)
    {
        for(tempnode = newnode->floor; tempnode; tempnode = tempnode->next) 
	{
            position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
            if(position_floor == -1)
	    {
                sprintf(errortext, "Floor %hu does not exist in Conference %d", tempnode->floorID, conferenceID);
		error = BFCP_INVALID_FLOORID;
		goto floor_request_report_err2;
            }
        }
    }
    else 
    {
        sprintf(errortext, "There are no floors in Conference %d", conferenceID);
	error = BFCP_INVALID_FLOORID;
	goto floor_request_report_err2;
    }

    /* Checks in which position each floor is, and add the request to the user's list */
    position_floor = 0;
    for(tempnode = newnode->floor; tempnode; tempnode = tempnode->next) {
        position_floor = bfcp_return_position_floor(server->list_conferences[i].floor, tempnode->floorID);
        if(position_floor != -1) {
            /* If the floor(s) is/are for a beneficiary, add the request to the beneficiary's list */
            if(newnode->beneficiaryID != 0)
                error = bfcp_add_user_request(conferenceID, TransactionID, server->list_conferences[i].user, newnode->beneficiaryID, position_floor, sockfd, y);
            else
                error = bfcp_add_user_request(conferenceID, TransactionID, server->list_conferences[i].user, newnode->userID, position_floor, sockfd, y);
            if(error == -1) {
                /* Remove the node */
                remove_floor_list(newnode->floor);
                remove_request_list_of_node(newnode->floorrequest);
                free(newnode->participant_info);
                newnode->participant_info = NULL;
                free(newnode->chair_info);
                newnode->chair_info = NULL;
                free(newnode);
                newnode = NULL;
                bfcp_mutex_unlock(count_mutex);
                return status;
            }
        } else {
            bfcp_mutex_unlock(count_mutex);
            return status;
        }
    }

    /* Check if the floors are FREE (TODO check state) */
    floor = newnode->floor;
    while(floor != NULL) {
        if(floor->status == 1)
            floor = floor->next;
        else
            break;
    }

    /*put the node in the accept list*/
    /*change the priority of the node to the lowest one*/
    newnode->priority = BFCP_NORMAL_PRIORITY ;

    error = bfcp_insert_request(server->list_conferences[i].pending, newnode, floorRequestID, NULL);
    if(error == -1) {
        bfcp_mutex_unlock(count_mutex);
        return status;
    }

    /* Store floor request ID */
    p_evt->FloorRequestID = floorRequestID;
    
    if ( bfcp_show_requestfloor_information(m_struct_server->list_conferences[i].user, m_struct_server->list_conferences[i].pending, 
					    m_struct_server->list_conferences[i].conferenceID, p_evt->userID , p_evt->TransactionID,
					    newnode, BFCP_PENDING, p_evt->sockfd, p_evt->transport) == -1 ) 
    {
        Log(ERR,"BFCPFSM_FloorRequest send  BFCPFSM_FloorRequestStatus PENDING failed ! ");
        bfcp_mutex_unlock(count_mutex);
        return status;
    }
    else {
        server->list_conferences[i].floorRequestID = server->list_conferences[i].floorRequestID + 1;

        /* The requester will constantly be notified about updates concerning his request */
        error = add_request_to_the_node(newnode, newnode->userID, sockfd, p_evt->transport);
        if(error == -1) {
            bfcp_mutex_unlock(count_mutex);
            return status;
        }
    }
    bfcp_mutex_unlock(count_mutex);
    return true;
}

bool BFCP_Server::SendHello(UINT32 p_userID, const char * remoteAddr, UINT16 remotePort, BFCP_SOCKET s, int tr )
{
    int error;
    UINT16 trID = 0;
    
    
    if ( s == INVALID_SOCKET ) 
	s = bfcp_get_user_sockfd( m_struct_server, m_confID, p_userID, &tr);

    if ( s == INVALID_SOCKET )
    {
	Log(ERR, "Cannot send Hello: client is not associated with any valid socket");
	return false;
    }
    
    bfcp_arguments *arguments = bfcp_new_arguments();
    if ( tr == BFCP_OVER_UDP)
    {
	if (remoteAddr != NULL) SetRemoteAddressAndPort(s, remoteAddr, remotePort);
	trID = m_trIdGenerator++;
	arguments->unreliable = 1;
    }
    else
    {
	arguments->unreliable = 0;
    }
        
    arguments->entity = bfcp_new_entity(m_confID, trID, p_userID);
    arguments->primitive = e_primitive_Hello;

    /* Create a list of all the primitives the FCS supports */
    arguments->primitives = bfcp_new_supported_list(e_primitive_FloorRequest,
                           e_primitive_FloorRelease,
                           /* e_primitive_FloorRequestQuery,
                           e_primitive_FloorRequestStatus,
                           e_primitive_UserQuery,
                           e_primitive_UserStatus,
			   */
                           e_primitive_FloorQuery,
                           /*
                           e_primitive_ChairAction,
                           e_primitive_ChairActionAck,*/
			   e_primitive_FloorStatus,
                           e_primitive_Hello,
                           e_primitive_HelloAck,
			   e_primitive_Goodbye,
			   e_primitive_GoodbyeAck,
                           e_primitive_Error, 0);

    /* Create a list of all the attributes the FCS supports */
    arguments->attributes= bfcp_new_supported_list(BENEFICIARY_ID,
                           FLOOR_ID,
                           FLOOR_REQUEST_ID,
                           PRIORITY,
                           REQUEST_STATUS,
                           ERROR_CODE,
                           ERROR_INFO,
                           PARTICIPANT_PROVIDED_INFO,
                           STATUS_INFO,
                           SUPPORTED_ATTRIBUTES,
                           SUPPORTED_PRIMITIVES,
                           USER_DISPLAY_NAME,
                           USER_URI,
                           BENEFICIARY_INFORMATION,
                           FLOOR_REQUEST_INFORMATION,
                           REQUESTED_BY_INFORMATION,
                           FLOOR_REQUEST_STATUS,
                           OVERALL_REQUEST_STATUS,
                           NONCE,
                           DIGEST, 0);

    bfcp_message * message = bfcp_build_message(arguments);
    if (!message) 
    {
	Log(ERR,"BFCPServer: Failed to build Hello message");
        return false;
    }

    
    Log(INF,"BFCPServer: sending Hello to socket [%d]", s);
    error = sendBFCPmessage(s, message);
    
    BFCP_SEND_CHECK_ERRORS();
    if ( error < 0 )
       Log(INF,"BFCPServer: failed to send Hello. err %d on sockfd [%d]", error, s);
    return error >= 0;
}

bool BFCP_Server::FloorRequestRespons(UINT32 p_userID,  UINT32 p_beneficiaryID , UINT16 p_TransactionID , UINT16 p_floorRequestID , e_bfcp_status p_bfcp_status , UINT16 p_queue_position,  e_bfcp_priority p_priority, bool p_InformALL )
{
    bfcp_floor *list_floors = create_floor_list(m_floorID, BFCP_FLOOR_STATE_WAITING, NULL );
    bool Status = true;
    
   
    bfcp_mutex_lock(count_mutex);
    
        Log(INF,"FloorRequestRespons UserId[%d] beneficiaryID[%d] TransactionID[%d] floorRequestID[%d] Status[%s] position[%d] priority[%d] informAll[%s]",
            p_userID , p_beneficiaryID , p_TransactionID , p_floorRequestID , getBfcpStatus(p_bfcp_status), p_queue_position , p_priority , p_InformALL?"true":"false" );
        int i, error, position_floor;
        pfloor next, next_floors, tempnode, free_floors, tempfloors = NULL;
        bfcp_node *newnode = NULL;
        //bfcp_floor *node = NULL;
        bfcp_queue *laccepted;
	int transport = 0;
	BFCP_SOCKET sockfd;

	/* Check if this conference exists and if user is in the conf */
	i = CheckConferenceAndUser(m_struct_server, m_confID, p_userID, -1);

        if( i < 0) 
	{
	    switch (i)
	    {
		case -2:
                    Log(ERR,"Conference %d does not exist", m_confID);
		    break;
		    
		case -3:
		    Log(ERR, "User %hu does not exist in Conference %d", p_userID, m_confID);
		    break;
		    
		default:
		    Log(ERR, "Internal error %i", i);
		    break;
	    }
            Status = false ;
        }

        if ( Status ) {
            /* Check if all the floors exist in the conference, otherwise send an error */
            for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
                position_floor = bfcp_return_position_floor(m_struct_server->list_conferences[i].floor, tempnode->floorID);
                if(position_floor == -1) {
                    Log(ERR, "Floor %hu does not exist in Conference %d", tempnode->floorID, m_confID);
                    Status = false ;
                }
            }
        }

	sockfd = bfcp_get_user_socket(m_struct_server->list_conferences[i].user, p_userID, &transport );
	if ( sockfd == INVALID_SOCKET )
	{
	    Status = false;	
	    Log(ERR, "Failed to retreive sockfd asociated with user ID %d.", p_userID);
	}
	
        if ( Status ) {
            switch ( p_bfcp_status )
	    {
                case BFCP_ACCEPTED:
		{
                    /* The chair accepted a request */
                    /* First check if the request node is in the Pending list */
                    if ( bfcp_give_user_of_request(m_struct_server->list_conferences[i].pending, p_floorRequestID) == 0)
		    {
                        Log(ERR, "Pending FloorRequest %d does not exist in Conference %d", p_floorRequestID, m_confID);
                        Status = false ;
                    }
		    else
		    {
                        /* Check if the floors involved in the accepted request exist */
                        for(tempnode = list_floors; tempnode != NULL; tempnode = tempnode->next) {
                            if(bfcp_change_status(m_struct_server->list_conferences[i].pending, tempnode->floorID, p_floorRequestID, BFCP_FLOOR_STATE_ACCEPTED, tempnode->chair_info) != 0) {
                                Log(ERR, "Floor %hu does not exist in Conference %d", tempnode->floorID, m_confID);
                                Status = false ;
                            }
                            if(bfcp_change_state_floor(m_struct_server->list_conferences[i].floor, tempnode->floorID, BFCP_FLOOR_STATE_ACCEPTED ) == -1) {
                                Log(ERR, "bfcp_change_state_floor Conference %d failed " ,m_confID);
                                Status = false ;
                            }
                        }
                    }

                    if ( Status ) {
                        /* Set the queue_position value if it is needed */
                        bfcp_change_queue_position(m_struct_server->list_conferences[i].pending, p_floorRequestID, p_queue_position);

                        /* If all the floors in the request have been accepted... */
                        if(bfcp_all_floor_status(m_struct_server->list_conferences[i].pending, p_floorRequestID, BFCP_FLOOR_STATE_ACCEPTED) == 0) {
                            /* Extract the request node from the Pending list */
                            newnode = bfcp_extract_request(m_struct_server->list_conferences[i].pending, p_floorRequestID);
                            /* Move the node to the Accepted list */
                            newnode->priority = p_priority;
                            if ( p_beneficiaryID && !newnode->beneficiaryID )
                                newnode->beneficiaryID = p_beneficiaryID ;
                            error = bfcp_insert_request(m_struct_server->list_conferences[i].accepted, newnode, p_floorRequestID, NULL);
                            if(error == -1) {
                                Log(ERR, "bfcp_insert_request falied ");
                                Status = false ;
                            } else {
                                /* Send FloorRequestStatus */

                                if ( bfcp_show_requestfloor_information(m_struct_server->list_conferences[i].user, m_struct_server->list_conferences[i].accepted,
									m_struct_server->list_conferences[i].conferenceID, p_userID, p_TransactionID, 
									newnode, p_bfcp_status, sockfd, transport) == -1 ) 
				{
                                    Log(ERR,"Send  BFCPFSM_FloorRequestStatus ACCPETED failed ! ");
                                    Status = false ;
                                }
                                if ( p_InformALL )
				{
                                    Status = FloorStatusRespons(p_userID , p_TransactionID , p_floorRequestID ,newnode, p_InformALL );
                                }
                            }
                        } else {
                            Log(ERR, "Floor not in the valid state. ");
                            Status = false ;
                        }
                    }
                }
                break ;
            case BFCP_GRANTED: {
                    /* The chair accepted a request */
                    /* First check if the request node is in the Pending list */
                    if(bfcp_give_user_of_request(m_struct_server->list_conferences[i].accepted, p_floorRequestID) == 0) {
                        Log(ERR, "Pending FloorRequest %d does not exist in Conference %d", p_floorRequestID, m_confID);
                        Status = false ;
                    } else {
                        /* Check if the floors involved in the accepted request exist */
                        for(tempnode = list_floors; tempnode != NULL; tempnode = tempnode->next) {
                            if(bfcp_change_status(m_struct_server->list_conferences[i].accepted, tempnode->floorID, p_floorRequestID, BFCP_FLOOR_STATE_GRANTED, tempnode->chair_info) != 0) {
                                Log(ERR, "Floor %hu does not exist in Conference %d", tempnode->floorID, m_confID);
                                Status = false ;
                            }
                            if(bfcp_change_state_floor(m_struct_server->list_conferences[i].floor, tempnode->floorID, BFCP_FLOOR_STATE_GRANTED ) == -1) {
                                Log(ERR, "bfcp_change_state_floor Conference %d failed " ,m_confID);
                                Status = false ;
                            }
                        }
                    }

                    if ( Status ) {
                        /* If all the floors in the request have been accepted... */
                        if(bfcp_all_floor_status(m_struct_server->list_conferences[i].accepted, p_floorRequestID, BFCP_FLOOR_STATE_GRANTED) == 0) {
                            /* Extract the request node from the Pending list */
                            newnode = bfcp_extract_request(m_struct_server->list_conferences[i].accepted, p_floorRequestID);
                            if ( newnode ) {
                                /* Move the node to the Accepted list */
                                newnode->priority = p_priority;
                                if ( p_beneficiaryID && !newnode->beneficiaryID  )
                                    newnode->beneficiaryID = p_beneficiaryID ;
                                error = bfcp_insert_request(m_struct_server->list_conferences[i].granted, newnode, p_floorRequestID, NULL);
                                if(error == -1) {
                                    Log(ERR, "bfcp_insert_request falied ");
                                    Status = false ;
                                }
				else
				{
                                    /* TODO Prepare all floor information needed by interested users */
                                    /* Send FloorRequestStatus */				    
                                    if ( bfcp_show_requestfloor_information(m_struct_server->list_conferences[i].user, m_struct_server->list_conferences[i].granted,
									    m_struct_server->list_conferences[i].conferenceID, p_userID, p_TransactionID,
									    newnode, p_bfcp_status, sockfd, transport) == -1 )
				    {
                                        Log(ERR,"Send  BFCPFSM_FloorRequestStatus GRANTED failed ! ");
                                        Status = false ;
                                    }
                                    if ( p_InformALL ) {
                                        Status = FloorStatusRespons(p_userID , p_TransactionID , p_floorRequestID  ,newnode, p_InformALL );
                                    }
                                }
                            } else {
                                Log(ERR, "request not found ");
                            }
                        } else {
                            Log(ERR, "Floor not in the valid state. ");
                            Status = false ;
                        }
                    }
                }
                break ;
            case  BFCP_DENIED: {
                    /* The chair denied a pending request */
                    /* Extract the request node from the Pending list */
                    newnode = bfcp_extract_request(m_struct_server->list_conferences[i].pending, p_floorRequestID);
                    if(newnode == NULL) {
                        Log(ERR, "Pending FloorRequest %d does not exist in Conference %d", p_floorRequestID, m_confID);
                        Status = false ;
                    } else {
                        if ( p_beneficiaryID && !newnode->beneficiaryID  )
                            newnode->beneficiaryID = p_beneficiaryID ;

                        /* Prepare all floor information needed by interested users */
                        if ( bfcp_show_requestfloor_information(m_struct_server->list_conferences[i].user, m_struct_server->list_conferences[i].granted,
								m_struct_server->list_conferences[i].conferenceID, p_userID , p_TransactionID,
								newnode, p_bfcp_status, sockfd, transport) == -1 ) 
			{
                            Log(ERR,"Send  BFCPFSM_FloorRequestStatus DENIED failed ! ");
                            Status = false ;
                        }
                        if ( p_InformALL )
			{
                            Status = FloorStatusRespons(p_userID , p_TransactionID , p_floorRequestID  ,newnode, p_InformALL );
                        }
                        /* Remove the request node from the Pending list */
                        if(newnode != NULL) {
                            remove_floor_list(newnode->floor);
                            remove_request_list_of_node(newnode->floorrequest);
                            free(newnode->participant_info);
                            newnode->participant_info = NULL;
                            free(newnode->chair_info);
                            newnode->chair_info = NULL;
                            free(newnode);
                            newnode = NULL;
                        }

                    }
                }
                break ;
            case BFCP_CANCELLED:
            case BFCP_RELEASED:
            case BFCP_REVOKED: {
                    /* The chair revoked a previously granted request */
                    /* Extract the request node from the Granted list */
                    bool foundOnAcceptList = false ;
                    newnode = bfcp_extract_request(m_struct_server->list_conferences[i].granted, p_floorRequestID);
                    if(newnode == NULL) {
                        foundOnAcceptList = true ;
                        newnode = bfcp_extract_request(m_struct_server->list_conferences[i].accepted, p_floorRequestID);
                        if(newnode == NULL) {
                            Log(ERR, "Granted FloorRequest %d does not exist in Conference %d", p_floorRequestID, m_confID);
                            Status = false ;
                        }
                    }
                    if(newnode != NULL) {
                        if ( p_beneficiaryID && !newnode->beneficiaryID  )
                            newnode->beneficiaryID = p_beneficiaryID ;
                        /* all floor information needed by interested users */
                        if ( bfcp_show_requestfloor_information(m_struct_server->list_conferences[i].user, foundOnAcceptList?m_struct_server->list_conferences[i].accepted:m_struct_server->list_conferences[i].granted,
								m_struct_server->list_conferences[i].conferenceID, p_userID , p_TransactionID,
								newnode, p_bfcp_status, sockfd, transport) == -1 )
			{
                            Log(ERR,"Send  BFCPFSM_FloorRequestStatus %s failed ! ",getBfcpStatus(p_bfcp_status));
                            Status = false ;
                        }
                        if ( p_InformALL ) {
                            Status = FloorStatusRespons(p_userID , p_TransactionID , p_floorRequestID  ,newnode, p_InformALL );
                        }
                        /* Remove the request node from the Granted list */
                        if(newnode != NULL) {
                            tempfloors = newnode->floor;
                            remove_request_list_of_node(newnode->floorrequest);
                            free(newnode->participant_info);
                            newnode->participant_info = NULL;
                            free(newnode->chair_info);
                            newnode->chair_info = NULL;
                            free(newnode);
                            newnode = NULL;
                        }

                        /* Set the state of the floors to FREE */
                        free_floors = tempfloors;
                        while(free_floors != NULL) {
                            error = bfcp_change_state_floor(m_struct_server->list_conferences[i].floor, free_floors->floorID, BFCP_FLOOR_STATE_WAITING );
                            if(error == -1) {
                                Log(ERR, "bfcp_change_state_floor Conference %d failed " ,m_confID);
                                Status = false ;
                            }
                            next = free_floors->next;
                            free(free_floors->chair_info);
                            free_floors->chair_info = NULL;
                            free(free_floors);
                            free_floors = NULL;
                            free_floors = next;
                        }


                        laccepted = m_struct_server->list_conferences[i].accepted;
                        /* if you want pass accepted -> granted */
                        /* if(give_free_floors_to_the_accepted_nodes(m_struct_server->list_conferences+i, laccepted, m_struct_server->list_conferences[i].floor, NULL) == -1) {
                            Log(ERR, "give_free_floors_to_the_accepted_nodes Conference %d failed ",m_confID);
                            Status = false ;
                        }*/
                    }
                }
                break ;
            default :
                Log(ERR, "Invalid new state ", p_bfcp_status);
                Status = false ;
            }

            /* Free the floors list */
            while(list_floors) {
                next_floors = list_floors->next;
                free(list_floors->chair_info);
                list_floors->chair_info = NULL;
                free(list_floors);
                list_floors = NULL;
                list_floors = next_floors;
            }
	}
	bfcp_mutex_unlock(count_mutex);
	return Status ;
}

bool BFCP_Server::SendGoodBye(UINT32 p_userID)
{
	BFCP_SOCKET sockfd;
	int transport;
	bfcp_message * m;
	UINT16 transID = 0;
	bool Status = true;
	
	/* Check if this conference exists and if user is in the conf */
	int i = CheckConferenceAndUser(m_struct_server, m_confID, p_userID, -1);

        if( i < 0) 
	{
	    switch (i)
	    {
		case -2:
                    Log(ERR,"Conference %d does not exist", m_confID);
		    break;
		    
		case -3:
		    Log(ERR, "User %hu does not exist in Conference %d", p_userID, m_confID);
		    break;
		    
		default:
		    Log(ERR, "Internal error %i", i);
		    break;
	    }
	    return false;
        }

	sockfd = bfcp_get_user_socket(m_struct_server->list_conferences[i].user, p_userID, &transport );
	if ( sockfd == INVALID_SOCKET )
	{
	    Status = false;	
	    Log(INF, "Cannot send GoodBye: socket of user ID %u is alread closed.", p_userID);
	    return false;
	}
	
	if (transport == BFCP_OVER_UDP) transID = m_trIdGenerator++;
	
	
	m = bfcp_build_message_Goodbye(
		bfcp_new_entity(m_confID, p_userID, transID),
		(transport == BFCP_OVER_UDP) ? 1 : 0 );
		
	if (m) return sendBFCPmessage(sockfd, m);

	return false;
}


bool BFCP_Server::AnswerGoodByeAck(UINT32 ConferenceID, UINT16 p_userID, UINT16 TransactionID, BFCP_SOCKET sockfd, int transport)
{
	bfcp_message * m;
	
	/* Check if this conference exists and if user is in the conf */
	int i = CheckConferenceAndUser(m_struct_server, m_confID, p_userID, -1);

        if( i < 0) 
	{
	    switch (i)
	    {
		case -2:
                    Log(ERR,"Conference %d does not exist", m_confID);
		    break;
		    
		case -3:
		    Log(ERR, "User %hu does not exist in Conference %d", p_userID, m_confID);
		    break;
		    
		default:
		    Log(ERR, "Internal error %i", i);
		    break;
	    }
	    return false;
        }

	
	m = bfcp_build_message_GoodbyeAck(
		bfcp_new_entity(ConferenceID, p_userID, TransactionID));
		
	if (m)
		return ( sendBFCPmessage(sockfd, m) >= 1);
	return false;
}


bool BFCP_Server::SendFloorStatus(UINT32 p_userID ,  UINT16 p_TransactionID , UINT16 p_floorRequestID  , bfcp_node *p_node ,bool p_InformALL ) {
    bool Status = false ;
    bfcp_mutex_lock(count_mutex);
    Status = FloorStatusRespons( p_userID , p_TransactionID , p_floorRequestID , p_node , p_InformALL );
    bfcp_mutex_unlock(count_mutex);
    return Status ;
}


bool BFCP_Server::FloorStatusRespons(UINT32 p_userID ,  UINT16 p_TransactionID , UINT16 p_floorRequestID  , bfcp_node *p_node ,bool p_InformALL )
{
    bfcp_floor *list_floors = create_floor_list(m_floorID, BFCP_FLOOR_STATE_WAITING, NULL );
    bool Status = true ;
    e_bfcp_status bfcp_status = BFCP_PENDING;
    
    
        Log(INF,"FloorStatusRespons UserId[%d] TransactionID[%d] floorRequestID[%d]  informAll[%s]",
            p_userID , p_TransactionID , p_floorRequestID , p_InformALL?"true":"false" );
        int actual_conference = 0 ;
        int i = 0 ;
        int position_floor = 0 ;
        pfloor   tempnode  = NULL;
        //size_t dLen = 0 ;
        actual_conference = m_struct_server->Actual_number_conference - 1;
        for(i = 0; i < actual_conference; i++) {
            if(m_struct_server->list_conferences[i].conferenceID == m_confID )
                break;
        }

        /* Check if this conference exists */
        if(m_struct_server->list_conferences[i].conferenceID != m_confID) {
            Log(ERR,"FloorStatusRespons Conference %d does not exist", m_confID);
            Status = false ;
        }

        if ( Status ) {
            /* Check if all the floors exist in the conference, otherwise send an error */
            for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
                position_floor = bfcp_return_position_floor(m_struct_server->list_conferences[i].floor, tempnode->floorID);
                if(position_floor == -1) {
                    Log(ERR, "FloorStatusRespons Floor %hu does not exist in Conference %d", tempnode->floorID, m_confID);
                    Status = false ;
                }
            }
        }

        if ( Status )
	{
            int status_floor = bfcp_return_state_floor(m_struct_server->list_conferences[i].floor , m_floorID );
            switch ( status_floor ) {
            case BFCP_FLOOR_STATE_GRANTED:
                bfcp_status = BFCP_GRANTED ;
                break ;
            case BFCP_FLOOR_STATE_ACCEPTED:
                bfcp_status = BFCP_ACCEPTED ;
                break ;
            default:
                bfcp_status = BFCP_PENDING ;
                break ;
            }
            fd_set allset ;
            FD_ZERO(&allset);
            if ( !p_InformALL && p_userID )
	    {
                if ( bfcp_show_floor_information( m_confID , p_TransactionID , p_userID , m_struct_server->list_conferences+i  , m_floorID, NULL , p_node , bfcp_status )== -1 ) {
                    Log(ERR,"FloorStatusRespons send  FloorStatus %s failed ! ",getBfcpStatus(bfcp_status));
                    Status = false ;
                }
            } else if ( p_InformALL ) {
                // floor status to list of users
                bfcp_user *user = NULL;
                bfcp_list_users *list_user = NULL;
                list_user = m_struct_server->list_conferences[i].user;
                if(list_user != NULL) {
                    user = list_user->users;
                    while(user) 
		    {
			if ( bfcp_show_floor_information( m_confID , 0 , user->userID , m_struct_server->list_conferences+i, m_floorID, NULL , p_node , bfcp_status )== -1 ) 
			{
			    Log(ERR,"FloorStatusRespons send  FloorStatus %s failed ! ",getBfcpStatus(bfcp_status));
			}
                        user = user->next;
                    }
                }
            }
        }
    
    return Status ;
}

bool BFCP_Server::GetFloorState(e_bfcp_status* p_bfcp_status , UINT32* p_userID ,  UINT32* p_beneficiaryID ,  UINT16* p_floorRequestID  ) {
    bool Status = true ;
    int actual_conference = 0 ;
    int i = 0 ;

    if ( !p_bfcp_status || !p_userID || !p_beneficiaryID || !p_floorRequestID )
        return false ;

    *p_bfcp_status = BFCP_PENDING ;
    *p_userID = 0 ;
    *p_beneficiaryID = 0 ;
    *p_floorRequestID = 0 ;
    actual_conference = m_struct_server->Actual_number_conference - 1;
    for(i = 0; i < actual_conference; i++) {
        if(m_struct_server->list_conferences[i].conferenceID == m_confID )
            break;
    }
    if ( i <= actual_conference ) {
        bfcp_mutex_lock(count_mutex);
        // int status_floor = BFCP_FLOOR_STATE_WAITING ;
        pnode node = m_struct_server->list_conferences[i].granted->head ;
        if ( node ) {
            *p_userID = node->userID ;
            *p_beneficiaryID = node->beneficiaryID ;
            *p_floorRequestID = node->floorRequestID ;
            *p_bfcp_status = BFCP_GRANTED ;
        } else {
            node = m_struct_server->list_conferences[i].accepted->head ;
            if ( node) {
                *p_userID = node->userID ;
                *p_beneficiaryID = node->beneficiaryID ;
                *p_floorRequestID = node->floorRequestID ;
                *p_bfcp_status = BFCP_ACCEPTED ;
            } else {
                node = m_struct_server->list_conferences[i].pending->head ;
                if ( node) {
                    *p_userID = node->userID ;
                    *p_beneficiaryID = node->beneficiaryID ;
                    *p_floorRequestID = node->floorRequestID ;
                }
            }
        }
        bfcp_mutex_unlock(count_mutex);
        Log(INF,"GetFloorState [%s] UserID[%d] beneficiaryID[%d] floorRequestID[%d]",getBfcpStatus(*p_bfcp_status) ,*p_userID , *p_beneficiaryID ,*p_floorRequestID );
    } else {
        Status = false ;
    }
    return Status ;
}

void BFCP_Server::OnGoodBye(UINT32 ConferenceID, UINT16 userID, UINT16 TransactionID, BFCP_SOCKET p_sockfd, int transport)
{
    char errortext[BFCP_STRING_SIZE]={0};	
    e_bfcp_error_codes error;
    int i = -1;
    
    bfcp_mutex_lock(count_mutex);
    i = CheckConferenceAndUser(m_struct_server, ConferenceID, userID, p_sockfd);

    /* Check parameters */
    switch (i)
    {
	case -1:
	default:
	    if ( i < 0 )
	    {
		error = BFCP_GENERIC_ERROR;
		strcpy(errortext, "Server internal error");
	    }
	    break;
	   
	case -2:
	    error = BFCP_CONFERENCE_DOES_NOT_EXIST;
	    sprintf(errortext, "Conference %d does not exist", ConferenceID);
	    break;
	   
	case -3:
	    error = BFCP_USER_DOES_NOT_EXIST;
	    sprintf(errortext, "User %d does not exist in Conference %d", userID, ConferenceID);
	    break;
	    
	case -4:
	    error = BFCP_UNAUTHORIZED_OPERATION;
	    sprintf(errortext, "Floor request cannot be performed from this connection");
	    break;
    }

    if ( i < 0 ) 
    {
        bfcp_error_code(ConferenceID, userID, TransactionID, error, errortext, NULL, p_sockfd, 0, transport);
        bfcp_mutex_unlock(count_mutex);
        return;
    }
	
    /* Report the Goodbye event to the application */ 
    if ( m_ServerEvent )
    {
	st_BFCP_fsm_event FsmEvt;
	
	FsmEvt.State = m_bfcpFsmSt;
	FsmEvt.TransactionID  = TransactionID;
        FsmEvt.userID = userID;
        FsmEvt.conferenceID = ConferenceID ;
	
	m_ServerEvent->OnBfcpServerEvent( BFCP_ACT_GoodBye, &FsmEvt );
    }
    
    /* Send ack */
    if ( AnswerGoodByeAck(ConferenceID, userID, TransactionID, p_sockfd, transport) )
    {
	Log(INF,"GoodBye received: user is going to be removed from conference");
	bfcp_delete_user_server(m_struct_server, ConferenceID, userID);
    }
    bfcp_mutex_unlock(count_mutex);
}

void BFCP_Server::Log(const  char* pcFile, int iLine, int iErrLevel , const  char* pcFormat, ...) {
    va_list arg;
    char s[3000];
    va_start(arg,pcFormat);
    vsnprintf(s,3000,pcFormat,arg);
    va_end(arg);
#ifdef WIN32
    eConfLog(pcFile,iLine,iErrLevel,s);
#else
    printf("%s:%d | %d | %s\n",pcFile?pcFile:"" , iLine , iErrLevel , s);
#endif
}


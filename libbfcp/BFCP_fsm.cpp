#include "stdafx.h"
#include "BFCP_fsm.h"

BFCP_fsm::~BFCP_fsm(void)
{
}

void BFCP_fsm::setName(const char* p_name ){
    if ( p_name ) {
        strncpy( m_name , p_name , BFCP_STRING_SIZE ) ; 
    }
    else
        memset ( m_name , 0 , BFCP_STRING_SIZE );
}

BFCP_fsm::BFCP_fsm()
{    
    m_bfcpFsmSt = BFCP_ACT_INITIALIZED ;
    memset ( m_name , 0 , BFCP_STRING_SIZE );
        
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
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAborted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
            {BFCP_ACT_INITIALIZED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
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
            {BFCP_ACT_FloorRequest, &BFCP_fsm::BFCPFSM_FloorRequest              } , /* BFCP_ACT_FloorRequest */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAborted   */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusGranted   */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorStatusAccepted        } , /* BFCP_ACT_FloorStatusAccepted   */
            {BFCP_ACT_CONNECTED  , &BFCP_fsm::BFCPFSM_FloorStatusAborted         } , /* BFCP_ACT_FloorStatusAborted   */
            {BFCP_ACT_SERVER_SHARE, &BFCP_fsm::BFCPFSM_FloorStatusGranted        } , /* BFCP_ACT_FloorStatusGranted   */
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
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_UpdateHwnd                 } , /* BFCP_ACT_FloorRequest */
            {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_FloorRelease               } , /* BFCP_ACT_FloorRelease */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_FloorRequestStatusAccepted } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_CONNECTED     , &BFCP_fsm::BFCPFSM_FloorRequestStatusAborted  } , /* BFCP_ACT_FloorRequestStatusAborted   */
            {BFCP_ACT_SHARE         , &BFCP_fsm::BFCPFSM_FloorRequestStatusGranted  } , /* BFCP_ACT_FloorRequestStatusGranted   */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_FloorStatusAccepted        } , /* BFCP_ACT_FloorStatusAccepted   */
            {BFCP_ACT_FloorRequest  , &BFCP_fsm::BFCPFSM_FloorStatusAborted         } , /* BFCP_ACT_FloorStatusAborted   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_FloorStatusGranted         } , /* BFCP_ACT_FloorStatusGranted   */
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
            {BFCP_ACT_FloorRelease  , &BFCP_fsm::BFCPFSM_FloorRequestStatusAccepted } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_CONNECTED     , &BFCP_fsm::BFCPFSM_FloorReleaseStatusAborted  } , /* BFCP_ACT_FloorRequestStatusAborted   */
            {BFCP_ACT_CONNECTED     , &BFCP_fsm::BFCPFSM_FloorRequestStatusGranted  } , /* BFCP_ACT_FloorRequestStatusGranted   */
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
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_UpdateHwnd                 } , /* BFCP_ACT_FloorRequest */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_FloorRelease               } , /* BFCP_ACT_FloorRelease */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
            {BFCP_ACT_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_CONNECTED , &BFCP_fsm::BFCPFSM_FloorRequestStatusAborted  } , /* BFCP_ACT_FloorRequestStatusAborted   */
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
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_FloorRequest               } , /* BFCP_ACT_FloorRequest */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRelease */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorRequestQuery */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserQuery */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorQuery */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairAction  */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Hello  */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_Error  */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_FloorRequestStatusAccepted } , /* BFCP_ACT_FloorRequestStatusAccepted   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_FloorRequestStatusAborted  } , /* BFCP_ACT_FloorRequestStatusAborted   */
            {BFCP_ACT_SHARE         , &BFCP_fsm::BFCPFSM_FloorRequestStatusGranted  } , /* BFCP_ACT_FloorRequestStatusGranted   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_UserStatus   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusAccepted   */
            {BFCP_ACT_CONNECTED     , &BFCP_fsm::BFCPFSM_FloorStatusAborted         } , /* BFCP_ACT_FloorStatusAborted   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_FloorStatusGranted   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_ChairActionAck   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_HelloAck   */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               } , /* BFCP_ACT_SHARE */
            {BFCP_ACT_SERVER_SHARE  , &BFCP_fsm::BFCPFSM_NullFunction               }   /* BFCP_ACT_SERVER_SHARE */
        }
    };
    BFCPFSM_init(BFCPStateMachine);
}



void BFCP_fsm::BFCPFSM_init(st_BFCP_fsm BFCPStateMachine[BFCP_ACT_LAST][BFCP_ACT_LAST])
{
    memcpy(&m_BFCPStateMachine , BFCPStateMachine , sizeof(m_BFCPStateMachine) );
}

bool BFCP_fsm::FsmCtrlPerform(e_BFCP_ACT p_evt , s_bfcp_msg_event* p_bfcp_evt )
{
        e_BFCP_ACT new_bfcpFsmSt = m_BFCPStateMachine[m_bfcpFsmSt][p_evt].new_state ; 
        Log(INF,"FSM [%s] current state [%s] event[%s] ... perform action", m_name,
            getBfcpFsmAct(m_bfcpFsmSt) , getBfcpFsmAct(p_evt), getBfcpFsmAct(new_bfcpFsmSt) ); 
        bool Status = (*this.*m_BFCPStateMachine[m_bfcpFsmSt][p_evt].function)(p_bfcp_evt)  ; 
        if ( Status ) 
	{
	    Log(INF,"FSM [%s] action sucessful. Current state [%s] => new state [%s]",
	        getBfcpFsmAct(m_bfcpFsmSt), getBfcpFsmAct(new_bfcpFsmSt) ); 
            m_bfcpFsmSt = new_bfcpFsmSt ;
            BFCPFSM_UpdatesBfcpFsmEvent( p_bfcp_evt , p_evt , m_bfcpFsmSt );
        }
	else
	{
	     Log(INF,"FSM [%s] action NOT successful. State will not change", getBfcpFsmAct(m_bfcpFsmSt) );
	}
        return Status ;
}

bool BFCP_fsm::BFCPFSM_NullFunction( s_bfcp_msg_event* p_evt ) {
    if ( p_evt ){
      Log(WAR,_T("BFCP FSM current state[%s] Status[%s] eventFloorId[%d] => No action"),
            getBfcpFsmAct(GetFSMState()) ,
            p_evt->Status?getBfcpStatus(p_evt->Status):"" ,p_evt->FloorID  ); 
     }else{
         Log(WAR,_T("BFCP FSM current state[%s] received NULL event => No action"), getBfcpFsmAct(GetFSMState()) );
     }
    return false ;
}


bool BFCP_fsm::BFCPFSM_FsmEvent( s_bfcp_msg_event* p_bfcpEvent ){
    bool status = false ;
    if ( !p_bfcpEvent )
        return status  ;
    Log(INF,_T("BFCPFSM_FsmEvent [%d / %s] status[%s] "),
        p_bfcpEvent->Event,getBfcpDescPrimitive(p_bfcpEvent->Event),
        getBfcpStatus(p_bfcpEvent->Status));
    switch ( p_bfcpEvent->Event )
    {
    case e_primitive_FloorRequest:
        return FsmCtrlPerform(BFCP_ACT_FloorRequest,p_bfcpEvent);
        break ; 
    case e_primitive_FloorRelease:
        return FsmCtrlPerform(BFCP_ACT_FloorRelease,p_bfcpEvent);
        break ; 
    case e_primitive_FloorRequestQuery:
        return FsmCtrlPerform(BFCP_ACT_FloorRequestQuery,p_bfcpEvent);
        break ; 
    case e_primitive_FloorRequestStatus:
        switch ( p_bfcpEvent->Status )
        {
        case BFCP_PENDING:
        case BFCP_ACCEPTED:
            return FsmCtrlPerform(BFCP_ACT_FloorRequestStatusAccepted,p_bfcpEvent);
            break ;
        case BFCP_GRANTED:
            return FsmCtrlPerform(BFCP_ACT_FloorRequestStatusGranted,p_bfcpEvent);
            break ; 
        case BFCP_DENIED:
        case BFCP_CANCELLED:
        case BFCP_RELEASED:
        case BFCP_REVOKED:
            return FsmCtrlPerform(BFCP_ACT_FloorRequestStatusAborted,p_bfcpEvent);
            break ;
        default:
            Log(ERR,_T("BFCPFSM_FsmEvent unknown Event[%d] status[%d]"),p_bfcpEvent->Event,p_bfcpEvent->Status );
            return false ;
            break ;
        }
        break ; 
    case e_primitive_UserQuery:
        return FsmCtrlPerform(BFCP_ACT_UserQuery,p_bfcpEvent);
        break ; 
    case e_primitive_UserStatus:
        return FsmCtrlPerform(BFCP_ACT_UserStatus,p_bfcpEvent);
        break ; 
    case e_primitive_FloorQuery:
        return FsmCtrlPerform(BFCP_ACT_FloorQuery,p_bfcpEvent);
        break ; 
    case e_primitive_FloorStatus:
        switch ( p_bfcpEvent->Status )
        {
        case BFCP_PENDING:
        case BFCP_ACCEPTED:
            return FsmCtrlPerform(BFCP_ACT_FloorStatusAccepted,p_bfcpEvent);
            break ;
        case BFCP_GRANTED:
            return FsmCtrlPerform(BFCP_ACT_FloorStatusGranted,p_bfcpEvent);
            break ; 
        case BFCP_DENIED:
        case BFCP_CANCELLED:
        case BFCP_RELEASED:
        case BFCP_REVOKED:
            return FsmCtrlPerform(BFCP_ACT_FloorStatusAborted,p_bfcpEvent);
            break ;
        default:
            Log(ERR,_T("BFCPFSM_FsmEvent unknown Event[%d] status[%d]"),p_bfcpEvent->Event,p_bfcpEvent->Status );
            return false ;
            break ;
        }
        break ; 
    case e_primitive_ChairAction:
        return FsmCtrlPerform(BFCP_ACT_ChairAction ,p_bfcpEvent);
        break ; 
    case e_primitive_ChairActionAck:
        return FsmCtrlPerform(BFCP_ACT_ChairActionAck ,p_bfcpEvent);
        break ; 
    case e_primitive_Hello:
        return FsmCtrlPerform(BFCP_ACT_Hello ,p_bfcpEvent);
        break ; 
    case e_primitive_HelloAck:
        return FsmCtrlPerform(BFCP_ACT_HelloAck ,p_bfcpEvent);
        break ; 
    case e_primitive_Error:
        return FsmCtrlPerform(BFCP_ACT_Error ,p_bfcpEvent);
        break ; 
    default :
        Log(ERR,_T("BFCPFSM_FsmEvent unknown Event[%d] status[%d]"),p_bfcpEvent->Event,p_bfcpEvent->Status );
        return false ;
        break ; 
    }
    return false ;
}

void BFCP_fsm::InitFsmEvent( st_BFCP_fsm_event * p_fsm_evt, e_BFCP_ACT p_state, const s_bfcp_msg_event* p_bfcp_evt )
{
    memset(p_fsm_evt,0, sizeof ( st_BFCP_fsm_event ));
    
    p_fsm_evt->State = p_state ;
    if ( p_bfcp_evt ) 
    {
        p_fsm_evt->TransactionID  = p_bfcp_evt->TransactionID;
        p_fsm_evt->userID = p_bfcp_evt->userID;
        p_fsm_evt->conferenceID = p_bfcp_evt->conferenceID ;
        p_fsm_evt->FloorID = p_bfcp_evt->FloorID ;
        p_fsm_evt->FloorRequestID = p_bfcp_evt->FloorRequestID ;
        p_fsm_evt->QueuePosition = p_bfcp_evt->QueuePosition;
        p_fsm_evt->BeneficiaryID = p_bfcp_evt->BeneficiaryID ;
        p_fsm_evt->i_parm = p_bfcp_evt->i_parm ;
        p_fsm_evt->pt_param = p_bfcp_evt->pt_param ;
        if ( p_bfcp_evt->c_param ) ft_tcsncpy(p_fsm_evt->c_param ,p_bfcp_evt->c_param , BFCP_STRING_SIZE );
    }
}

/**
 * 
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file client.cpp
 *
 * \version $Revision: 2148 $
 *
 * \date $Date: 2014-01-22 12:14:17 +0100 (Wed, 22 Jan 2014) $
 *
 * \remarks 
 *
 * \ingroup libbfcp
 *
 * \namespace  sampleClient
 *
 * \brief Sample test of BFCP particpant API .
 */

/* ==========================================================================*/
/* File identification                                                       */
/* ==========================================================================*/

/* ==========================================================================*/
/* System include(s)                                                         */
/* ==========================================================================*/
#include <stdio.h>
#include <inttypes.h>
#include "client.h"

/* Helper Macros to check for errors */
#define BFCP_CHECK_INTEGER				\
	if (error == 0) {				\
		printf("An integer is needed!\n");	\
		break;					\
	}

sampleClient::sampleClient() {
    Log(INF,"sampleClient instance created. ");
    SetFloorctrlMode(FLOOCTRL_MODE_CLIENT) ;
    m_BFCP_Participant = NULL ;
    SetConfID(0) ;
    SetUserID(0) ;
    SetFloorID(0 );
    SetStreamID(0) ;
    SetIsPassive(false) ;
#if 0
    Log(INF,"sampleClient : sz unsigned short int:%d",sizeof ( unsigned short int )) ;
    Log(INF,"sampleClient : sz unsigned long int:%d",sizeof (unsigned long int)) ;
    Log(INF,"sampleClient : sz unsigned short:%d",sizeof (unsigned short)) ;
    Log(INF,"sampleClient : sz unsigned char:%d",sizeof (unsigned char)) ;
    Log(INF,"sampleClient : sz int:%d",sizeof (int)) ;
    Log(INF,"sampleClient : sz UINT16:%d",sizeof ( UINT16 )) ;
    Log(INF,"sampleClient : sz UINT32:%d",sizeof ( UINT32 )) ;
#endif
}

sampleClient::~sampleClient() {

    Log(INF,"sampleClient instance destroy. ");
    if ( m_BFCP_Participant != NULL )
        delete m_BFCP_Participant;
    m_BFCP_Participant = NULL ;
}

int sampleClient::OpenParticipantTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive ) {
    int Status = 0 ;
    try {
        if ( !m_confID || !m_userID || !m_floorID )
            return Status ;

        if ( m_BFCP_Participant == NULL  )
            m_BFCP_Participant = new BFCP_Participant( m_confID , m_userID , m_floorID , m_streamID , this );

        if ( m_BFCP_Participant ) {
            if ( m_BFCP_Participant->isStarted() ) {
                if ( m_IsPassive ) {
                    if ( local_address && local_port ) {
                        if ( strstr(m_BFCP_Participant->getLocalAdress(),local_address) != NULL &&
                                m_BFCP_Participant->getLocalPort() == local_port ) {
                            Log(INF,"OpenParticipantTcpConnection aldready started with the same connection . ");
                            return BFCPAPI_SUCCESS ;
                        } else if ( local_port && m_BFCP_Participant->getLocalPort() != local_port ) {
                            m_BFCP_Participant->CloseTcpConnection();
                        }
                    }
                } else  if ( local_address && local_port ) {
                    if ( strstr(m_BFCP_Participant->getRemoteAdress(),remote_address) != NULL &&
                            m_BFCP_Participant->getRemotePort() == remote_port &&
                            strstr(m_BFCP_Participant->getLocalAdress(),local_address) != NULL &&
                            m_BFCP_Participant->getLocalPort() == local_port ) {
                        Log(INF,"OpenParticipantTcpConnection aldready started with the same connection . ");
                        return BFCPAPI_SUCCESS ;
                    } else {
                        m_BFCP_Participant->CloseTcpConnection();
                    }
                }
            }

            if ( m_BFCP_Participant->OpenTcpConnection( local_address,local_port,remote_address,remote_port,isPassive?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE)) {
                Log(INF,"OpenParticipantTcpConnection instanciation sucess ");
                Status = BFCPAPI_SUCCESS ;
            } else {
                Log(ERR,"OpenParticipantTcpConnection connection failed ");
            }
        } else {
            Log(ERR,"OpenParticipantTcpConnection invalid address or port");
        }
    } catch(...) {
        Log(ERR, "BFCPApiOpenTcpConnection exp");
    }
    return Status ;
}

// FSM server callback exit function ( if transaction success )
bool sampleClient::OnBfcpParticipantEvent(BFCP_fsm::e_BFCP_ACT p_evt ,BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent ) {
    bool Status = false ;
    if ( !p_FsmEvent )
        return Status ;

    Log(INF,_T("OnBfcpParticipantEvent evt[%s] state[%s]"), getBfcpFsmAct(p_evt),getBfcpFsmAct(p_FsmEvent->State)  );

    switch ( p_evt ) {
    case BFCP_fsm::BFCP_ACT_UNDEFINED :
        break ;
    case BFCP_fsm::BFCP_ACT_INITIALIZED  :
        break ;
    case BFCP_fsm::BFCP_ACT_DISCONNECTED  :
        Status = disconnected() ;
        break ;
    case BFCP_fsm::BFCP_ACT_CONNECTED :
        Status = connected() ;
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequest :
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRelease  :
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestQuery :
        break ;
    case BFCP_fsm::BFCP_ACT_UserQuery  :
        break ;
    case BFCP_fsm::BFCP_ACT_FloorQuery  :
        break ;
    case BFCP_fsm::BFCP_ACT_ChairAction  :
        break ;
    case BFCP_fsm::BFCP_ACT_Hello :
        break ;
    case BFCP_fsm::BFCP_ACT_Error :
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAccepted :
        Status = floorRequestStatusAccepted(p_FsmEvent) ;
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAborted :
        Status = floorRequestStatusAborted(p_FsmEvent);
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusGranted  :
        Status = floorRequestStatusGranted(p_FsmEvent) ;
        break ;
    case BFCP_fsm::BFCP_ACT_UserStatus :
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusAccepted :
        Status = floorStatusAccepted(p_FsmEvent) ;
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusAborted :
        Status = floorStatusAborted(p_FsmEvent)  ;
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusGranted  :
        Status = floorStatusGranted(p_FsmEvent) ;
        break ;
    case BFCP_fsm::BFCP_ACT_ChairActionAck :
        break ;
    case BFCP_fsm::BFCP_ACT_HelloAck  :
        break ;
    case BFCP_fsm::BFCP_ACT_SHARE :
        Status = true ;
        break ;
    case BFCP_fsm::BFCP_ACT_SERVER_SHARE :
        Status = true ;
        break ;
    default :
        break ;
    }

    return Status ;
}


bool sampleClient::connected() {
    Log(INF,_T("BFCP connection success."));
    return true ;
}

bool sampleClient::disconnected() {
    Log(INF,_T("BFCP disconnected."));
    return true ;
}

/*
+-------+-----------+
| Value | Status    |
+-------+-----------+
|   1   | Pending   |  floorRequestStatusAccepted
|   2   | Accepted  |  floorRequestStatusAccepted
|   3   | Granted   |  floorRequestStatusGranted
|   4   | Denied    |  floorRequestStatusAborted
|   5   | Cancelled |  floorRequestStatusAborted
|   6   | Released  |  floorRequestStatusAborted
|   7   | Revoked   |  floorRequestStatusAborted
+-------+-----------+
*/

bool sampleClient::floorRequestStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusGranted. myFloorId[%d] eventFloorId[%d]"),m_floorID , p_evt->FloorID );
if ( !p_evt->FloorID  ||  m_floorID == p_evt->FloorID ) {
    return true ;
}
    else {
        Log(ERR,_T("BFCP floorRequestStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorRequestStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusAborted. myFloorId[%d] eventFloorId[%d]"),m_floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  || m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP floorRequestStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorRequestStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  || m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorReleaseStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorStatusAccepted( BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorStatusAccepted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP FloorStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorStatusGranted( BFCP_fsm::st_BFCP_fsm_event* p_evt ) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorStatusGranted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP FloorStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt ) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorRequestAborted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ) {
        return true ;
    } else {
        Log(ERR,_T("BFCP FloorRequestAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool sampleClient::floorRequest(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    bool status = false ;
    if ( !m_BFCP_Participant ) 
	return status ; 
    if ( m_BFCP_Participant->bfcp_floorRequest_participant(m_floorID) == -1 ) {
        Log(ERR,"FloorRequest send  floorRequest failed ! ");
    } else {
        status = true ;
    }
    return status ;
}

bool sampleClient::floorRelease(BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    bool status = false ;
    if ( m_BFCP_Participant->bfcp_floorRelease_participant() == -1 ) {
        Log(ERR,"FloorRelease send  FloorRelease failed ! ");
    } else {
        status = true ;
    }
    return status ;
}

// Use only for nego .
void sampleClient::SetConfID( UINT32 p_confID ) {
    m_confID = p_confID ;
}

UINT32 sampleClient::GetConfID( ) {
    return m_confID ;
}

void sampleClient::SetUserID( UINT16 p_userID ) {
    m_userID = p_userID ;
}

UINT16 sampleClient::GetUserID( ) {
    return m_userID ;
}

void sampleClient::SetFloorID( UINT16 p_floorID ) {
    m_floorID = p_floorID ;
}

UINT16 sampleClient::GetFloorID( ) {
    return m_floorID ;
}

void sampleClient::SetStreamID( UINT16 p_streamID ) {
    m_streamID = p_streamID ;
}

UINT16 sampleClient::GetStreamID( ) {
    return m_streamID ;
}

void sampleClient::SetIsPassive( bool p_IsServer ) {
    Log(INF,"SetIsPassive [%s] => [%s] ",m_IsPassive?"true":"false",p_IsServer?"true":"false");
    m_IsPassive = p_IsServer ;
}

bool sampleClient::GetIsPassive( ) {
    return m_IsPassive ;
}

void sampleClient::SetFloorctrlMode( e_floorctrlMode pfloorctrlMode ) {
    Log(INF,"SetFloorctrlMode [%d] => [%d] ",m_e_floorctrlMode,pfloorctrlMode);
    if ( m_e_floorctrlMode == pfloorctrlMode   )
        return ;

    m_e_floorctrlMode = pfloorctrlMode ;
}

e_floorctrlMode sampleClient::GetFloorctrlMode(void) {
    return m_e_floorctrlMode;
}

/** \brief Menu to manipulate the Floor Control Server options and operations */
void sampleClient::menu(char *lineptr) {
    char line[80] = { 0 } ;
    char* text1 = NULL;
    UINT32 conferenceID = 0;
    UINT16 userID = 0, floorID = 0, beneficiaryID = 0;
    int  error = 0, status = 0, port_server = 0, priority = 0;
    UINT16 floorRequestID = 0;

    printf("%s%s%s%s%s%s%s%s%s%s",
           "\n--------PARTICIPANT LIST-----------------------------\n",
           " ?      - Show the menu\n",
           " c      - Create the Participant\n",
           " d      - Destroy the Participant\n",
           "BFCP Messages:\n",
           " h      - hello \n",
           " r      - FloorRequest\n",
           " l      - FloorRelease\n",
           " q      - quit                   \n",
           "------------------------------------------------------\n\n");
    while(fgets(line, 79, stdin) != NULL) {
        lineptr = line;
        while(*lineptr == ' ' || *lineptr == '\t')
            ++lineptr;
        switch(*lineptr) {
        case '?':
            printf("%s%s%s%s%s%s%s%s%s%s",
                   "\n--------PARTICIPANT LIST-----------------------------\n",
                   " ?      - Show the menu\n",
                   " c      - Create the Participant\n",
                   " d      - Destroy the Participant\n",
                   "BFCP Messages:\n",
                   " h      - hello \n",
                   " r      - FloorRequest\n",
                   " l      - FloorRelease\n",
                   " q      - quit                   \n",
                   "------------------------------------------------------\n\n");
            break;
        case 'c':
            ++lineptr;
	printf("Enter the userID of the participant:\n");
            error = scanf ("%hu" , &userID);
            SetUserID(userID);
	++lineptr;
            printf("Enter the conferenceID of the conference:\n");
            error = scanf ("%d", &conferenceID);
            SetConfID(conferenceID);
	++lineptr;
	printf("Enter the FloorID:\n");
            error = scanf ("%hu" , &floorID);
            SetFloorID(floorID);
#ifndef WIN32
            printf("Enter the IP address of the Floor Control Server: \n");
            scanf (" %a[^\n]", &text1);
#else
            /* FIXME fix broken scanf in WIN32 */
            text1 = calloc(20, sizeof(char));
            sprintf(text1, "127.0.0.1");
            printf("Defaulting Floor Control Server IP to %s...\n", text1);
#endif

            printf("Enter the listening port of the Floor Control Server: \n");
            error = scanf ("%i", &port_server);
            BFCP_CHECK_INTEGER;
            ++lineptr;
            OpenParticipantTcpConnection( NULL , 0 , text1 , port_server , GetIsPassive() );
            free(text1);
            break;
        case 'd':
            ++lineptr;
            if ( m_BFCP_Participant )
                delete m_BFCP_Participant ;
            m_BFCP_Participant = NULL ;
	    break ; 
         case 'h':
            ++lineptr;
            if ( m_BFCP_Participant )
                m_BFCP_Participant->bfcp_hello_participant(NULL) ;
	    break ; 
         case 'r':
            ++lineptr;
            printf("Enter the BeneficiaryID of the new request \n");
            error = scanf ("%hu" , &beneficiaryID);
            printf("Enter the priority for this request (0=lowest --> 4=highest):\n");
            error = scanf ("%i", &priority);
            BFCP_CHECK_INTEGER;
            if ( m_BFCP_Participant )
                m_BFCP_Participant->bfcp_floorRequest_participant( GetFloorID() );
            break;
        case 'l':
            ++lineptr;
            printf("Enter the FloorRequestID of the request you want to release:( 0 = current ) \n");
            error = scanf ("%hu", &floorRequestID);
            if ( !floorRequestID ) {
                if ( m_BFCP_Participant )
                    m_BFCP_Participant->bfcp_floorRelease_participant();
            } else {
                if ( m_BFCP_Participant )
                    m_BFCP_Participant->bfcp_floorRelease_participant( m_BFCP_Participant->GetCurrentParticpantInfo() , floorRequestID );
            }
            break;
        case 'q':
            status = 0;
            return;
            break;
        case '\n':
            break;
        default:
            printf("Invalid menu choice - try again\n");
            break;
        }
    }
}

void sampleClient::Log(const char* pcFile, int iLine, int iErrLevel , const  char* pcFormat, ...) {
    va_list arg;
    char s[3000];
    va_start(arg,pcFormat);
    vsnprintf(s,3000,pcFormat,arg);
    va_end(arg);
    if ( iErrLevel )
        printf("\033[31m[ %s:%d | %d | %s \033[0m \n",pcFile?pcFile:"" , iLine , iErrLevel , s);
    else
        printf("%s:%d | %d | %s\n",pcFile?pcFile:"" , iLine , iErrLevel , s);
}

/* Main */
int main (int argc, char *argv[]) {
    char *lineptr = NULL;
    printf("\nBinary Floor Control Protocol (BFCP) Participant Tester\n\n");
    sampleClient  participant ;
    participant.menu(lineptr);
    return 0;
}


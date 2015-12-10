/**
 *
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file server.cpp
 *
 * \version $Revision: 2613 $
 *
 * \date $Date: 2015-11-18 09:33:06 +0100 (Wed, 18 Nov 2015) $
 *
 * \remarks 
 *
 * \ingroup libbfcp
 *
 *
 * \namespace  sampleServer
 *
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
#include "server.h"

/**  Helper Macro to check for integer errors
*\def BFCP_CHECK_INTEGER
*/
#define BFCP_CHECK_INTEGER				\
	if(error == 0) {				\
		printf("An integer is needed!\n");	\
		break;					\
	}



sampleServer::sampleServer() {
    m_e_floorctrlMode = FLOOCTRL_MODE_SERVER ;
    m_BFCP_Server = NULL ;
    SetConfID(0) ;
    SetUserID(0) ;
    SetFloorID(0 );
    SetStreamID(0) ;
    SetIsPassive(true) ;
}


sampleServer::~sampleServer() {

    Log(INF,"FCS instance destroy. ");
    StopServer();
}

int sampleServer::StopServer() {
    if ( m_BFCP_Server != NULL )
        delete m_BFCP_Server;
    m_BFCP_Server = NULL;
    return 1 ;
}

int sampleServer::StartServer(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive ) 
{
    int Status = BFCPAPI_ERROR ;
    try {
        if ( !GetFloorID() ) {
            Log(ERR,"StartServer invalid floor ID ");
            return Status ;
        }

        if ( m_BFCP_Server == NULL  )
            m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF , m_confID , m_userID , m_floorID , m_streamID , this );


        if (m_BFCP_Server ) 
	{
            if ( m_BFCP_Server->isStarted() )
	    {
                if ( m_IsPassive )
		{
                    if ( local_address!=NULL && local_port!=0 )
		    {
                        if ( strstr(m_BFCP_Server->getLocalAdress(),local_address) != NULL && m_BFCP_Server->getLocalPort() == local_port ) 
			{
                            Log(INF,"StartServer aldready started with the same connection . ");
                            return BFCPAPI_SUCCESS ;
                        } else {
                            Log(INF,"StartServer aldready started close current connection . ");
                            m_BFCP_Server->CloseTcpConnection();
                        }
                    } else {
                        Log(INF,"StartServer aldready started on ANY_ADDRESS . ");
                        return BFCPAPI_SUCCESS ;
                    }
                } else {
                    if ( strstr(m_BFCP_Server->getRemoteAdress(),remote_address) != NULL &&
                            m_BFCP_Server->getRemotePort() == remote_port &&
                            strstr(m_BFCP_Server->getLocalAdress(),local_address) != NULL &&
                            m_BFCP_Server->getLocalPort() == local_port ) {
                        Log(INF,"StartServer aldready started with the same connection . ");
                        return BFCPAPI_SUCCESS ;
                    } else {
                        Log(INF,"StartServer aldready started, start new connection . ");
                    }
                }
            }

            if ( m_BFCP_Server->OpenTcpConnection( local_address,local_port,remote_address,remote_port,isPassive?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE)) {
                Log(INF,"StartServer sucess ");
                Status = BFCPAPI_SUCCESS ;
            } else {
                Log(ERR,"BFCPApiStartServer failed ");
            }
        } else {
            Log(ERR,"StartServer invalid address or port");
        }
    } catch(...) {
        Log(ERR, "StartServer exp");
    }
    return Status ;
}

/**
 *  \brief Floor control server callback for BFCP events and respons 
 *
 * This callback is called when server receved an event or connection.
 * p_evt is the current event and p_FsmEvent is the context and informations of event 
 * @param p_evt \ref BFCP_fsm::e_BFCP_ACT current event of BFCP server 
 * @param p_FsmEvent \ref  BFCP_fsm::st_BFCP_fsm_event informations struct of events 
 * @return  true success , false failed 
 */
bool sampleServer::OnBfcpServerEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent ) {
    bool Status = false ;
    if ( !p_FsmEvent )
        return Status ;

    Log(INF,_T("OnBfcpServerEvent evt[%s] state[%s]"), getBfcpFsmAct(p_evt),getBfcpFsmAct(p_FsmEvent->State)  );

    switch ( p_evt ) {
    case BFCP_fsm::BFCP_ACT_UNDEFINED :
        break ;
    case BFCP_fsm::BFCP_ACT_INITIALIZED  :
        break ;
    case BFCP_fsm::BFCP_ACT_DISCONNECTED  :
        /* participant have closed network connection */
        break ;
    case BFCP_fsm::BFCP_ACT_CONNECTED :
        /*  participant are connected */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequest :
        /*  participant have send BFCP floor request  */
        /*  In this school sample with automatic accept and granted this request */
        /*  if another participant have the floor , we send revoked status */
        /*  remarks , bfcp library auto send pending request */
        if ( m_BFCP_Server ) {
            e_bfcp_status bfcp_status = BFCP_PENDING ;
            UINT32 userID = 0 ;
            UINT32 beneficiaryID = 0 ;
            UINT16 floorRequestID = 0 ;
            /* check FloorState */
            if ( m_BFCP_Server->GetFloorState(&bfcp_status , &userID ,  &beneficiaryID ,  &floorRequestID  ) ) {
                if ( bfcp_status == BFCP_GRANTED && userID ) {
                    /* revoke current GRANTED bfcp request */
                    m_BFCP_Server->FloorRequestRespons( userID , beneficiaryID , p_FsmEvent->TransactionID ,floorRequestID , BFCP_REVOKED , 0 , BFCP_NORMAL_PRIORITY , false );
                }
            }
            /* accept new request */
            Status = m_BFCP_Server->FloorRequestRespons( p_FsmEvent->userID , p_FsmEvent->userID , p_FsmEvent->TransactionID , p_FsmEvent->FloorRequestID , BFCP_ACCEPTED , 0 , BFCP_NORMAL_PRIORITY , false );
            /* and granted new request */
            if ( Status )
                Status = m_BFCP_Server->FloorRequestRespons( p_FsmEvent->userID , p_FsmEvent->userID , p_FsmEvent->TransactionID ,  p_FsmEvent->FloorRequestID ,BFCP_GRANTED , 0 , BFCP_NORMAL_PRIORITY , true );
        }
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRelease  :
        /* participant have send floor release request */
        if ( m_BFCP_Server ) {
            /* alert all particpant of the new state */
            Status = m_BFCP_Server->SendFloorStatus( 0 , 0 , 0 , NULL , true ) ;
        }
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestQuery :
        /* actually this request are not supported , you shoould never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_UserQuery  :
        /* actually this request are not supported , you shoould never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorQuery  :
        /* actually this request are not supported , you shoould never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_ChairAction  :
        /* actually this request are not supported , you shoould never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_Hello :
        /*  FCS have received an hello message , libbfcp have automatically send helloAck   */
        break ;
    case BFCP_fsm::BFCP_ACT_Error :
        /*  FCS have received an error message */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAccepted :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAborted :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusGranted  :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_UserStatus :
        /* actually this request are not supported , you shoould never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusAccepted :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusAborted :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_FloorStatusGranted  :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_ChairActionAck :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_HelloAck  :
        /*  FCS have send an helloAck  message , send floor status to inform status of conference */
        if ( m_BFCP_Server ) {
            Status = m_BFCP_Server->SendFloorStatus( p_FsmEvent->userID , p_FsmEvent->BeneficiaryID , 0 , NULL , false ) ;
        }
        break ;
    case BFCP_fsm::BFCP_ACT_SHARE :
        /* not valid on server  , you should never receive this event */
        break ;
    case BFCP_fsm::BFCP_ACT_SERVER_SHARE :
        /* not valid on server  , you should never receive this event */
        break ;
    default :
        break ;
    }
    return Status ;
}

void sampleServer::SetConfID( UINT32 p_confID ) {
    m_confID = p_confID ;
}

UINT32 sampleServer::GetConfID( ) {
    return m_confID ;
}

void sampleServer::SetUserID( UINT16 p_userID ) {
    m_userID = p_userID ;
}

bool sampleServer::AddUserIDinConf( UINT16 p_userID ) {
    bool Status = false ;
    if ( m_e_floorctrlMode && m_BFCP_Server ) {
        Status = m_BFCP_Server->AddUser(p_userID);
    }
    return Status ;
}

bool  sampleServer::RemoveUserIDinConf( UINT16 p_userID ) {
    bool Status = false ;
    if ( m_BFCP_Server )
        Status =  m_BFCP_Server->RemoveUserInConf(p_userID);
    return Status ;
}


UINT16 sampleServer::GetUserID( ) {
    return m_userID ;
}

void sampleServer::SetFloorID( UINT16 p_floorID ) {
    m_floorID = p_floorID ;
}

UINT16 sampleServer::GetFloorID( ) {
    return m_floorID ;
}

void sampleServer::SetStreamID( UINT16 p_streamID ) {
    m_streamID = p_streamID ;
}

UINT16 sampleServer::GetStreamID( ) {
    return m_streamID ;
}

void sampleServer::SetIsPassive( bool p_IsServer ) {
    Log(INF,"SetIsPassive [%s] => [%s] ",m_IsPassive?"true":"false",p_IsServer?"true":"false");
    m_IsPassive = p_IsServer ;
}

bool sampleServer::GetIsPassive( ) {
    return m_IsPassive ;
}

void sampleServer::SetFloorctrlMode( e_floorctrlMode pfloorctrlMode ) {
    Log(INF,"SetFloorctrlMode [%d] => [%d] ",m_e_floorctrlMode,pfloorctrlMode);
    if ( m_e_floorctrlMode == pfloorctrlMode )
        return ;

    m_e_floorctrlMode = pfloorctrlMode ;
}

e_floorctrlMode sampleServer::GetFloorctrlMode(void) {
    return m_e_floorctrlMode;
}

/* Menu to manipulate the Floor Control Server options and operations */
void sampleServer::menu(char *lineptr)
{
    char line[80];
    int  error = 0, port = 0,  status = 0 ;
    UINT32 conferenceID = 0;
    UINT16 userID = 0, floorID = 0 ;
    if ( lineptr )
        strncpy( line , lineptr , 80 );

    char yesno;
    
    printf("%s%s%s%s%s%s%s%s%s",
           "\n--------CONFERENCE SERVER-----------------------------------\n",
           " ?      - Show the menu\n",
           " c      - Create the Floor Control Server\n",
           " d      - Destroy the Floor Control Server\n",
           " a      - Add a new user\n",
           " k      - Delete a user\n",
           " s      - Show the conferences in the BFCP server\n",
           " q      - Quit\n",
           "------------------------------------------------------------------\n\n");
    while(fgets(line, 79, stdin) != NULL) {
        lineptr = line;
        while(*lineptr == ' ' || *lineptr == '\t')
            ++lineptr;
        switch(*lineptr) {
        case '?':
            printf("%s%s%s%s%s%s%s%s%s",
                   "\n--------CONFERENCE SERVER-----------------------------------\n",
                   " ?      - Show the menu\n",
                   " c      - Create the Floor Control Server\n",
                   " d      - Destroy the Floor Control Server\n",
                   " a      - Add a new user\n",
                   " k      - Delete a user\n",
                   " s      - Show the conferences in the BFCP server\n",
                   " q      - Quit\n",
                   "------------------------------------------------------------------\n\n");
            break;
        case 'c':
            ++lineptr;
            printf("Enter the conferenceID of the FCS:\n");
            error = scanf ("%d", &conferenceID);
            SetConfID(conferenceID);
            ++lineptr;
            printf("Enter the FloorID of the FCS:\n");
            error = scanf ("%hu" , &floorID);
            SetFloorID(floorID);
            ++lineptr;
            printf("Enter the listening port for the Floor Control Server:\n");
            error = scanf("%i", &port);
            BFCP_CHECK_INTEGER;
            if ( m_BFCP_Server != NULL )
                delete m_BFCP_Server;
            // Create server And start
            StartServer( NULL , port , NULL , 0 , GetIsPassive() );
            break;
        case 'd':
            ++lineptr;
            // Close connections and destroy server
            if ( m_BFCP_Server != NULL )
                delete m_BFCP_Server;
            m_BFCP_Server = NULL ; 
            break;
        case 's':
            ++lineptr;
            // Dump server stat
            if ( m_BFCP_Server != NULL )
                m_BFCP_Server->DumpServer();
            break;
        case 'a':
            ++lineptr;
            printf("Enter the UserID:\n");
            error = scanf("%hu", &userID);
            // Add user before connection
            if ( m_BFCP_Server != NULL )
	    {
                if ( m_BFCP_Server->AddUser( userID ) )
		{
		    printf("User %u added successfully.", userID);
		    printf("Should we open an UDP connection for this user ? (y/n):");
		    yesno = 'n';
		    scanf("%c", &yesno);
		    if (yesno == 'y')
		    {
			int port = 0;;
			
			printf("UDP port to use (>= 6000) : ");
			scanf("%d", &port);
			if (port >= 6000)
			{
			    if ( m_BFCP_Server->OpenUdpConnection(userID, NULL, port) )
			    {
				puts("UDP connection is open");
			    }
			    else
			    {
				puts("Failed to open UDP cnx");
			    }
			}
			else
			{
			     puts("Invalid port for UDP connection !");
			}
		    }
		}
		else
		{
		    puts("Failed to add user.");
		}
	    }
	    else
	    {
		puts("Server is not started");
	    }
	  
            break;
        case 'k':
            ++lineptr;
            printf("Enter the UserID:\n");
            error = scanf("%hu", &userID);
            // Remove user
            if ( m_BFCP_Server != NULL )
                m_BFCP_Server->RemoveUserInConf( userID );
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

void sampleServer::Log(const  char* pcFile, int iLine, int iErrLevel ,const  char* pcFormat, ...) {
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
    printf("\nBinary Floor Control Protocol (BFCP) Floor Control Server (FCS) Tester\n\n");
    sampleServer tester ;
    tester.menu(lineptr);
    return 0;
}

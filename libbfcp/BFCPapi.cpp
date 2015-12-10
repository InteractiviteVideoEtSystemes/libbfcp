
#include "stdafx.h"
#include "BFCPapi.h"
#include "ftiwindowgrabber.h"
#include "CodecControllerAPI.h"
#include "CallControllerAPI.h"
#include "bfcp_messages.h"
#include "bfcp_strings.h"

#define SERVER_DEFAULT_USERID 0xFF

BFCPApi::BFCPApi(BFCPApiEvent* p_listener)
{

    LogInit();
    
    eConfLog(INF,"BFCPApi instance created. ");
    m_windowGrabber = NULL ; 
    m_confHandle    = NULL ;
    m_codecControler = NULL ; 
    m_callControler = NULL ;
    m_callStackGroup = NULL ; 
    m_listener = p_listener ;
    m_e_floorctrlMode = FLOOCTRL_MODE_CLIENT ;
    m_BFCP_Participant = NULL ;
    m_BFCP_Server = NULL ; 
    m_confID  = BFCP_SERVER_BASE_CONFID ;
    m_userID  = BFCP_SERVER_BASE_USERID ;
    m_floorID  = BFCP_SERVER_BASE_FLOORID ;
    m_streamID  = BFCP_SERVER_BASE_STREAMID ;
    m_IsPassive = false ;
    m_hWndApplicationSelected = NULL ; 
    bfcp_mutex_init(m_mutexServer,NULL);
    bfcp_mutex_init(m_mutexParticipant,NULL);
#if 0
     eConfLog(INF,"BFCPApi : sz unsigned short int:%d",sizeof ( unsigned short int )) ;
     eConfLog(INF,"BFCPApi : sz unsigned long int:%d",sizeof (unsigned long int)) ;
     eConfLog(INF,"BFCPApi : sz unsigned short:%d",sizeof (unsigned short)) ;
     eConfLog(INF,"BFCPApi : sz unsigned char:%d",sizeof (unsigned char)) ;
     eConfLog(INF,"BFCPApi : sz int:%d",sizeof (int)) ;
     eConfLog(INF,"BFCPApi : sz UINT16:%d",sizeof ( UINT16 )) ;
     eConfLog(INF,"BFCPApi : sz UINT32:%d",sizeof ( UINT32 )) ;
#endif
}

BFCPApi::~BFCPApi(){

    eConfLog(INF,"BFCPApi instance destroy. ");
    BFCPApiCloseTcpConnection();
    m_windowGrabber = NULL ;
    m_confHandle    = NULL ;
    if(m_codecControler)
    {
        m_codecControler->RemoveCodecControllerCB(this);
    }
    m_codecControler = NULL ;  
    if(m_callControler)
	{
		m_callControler->RemoveCallStackCB(m_callStackGroup, this);
	}
    m_callControler = NULL ;
    m_callStackGroup = NULL ; 
    bfcp_mutex_lock(m_mutexParticipant);
    if ( m_BFCP_Participant != NULL )
        delete m_BFCP_Participant;
    m_BFCP_Participant = NULL ;
    bfcp_mutex_destroy(m_mutexParticipant);

    bfcp_mutex_lock(m_mutexServer);
    if ( m_BFCP_Server != NULL )
        delete m_BFCP_Server;
    m_BFCP_Server = NULL;
    bfcp_mutex_destroy(m_mutexServer);
}

int BFCPApi::BFCPApiOpenTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port  ){
    int Status = BFCPAPI_ERROR ;
    eConfLog(INF,"BFCPApiOpenTcpConnection mode[%s] confId[%d] userId[%d] floorID[%d] streamID[%d] server[%s] network [%s:%d]<=>[%s:%d] ",
        m_e_floorctrlMode==FLOOCTRL_MODE_CLIENT?"BFCP PARTICIPANT":"BFCP SERVER",
        GetConfID(),GetUserID(),GetFloorID(),GetStreamID(),m_IsPassive?"TRUE":"FALSE",
        local_address?local_address:"",
        local_port?local_port:0 ,
        remote_address?remote_address:"",
        remote_port?remote_port:0 );

    if ( m_e_floorctrlMode==FLOOCTRL_MODE_CLIENT ){  
        Status = BFCPApiOpenParticipantTcpConnection( local_address , local_port , remote_address , remote_port ,m_IsPassive);
    }else{
        if ( !m_IsPassive ){
             eConfLog(INF,"BFCPApiOpenTcpConnection server active mode not supported ! forcing mode actif ");
             m_IsPassive = true ; 
        }
              
        Status = BFCPApiOpenServerTcpConnection( local_address , local_port , remote_address , remote_port,m_IsPassive );
    }
    return Status ;
}

int BFCPApi::BFCPApiOpenParticipantTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive ){
    int Status = BFCPAPI_ERROR ;
    TRY{
        if ( !m_confID || !m_userID || !m_floorID )
            return Status ;

        if ( m_BFCP_Participant == NULL  )
            m_BFCP_Participant = new BFCP_Participant( m_confID , m_userID , m_floorID , m_streamID , this );

        if ( m_BFCP_Participant )
        {
            if ( m_BFCP_Participant->isStarted() ){
                if ( m_IsPassive ){
                    if ( local_address && local_port ){
                        if ( strstr(m_BFCP_Participant->getLocalAdress(),local_address) != NULL &&  
                            m_BFCP_Participant->getLocalPort() == local_port ){
                                eConfLog(INF,"BFCPApiOpenParticipantTcpConnection aldready started with the same connection . ");
                                return BFCPAPI_SUCCESS ;
                        }else if ( local_port && m_BFCP_Participant->getLocalPort() != local_port ){
                            m_BFCP_Participant->CloseTcpConnection();
                        }
                    }
                }
                else  if ( local_address && local_port ){ 
                    if ( strstr(m_BFCP_Participant->getRemoteAdress(),remote_address) != NULL &&  
                        m_BFCP_Participant->getRemotePort() == remote_port &&
                        strstr(m_BFCP_Participant->getLocalAdress(),local_address) != NULL &&  
                        m_BFCP_Participant->getLocalPort() == local_port ){
                            eConfLog(INF,"BFCPApiOpenParticipantTcpConnection aldready started with the same connection . ");
                            return BFCPAPI_SUCCESS ;
                    }
                    else {
                        m_BFCP_Participant->CloseTcpConnection();
                    }
                }
            }

            if ( m_BFCP_Participant->OpenTcpConnection( local_address,local_port,remote_address,remote_port,isPassive?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE))
            {
                eConfLog(INF,"BFCPApiOpenParticipantTcpConnection instanciation sucess ");
                Status = BFCPAPI_SUCCESS ;
            }else{
                eConfLog(ERR,"BFCPApiOpenParticipantTcpConnection connection failed ");
            }
        }else{
            eConfLog(ERR,"BFCPApiOpenParticipantTcpConnection invalid address or port");
        } 
    }catch(...)
    {
        eConfLog(ERR, "BFCPApiOpenTcpConnection exp");
    }
        return Status ;   
}


int BFCPApi::BFCPApiOpenServerTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive ){
    int Status = BFCPAPI_ERROR ;
    TRY{         
        if ( !GetFloorID() ){
            eConfLog(ERR,"BFCPApiOpenServerTcpConnection invalid floor ID ");
            return Status ;
        }

        if ( m_BFCP_Server == NULL  )
            m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF , m_confID , m_userID , m_floorID , m_streamID , this );


        if (local_address!=NULL && local_port!=0 && m_BFCP_Server )
        {
            if ( m_BFCP_Server->isStarted() ){
                if ( m_IsPassive ){
                    if ( local_address!=NULL && local_port!=0 ){
                        if ( strstr(m_BFCP_Server->getLocalAdress(),local_address) != NULL &&  
                            m_BFCP_Server->getLocalPort() == local_port ){
                                eConfLog(INF,"BFCPApiOpenServerTcpConnection aldready started with the same connection . ");
                                return BFCPAPI_SUCCESS ;
                        }else{
                            eConfLog(INF,"BFCPApiOpenServerTcpConnection aldready started close current connection . ");
                            m_BFCP_Server->CloseTcpConnection();
                        }
                    }else{
                        eConfLog(INF,"BFCPApiOpenServerTcpConnection aldready started on ANY_ADDRESS . ");
                        return BFCPAPI_SUCCESS ;
                    }
                }
                else {
                    if ( strstr(m_BFCP_Server->getRemoteAdress(),remote_address) != NULL &&  
                        m_BFCP_Server->getRemotePort() == remote_port &&
                        strstr(m_BFCP_Server->getLocalAdress(),local_address) != NULL &&  
                        m_BFCP_Server->getLocalPort() == local_port ){
                            eConfLog(INF,"BFCPApiOpenServerTcpConnection aldready started with the same connection . ");
                            return BFCPAPI_SUCCESS ;
                    }
                    else {
                        eConfLog(INF,"BFCPApiOpenServerTcpConnection aldready started, start new connection . ");
                    }
                }
            }

            if ( m_BFCP_Server->OpenTcpConnection( local_address,local_port,remote_address,remote_port,isPassive?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE))
            {
                eConfLog(INF,"BFCPApiOpenServerTcpConnection sucess ");
                Status = BFCPAPI_SUCCESS ;
            }else{
                eConfLog(ERR,"BFCPApiOpenServerTcpConnection failed ");
            }
        }else{
            eConfLog(ERR,"BFCPApiOpenServerTcpConnection invalid address or port");
        }
    }catch(...)
    {
        eConfLog(ERR, "BFCPApiOpenServerTcpConnection exp");
    }
        return Status ;   
}

int BFCPApi::BFCPApiCloseTcpConnection(){
    SetWindowHandle(NULL);
    bfcp_mutex_lock(m_mutexParticipant);
    if ( m_BFCP_Participant != NULL )
        delete m_BFCP_Participant;
    m_BFCP_Participant = NULL ;
    bfcp_mutex_unlock(m_mutexParticipant);

    bfcp_mutex_lock(m_mutexServer);
    if ( m_BFCP_Server != NULL ){
        delete m_BFCP_Server;
        m_BFCP_Server = NULL ;
    }
    bfcp_mutex_unlock(m_mutexServer);
    return BFCPAPI_SUCCESS;
}

void BFCPApi::SetWindowHandle(HWND hWndApplicationSelected){
    bool Status = false  ;
    if ( m_BFCP_Participant ){
        BFCP_fsm::e_BFCP_ACT action = BFCP_fsm::BFCP_ACT_FloorRequest ;
        if ( !hWndApplicationSelected ){
            action =  BFCP_fsm::BFCP_ACT_FloorRelease  ;
        }
        s_bfcp_msg_event evt ;
        memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
        evt.pt_param = (void*)hWndApplicationSelected ;
        Status =  m_BFCP_Participant->FsmCtrlPerform( action , &evt ) ;
    }
   
    if ( Status ) {
        eConfLog(ERR,"SetWindowHandle success update Hwnd [0x%x] => [0x%x] ",m_hWndApplicationSelected , hWndApplicationSelected);
        m_hWndApplicationSelected = hWndApplicationSelected ;
    }
    
}

void BFCPApi::setCodecControllerAPI( CodecControllerAPI* pCodecControler ) {
    if(m_codecControler)
    {
        m_codecControler->RemoveCodecControllerCB(this);
    }
    m_codecControler = pCodecControler ;
    if(m_codecControler)
    {
        m_codecControler->AddCodecControllerCB(this);
    }
}


void BFCPApi::setCallControllerAPI( CallControllerAPI* pCallControler, const void* pCallStackGroup ){
    if(m_callControler)
    {
		m_callControler->RemoveCallStackCB(m_callStackGroup, this);
	}
 
    m_callControler = pCallControler ;
    m_callStackGroup =(void*) pCallStackGroup ;
    if(m_callControler)
    {
        m_callControler->AddCallStackCB(m_callStackGroup, this);
    }
}

const void *BFCPApi::OnWindowGrabberCreated(const void *callHandle, const unsigned int channelId, const void *windowGrabber, VideoFormatStruct *format, Codec *codec)
{
    m_windowGrabber = windowGrabber;
    eConfLog(INF,_T("OnWindowGrabberCreated [%p]"),m_windowGrabber); 
    return m_windowGrabber;
}


void BFCPApi::OnModuleRemoved(const void *confHandle, const void *module)
{
    //eConfLog(INF,_T("OnModuleRemoved ")); 
}


void BFCPApi::OnError(const void *handle, unsigned int errorCode)
{
    eConfLog(INF,_T("OnError %d "),errorCode); 
}

void BFCPApi::OnConnectedCall(const void *confHandle, const void *callHandle, RemotePartyInformations &informations)
{
    eConfLog(INF,_T("OnConnectedCall [%p]"),confHandle); 
}


void BFCPApi::OnReadyToOpenChannels(const void *handle)
{

    //eConfLog(INF,_T("OnReadyToOpenChannels ")); 
}


void BFCPApi::OnEndOfCall(const void *handle, const unsigned int reason, const TCHAR * szExtendedReason)
{

    //eConfLog(INF,_T("OnConnectedCall ")); 
}


void BFCPApi::OnChannelCreated(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec)
{
    //eConfLog(INF,_T("OnChannelCreated ")); 
}


void BFCPApi::OnChannelDestroyed(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec)
{

    //eConfLog(INF,_T("OnChannelDestroyed")); 
}


const unsigned int BFCPApi::OnCanUseCodecForAnOutgoingChannel(const void *callHandle, Codec *codec)
{
    eConfLog(INF,_T("OnCanUseCodecForAnOutgoingChannel [%s]"),codec?codec->ToString():""); 
    return true;
}

// FSM server callback exit function ( if transaction success ) 
bool BFCPApi::OnBfcpServerEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent )
{
    bool Status = false ; 
    if ( !p_FsmEvent ) 
        return Status ; 
        
    eConfLog(INF,_T("OnBfcpServerEvent evt[%s] state[%s]"), getBfcpFsmAct(p_evt),getBfcpFsmAct(p_FsmEvent->State)  ); 

    switch ( p_evt )
    {
    case BFCP_fsm::BFCP_ACT_UNDEFINED :
        break ; 
    case BFCP_fsm::BFCP_ACT_INITIALIZED  :
        break ; 
    case BFCP_fsm::BFCP_ACT_DISCONNECTED  :
        if ( m_BFCP_Server ){
            // Destroy default client (pt a pt )
            m_BFCP_Server->RemoveUserInConf(SERVER_DEFAULT_USERID);
        }
        // alert application only if it's client 
        // Status = disconnected() ; 
        break ; 
    case BFCP_fsm::BFCP_ACT_CONNECTED :
        if ( m_BFCP_Server )
            m_BFCP_Server->DumpServer();
        // alert application only if it's client 
        // Status = connected() ; 
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorRequest :
        if ( m_BFCP_Server ){
            e_bfcp_status bfcp_status = BFCP_PENDING ;
            UINT32 userID = 0 ;
            UINT32 beneficiaryID = 0 ; 
            UINT16 floorRequestID = 0 ;
            if ( m_BFCP_Server->GetFloorState(&bfcp_status , &userID ,  &beneficiaryID ,  &floorRequestID  ) ){
                if ( bfcp_status == BFCP_GRANTED && userID )
                    m_BFCP_Server->FloorRequestRespons( userID , beneficiaryID , p_FsmEvent->TransactionID ,floorRequestID , BFCP_REVOKED , 0 , BFCP_NORMAL_PRIORITY , false );
            }
            Status = m_BFCP_Server->FloorRequestRespons( p_FsmEvent->userID , p_FsmEvent->userID , p_FsmEvent->TransactionID , p_FsmEvent->FloorRequestID , BFCP_ACCEPTED , 0 , BFCP_NORMAL_PRIORITY , false );
            if ( Status )
                Status = m_BFCP_Server->FloorRequestRespons( p_FsmEvent->userID , p_FsmEvent->userID , p_FsmEvent->TransactionID ,  p_FsmEvent->FloorRequestID ,BFCP_GRANTED , 0 , BFCP_NORMAL_PRIORITY , true );
        }
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorRelease  :
        if ( m_BFCP_Server ){
            Status = m_BFCP_Server->SendFloorStatus( 0 , 0 , 0 , NULL , true ) ; 
        }
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
        if ( m_BFCP_Server ){
            // Ajout du client par defaut (pt a pt )
            if ( !m_BFCP_Participant  ){
                m_BFCP_Server->AddUser(SERVER_DEFAULT_USERID);
                m_BFCP_Participant = new BFCP_Participant( m_confID , SERVER_DEFAULT_USERID , m_floorID , 0 , this );
                if ( m_BFCP_Participant )
                {
                    BFCPApiOpenParticipantTcpConnection( m_BFCP_Server->getLocalAdress() , m_BFCP_Server->getLocalPort()+4 , m_BFCP_Server->getLocalAdress() , m_BFCP_Server->getLocalPort(),false );
                }
            }
        }
        break ; 
    case BFCP_fsm::BFCP_ACT_Error :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAccepted :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusAborted :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorRequestStatusGranted  :
        break ; 
    case BFCP_fsm::BFCP_ACT_UserStatus :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorStatusAccepted :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorStatusAborted :
        break ; 
    case BFCP_fsm::BFCP_ACT_FloorStatusGranted  :
        break ; 
    case BFCP_fsm::BFCP_ACT_ChairActionAck :
        break ; 
    case BFCP_fsm::BFCP_ACT_HelloAck  :
        if ( m_BFCP_Server ){
            Status = m_BFCP_Server->SendFloorStatus( p_FsmEvent->userID , p_FsmEvent->BeneficiaryID , 0 , NULL , false ) ; 
        }
        break ; 
    case BFCP_fsm::BFCP_ACT_SHARE :
        break ; 
    case BFCP_fsm::BFCP_ACT_SERVER_SHARE :
        break ; 
    default :
        break ; 
    }
    if ( Status &&  m_listener ) 
        m_listener->OnBfcpApiEvent( p_FsmEvent );
    return Status ;
} 

// FSM server callback exit function ( if transaction success ) 
bool BFCPApi::OnBfcpParticipantEvent(BFCP_fsm::e_BFCP_ACT p_evt ,BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent )
{
    bool Status = false ; 
    if ( !p_FsmEvent ) 
        return Status ; 
        
    eConfLog(INF,_T("OnBfcpParticipantEvent evt[%s] state[%s]"), getBfcpFsmAct(p_evt),getBfcpFsmAct(p_FsmEvent->State)  ); 

    switch ( p_evt )
    {
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
        if ( p_FsmEvent->State == BFCP_fsm::BFCP_ACT_SHARE )
            Status = updateHwnd(p_FsmEvent);
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
    if ( Status &&  m_listener ) 
        m_listener->OnBfcpApiEvent( p_FsmEvent );
    return Status ;
}


bool BFCPApi::connected(){
    eConfLog(INF,_T("BFCP connection success."));
    if ( m_listener )
        m_listener->OnBfcpApiConnected(true);
    return true ;
}

bool BFCPApi::disconnected(){
    eConfLog(INF,_T("BFCP disconnected."));
    m_hWndApplicationSelected = NULL ; 
    //SetWindowHandle2Grabber();
    if ( m_listener )
        m_listener->OnBfcpApiConnected(false);
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

bool BFCPApi::floorRequestStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt){
 if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP floorRequestStatusGranted. myFloorId[%d] eventFloorId[%d]"),m_floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  ||  m_floorID == p_evt->FloorID ){
        return SetWindowHandle2Grabber();
    }else{
        eConfLog(ERR,_T("BFCP floorRequestStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ;
    }
}

bool BFCPApi::floorRequestStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP floorRequestStatusAborted. myFloorId[%d] eventFloorId[%d]"),m_floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  || m_floorID == p_evt->FloorID ){
        m_hWndApplicationSelected = NULL ; 
        SetWindowHandle2Grabber();
        return true ;
    }
    else {
        eConfLog(ERR,_T("BFCP floorRequestStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCPApi::floorRequestStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  || m_floorID == p_evt->FloorID ){
        return true ;
    }
    else{
        eConfLog(ERR,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCPApi::floorReleaseStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ){
        m_hWndApplicationSelected = NULL ; 
        SetWindowHandle2Grabber();
        return true ;
    } else{
        eConfLog(ERR,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCPApi::floorStatusAccepted( BFCP_fsm::st_BFCP_fsm_event* p_evt) {
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP FloorStatusAccepted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ){
        return true ;
    } else{
        eConfLog(ERR,_T("BFCP FloorStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCPApi::floorStatusGranted( BFCP_fsm::st_BFCP_fsm_event* p_evt ) {
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP FloorStatusGranted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ){
        return true ;
    } else{
        eConfLog(ERR,_T("BFCP FloorStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCPApi::floorStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt ) {
    if ( !p_evt )
        return false ;
    eConfLog(INF,_T("BFCP FloorRequestAborted. myFloorId[%d] eventFloorId[%d] "),m_floorID , p_evt->FloorID );
    if ( m_floorID == p_evt->FloorID ){

        return true ;
    } else{
        eConfLog(ERR,_T("BFCP FloorRequestAborted. myFloorId[%d] != eventFloorId[%d]"),m_floorID , p_evt->FloorID );
        return false ; 
    }
}


bool BFCPApi::floorRequest(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    bool status = false ;
    if ( m_BFCP_Participant->bfcp_floorRequest_participant(m_floorID) == -1 ){
        eConfLog(ERR,"FloorRequest send  floorRequest failed ! ");
    }else{
        status = true ;
    }
    return status ;
}

bool BFCPApi::floorRelease(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    bool status = false ;
    if ( m_BFCP_Participant->bfcp_floorRelease_participant() == -1 ){
        eConfLog(ERR,"FloorRelease send  FloorRelease failed ! ");
    }else{
        status = true ;
    }
    return status ;
}

bool BFCPApi::updateHwnd(BFCP_fsm::st_BFCP_fsm_event* p_evt){
    // call by SetWindowHandle state BFCP_ACT_FloorRequest 
    // Update hwnd made by status true 
    eConfLog(INF,"updateHwnd  [0x%p] ",p_evt?p_evt->pt_param:0);
    if ( p_evt ){
        m_hWndApplicationSelected = (HWND) p_evt->pt_param ;
        return SetWindowHandle2Grabber();
    }
    return false ;
}

bool BFCPApi::SetWindowHandle2Grabber(){
    FTIWindowGrabber *pIWindowGrabber = NULL;
     eConfLog(INF,"SetWindowHandle2Grabber [0x%p] m_windowGrabber[0x%p] m_codecControler[0x%p] m_confHandle[0x%p]",
         m_hWndApplicationSelected,m_windowGrabber ,m_codecControler , m_confHandle);
    if ( m_windowGrabber && m_codecControler && m_confHandle ){
        pIWindowGrabber = (FTIWindowGrabber *)m_codecControler->QueryInterface(m_confHandle, m_windowGrabber, (void*)&FTIID_WindowGrabber);	
        if(pIWindowGrabber){
            pIWindowGrabber->SetWindowHandle((ULONG)m_hWndApplicationSelected);
            return true ;
        }
        else 
            return false ;
    }else
        return false  ;
}

// Use only for nego .
void BFCPApi::SetConfID( UINT32 p_confID ) 
{ 
    m_confID = p_confID ; 
    bfcp_mutex_lock(m_mutexServer);
    if ( m_e_floorctrlMode && m_BFCP_Server && m_BFCP_Server->GetConfID()!= p_confID ){
        delete m_BFCP_Server ;
        m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF ,m_confID , m_userID , m_floorID , m_streamID,  this);
    }
    bfcp_mutex_unlock(m_mutexServer);
}

UINT32 BFCPApi::GetConfID( )
{ 
    if ( m_e_floorctrlMode && m_BFCP_Server )
        return m_BFCP_Server->GetConfID();
    return m_confID ;
}

void BFCPApi::SetUserID( UINT16 p_userID )
{ 
    m_userID = p_userID ;
}

bool BFCPApi::AddUserIDinConf( UINT16 p_userID )
{
    bool Status = false ; 
    if ( m_e_floorctrlMode && m_BFCP_Server ){
        Status = m_BFCP_Server->AddUser(p_userID);
    }
    return Status ;
}

bool  BFCPApi::RemoveUserIDinConf( UINT16 p_userID )
{ 
    bool Status = false ; 
    if ( m_BFCP_Server )
        Status =  m_BFCP_Server->RemoveUserInConf(p_userID);
    return Status ;
}


UINT16 BFCPApi::GetUserID( )
{ 
    if ( m_e_floorctrlMode && m_BFCP_Server )
        return m_BFCP_Server->GetFirstUserID();
    return m_userID ;
}

void BFCPApi::SetFloorID( UINT16 p_floorID )
{ 
    m_floorID = p_floorID ;
    bfcp_mutex_lock(m_mutexServer);
    if ( m_e_floorctrlMode && m_BFCP_Server && m_BFCP_Server->GetFloorID()!= p_floorID ){
        delete m_BFCP_Server ;
        m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF ,m_confID , m_userID , m_floorID , m_streamID,  this);
    }
    bfcp_mutex_unlock(m_mutexServer);
}

UINT16 BFCPApi::GetFloorID( )
{ 
    if ( m_e_floorctrlMode && m_BFCP_Server )
        return m_BFCP_Server->GetFloorID();
    return m_floorID ;
}

void BFCPApi::SetStreamID( UINT16 p_streamID )
{ 
    m_streamID = p_streamID ; 
#if 0 // Server don't support stream id , TODO ...... make code 
    bfcp_mutex_lock(m_mutexServer);
    if ( m_e_floorctrlMode && m_BFCP_Server && m_BFCP_Server->GetStreamID()!= p_streamID ){
        delete m_BFCP_Server ;
        m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF ,m_confID , m_userID , m_floorID , m_streamID,  this);
    }
    bfcp_mutex_unlock(m_mutexServer);
#endif
}

UINT16 BFCPApi::GetStreamID( )
{ 
   if ( m_e_floorctrlMode && m_BFCP_Server )
        return m_BFCP_Server->GetStreamID();
    return m_streamID ;
}

void BFCPApi::SetIsPassive( bool p_IsServer )
{ 
    eConfLog(INF,"SetIsPassive [%s] => [%s] ",m_IsPassive?"true":"false",p_IsServer?"true":"false");
    m_IsPassive = p_IsServer ;
}

bool BFCPApi::GetIsPassive( )
{ 
    return m_IsPassive ;
}

void BFCPApi::SetFloorctrlMode( e_floorctrlMode pfloorctrlMode )
{
    eConfLog(INF,"SetFloorctrlMode [%d] => [%d] ",m_e_floorctrlMode,pfloorctrlMode);
    if ( m_e_floorctrlMode == pfloorctrlMode && ( m_BFCP_Participant||m_BFCP_Server) )
        return ;
        
    m_e_floorctrlMode = pfloorctrlMode ;
    if ( pfloorctrlMode ){
        bfcp_mutex_lock(m_mutexParticipant);
        if ( m_BFCP_Participant ){
            delete m_BFCP_Participant ;
            m_BFCP_Participant = NULL ;
        }
        bfcp_mutex_unlock(m_mutexParticipant);
        bfcp_mutex_lock(m_mutexServer);
        if (  !m_BFCP_Server ){
            m_BFCP_Server = new BFCP_Server( BFCP_MAX_CONF ,m_confID , m_userID , m_floorID , m_streamID,  this);
        }
        bfcp_mutex_unlock(m_mutexServer);
    }
    bfcp_mutex_lock(m_mutexServer);
    if ( !pfloorctrlMode && m_BFCP_Server ){
        delete m_BFCP_Server ;
        m_BFCP_Server = NULL ; 
    }
    bfcp_mutex_unlock(m_mutexServer);   
}

e_floorctrlMode BFCPApi::GetFloorctrlMode(void)
{
    return m_e_floorctrlMode;
} 

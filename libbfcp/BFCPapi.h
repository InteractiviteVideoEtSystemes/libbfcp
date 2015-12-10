/**
 *
 * Sample test of BFCP particpant API .
 *
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file BFCPapi.h
 *
 * \version $Revision: 2172 $
 *
 * \date $Date: 2014-01-27 09:08:19 +0100 (Mon, 27 Jan 2014) $
 *
 * \remarks 
 *
 * \ingroup libbfcp
 *
 * \brief API for BFCP in eConf (Windows) context . 
 */
#ifndef _BFCPAPI_H_
#define _BFCPAPI_H_
#include "icallstackcb.h"
#include "codecControllercb.h"
#include "BFCP_participant.h"
#include "BFCP_Server.h"


#if defined(__PCWINDOWS__) || defined(__IPAQ__)
#ifdef BFCP_DLL_EXPORTS
	#define BFCP_API __declspec(dllexport)
#else
	#define BFCP_API __declspec(dllimport)
#endif
#else
#define BFCP_API
#endif

class CodecControllerAPI;
class CallControllerAPI;

#define BFCPAPI_SUCCESS 1
#define BFCPAPI_ERROR   0

class BFCP_API BFCPApi : public ICallStackCB,
						 public CodecControllerCB,
						 public BFCP_Participant::ParticipantEvent ,
						 public BFCP_Server::ServerEvent 
{
public:
    class BFCPApiEvent
    {
        public: virtual bool OnBfcpApiConnected(bool p_connected) = 0 ;
        public: virtual bool OnBfcpApiEvent(void* p_ApiEvent ) = 0 ;
    };
    typedef BFCP_fsm::st_BFCP_fsm_event s_bfcpApi_event ;
    BFCPApi(BFCPApiEvent* p_listener);
    ~BFCPApi();

    int                 BFCPApiOpenTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port);
    int                 BFCPApiCloseTcpConnection();
    void                SetWindowHandle( HWND hWndApplicationSelected);
    void                setCodecControllerAPI( CodecControllerAPI* pCodecControler );
    void                setCallControllerAPI( CallControllerAPI* pCallControler , const void* pCallStackGroup);
    void                setConfHandle( const void *	pConfHandle) { m_confHandle = pConfHandle ; } ;
    const void *        GetWindowGrabber() { return m_windowGrabber ; };
    
    // Use only for nego .
    void                SetConfID( UINT32 p_confID ) ;
    UINT32              GetConfID( ) ;
    void                SetUserID( UINT16 p_userID );
    UINT16              GetUserID( );
    void                SetFloorID( UINT16 p_floorID );
    UINT16              GetFloorID( ) ;
    void                SetStreamID( UINT16 p_streamID );
    UINT16              GetStreamID( );
    void                SetIsPassive( bool p_IsServer );
    bool                GetIsPassive( ) ;
    void                SetFloorctrlMode( e_floorctrlMode pfloorctrlMode ) ;
    e_floorctrlMode GetFloorctrlMode(void) ;
    
    // User management ( Server ) 
    bool AddUserIDinConf( UINT16 p_userID );
    bool RemoveUserIDinConf( UINT16 p_userID );

	// ICallSatckCB implementation
	virtual void		OnConnectedCall(const void *confHandle, const void *callHandle, RemotePartyInformations &informations);
	virtual void		OnReadyToOpenChannels(const void *handle);
	virtual void		OnEndOfCall(const void *handle, const unsigned int reason, const TCHAR * szExtendedReason);
	virtual void		OnChannelCreated(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec);
	virtual void		OnChannelDestroyed(const void *handle, const unsigned int channelId, Direction dir, FtCodecType type, Codec *codec);
	virtual const void	*OnWindowGrabberCreated(const void *callHandle, const unsigned int channelId, const void *windowGrabber, VideoFormatStruct *format, Codec *codec);
	virtual void		OnModuleRemoved(const void *confHandle, const void *module);
	virtual const unsigned int	OnCanUseCodecForAnOutgoingChannel(const void *callHandle, Codec *codec);
	virtual	void		OnError(const void *handle, unsigned int errorCode);
	
    // BFCP_Participant::ParticipantEvent
    virtual bool OnBfcpParticipantEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent );
    // BFCP_Server::ServerEvent
    virtual bool OnBfcpServerEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent );
 
public:
    bool                connected(void); 
    bool                disconnected(void); 
    bool                floorRequestStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRequestStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRequestStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorReleaseStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                SetWindowHandle2Grabber(void);
    bool                floorRequest(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRelease(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                updateHwnd(BFCP_fsm::st_BFCP_fsm_event* p_evt);

private:
    BFCP_Participant*   m_BFCP_Participant ;
    BFCP_Server*        m_BFCP_Server ;
    const void *	    m_windowGrabber;
    const void *	    m_confHandle;
    CodecControllerAPI* m_codecControler ;
    CallControllerAPI*	m_callControler;	
    void*               m_callStackGroup ;
    e_floorctrlMode     m_e_floorctrlMode ;
    HWND                m_hWndApplicationSelected ;
    // Only for SIP nego 
    UINT32              m_confID ;
    UINT16              m_userID ;
    UINT16              m_floorID ;
    UINT16              m_streamID ;
    bool                m_IsPassive ;
    BFCPApiEvent*       m_listener ;
    int                 BFCPApiOpenServerTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive);
    int                 BFCPApiOpenParticipantTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive);
    bfcp_mutex_t       m_mutexServer ;
    bfcp_mutex_t       m_mutexParticipant ;
};


static const struct _bfcp_floorctrlModes {
	int floorctrlMode;
	const char *description;
	const char *UpperDescription;
} _bfcp_floorctrlMode[] = {
	{ FLOOCTRL_MODE_CLIENT, "c-only" , "C-ONLY"},
	{ FLOOCTRL_MODE_SERVER, "s-only" , "S-ONLY"},
	{ FLOOCTRL_MODE_CLIENT_AND_SERVER, "c-s" , "C-S"},
};
inline const char* getBfcpFloorctrlMode( UINT32 p){
    if ( p < FLOOCTRL_MODE_CLIENT || p > FLOOCTRL_MODE_CLIENT_AND_SERVER )
        p=0;
    return _bfcp_floorctrlMode[p].description ;
}

#endif

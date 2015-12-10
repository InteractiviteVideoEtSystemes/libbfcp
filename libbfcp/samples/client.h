/**
 *
 *
 * \brief Sample test of BFCP particpant API .
 *
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file client.h
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
 */

#ifndef _BFCP_CLIENT_TEST_H_
#define _BFCP_CLIENT_TEST_H_
#include <bfcp_participant.h>

#define BFCPAPI_SUCCESS 1
#define BFCPAPI_ERROR 0

typedef enum {
    FLOOCTRL_MODE_CLIENT = 0 ,
    FLOOCTRL_MODE_SERVER ,
    FLOOCTRL_MODE_CLIENT_AND_SERVER
}e_floorctrlMode ;

class  sampleClient : public BFCP_Participant::ParticipantEvent {
public:
    sampleClient();
    ~sampleClient();
    void                SetConfID( UINT32 p_confID ) ;
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
    void                menu(char *lineptr) ;
    // BFCP_Participant::ParticipantEvent
    virtual bool OnBfcpParticipantEvent(BFCP_fsm::e_BFCP_ACT p_evt , BFCP_fsm::st_BFCP_fsm_event* p_FsmEvent );
    // traces
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) ;

private:
    bool                connected(void);
    bool                disconnected(void);
    bool                floorRequestStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRequestStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRequestStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusAccepted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusGranted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorReleaseStatusAborted(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRequest(BFCP_fsm::st_BFCP_fsm_event* p_evt);
    bool                floorRelease(BFCP_fsm::st_BFCP_fsm_event* p_evt);


    BFCP_Participant*   m_BFCP_Participant ;
    e_floorctrlMode       m_e_floorctrlMode ;
    UINT32                  m_confID ;
    UINT16                  m_userID ;
    UINT16                  m_floorID ;
    UINT16                  m_streamID ;
    bool                      m_IsPassive ;
    int                         OpenParticipantTcpConnection(const char* local_address, int local_port, const char* remote_address, int remote_port, bool isPassive);
};

#endif

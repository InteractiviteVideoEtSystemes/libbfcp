/**
 *
 * \brief Finite State Machine for BFCP 
 *
 * \author Philippe Verney
 *
 * \file bfcp_fsm.h
 *
 * \version $Revision: 2583 $
 *
 * \date $Date: 2015-11-13 11:17:55 +0100 (Fri, 13 Nov 2015) $
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \remarks :
 */
 #ifndef _BFCP_FSM_H_
#define _BFCP_FSM_H_

#include "bfcp_messages.h"
#include "bfcp_strings.h"


class BFCP_fsm
{
public:
    BFCP_fsm(void);
    virtual ~BFCP_fsm(void);
    /* \enum e_BFCP_ACT 
    * State machine event and state 
    */
    
    typedef enum {
        BFCP_ACT_UNDEFINED = 0 ,  /** @brief State machine not initialized */
        BFCP_ACT_INITIALIZED , /** @brief State machine initialized */
        BFCP_ACT_DISCONNECTED , /** @brief event / state disconnected  */
        BFCP_ACT_CONNECTED ,  /** @brief event / state connected  */
        BFCP_ACT_FloorRequest ,  /** @brief  event / state BFCP floor request */
        BFCP_ACT_FloorRelease , /** @brief  event / state BFCP floor release */
        BFCP_ACT_FloorRequestQuery , /** @brief  event / state BFCP Floor Request Query */
        BFCP_ACT_UserQuery ,  /** @brief  event / state BFCP UserQuery */
        BFCP_ACT_FloorQuery , /** @brief  event / state  BFCP FloorQuery */
        BFCP_ACT_ChairAction , /** @brief  event / state  BFCP ChairAction */
        BFCP_ACT_Hello, /** @brief  event / state  BFCP Hello */
        BFCP_ACT_Error, /** @brief  event / state BFCP Error  */
        BFCP_ACT_FloorRequestStatusAccepted , /** @brief  event / state  BFCP FloorRequestStatusAccepted */
        BFCP_ACT_FloorRequestStatusAborted , /** @brief  event / state  BFCP FloorRequestStatusAborted */
        BFCP_ACT_FloorRequestStatusGranted , /** @brief  event / state  BFCP FloorRequestStatusGranted */
        BFCP_ACT_UserStatus , /** @brief  event / state  BFCP UserStatus */
        BFCP_ACT_FloorStatusAccepted , /** @brief  event / state  BFCP FloorStatusAccepted */
        BFCP_ACT_FloorStatusAborted , /** @brief  event / state  BFCP FloorStatusAborted */
        BFCP_ACT_FloorStatusGranted , /** @brief event / state   BFCP FloorStatusGranted */
        BFCP_ACT_ChairActionAck , /** @brief event / state  BFCP ChairActionAck  */
        BFCP_ACT_HelloAck , /** @brief event / state   BFCP HelloAck */
        BFCP_ACT_SHARE , /** @brief  event / state  participant send video stream  */
        BFCP_ACT_SERVER_SHARE, /** @brief event / state   server send video stream */
	BFCP_ACT_GoodBye,
	BFCP_ACT_GoodByeAck,
        BFCP_ACT_LAST /** @brief just for size   */
    } e_BFCP_ACT ;   
        
protected:
    typedef bool (BFCP_fsm::*tBFCP_fsm_function) ( s_bfcp_msg_event* p_evt ) ;
    typedef struct
    {
        e_BFCP_ACT new_state ;
        tBFCP_fsm_function function ;
    } st_BFCP_fsm ;
    
    st_BFCP_fsm m_BFCPStateMachine[BFCP_ACT_LAST][BFCP_ACT_LAST] ;
    e_BFCP_ACT m_bfcpFsmSt ;
    
public:
    /** \struct st_BFCP_fsm_event 
     * \brief State machine event 
    */
    typedef struct 
    {
	int transport;
        e_BFCP_ACT  State ;  /** \brief State of Final State Machine*/
        UINT16  TransactionID ; /** \brief transaction ID of request  \ref BFCP-PROTOCOL-TRANSACTION   */
        UINT16  userID ;  /** \brief user ID of request \ref BFCP-COMMON-HEADER  */
        UINT32  conferenceID ; /** \brief conference ID of request \ref BFCP-COMMON-HEADER */
        UINT16  FloorID ; /** \brief floor id of request \ref FLOOR-ID*/
        UINT16  FloorRequestID ; /** \brief floor request id \ref FLOOR-REQUEST-ID */
        UINT16  QueuePosition ;  /** \brief queue position \ref  REQUEST-STATUS  */
        UINT16  BeneficiaryID ; /** \brief benficiary ID of request  \ref BENEFICIARY-ID */
        UINT16  i_parm ; /** \brief  integer for variables paramters */
        char    c_param[BFCP_STRING_SIZE] ; /** \brief  char table for or variables paramters  */
        void*   pt_param ; /** \brief   pointer  or variables paramters */
    }
    st_BFCP_fsm_event ;
    
    
    /** 
     *  Copy an s_bfcp_msg_event into a st_BFCP_fsm_event. The FSM event is notified to the external
     *  application.
     *
     *  @param p_fsm_evt: FSM event structure to fill
     *  @param p_state: state of FSM in which the event needs to be filled.
     *  @param p_bfcp_evt: message event processed by state machine. Can be NULL
     */
    void InitFsmEvent( st_BFCP_fsm_event * p_fsm_evt, e_BFCP_ACT p_state, const s_bfcp_msg_event* p_bfcp_evt );
    
    e_BFCP_ACT GetFSMState() { return m_bfcpFsmSt ; } ;
    bool FsmCtrlPerform(e_BFCP_ACT p_evt , s_bfcp_msg_event* p_param =NULL );
private:
    char m_name[BFCP_STRING_SIZE] ;
    
public:
    // name for traces 
    void setName(const char* p_name );
    
    // event action for fsm
    virtual bool BFCPFSM_FsmEvent( s_bfcp_msg_event* p_evt );
    // logs
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...) = 0;
    // Virtual FSM transistion
    virtual void BFCPFSM_init(st_BFCP_fsm BFCPStateMachine[BFCP_ACT_LAST][BFCP_ACT_LAST]) ;
    virtual bool BFCPFSM_NullFunction( s_bfcp_msg_event* p_evt );
    virtual bool BFCPFSM_Connected(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_Disconnected(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_FloorStatusAccepted(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_FloorStatusGranted(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_FloorStatusAborted(  s_bfcp_msg_event* p_evt ){return true;};
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
    virtual bool BFCPFSM_FloorRequestStatusAccepted(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_FloorRequestStatusGranted(  s_bfcp_msg_event* p_evt ) {return true;};
    virtual bool BFCPFSM_FloorRequestStatusAborted(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_FloorReleaseStatusAborted(  s_bfcp_msg_event* p_evt ) {return true;};
    virtual bool BFCPFSM_FloorRelease(  s_bfcp_msg_event* p_evt ) {return true;};
    virtual bool BFCPFSM_FloorRequest(  s_bfcp_msg_event* p_evt ){return true;};
    virtual bool BFCPFSM_UpdateHwnd(  s_bfcp_msg_event* p_evt ) {return true;};
    virtual bool BFCPFSM_Hello(s_bfcp_msg_event* p_evt) {return true;};
    virtual bool BFCPFSM_HelloAck(s_bfcp_msg_event* p_evt) {return true;};
    virtual bool BFCPFSM_PrimitiveNotSupported(s_bfcp_msg_event* p_evt) {return true;};
    // Virtual FSM exit function
    virtual bool BFCPFSM_UpdatesBfcpFsmEvent( s_bfcp_msg_event* p_bfcp_evt , e_BFCP_ACT p_evt ,e_BFCP_ACT p_st ){return true;};
};

static const struct _bfcp_actions {
	int state;
	const char *description;
} _bfcp_action[] = {
	{ BFCP_fsm::BFCP_ACT_UNDEFINED, "undefined" },
	{ BFCP_fsm::BFCP_ACT_INITIALIZED, "initialized" },
	{ BFCP_fsm::BFCP_ACT_DISCONNECTED, "disconnected" },
	{ BFCP_fsm::BFCP_ACT_CONNECTED, "connected" },
	{ BFCP_fsm::BFCP_ACT_FloorRequest, "floorRequest" },
	{ BFCP_fsm::BFCP_ACT_FloorRelease, "floorRelease" },
	{ BFCP_fsm::BFCP_ACT_FloorRequestQuery, "FloorRequestQuery" },
	{ BFCP_fsm::BFCP_ACT_UserQuery, "UserQuery" },
	{ BFCP_fsm::BFCP_ACT_FloorQuery, "FloorQuery" },
	{ BFCP_fsm::BFCP_ACT_ChairAction, "ChairAction" },
	{ BFCP_fsm::BFCP_ACT_Hello, "Hello" },
	{ BFCP_fsm::BFCP_ACT_Error, "Error" },
    { BFCP_fsm::BFCP_ACT_FloorRequestStatusAccepted ,"FloorRequestStatusAccepted" },
    { BFCP_fsm::BFCP_ACT_FloorRequestStatusAborted ,"FloorRequestStatusAborted" },
    { BFCP_fsm::BFCP_ACT_FloorRequestStatusGranted ,"FloorRequestStatusGranted" },
    { BFCP_fsm::BFCP_ACT_UserStatus ,"UserStatus" },
    { BFCP_fsm::BFCP_ACT_FloorStatusAccepted ,"FloorStatusAccepted" },
    { BFCP_fsm::BFCP_ACT_FloorStatusAborted ,"FloorStatusAborted" },
    { BFCP_fsm::BFCP_ACT_FloorStatusGranted ,"FloorStatusGranted" },
    { BFCP_fsm::BFCP_ACT_ChairActionAck ,"ChairActionAck" },
    { BFCP_fsm::BFCP_ACT_HelloAck ,"HelloAck" },
    { BFCP_fsm::BFCP_ACT_SHARE,"Share" },
    { BFCP_fsm::BFCP_ACT_SERVER_SHARE,"ServerShare" },
    { BFCP_fsm::BFCP_ACT_LAST, "Unknown" }
} ;


__inline const char* getBfcpFsmAct( UINT32 p){
    if ( p < BFCP_fsm::BFCP_ACT_INITIALIZED || p > BFCP_fsm::BFCP_ACT_LAST )
        p=0;
    return _bfcp_action[p].description ;
}
#endif

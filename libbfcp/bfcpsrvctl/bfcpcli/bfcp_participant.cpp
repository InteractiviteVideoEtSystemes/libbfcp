
#ifdef WIN32
#include "stdafx.h"
#endif
#include <sstream>

#include "BFCPexception.h"
#include "bfcp_participant.h"
#include "bfcp_strings.h"
#include "stdafx.h"
#include "bfcp_threads.h"
    
/* Macro to check for errors after sending a BFCP message */
#define BFCP_SEND_CHECK_ERRORS(msg,args,err)			\
    if (args != NULL) bfcp_free_arguments(args);\
    if (msg != NULL) bfcp_free_message(msg); \
    if (err) Log(INF,"BFCP_Participant: error sending BFCP msg %d", err)

    
extern "C" void _ParticpantLog(char* pcFile, int iLine, int iErrorLevel, char* pcFormat, ...)
{
    static BFCP_Participant _p ;
    va_list arg;
    char s[BFCP_STRING_SIZE];
    va_start(arg,pcFormat);
    vsnprintf(s,BFCP_STRING_SIZE,pcFormat,arg);
    va_end(arg);
    return  _p.Log(pcFile, iLine, iErrorLevel, s ) ;
}
    
BFCP_Participant::BFCP_Participant(UINT32 p_confID ,UINT16 p_userID , UINT16 p_floorID , UINT16 p_streamID , BFCP_Participant::ParticipantEvent* p_ParticipantEvent)
{
    st_bfcp_participant_information* struct_participant;
    
    if(p_confID == 0)
        throw IllegalArgumentException("BFCP_Participant:: conferenceID invalid");
    if(p_userID == 0)
        throw IllegalArgumentException("BFCP_Participant:: userID invalid");
    if(p_floorID == 0)
        throw IllegalArgumentException("BFCP_Participant:: userID invalid");
    
    setName("Participant");
    
    /* Allocate and setup the new participant */
    struct_participant = (st_bfcp_participant_information*)calloc(1, sizeof(st_bfcp_participant_information));
    if(struct_participant == NULL)
        throw IllegalArgumentException("BFCP_Participant:: Allocate and setup invalid");

     Log(INF,"BFCP_Participant:: created participant conferenceID[%d] userID[%d] floorID[%d] stramID[%d]",
        p_confID , p_userID, p_floorID , p_streamID );
    struct_participant->conferenceID = p_confID;
    struct_participant->userID = p_userID;
    bfcp_insert_floor_participant(struct_participant, p_floorID) ;
    m_bfcp_participant_information = struct_participant ;
    m_currentFloorRequestID= 0 ;
    m_ParticipantEvent = p_ParticipantEvent  ; 
    bfcp_mutex_init(count_mutex, NULL);
    m_PartSocket = INVALID_SOCKET ;
    BFCP_msg_LogCallback(  _ParticpantLog  );
}

BFCP_Participant::~BFCP_Participant(void)
{
    removeSession();
#ifdef WIN32
    if ( count_mutex ) {
#endif
        bfcp_mutex_lock(count_mutex);
        if ( m_bfcp_participant_information ) {
            bfcp_destroy_bfcp_participant(&m_bfcp_participant_information);
            m_bfcp_participant_information = NULL ;
        }
        checkFloorRequestID( 0 );
        bfcp_mutex_destroy(count_mutex);
#ifdef WIN32

    }
#endif
    m_PartSocket = INVALID_SOCKET ;
}

bool BFCP_Participant::CloseTcpConnection(){
    removeSession();
    return true;
}

/* Create a new Participant */
bool BFCP_Participant::OpenTcpConnection(const char* local_address, 
                                   int local_port, 
                                   const char* remote_address, 
                                   int remote_port, 
                                   bool isServer)
{
    bool Status = false ;
    m_base_transactionID = 1 ; 
    m_bfcp_transport = BFCP_OVER_TCP;
    if ( !m_bfcp_participant_information )
    {
        Log(ERR,"BFCP_Participant:: invalid participant ! ");
        //throw IOException("BFCP_Participant:: Connection connect failed");
    }
    
    try {
        Log(INF,"BFCP_Participant:: OpenTcpConnection conferenceID[%d] userID[%d] floorID[%d] server[%s] network [%s:%d]<=>[%s:%d] ",
            m_bfcp_participant_information->conferenceID,
            m_bfcp_participant_information->userID,
            m_bfcp_participant_information->pfloors?m_bfcp_participant_information->pfloors->floorID:0,
            isServer?"TRUE":"FALSE",
            local_address?local_address:"",
            local_port?local_port:0 ,
            remote_address?remote_address:"",
            remote_port?remote_port:0 );
        SelLocalConnection(local_address,local_port,isServer?BFCPConnectionRole::PASSIVE:BFCPConnectionRole::ACTIVE);
        if ( !isServer ){
            if (remote_address!=NULL && remote_port!=0)
            {
                if ( setRemoteEndpoint(remote_address,remote_port)  ){
                    if ( connect() ) {
                        Log(INF,"BFCP_Participant:: connection lauched ");
                        Status = true ;
                    }else{
                        removeSession();
                        Log(ERR,"BFCP_Participant:: Connection connect failed ");
                        //throw IOException("BFCP_Participant:: Connection connect failed");
                    }
                }else{
                    Log(ERR,"BFCP_Participant setRemoteEndpoint failed ");
                    //throw IOException("BFCP_Participant:: setRemoteEndpoint failed");
                }
            }else{
                Log(ERR,"BFCP_Participant invalid address ");
                //throw IOException("BFCP_Participant:: invalid address ");
            }
        }else{
            if ( connect() ) {
                Log(INF,"BFCP_Participant Connection success ");
                Status = true ;
            }else{
                removeSession();
                Log(ERR,"BFCP_Participant connect failed ");
                //throw IOException("BFCP_Participant:: connect failed ");
            }
        }
    }
    catch(...) { 
        Log(ERR,_T("BFCP_Participant error")); 
        //throw IllegalArgumentException("BFCP_Participant:: failed ");
    }
    return Status ;
}

/* Destroy an existing Participant */
int BFCP_Participant::bfcp_destroy_bfcp_participant(st_bfcp_participant_information **participantp)
{
	if(participantp == NULL)
		return -1;

    st_bfcp_participant_information *participant = *participantp;
    if ( participant ){
        remove_floor_list(participant->pfloors);
        participant->pfloors = NULL ;
        free(participant);
        participant = NULL;
    }
    *participantp = NULL;
    m_bfcp_transport = -1;

	return 0;
}

/* Add a floor to the list of floors the participant will be aware of */
int BFCP_Participant::bfcp_insert_floor_participant(st_bfcp_participant_information* participant, UINT16 floorID)
{
	if(floorID <= 0)
		return -1;
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

    bfcp_floors_participant* tmp_floor = insert_floor_list(participant->pfloors,floorID, NULL);
    if ( tmp_floor ) 
        participant->pfloors = tmp_floor ;

	return 0;
}

/* Delete a floor from the list of floors the participant is aware of */
int BFCP_Participant::bfcp_delete_floor_participant(st_bfcp_participant_information* participant, UINT16 floorID)
{
	if(floorID <= 0)
		return -1;
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

	st_bfcp_floors_participant* floor = NULL ;
	st_bfcp_floors_participant* temp_floor = NULL ;;
	floor = participant->pfloors;

	if(floor != NULL) {
		if(floor->floorID == floorID) {
			participant->pfloors = floor->next;
		} else {
			while((floor->next != NULL) && (floor->next->floorID != floorID))
				floor = floor->next;
			if(floor->next!=NULL) {
				temp_floor = floor ;
				floor = floor->next;
				temp_floor->next = floor->next;
			}
		}
	}

	if((floor == NULL) || (floor->floorID != floorID))
		/* This floorID is not in the list */
		return -1;

	free(floor);
	floor = NULL;

	return 0;
}


/* BFCP Participant side Messages-related operations */

/* Hello */
int BFCP_Participant::bfcp_hello_participant(st_bfcp_participant_information* participant)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

	bfcp_arguments *arguments;
	bfcp_message *message;

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'Hello' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_Hello;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;
	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}


	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	int error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);
	
	return 0;
}

int BFCP_Participant::bfcp_floorRequest_participant(UINT16 p_floorID){
    st_bfcp_participant_information* participant =  m_bfcp_participant_information ;
    UINT16 beneficiaryID = m_bfcp_participant_information->userID ;
    e_bfcp_priority priority = BFCP_NORMAL_PRIORITY ;

    Log(INF,"BFCP_Participant:: created floorRequest floorID[%d] ",p_floorID  );
    st_bfcp_floors_participant*  floor_list=NULL ; 
    bfcp_floors_participant* tmp_floor = insert_floor_list(floor_list,p_floorID, NULL);
    if ( tmp_floor ) 
        floor_list = tmp_floor ;

    int error = bfcp_floorRequest_participant(participant, beneficiaryID, priority, floor_list, NULL);
    if((error == -1) && (floor_list != NULL)) {
        /* Free the request */
        Log(ERR,"Error sending the message: do the floors in the request exist? ");
        remove_floor_list(floor_list);
    } 
    return error ;
}

/* FloorRequest */
int BFCP_Participant::bfcp_floorRequest_participant(st_bfcp_participant_information* participant, UINT16 beneficiaryID, e_bfcp_priority priority, bfcp_floors_participant *list_floors, char *participant_info)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;
	if(priority > BFCP_HIGHEST_PRIORITY)
        priority = BFCP_HIGHEST_PRIORITY;
    if(list_floors == NULL){
        Log(ERR,"floors is NULL ");
        return -1;
    }

	bfcp_arguments *arguments = NULL;
	bfcp_message *message;
	int error = 0 ;
	size_t dLen = 0 ;
	bfcp_floor_id_list *node = NULL;

	bfcp_floors_participant *tempnode, *temp_list_floors, *floors_IDs = NULL;

    Log(INF,"bfcp_floorRequest_participant: find  participant floors[0x%p] participant floorID[%d] request floorID[%d]",
                participant->pfloors ,participant->pfloors?participant->pfloors->floorID:0,list_floors?list_floors->floorID:0);

  
	/* Check if all the provided floors exist, otherwise give an error */
	for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
		temp_list_floors = participant->pfloors;
        
        while(temp_list_floors && (temp_list_floors->floorID > tempnode->floorID)){
            Log(INF,"bfcp_floorRequest_participant: check  participant floors[%p] participant floorID[%d] request floorID[%d]",
                temp_list_floors ,temp_list_floors?temp_list_floors->floorID:0,tempnode?tempnode->floorID:0);
            temp_list_floors = temp_list_floors->next;

        }
        if((temp_list_floors == NULL) || (tempnode->floorID != temp_list_floors->floorID)){
            /* This floor is not in the list */
            Log(ERR,"bfcp_floorRequest_participant: This floor is not in the list temp_list_floors[%p] tempnode->floorID[%d] temp_list_floors->floorID[%d] ",
                temp_list_floors ,tempnode?tempnode->floorID:0 ,temp_list_floors?temp_list_floors->floorID:0);
            return -1;
        }
    }

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'FloorRequest' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_FloorRequest;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;

	floors_IDs = list_floors;
	if(floors_IDs != NULL)
		node = bfcp_new_floor_id_list(floors_IDs->floorID, 0);
	floors_IDs = floors_IDs->next;

	while(floors_IDs != NULL){
		bfcp_add_floor_id_list(node,floors_IDs->floorID, 0);
		floors_IDs = floors_IDs->next;
	}

	arguments->fID = node;

	if(beneficiaryID > 0)
		arguments->bID = beneficiaryID;
		else
		arguments->bID = participant->userID ;
		

	if(participant_info != NULL) {
		/* If there's Participant-provided Info text, add it */
		dLen = strlen(participant_info);
		if(dLen != 0) {
			arguments->pInfo = (char *)calloc(1, dLen*sizeof(char)+1);
			if(arguments->pInfo == NULL){
			    bfcp_mutex_unlock(count_mutex);
				return -1;
            }
			memcpy(arguments->pInfo, participant_info, dLen+1);
		} else
			arguments->pInfo = NULL;
	}

	arguments->priority = priority;
	
	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		Log(ERR,"Build message failed ");
		return -1;
	}

	remove_floor_list(list_floors);
    list_floors = NULL ;
	bfcp_mutex_unlock(count_mutex);

	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);

	return 0;
}

/* FloorRelease */
int BFCP_Participant::bfcp_floorRelease_participant(){
    st_bfcp_participant_information* participant =  m_bfcp_participant_information ;

    Log(INF,"BFCP_Participant:: created floorRelease FloorRequestID[%d] ",m_currentFloorRequestID  );

    int error = bfcp_floorRelease_participant(participant,m_currentFloorRequestID);
    return error ;
}


int BFCP_Participant::bfcp_floorRelease_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

	bfcp_arguments *arguments = NULL;
	bfcp_message *message;
	int error;

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'FloorRelease' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_FloorRelease;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;

	arguments->frqID = floorRequestID;

	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}


	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);


	return 0;
}

/* FloorRequestQuery */
int BFCP_Participant::bfcp_floorRequestQuery_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;
	if(floorRequestID <= 0)
		return -1;

	bfcp_arguments *arguments = NULL;
	bfcp_message *message;
	int error;

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'FloorRequestQuery' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_FloorRequestQuery;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;

	arguments->frqID = floorRequestID;

	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}

	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);


	return 0;
}

/* UserQuery */
int BFCP_Participant::bfcp_userQuery_participant(st_bfcp_participant_information* participant, UINT16 beneficiaryID)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

	bfcp_arguments *arguments = NULL;
	bfcp_message *message;
	int error;

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'UserQuery' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_UserQuery;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;

	arguments->bID = beneficiaryID;

	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}

	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);


	return 0;
}

/* UserQuery */
int BFCP_Participant::bfcp_floorQuery_participant(st_bfcp_participant_information* participant, bfcp_floors_participant *list_floors)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;

	bfcp_floors_participant *temp_list_floors, *tempnode;
	bfcp_arguments *arguments = NULL;
	bfcp_message *message;
	bfcp_floors_participant *floors_IDs;
	int error;

	/* Check if all the provided floors exist, otherwise give an error */
	for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
		temp_list_floors = participant->pfloors;
		while(temp_list_floors && (temp_list_floors->floorID > tempnode->floorID))
			temp_list_floors = temp_list_floors->next;

		if((temp_list_floors == NULL) || (tempnode->floorID != temp_list_floors->floorID))
			/* This floor is not in the list */
			return -1;
	}

	bfcp_mutex_lock(count_mutex);

	/* Prepare a new 'FloorQuery' message */
	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_FloorQuery;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;

	floors_IDs = list_floors;
	while(floors_IDs != NULL) {
		if(arguments->fID)
			bfcp_add_floor_id_list(arguments->fID, floors_IDs->floorID, 0);
		else
			arguments->fID = bfcp_new_floor_id_list(floors_IDs->floorID, 0);
		floors_IDs = floors_IDs->next;
	}

	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}
	remove_floor_list(list_floors);
    list_floors = NULL ;
	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);



	return 0;
}

int BFCP_Participant::bfcp_chairAction_participant(st_bfcp_participant_information* participant, UINT16 floorRequestID, char *statusInfo, UINT16 status, bfcp_floors_participant *list_floors, UINT16 queue_position)
{
	if(participant == NULL)
		participant = m_bfcp_participant_information ;
	if(list_floors == NULL)
		return -1;
	if(floorRequestID <= 0)
		return -1;
	if((status != BFCP_ACCEPTED) && (status != BFCP_DENIED) && (status != BFCP_REVOKED))
		return -1;

	bfcp_floors_participant *temp_list_floors, *tempnode;
	bfcp_arguments *arguments;
	bfcp_message *message;
	bfcp_floors_participant *floors_IDs;
	int error;
	bfcp_floor_request_status *fRS = NULL, *fRS_temp;
	bfcp_overall_request_status *oRS;

	/* Check if all the floors in the request exist, otherwise give an error */
	for(tempnode = list_floors; tempnode; tempnode = tempnode->next) {
		temp_list_floors = participant->pfloors;
		while(temp_list_floors && (temp_list_floors->floorID > tempnode->floorID))
			temp_list_floors = temp_list_floors->next;
		if((temp_list_floors == NULL) || (tempnode->floorID != temp_list_floors->floorID))
			/* This floor is not in the list */
			return -1;
	}

	bfcp_mutex_lock(count_mutex);

	arguments = bfcp_new_arguments();
	arguments->primitive = e_primitive_ChairAction;
	arguments->entity = bfcp_new_entity(participant->conferenceID, m_base_transactionID, participant->userID);
	m_base_transactionID++;
	
	if(status != BFCP_ACCEPTED)
		queue_position = 0;

	floors_IDs = list_floors;
	if(floors_IDs != NULL)
		fRS = bfcp_new_floor_request_status(floors_IDs->floorID, status , queue_position, floors_IDs->sInfo);
	if(fRS == NULL){
	    bfcp_mutex_unlock(count_mutex);
		return -1;
    }
	floors_IDs = floors_IDs->next;
	while(floors_IDs != NULL) {
		fRS_temp = bfcp_new_floor_request_status(floors_IDs->floorID, status, queue_position , floors_IDs->sInfo);
		if(fRS_temp != NULL)
			bfcp_list_floor_request_status(fRS, fRS_temp, NULL);
		floors_IDs = floors_IDs->next;
	}

	oRS = bfcp_new_overall_request_status(floorRequestID, status, queue_position, statusInfo);
	
	arguments->frqInfo = bfcp_new_floor_request_information(floorRequestID, oRS, fRS, NULL, NULL, BFCP_NORMAL_PRIORITY, NULL);

	message = bfcp_build_message(arguments);
	if(!message) {
		bfcp_mutex_unlock(count_mutex);
		return -1;
	}

	remove_floor_list(list_floors);
    list_floors = NULL ; 
	bfcp_mutex_unlock(count_mutex);
	/* Send the message to the FCS */
	error = sendBFCPmessage(m_PartSocket,message);
	BFCP_SEND_CHECK_ERRORS(message, arguments, error);


	return 0;
}


/* Helper operations */

/* Create a 'bfcp_floors_participant' element */
st_bfcp_floors_participant *BFCP_Participant::create_floor_list(UINT16 floorID, char *status_info)
{
	bfcp_floors_participant *floor_list;
	size_t dLen = 0;

	/* Allocate a new element */
	floor_list = (bfcp_floors_participant *)calloc(1, sizeof(bfcp_floors_participant));
	if(floor_list == NULL)
		return NULL;

	else {
		/* Initialize the new element */
		floor_list->floorID = floorID;
		if(status_info != NULL) {
			dLen = strlen(status_info);
			if(dLen != 0) {
				floor_list->sInfo = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor_list->sInfo == NULL)
					return NULL;
				memcpy(floor_list->sInfo, status_info, dLen+1);
			}
		} else
			floor_list->sInfo = NULL;
		floor_list->next = NULL;
	}

	return floor_list;
}

/* Create a 'bfcp_floors_participant' element and add it to an existing list */
bfcp_floors_participant *BFCP_Participant::insert_floor_list(st_bfcp_floors_participant* floor_list, UINT16 floorID, char *status_info)
{
	if(floorID <= 0)
		return NULL;

	st_bfcp_floors_participant* floor = NULL ; 
	st_bfcp_floors_participant* ini_floor_list = NULL ;
	size_t dLen = 0;
    Log(INF,"insert_floor_list FloorID %d ",floorID);
	/* First check if such a floor already exists */
	ini_floor_list = floor_list;
	while(ini_floor_list) {
		if(ini_floor_list->floorID == floorID){
			Log(ERR,"insert_floor_list FloorID %d already exists",floorID);
			return NULL;
        }
		ini_floor_list = ini_floor_list->next;
	}
	ini_floor_list = NULL;

	/* Allocate a new element */
    floor = (st_bfcp_floors_participant*)calloc(1, sizeof(st_bfcp_floors_participant));
    if(floor == NULL){
        Log(ERR,"insert_floor_list allocation memory failed!");
        return NULL;
    }
    memset(floor , 0 , sizeof(bfcp_floors_participant) );
    
	if(floor_list == NULL) {
	    Log(ERR,"floor_list is null create floor_list FloorID %d ",floorID);
		floor->floorID = floorID;
		if(status_info != NULL) {
			/* If there's Status Info text, add it */
			dLen = strlen(status_info);
			if(dLen != 0){
				floor->sInfo = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor->sInfo == NULL)
					return NULL;
				memcpy(floor->sInfo, status_info, dLen+1);
			}
		} else
			floor->sInfo = NULL;
		floor->next = NULL;
		floor_list = floor;
	} else if(floor_list->floorID < floorID) {
	    Log(INF,"floor_list start with floorID %d insert before FloorID %d ",floor_list->floorID,floorID);
		floor->floorID = floorID;
		if(status_info != NULL) {
			/* If there's Status Info text, add it */
			dLen = strlen(status_info);
			if(dLen != 0){
				floor->sInfo = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor->sInfo == NULL)
					return NULL;
				memcpy(floor->sInfo, status_info, dLen+1);
			}
		} else
			floor->sInfo = NULL;
		floor->next = floor_list;
		floor_list = floor;	
	} else {
		ini_floor_list = floor_list;
		while(ini_floor_list->next && (ini_floor_list->next->floorID > floorID))
			ini_floor_list = ini_floor_list->next;
			
        Log(INF,"floor_list after FloorID %d new FloorID[%d]",floor_list->floorID,floorID);
		
		floor->floorID = floorID;
		if(status_info != NULL) {
			/* If there's Status Info text, add it */
			dLen = strlen(status_info);
			if(dLen != 0){
				floor->sInfo = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor->sInfo == NULL)
					return NULL;
				memcpy(floor->sInfo, status_info, dLen+1);
			}
		} else
			floor->sInfo = NULL;
		
		floor->next = ini_floor_list->next;
		ini_floor_list->next = floor;	
	}
	Log(INF,"insert_floor_list floorID[%d] success ! floor_list[%p]",floorID,floor_list);
	return floor_list;
}

/* Destroy a list of 'bfcp_floors_participant' elements */
int BFCP_Participant::remove_floor_list(st_bfcp_floors_participant* floor_list)
{
	st_bfcp_floors_participant* next = NULL ;

	/* Free all the elements from the floors list */
	while(floor_list){
	    
        next = floor_list->next;
        if ( floor_list->sInfo ){
            free(floor_list->sInfo);
        }
        floor_list->sInfo = NULL;
        free(floor_list);
		floor_list = next;
	}
    floor_list = NULL ;
	return 0;
}

// CallBack

/*-----------------------------------------------------------------------------------------*/
int BFCP_Participant::ProcessBFCPmessage(bfcp_received_message * m, BFCP_SOCKET s)
{
    if (m) bfcp_received_msg(m);
    
    return 0;
}


/* Callback to receive notifications from the underlying library about incoming BFCP messages */
bool BFCP_Participant::bfcp_received_msg(bfcp_received_message *recv_msg)
{
    int j, i;
    bfcp_supported_list *info_primitives, *info_attributes;
    bfcp_floor_request_information *tempInfo;
    bfcp_floor_request_status *tempID;

    if(!recv_msg) {
        Log(ERR,"Invalid message received...");
        return false ;
    }
    if(!recv_msg->arguments) {
        Log(ERR,"Invalid arguments in the received message...");
        bfcp_free_received_message(recv_msg);
        return false ;
    }
    if(!recv_msg->entity) {
        Log(ERR,"Invalid IDs in the message header...");
        bfcp_free_received_message(recv_msg);
        return false ;
    }
    UINT32 conferenceID = recv_msg->entity->conferenceID;
    UINT16 userID = recv_msg->entity->userID;
    UINT16 transactionID = recv_msg->entity->transactionID;

    /* Output will be different according to the BFCP primitive in the message header */
    s_bfcp_msg_event evt ;
    memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
    evt.Event         = (e_bfcp_primitives)recv_msg->primitive ;
    evt.TransactionID = transactionID ;
    evt.userID        = userID ;
    evt.conferenceID  = conferenceID ;
    switch(recv_msg->primitive) {
        case e_primitive_Error:
            Log(INF,"Error:");
            if(!recv_msg->arguments->error)
                break;
            Log(INF,"Error n.    %d", recv_msg->arguments->error->code);
            Log(INF,"Error info: %s", recv_msg->arguments->eInfo ? recv_msg->arguments->eInfo : "No info");
            evt.Error_codes = (e_bfcp_error_codes)recv_msg->arguments->error->code ;
            BFCPFSM_FsmEvent( &evt );
            break;
        case e_primitive_HelloAck:
            Log(INF,"HelloAck:");
            info_primitives = recv_msg->arguments->primitives;
            Log(INF,"Supported Primitives:");
            while(info_primitives != NULL) {
                Log(INF,"%s", getBfcpDescPrimitive( (e_bfcp_primitives) info_primitives->element) );
                evt.Support_primitives[info_primitives->element] = true ;
                info_primitives = info_primitives->next;
            }
            info_attributes=recv_msg->arguments->attributes;
            Log(INF,"Supported Attributes:");
            while(info_attributes != NULL) {
                Log(INF,"%s", getBfcpAttribute( (e_bfcp_attibutes)info_attributes->element) );
                evt.Support_attributes[info_attributes->element] = true ;
                info_attributes = info_attributes->next;
            }
            Log(INF,"");
            BFCPFSM_FsmEvent( &evt );
            break;
        case e_primitive_ChairActionAck:
            Log(INF,"ChairActionAck:");
            Log(INF,"TransactionID: %d", transactionID);
            Log(INF,"UserID         %d", userID);
            Log(INF,"ConferenceID:  %lu", conferenceID);
            Log(INF,"");
            BFCPFSM_FsmEvent( &evt );
            break;
        case e_primitive_FloorRequestStatus:
        case e_primitive_FloorStatus:
            if(recv_msg->primitive == e_primitive_FloorStatus)
                Log(INF,"FloorStatus:");
            else
                Log(INF,"FloorRequestStatus:");
            Log(INF,"TransactionID: %d", transactionID);
            Log(INF,"UserID         %d", userID);
            Log(INF,"ConferenceID:  %lu", conferenceID);
            if(recv_msg->arguments->fID != NULL){
                Log(INF,"FloorID:       %d", recv_msg->arguments->fID->ID);
                evt.FloorID = recv_msg->arguments->fID->ID ;
                }
            if(recv_msg->arguments->frqInfo) {
                tempInfo = recv_msg->arguments->frqInfo;
                while(tempInfo) {
                    Log(INF,"FLOOR-REQUEST-INFORMATION:");
                    Log(INF,"   Floor Request ID:   %d", tempInfo->frqID);
                    checkFloorRequestID( tempInfo->frqID ) ;
                       evt.FloorRequestID = tempInfo->frqID ;
                    if(tempInfo->oRS) {
                        Log(INF,"   OVERALL REQUEST STATUS:");
                        if(tempInfo->oRS->rs){
                            Log(INF,"      Queue Position  %d", tempInfo->oRS->rs->qp);
                            Log(INF,"      RequestStatus   %s", getBfcpStatus(tempInfo->oRS->rs->rs) );
                            evt.Status = (e_bfcp_status)tempInfo->oRS->rs->rs ;
                            evt.QueuePosition = tempInfo->oRS->rs->qp ;
                        }
                        if(tempInfo->oRS->sInfo)
                            Log(INF,"      Status Info:   %s", tempInfo->oRS->sInfo);
                    }
                    if(tempInfo->fRS) {
                        Log(INF,"   FLOOR REQUEST STATUS:");
                        tempID = tempInfo->fRS;
                        j = 0;
                        while(tempID) {
                            Log(INF,"   FLOOR IDs:");
                            j++;
                            Log(INF,"      (n.%d):  %d", j, tempID->fID);
                            evt.FloorID = tempID->fID ;
                            if(tempID->rs->rs){
                                Log(INF,"      RequestStatus  %s", getBfcpStatus(tempID->rs->rs));
                                Log(INF,"      Queue Position  %d", tempID->rs->qp);
                                evt.FloorStatus = (e_bfcp_status)tempID->rs->rs ;
                            }
                            if ( tempID->sInfo )
                                Log(INF,"      Status Info:   %s", tempID->sInfo);
                            tempID = tempID->next;
                        }
                    }
                    if(tempInfo->beneficiary) {
                        Log(INF,"   BENEFICIARY-INFORMATION:");
                        if(tempInfo->beneficiary->ID){
                            Log(INF,"      Benefeciary ID: %d", tempInfo->beneficiary->ID);
                            evt.BeneficiaryID = tempInfo->beneficiary->ID ;
                            }
                        if(tempInfo->beneficiary->display)
                            Log(INF,"      Display Name:   %s", tempInfo->beneficiary->display);
                        if(tempInfo->beneficiary->uri)
                            Log(INF,"      User URI:       %s", tempInfo->beneficiary->uri);
                    }
                    if(tempInfo->requested_by) {
                        Log(INF,"    REQUESTED BY INFORMATION:");
                        if(tempInfo->requested_by->ID)
                            Log(INF,"      Requested-by ID:  %d", tempInfo->requested_by->ID);
                        if(tempInfo->requested_by->display)
                            Log(INF,"      Display Name:     %s", tempInfo->requested_by->display);
                        if(tempInfo->requested_by->uri)
                            Log(INF,"      User URI:         %s", tempInfo->requested_by->uri);
                    }
                    if(tempInfo->priority){
                        Log(INF,"    PRIORITY:                   %d", tempInfo->priority);
                        evt.Priority = (e_bfcp_priority)tempInfo->priority ;
                    }
                    if(tempInfo->pInfo)
                        Log(INF,"    PARTICIPANT PROVIDED INFO:  %s", tempInfo->pInfo);
                    Log(INF,"---");
                    tempInfo=tempInfo->next;
                }
            }
            BFCPFSM_FsmEvent( &evt );
            Log(INF,"");
            break;
        case e_primitive_UserStatus:
            Log(INF,"UserStatus:");
            Log(INF,"TransactionID: %d", transactionID);
            Log(INF,"UserID         %d", userID);
            Log(INF,"ConferenceID:  %ld", conferenceID);
            i = 0;
            if(recv_msg->arguments->beneficiary){
                Log(INF,"BeneficiaryInformation %d:", recv_msg->arguments->beneficiary->ID);
                evt.BeneficiaryID = recv_msg->arguments->beneficiary->ID ;
            }
            tempInfo=recv_msg->arguments->frqInfo;
            while(tempInfo) {
                i++;
                Log(INF,"FLOOR-REQUEST-INFORMATION (%d):",i);
                tempID = tempInfo->fRS;
                j = 0;
                while(tempID) {
                    Log(INF,"   FLOOR IDs:");
                    j++;
                    Log(INF,"      (n.%d): %d", j, tempID->fID);
                    evt.FloorID = tempID->fID ;
                    if(tempID->rs->rs) {
                        Log(INF,"      RequestStatus  %s", getBfcpStatus(tempID->rs->rs));
                        evt.FloorStatus = (e_bfcp_status)tempID->rs->rs ;
                    }
                    Log(INF,"      Status Info:   %s", tempID->sInfo ? tempID->sInfo : "No info");
                    tempID = tempID->next;
                }
                Log(INF,"   FloorRequestID %d", tempInfo->frqID);
                checkFloorRequestID( tempInfo->frqID );
                evt.FloorRequestID = tempInfo->frqID ;
                if(tempInfo->oRS) {
                    Log(INF,"   OVERALL REQUEST STATUS:");
                    if(tempInfo->oRS->rs){
                        Log(INF,"      Queue Position  %d", tempInfo->oRS->rs->qp);
                        Log(INF,"      RequestStatus   %s", getBfcpStatus(tempInfo->oRS->rs->rs));
                        evt.Status = (e_bfcp_status)tempInfo->oRS->rs->rs ;
                        evt.QueuePosition = tempInfo->oRS->rs->qp ;
                    }
                    if(tempInfo->oRS->sInfo)
                        Log(INF,"      Status Info:   %s", tempInfo->oRS->sInfo ? tempInfo->oRS->sInfo : "No info");
                }
                if(tempInfo->beneficiary){
                    Log(INF,"   BeneficiaryID  %d", tempInfo->beneficiary->ID);
                    evt.BeneficiaryID = tempInfo->beneficiary->ID ;
                }
                if(tempInfo->requested_by)
                    Log(INF,"   Requested_byID %d", tempInfo->requested_by->ID);
                Log(INF,"   Participant Provided info:     %s", tempInfo->pInfo ? tempInfo->pInfo : "No info");
                tempInfo = tempInfo->next;
            }
            BFCPFSM_FsmEvent( &evt );
            Log(INF,"");
            break;
        default:
            break;
    }

    if(recv_msg != NULL)
        bfcp_free_received_message(recv_msg);
    return true ; 
}

bool BFCP_Participant::checkFloorRequestID( UINT16 p_FloorRequestID ){
    Log(INF,"checkFloorRequestID current FloorRequestID[%d] new FloorRequestID[%d]",
        m_currentFloorRequestID,p_FloorRequestID);
        
    //if ( ( m_currentFloorRequestID && p_FloorRequestID != m_currentFloorRequestID ) ){
    //    Log(ERR,"Error current FloorRequestID[%d] new FloorRequestID[%d] ",m_currentFloorRequestID,p_FloorRequestID);
    //    return false ;
    //}
    m_currentFloorRequestID = p_FloorRequestID ;      
    return true ; 
}

// FSM
bool BFCP_Participant::BFCPFSM_UpdatesBfcpFsmEvent( s_bfcp_msg_event* p_bfcp_evt , e_BFCP_ACT p_evt , e_BFCP_ACT p_st )
{
    Log(INF,_T("BFCPFSM_UpdatesBfcpFsmEvent current  event[%s]  state[%s]"), getBfcpFsmAct(p_evt), getBfcpFsmAct(p_st) ); 
    st_BFCP_fsm_event bfcpFsmEvt ;
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
        break ; 
    case BFCP_ACT_FloorRelease  :
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
        break ; 
    case BFCP_ACT_FloorRequestStatusAccepted :
        Status = true ; 
        break ; 
    case BFCP_ACT_FloorRequestStatusAborted :
        Status = true ; 
        break ; 
    case BFCP_ACT_FloorRequestStatusGranted  :
        Status = true ; 
        break ; 
    case BFCP_ACT_UserStatus :
        break ; 
   case BFCP_ACT_FloorStatusAccepted :
        Status = true ; 
        break ; 
    case BFCP_ACT_FloorStatusAborted :
        Status = true ; 
        break ; 
    case BFCP_ACT_FloorStatusGranted  :
        Status = true ; 
        break ; 
    case BFCP_ACT_ChairActionAck :
        break ; 
    case BFCP_ACT_HelloAck  :
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
    if ( Status ) {
        memset(&bfcpFsmEvt,0, sizeof ( st_BFCP_fsm_event ));
        bfcpFsmEvt.State = p_st ;
        if ( p_bfcp_evt ){
            bfcpFsmEvt.TransactionID  = p_bfcp_evt->TransactionID;
            bfcpFsmEvt.userID = p_bfcp_evt->userID; 
            bfcpFsmEvt.conferenceID = p_bfcp_evt->conferenceID ;
            bfcpFsmEvt.FloorID = p_bfcp_evt->FloorID ;
            bfcpFsmEvt.FloorRequestID = p_bfcp_evt->FloorRequestID ;
            bfcpFsmEvt.QueuePosition = p_bfcp_evt->QueuePosition; 
            bfcpFsmEvt.BeneficiaryID = p_bfcp_evt->BeneficiaryID ;
            bfcpFsmEvt.i_parm = p_bfcp_evt->i_parm ;
            bfcpFsmEvt.pt_param = p_bfcp_evt->pt_param ;
            if ( p_bfcp_evt->c_param ) 
                ft_tcsncpy(bfcpFsmEvt.c_param ,p_bfcp_evt->c_param , BFCP_STRING_SIZE );
        }else{
            if ( m_bfcp_participant_information ){
            bfcpFsmEvt.userID = m_bfcp_participant_information->userID ;
            bfcpFsmEvt.FloorID = m_bfcp_participant_information->pfloors->floorID ; 
            bfcpFsmEvt.conferenceID = m_bfcp_participant_information->conferenceID ;
            }
        }
        if ( m_ParticipantEvent ) 
            m_ParticipantEvent->OnBfcpParticipantEvent( p_evt, &bfcpFsmEvt );

    }
    return Status ;
}

bool BFCP_Participant::OnBFCPConnected(BFCP_SOCKET socket, const char* remoteIp , int remotePort)
{
    Log(INF,_T("BFCP connection callback sock fd [%d] [%s:%d]"), socket, remoteIp ,remotePort);
    m_PartSocket = socket ;
    s_bfcp_msg_event evt ;
    memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
    if ( remoteIp ) 
        strncpy(evt.c_param , remoteIp , BFCP_STRING_SIZE );
    if ( remotePort )
        evt.i_parm = remotePort ;
    return FsmCtrlPerform( BFCP_fsm::BFCP_ACT_CONNECTED , &evt ) ;
}

bool BFCP_Participant::OnBFCPDisconnected(BFCP_SOCKET socket)
{
    Log(INF,_T("BFCP disconnection callback sock fd [%d] [%s:%d]"), socket);
    s_bfcp_msg_event evt ;
    memset ( &evt , 0 , sizeof(s_bfcp_msg_event));
    return  FsmCtrlPerform( BFCP_fsm::BFCP_ACT_DISCONNECTED , &evt ) ;
}

bool BFCP_Participant::BFCPFSM_Connected(  s_bfcp_msg_event* p_evt ){
    return (bfcp_hello_participant(NULL)==0);
}

bool BFCP_Participant::BFCPFSM_Disconnected(  s_bfcp_msg_event* p_evt ){
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

bool BFCP_Participant::BFCPFSM_FloorRequestStatusGranted(s_bfcp_msg_event* p_evt){
 if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusGranted. myFloorId[%d] eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  ||  m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){
        return true ;
    }else{
        Log(ERR,_T("BFCP floorRequestStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ;
    }
}

bool BFCP_Participant::BFCPFSM_FloorRequestStatusAborted(s_bfcp_msg_event* p_evt){
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusAborted. myFloorId[%d] eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
    if ( !p_evt->FloorID  || m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){
        return true ;
    }
    else {
        Log(ERR,_T("BFCP floorRequestStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCP_Participant::BFCPFSM_FloorRequestStatusAccepted(s_bfcp_msg_event* p_evt){
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] eventFloorId[%d] Status[%s]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID ,getBfcpStatus(p_evt->Status) );
    if ( !p_evt->FloorID  || m_bfcp_participant_information->pfloors->floorID  == p_evt->FloorID ){
        return true ;
    }
    else{
        Log(ERR,_T("BFCP floorRequestStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID  , p_evt->FloorID );
        return false ; 
    }
}

bool BFCP_Participant::BFCPFSM_FloorReleaseStatusAborted(s_bfcp_msg_event* p_evt){
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] eventFloorId[%d] Status[%s]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID ,getBfcpStatus(p_evt->Status));
    if ( m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){
        return true ;
    } else{
        Log(ERR,_T("BFCP floorReleaseStatusAborted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCP_Participant::BFCPFSM_FloorStatusAccepted( s_bfcp_msg_event* p_evt) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorStatusAccepted. myFloorId[%d] eventFloorId[%d] Status[%s]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID ,getBfcpStatus(p_evt->Status));
    if ( m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){
        return true ;
    } else{
        Log(ERR,_T("BFCP FloorStatusAccepted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCP_Participant::BFCPFSM_FloorStatusGranted( s_bfcp_msg_event* p_evt ) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorStatusGranted. myFloorId[%d] eventFloorId[%d] BeneficiaryID[%d] Status[%s]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID ,p_evt->BeneficiaryID , getBfcpStatus(p_evt->Status));
    if ( m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){
        return true ;
    } else{
        Log(ERR,_T("BFCP FloorStatusGranted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ; 
    }
}

bool BFCP_Participant::BFCPFSM_FloorStatusAborted(s_bfcp_msg_event* p_evt ) {
    if ( !p_evt )
        return false ;
    Log(INF,_T("BFCP FloorRequestAborted. myFloorId[%d] eventFloorId[%d] Status[%s]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID ,getBfcpStatus(p_evt->Status));
    if ( m_bfcp_participant_information->pfloors->floorID == p_evt->FloorID ){

        return true ;
    } else{
        Log(ERR,_T("BFCP FloorRequestAborted. myFloorId[%d] != eventFloorId[%d]"),m_bfcp_participant_information->pfloors->floorID , p_evt->FloorID );
        return false ; 
    }
}


bool BFCP_Participant::BFCPFSM_FloorRequest(s_bfcp_msg_event* p_evt){
    bool status = false ;
    if ( bfcp_floorRequest_participant(m_bfcp_participant_information->pfloors->floorID) == -1 ){
        Log(ERR,"FloorRequest send  floorRequest failed ! ");
    }else{
        status = true ;
    }
    return status ;
}

bool BFCP_Participant::BFCPFSM_FloorRelease(s_bfcp_msg_event* p_evt){
    bool status = false ;
    if ( bfcp_floorRelease_participant() == -1 ){
        Log(ERR,"FloorRelease send  FloorRelease failed ! ");
    }else{
        status = true ;
    }
    return status ;
}

bool BFCP_Participant::BFCPFSM_UpdateHwnd(s_bfcp_msg_event* p_evt){
    // call by SetWindowHandle state BFCP_ACT_FloorRequest 
    // Update hwnd made by status true 
    if ( p_evt ){
        return true;
    }
    return false ;
}

void BFCP_Participant::Log(const  char* pcFile, int iLine, int iErrLevel ,const  char* pcFormat, ...) {
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


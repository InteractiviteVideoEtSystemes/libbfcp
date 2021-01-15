/**
 *
 * \brief BFCP Request list management  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_link_list.cpp
 *
 * \version $Revision: 2555 $
 *
 * \date $Date: 2015-11-09 15:53:03 +0100 (Mon, 09 Nov 2015) $
 *
 * \remarks :
 */
#include "stdafx.h"
#include "bfcp_threads.h"
#include "BFCPexception.h"
#include "bfcp_link_list.h"

BFCP_LinkList::BFCP_LinkList(){
}

BFCP_LinkList::~BFCP_LinkList(void){
}

/* Create a new linked list of BFCP queues */
struct bfcp_queue *BFCP_LinkList::bfcp_create_list(void)
{
	bfcp_queue *conference;

	/* Create a new list of BFCP queues */
	conference = (bfcp_queue *)calloc(1, sizeof(bfcp_queue));

	/* Initialize the list */
	if(conference == NULL)
		return NULL;
	else {
		conference->head = NULL;
		conference->tail = NULL;
	}

	return conference;
}

/* Initialize a new FloorRequest node */
struct bfcp_node *BFCP_LinkList::bfcp_init_request(UINT16 userID, UINT16 beneficiaryID, e_bfcp_priority priority, char *participant_info, UINT16 floorID)
{
	if(userID == 0)
		return NULL;
	if(floorID == 0)
		return NULL;

	pnode newnode;
	pfloor floor_list;
	size_t dLen;

	/* Check if the priority argument is valid */
	if(priority > BFCP_HIGHEST_PRIORITY)
		priority = BFCP_HIGHEST_PRIORITY;
	
	/* Create a new node */
	newnode = (pnode)calloc(1, sizeof(bfcp_node));
	if(!newnode)
		return (NULL);

	newnode->next = newnode->prev= NULL;

	newnode->userID = userID;
	newnode->beneficiaryID = beneficiaryID;
	newnode->priority = priority;
	newnode->queue_position = 0;
	newnode->chair_info = NULL;
	newnode->floorrequest = NULL;

	/* Add participant-provided text, if present */
	if(participant_info != NULL) {
		dLen= strlen(participant_info);
		if(dLen != 0) {
			newnode->participant_info = (char *)calloc(1, dLen*sizeof(char)+1);
			if(newnode->participant_info == NULL)
				return NULL;
			memcpy(newnode->participant_info, participant_info, dLen+1);
		}
	} else
		newnode->participant_info= NULL;

	/* Create a new list of floors */
	floor_list = (pfloor)calloc(1, sizeof(bfcp_floor));

	/* Initialize the list */
	if(floor_list == NULL)
		return NULL;
	else{
		floor_list->floorID = floorID;
		floor_list->status = BFCP_FLOOR_STATE_WAITING;
		floor_list->chair_info = NULL;
		floor_list->pID = BFCP_NULL_THREAD_HANDLE;
		floor_list->next = NULL;
		newnode->floor = floor_list;
	}

	return newnode;
}

/* Add a floor to an existing FloorRequest */
int BFCP_LinkList::bfcp_add_floor_to_request(pnode newnode, UINT16 floorID)
{
	if(newnode == NULL)
		return -1;
	if(floorID == 0)
		return -1;

	pfloor floor_list, ini_floor_list, floor;

	/* Check if a floor with the same ID already exists in the list */
	for(floor = newnode->floor; floor; floor = floor->next) {
		if(floor->floorID == floorID)
			/* This floor already exists in the list */
			return -1;
	}

	/* Create a new list of floors */
	floor_list = (pfloor)calloc(1, sizeof(bfcp_floor));

	/* Initialize the list */
	if(floor_list == NULL)
		return -1;
	else {
		if(newnode->floor == NULL) {
			floor_list->floorID = floorID;
			floor_list->status = BFCP_FLOOR_STATE_WAITING;
			floor_list->chair_info = NULL;
			floor_list->pID = BFCP_NULL_THREAD_HANDLE;
			floor_list->next= newnode->floor;
			newnode->floor= floor_list;
		} else if(newnode->floor->floorID < floorID) {
			floor_list->floorID = floorID;
			floor_list->status = BFCP_FLOOR_STATE_WAITING;
			floor_list->chair_info = NULL;
			floor_list->pID = BFCP_NULL_THREAD_HANDLE;
			floor_list->next = newnode->floor;
			newnode->floor = floor_list;
		} else {
			ini_floor_list = newnode->floor;
			while((ini_floor_list->next) && (ini_floor_list->next->floorID > floorID))
				ini_floor_list=ini_floor_list->next;
			floor_list->floorID = floorID;
			floor_list->status = BFCP_FLOOR_STATE_WAITING;
			floor_list->chair_info = NULL;
			floor_list->pID=BFCP_NULL_THREAD_HANDLE;
			floor_list->next = ini_floor_list->next;
			ini_floor_list->next = floor_list;	
		}
	}

	return 0;
}

/* Add an existing FloorRequest to a BFCP queue */
int BFCP_LinkList::bfcp_insert_request(bfcp_queue *conference, pnode newnode, UINT16 floorRequestID, char *chair_info)
{
	if(conference == NULL)
		return -1;
	if(newnode == NULL)
		return -1;
	if(floorRequestID == 0)
		return -1;

	pnode traverse;
	size_t dLen, y = 1;

	/* Add the floorRequestID to the node */
	newnode->floorRequestID = floorRequestID;	
	Log(INF, ">> Inserting floorRequestID [%d] request into queue[0x%p]",floorRequestID, conference);

	if(chair_info != NULL) {
		dLen = strlen(chair_info);
		if(dLen != 0) {
			if(newnode->chair_info != NULL) {
				free(newnode->chair_info);
				newnode->chair_info = NULL;
			}
			newnode->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
			if(newnode->chair_info == NULL)
				return -1;
			memcpy(newnode->chair_info, chair_info, dLen+1);
		}
	} else
		newnode->chair_info = NULL;

	/* Insert the new node in the structure*/
	traverse = conference->head;

	/* If queue_position is not 0, we set the one the chair stated */
	if((newnode->queue_position != 0) && (traverse != NULL)) {
		/* Insert the new node in the structure*/
		traverse = conference->tail;
		while(traverse->prev) {
			if(y < newnode->queue_position)
				y = y + 1;
			else
				break;
			traverse = traverse->prev;
		}
	
		if(y != newnode->queue_position) {
			traverse = conference->head;
			newnode->queue_position = 0;
		}
		newnode->priority = BFCP_LOWEST_PRIORITY;
	}

	if(traverse == NULL) {
		newnode->next = NULL;
		newnode->prev = NULL;
		conference->head = newnode;
		conference->tail = newnode;
	} else {
		if((traverse->priority >= newnode->priority) && (newnode->queue_position == 0)) {
			newnode->next = traverse; 
			newnode->prev = NULL;
			conference->head = newnode;
			if(traverse)
				traverse->prev = newnode;
			if(!conference->head)
				conference->head = newnode;
			if(!conference->tail)
				conference->tail = newnode;
		} else {
			while(traverse->next && (traverse->next->priority < newnode->priority))
				traverse=traverse->next;

			newnode->next = traverse->next;
			traverse->next = newnode;
			newnode->prev = traverse;
			if(newnode->next)
				newnode->next->prev = newnode;
			else
				conference->tail = newnode;
		}
	}
	Log(INF, "<< Inserted floorRequestID [%d] request.",floorRequestID);

	return ++floorRequestID;
}

/* Return the UserID of the user who made the request */
UINT16 BFCP_LinkList::bfcp_give_user_of_request(bfcp_queue *conference, UINT16 floorRequestID)
{
	if(conference == NULL)
		return 0;
	if(floorRequestID == 0)
		return 0;

	pnode traverse;
	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || traverse->floorRequestID!= floorRequestID){
		Log(INF,"bfcp_give_user_of_request floorRequestID[%d] This node is not in the list request queue[0x%p]",floorRequestID,conference);
		return 0;
    }
	else {
		if(traverse->beneficiaryID != 0){
		    Log(INF,"bfcp_give_user_of_request floorRequestID[%d] request queue[0x%p] user is beneficiaryID[%d] ",floorRequestID,conference,traverse->beneficiaryID);
			return(traverse->beneficiaryID);
        }
		else{
			Log(INF,"bfcp_give_user_of_request floorRequestID[%d] request queue[0x%p] user [%d] ",floorRequestID,conference,traverse->userID);
			return(traverse->userID);
        }
	}
}

/* Change status to a floor in a request */
int BFCP_LinkList::bfcp_change_status(bfcp_queue *conference, UINT16 floorID, UINT16 floorRequestID, e_floor_state status, char *floor_chair_info)
{
	if(conference == NULL)
		return -1;
	if(floorRequestID == 0)
		return -1;
	if((status < BFCP_FLOOR_STATE_WAITING) || (status > BFCP_FLOOR_STATE_GRANTED))
		return -1;

	pnode traverse;
	pfloor floor;
	size_t dLen;
	
	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return -1;
	
	floor = traverse->floor;
	while(floor) {
		if(floor->floorID == floorID) {
			floor->status = status;
			/* If there's chair-provided text, add it */
			if(floor_chair_info != NULL) {
				dLen = strlen(floor_chair_info);
				if(dLen != 0) {
					if(floor->chair_info != NULL) {
						free(floor->chair_info);
						floor->chair_info = NULL;
					}
					floor->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
					if(floor->chair_info == NULL)
						return -1;
					memcpy(floor->chair_info, floor_chair_info, dLen+1);
				}
			} else
			floor->chair_info = NULL;
			return 0;
		}
		floor = floor->next;
	}

	/* If we arrived so far, some error happened */
	return -1;
	
}

/* Check if the overall status is actually the status of every floor in the request (?) */
int BFCP_LinkList::bfcp_all_floor_status(bfcp_queue *conference, UINT16 floorRequestID, e_floor_state status)
{
	if(conference == NULL)
		return -1;
	if(floorRequestID == 0)
		return -1;
	if((status < BFCP_FLOOR_STATE_WAITING) || (status > BFCP_FLOOR_STATE_GRANTED))
		return -1;

	pnode traverse;
	pfloor floor;

	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return -1;

	floor = traverse->floor;
	while(floor) {
		if(floor->status != status)
			return -1;
		floor = floor->next;
	}

	return 0;
}

/* Check if the pthread identifier is valid (?) */
int BFCP_LinkList::bfcp_all_floor_pID(pnode newnode)
{
	if(newnode == NULL)
		return 0;

	pfloor floor;

	floor = newnode->floor;

	while(floor) {
		if(floor->pID!=BFCP_NULL_THREAD_HANDLE)
			return -1;
		floor=floor->next;
	}

	return 0;
}

/*Remove a floor from a floor request information (?) */
int BFCP_LinkList::bfcp_delete_node_with_floorID(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list) {
    if(conference == NULL)
        return -1;
    if(floorID == 0)
        return -1;

    pnode traverse, traverse_temp;
    pfloor floor, temp, next;
    floor_request_query *temp_request;
    floor_request_query *next_request;
    //floor_request_query *floorrequest;
    int delete_node = 0, i = 0;
    /* UINT16 userID; */

    traverse = conference->head;

    while(traverse) {
        floor = traverse->floor;
        delete_node = 0;
        while((floor != NULL) && (floor->floorID >= floorID)) {
            if(floor->floorID == floorID) {
                /* The head pointer points to the node we want to delete */
                traverse_temp = traverse;
/*
                if(traverse_temp->beneficiaryID !=0)
                    userID = traverse_temp->beneficiaryID;
                else
                    userID= traverse_temp->userID;

                floorrequest = traverse_temp->floorrequest;
*/

                if (traverse_temp == conference->head) {
                    conference->head = traverse_temp->next;
                    traverse = conference->head;
                    if(traverse != NULL) {
                        traverse->prev = NULL;
                        if(traverse->next == NULL)
                            conference->tail = traverse;
                    } else
                        conference->tail = NULL;
                } else {
                    if(traverse_temp->prev) {
                        /* It is not the first element */
                        traverse = traverse_temp->prev;
                        traverse_temp->prev->next = traverse_temp->next;
                    }
                    if(traverse_temp->next) {
                        /* It is not the last element */
                        traverse = traverse_temp->prev;
                        traverse_temp->next->prev = traverse_temp->prev;
                    } else {
                        traverse = NULL;
                        conference->tail = traverse_temp->prev;
                    }
                }

                /* Free all the elements from the floor list */
                temp = traverse_temp->floor;
                while(temp) {
                    /* Kill the threads */
                    if(type_list == 1) {
                        if(temp->pID != BFCP_NULL_THREAD_HANDLE) {
                            BFCP_THREAD_KILL(temp->pID);
                            temp->pID = BFCP_NULL_THREAD_HANDLE;
                        }
                    }

                    next = temp->next;
                    if(temp->status == BFCP_FLOOR_STATE_GRANTED ) {
                        i = bfcp_return_position_floor(lfloors, temp->floorID);
                        if(i != -1) {
                            if(lfloors != NULL) {
                                if(lfloors->floors != NULL)
                                    lfloors->floors[i].floorState = BFCP_FLOOR_STATE_WAITING;
                            }
                        }
                    }
                    free(temp->chair_info);
                    temp->chair_info = NULL;
                    free(temp);
                    temp = NULL;
                    temp = next;
                }

                /* Free all the elements from the request list */
                temp_request = traverse_temp->floorrequest;
                while(temp_request != NULL) {
                    next_request = temp_request->next;
                    free(temp_request);
                    temp_request = NULL;
                    temp_request = next_request;
                }

                free(traverse_temp->participant_info);
                traverse_temp->participant_info = NULL;
                free(traverse_temp->chair_info);
                traverse_temp->chair_info = NULL;
                free(traverse_temp);
                traverse_temp = NULL;
                floor = NULL;
                delete_node = 1;
            } else
                floor = floor->next;
        }
        if((traverse != NULL) && (delete_node !=1))
            traverse = traverse->next;
    }

    return 0;
}

/* Remove all elements related to an user from a floor request information (?) */
int BFCP_LinkList::bfcp_delete_node_with_userID(bfcp_queue *conference, UINT16 userID, bfcp_list_floors *lfloors) {
    if(conference == NULL)
        return 0;
    if(userID == 0)
        return -1;
    if(lfloors == NULL)
        return 0;
    if(lfloors->floors == NULL)
        return 0;

    pnode traverse, traverse_temp;
    pfloor temp, next;
    floor_request_query *temp_request;
    floor_request_query *next_request;
    int i = 0;

    traverse = conference->head;

    while(traverse!=NULL) {
        if((traverse->userID == userID) || (traverse->beneficiaryID == userID)) {
            /* The head pointer points to the node we want to delete */
            traverse_temp = traverse;
            if(traverse_temp == conference->head) {
                conference->head = traverse_temp->next;
                traverse = conference->head;
                if(traverse != NULL) {
                    traverse->prev = NULL;
                    if(traverse->next == NULL)
                        conference->tail = traverse;
                } else
                    conference->tail = NULL;
            } else {
                if(traverse_temp->prev) {
                    /* It is not the first element */
                    traverse = traverse_temp->prev;
                    traverse_temp->prev->next = traverse_temp->next;
                }
                if(traverse_temp->next) {
                    /* It is not the last element */
                    traverse = traverse_temp->prev;
                    traverse_temp->next->prev = traverse_temp->prev;
                } else {
                    traverse = NULL;
                    conference->tail = traverse_temp->prev;
                }
            }
            /* Free all the elements from the floor list */
            temp = traverse_temp->floor;
            while(temp != NULL) {
                next = temp->next;
                if(temp->status == 2) {
                    i = bfcp_return_position_floor(lfloors, temp->floorID);
                    if(i != -1)
                        lfloors->floors[i].floorState = BFCP_FLOOR_STATE_WAITING;
                }
                free(temp->chair_info);
                temp->chair_info = NULL;
                free(temp);
                temp = NULL;
                temp = next;
            }
            /* Free all the elements from the request list */
            temp_request = traverse_temp->floorrequest;
            while(temp_request != NULL) {
                next_request = temp_request->next;
                free(temp_request);
                temp_request = NULL;
                temp_request = next_request;
            }

            free(traverse_temp->participant_info);
            traverse_temp->participant_info = NULL;
            free(traverse_temp->chair_info);
            traverse_temp->chair_info = NULL;
            free(traverse_temp);
            traverse_temp = NULL;
        } else
            traverse = traverse->next;
    }

    return 0;
}

/* Remove a FloorRequest from the BFCP queues */
bfcp_floor *BFCP_LinkList::bfcp_delete_request(bfcp_queue *conference, UINT16 floorRequestID, int type_queue)
{
	if(conference == NULL)
		return NULL;
	if(floorRequestID == 0)
		return NULL;

	pnode traverse;
	pfloor temp, floor;

	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;
	
	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return NULL;

	/* Remove the thread if this node is in the pending queue*/
	if(type_queue==2) {
		floor = traverse->floor;
        while(floor) {
            if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                BFCP_THREAD_KILL(floor->pID);
                floor->pID = BFCP_NULL_THREAD_HANDLE;
            }
            floor = floor->next;
        }
	}

	/* The head pointer points to the node we want to delete */
	if(traverse == conference->head)
		conference->head = traverse->next;
	if(traverse->prev)
		/* It is not the first element */
		traverse->prev->next = traverse->next;
	if(traverse->next)
		/* It is not the last element */
		traverse->next->prev = traverse->prev;
	else
		conference->tail = traverse->prev;

	/* temp is the list with all the floors */
	temp = traverse->floor;

	/* Remove the list of requests */
	remove_request_list_of_node(traverse->floorrequest);

	free(traverse->participant_info);
	traverse->participant_info = NULL;
	free(traverse->chair_info);
	traverse->chair_info = NULL;
	free(traverse);
	traverse = NULL;

	return temp;
}

/* Get a FloorRequest from one of the BFCP queues */
bfcp_node *BFCP_LinkList::bfcp_extract_request(bfcp_queue *conference, UINT16 floorRequestID)
{
	if(conference == NULL)
		return NULL;
	if(floorRequestID == 0)
		return NULL;

	pnode traverse;
	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return NULL;

	/* The head pointer points to the node we want to retrieve */
	if(traverse == conference->head)
		conference->head = traverse->next;
	if(traverse->prev)
		/* It is not the first element */
		traverse->prev->next = traverse->next;
	if(traverse->next)
		/* It is not the last element */
		traverse->next->prev = traverse->prev;
	else
		conference->tail = traverse->prev;

	return traverse;
}

/* Setup a FloorRequest so that it is to be sent in a BFCP message (?) */
int BFCP_LinkList::bfcp_floor_request_query_server(bfcp_queue *conference, UINT16 floorRequestID, UINT16 userID, int sockfd, int transport)
{
	if(conference == NULL)
		return -1;
	if(floorRequestID == 0)
		return -1;

	pnode traverse;
	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return -1;

	return add_request_to_the_node(traverse, userID, sockfd, transport);
}

/* Remove all requests from a list */
int BFCP_LinkList::bfcp_clean_request_list(bfcp_queue *conference)
{
	if(conference == NULL)
		return -1;

	pnode traverse, node;
	pfloor temp, next;
	floor_request_query *temp_request;
	floor_request_query *next_request;

	traverse = conference->head;
	while(traverse) {
		node = traverse;
		traverse = traverse->next;

		/* Free all the elements of the floor list */
		temp = node->floor;
		while(temp) {
			/* Free all the threads handling the request */
			if(temp->pID != BFCP_NULL_THREAD_HANDLE) {
                 BFCP_THREAD_KILL(temp->pID);
				temp->pID = BFCP_NULL_THREAD_HANDLE;
			}
			next = temp->next;
			free(temp->chair_info);
			temp->chair_info = NULL;
			free(temp);
			temp = NULL;
			temp = next;
		}
		/* Free all the elements from the request list */
		temp_request = node->floorrequest;
		while(temp_request) {
			next_request = temp_request->next;
			free(temp_request);
			temp_request = NULL;
			temp_request = next_request;
		}

		free(node->participant_info);
		node->participant_info = NULL;
		free(node->chair_info);
		node->chair_info = NULL;
		free(node);
		node = NULL;
	}
	conference->head = NULL;
	conference->tail = NULL;
	
	return 0;
}

/* Free a linked list of requests */
int BFCP_LinkList::bfcp_remove_request_list(bfcp_queue **conference_p)
{
	if(conference_p == NULL)
		return 0;

	int error;
	bfcp_queue *conference = *conference_p;

	error = bfcp_clean_request_list(conference);
	if(error==0) {
		free(conference);
		conference = NULL;
		*conference_p = NULL;
	}
	else
		return -1;

	return 0;
}

/* Kill all the running threads handling a specific FloorRequest */
int BFCP_LinkList::bfcp_kill_threads_request_with_FloorRequestID(bfcp_queue *conference, UINT16 floorRequestID)
{
	if(conference == NULL)
		return -1;
	if(floorRequestID == 0)
		return -1;

	pnode traverse;
	pfloor floor;

	traverse = conference->head;
	
	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return -1;
	
    floor = traverse->floor;
    while(floor) {
        if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
            BFCP_THREAD_KILL(floor->pID);
            floor->pID = BFCP_NULL_THREAD_HANDLE;
        }
        floor = floor->next; 
    }

	return 0;
}

/* Convert a 'bfcp_node' info to 'bfcp_floor_request_information' (bfcp_messages.h) */
bfcp_floor_request_information *BFCP_LinkList::bfcp_show_floorrequest_information(bfcp_queue *conference, lusers users, UINT32 floorRequestID, int type_queue)
{
	if(conference == NULL)
		return NULL;

	pnode traverse;
	pfloor floor;
	bfcp_user_information *beneficiary_info, *user_info;
	bfcp_floor_request_information *frqInfo;
	bfcp_overall_request_status *oRS = NULL;
	bfcp_floor_request_status *fRS_temp = NULL, *fRS = NULL;
	
	traverse = conference->tail;
	
	if(!traverse)
		/* The list is empty */
		return NULL;
    e_bfcp_status e_status = BFCP_PENDING ;
	while(traverse) {
		if(traverse->floorRequestID == floorRequestID) {
			if(type_queue == 0){
				/* Granted */
				e_status = BFCP_GRANTED ;
				oRS = bfcp_new_overall_request_status(traverse->floorRequestID, BFCP_GRANTED, 0, traverse->chair_info);
			} else if(type_queue==1) {
				/* Accepted */
				e_status = BFCP_ACCEPTED ;
				oRS = bfcp_new_overall_request_status(traverse->floorRequestID, BFCP_ACCEPTED, traverse->queue_position, traverse->chair_info);
			} else if(type_queue==2) {
				/* Pending */
				e_status = BFCP_PENDING ;
				oRS = bfcp_new_overall_request_status(traverse->floorRequestID, BFCP_PENDING, traverse->priority, traverse->chair_info);
			} else {
				/* Revoke */
				e_status = BFCP_REVOKED ;
				oRS = bfcp_new_overall_request_status(traverse->floorRequestID, BFCP_REVOKED, 0, traverse->chair_info);
            }
			floor = traverse->floor;
			if(floor != NULL) {
				fRS = bfcp_new_floor_request_status(floor->floorID, e_status , 0, floor->chair_info);
				floor = floor->next;
				while(floor) {
					fRS_temp = bfcp_new_floor_request_status(floor->floorID, e_status, 0, floor->chair_info);
					if(fRS_temp != NULL)
						bfcp_list_floor_request_status(fRS, fRS_temp, NULL);
					floor = floor->next;
				}
			}

            if(traverse->beneficiaryID !=0) {
                beneficiary_info = BFCP_LinkList_show_user_information(users, traverse->beneficiaryID);
                if(beneficiary_info == NULL) {
					bfcp_free_user_information(beneficiary_info);
					return NULL;
				}
			} else
				beneficiary_info=NULL;

            if(traverse->userID != 0) {
                    user_info = BFCP_LinkList_show_user_information(users, traverse->userID);
                if(user_info == NULL) {
					bfcp_free_user_information(user_info);
					return NULL;
				}
			} else
				user_info = NULL;
		
			frqInfo = bfcp_new_floor_request_information(traverse->floorRequestID, oRS, fRS, beneficiary_info, user_info, traverse->priority, traverse->participant_info);
			return frqInfo;
		}
		traverse = traverse->prev;
	}

	/* If we arrived so far, something wrong happened */
	return NULL;
}

/* Create a new linked list of floors */
bfcp_floor *BFCP_LinkList::create_floor_list(UINT16 floorID, e_floor_state status, char *floor_chair_info)
{
	if(status > BFCP_FLOOR_STATE_GRANTED )
		return NULL;

	bfcp_floor *floor_list;
	size_t dLen;

	/* Create a new list of floors */
	floor_list = (pfloor)calloc(1, sizeof(bfcp_floor));

	/* Initialize the list*/
	if(floor_list == NULL)
		return NULL;
	else {
		floor_list->floorID = floorID;
		floor_list->status = status;
		floor_list->pID = BFCP_NULL_THREAD_HANDLE;
		/* If there's chair-provided text, add it */
		if(floor_chair_info != NULL) {
			dLen= strlen(floor_chair_info);
			if(dLen != 0) {
				floor_list->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor_list->chair_info == NULL)
					return NULL;
				memcpy(floor_list->chair_info, floor_chair_info, dLen+1);
			}
		} else
			floor_list->chair_info = NULL;
	
		floor_list->next = NULL;
	}

	return floor_list;
}

/* Add floors to a list in order */
bfcp_floor *BFCP_LinkList::add_floor_list(bfcp_floor *floor_list, UINT16 floorID, e_floor_state status, char *floor_chair_info)
{
	if((status < BFCP_FLOOR_STATE_WAITING  ) || (status > BFCP_FLOOR_STATE_GRANTED))
		return NULL;
	if(floor_list == NULL)
		return NULL;

	pfloor ini_floor_list, floor;
	size_t dLen;

    /* Create a new floor instance */
	floor = (pfloor)calloc(1, sizeof(bfcp_floor));

	/* Initialize the floor */
	if(floor == NULL)
		return NULL;

	if(floor_list->floorID < floorID) {
		floor->floorID = floorID;
		floor->status = status;
		floor->pID = BFCP_NULL_THREAD_HANDLE;
		/* If there's chair-provided text, add it */
		if(floor_chair_info != NULL) {
			dLen = strlen(floor_chair_info);
			if(dLen != 0) {
				floor->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor->chair_info == NULL)
					return NULL;
				memcpy(floor->chair_info, floor_chair_info, dLen+1);
			}
		} else
			floor->chair_info = NULL;

		floor->next = floor_list;
		floor_list = floor;	
	} else if(floor_list->floorID > floorID) {
		ini_floor_list = floor_list;
		while(ini_floor_list->next && (ini_floor_list->next->floorID > floorID))
			ini_floor_list = ini_floor_list->next;
		floor->floorID = floorID;
		floor->status = status;
		floor->pID = BFCP_NULL_THREAD_HANDLE;
		/* If there's chair-provided text, add it */
		if(floor_chair_info != NULL) {
			dLen = strlen(floor_chair_info);
			if(dLen != 0) {
				floor->chair_info = (char *)calloc(1, dLen*sizeof(char)+1);
				if(floor->chair_info == NULL)
					return NULL;
				memcpy(floor->chair_info, floor_chair_info, dLen+1);
			}
		} else
			floor->chair_info = NULL;

		floor->next = ini_floor_list->next;
		ini_floor_list->next = floor;	
	}

	return(floor_list);
}

/* Free a linked list of requests */
int BFCP_LinkList::remove_floor_list(bfcp_floor *floor_list)
{
	pfloor next;

	/* Free all the elements from the floor list */
	while(floor_list) {
		next = floor_list->next;
		free(floor_list->chair_info);
		floor_list->chair_info = NULL;
		free(floor_list);
		floor_list = NULL;
		floor_list = next;
	}

	return 0;
}

/* Remove the list of requests from a request node */
int BFCP_LinkList::remove_request_list_of_node(floor_request_query *floorrequest)
{
	floor_request_query * next = NULL;

	/* Free all the elements from the floor list */
	while(floorrequest) {
		next = floorrequest->next;
		floorrequest->next = NULL;
		free(floorrequest);
		floorrequest = NULL;
		floorrequest = next;
	}

	return 0;
}

/* Add a request to a request node */
int BFCP_LinkList::add_request_to_the_node(pnode traverse, UINT16 userID, int sockfd, int transport)
{
	if(traverse == NULL)
		return -1;

	int exist_query;
	floor_request_query *floorrequest = NULL;
	floor_request_query *newnode = NULL;

	floorrequest=traverse->floorrequest;

	/* If the request already exists in the list, we don't add it again */
	exist_query = 0;
	while(floorrequest != NULL) {
		if(floorrequest->userID == userID) {
			exist_query = 1;
			break;
		}
		floorrequest = floorrequest->next;
	}

	if(exist_query == 0) {
		/* Create the new node */
		newnode = (floor_request_query *)calloc(1, sizeof(floor_request_query));
		if(newnode == NULL)
			return -1;
	
		floorrequest = traverse->floorrequest;
	
		/* Add the request to the listto the list */
		newnode->userID = userID;
		newnode->fd = sockfd;
		newnode->transport = transport;
		newnode->next = floorrequest;
		traverse->floorrequest = newnode;
	}

	return 0;
}

/* Request a request from a request node */
int BFCP_LinkList::remove_request_from_the_node(pnode traverse, UINT16 userID)
{
	if(traverse == NULL)
		return 0;

	floor_request_query *floorrequest = NULL;
	floor_request_query *newnode = NULL;

	floorrequest = traverse->floorrequest;
	if(floorrequest == NULL)
		return 0;

	/* If the request exists in the list, we remove it from the node */
	if(floorrequest->userID == userID) {
		traverse->floorrequest = floorrequest->next;
		floorrequest->next = NULL;
		free(floorrequest);
		floorrequest = NULL;
		return 0;
	}

	while(floorrequest->next != NULL) {
		if(floorrequest->next->userID == userID) {
			newnode = floorrequest->next;
			floorrequest->next = newnode->next;
			free(newnode);
			newnode = NULL;
			return 0;
		}
		floorrequest = floorrequest->next;
	}

	return 0;
}

/* ?? */
int BFCP_LinkList::bfcp_accepted_pending_node_with_floorID(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list)
{
	if(conference == NULL)
		return -1;
	if(floorID == 0)
		return -1;

	pnode traverse, traverse_temp;
	int delete_node = 0, error = 0;
	/* UINT16 userID; 
	floor_request_query *floorrequest; */
	bfcp_node *newnode = NULL;
	pfloor floor;

	traverse = conference->head;

	while(traverse) {
		floor = traverse->floor;
		delete_node = 0;
		while((floor != NULL) && (floor->floorID >= floorID)) {
			if(floor->floorID == floorID) {
				floor->status = BFCP_FLOOR_STATE_ACCEPTED;
				floor->chair_info = NULL;
			}

			/* If all the floors in the request have been accepted... */
			if(bfcp_all_floor_status(conference, traverse->floorRequestID, BFCP_FLOOR_STATE_ACCEPTED) == 0) {
				traverse_temp = traverse->next;
				/* ...extract the node request from the Pending list... */
				newnode = bfcp_extract_request(conference, traverse->floorRequestID);

                /* ...and remove the threads for this node */
                floor = newnode->floor;
                while(floor) {
                    if(floor->pID != BFCP_NULL_THREAD_HANDLE) {
                        BFCP_THREAD_KILL(floor->pID);
                        floor->pID = BFCP_NULL_THREAD_HANDLE;
                    }
                    floor = floor->next;
                }

				/* Put the node in the Accepted list */
				/* Change the priority of the node to the lowest one */
				newnode->priority = BFCP_LOWEST_PRIORITY;

				error = bfcp_insert_request(accepted, newnode, traverse->floorRequestID, NULL);
				if(error == -1)
					return (-1);

				/* Add the floor request information to the floor nodes */
/*
				if(newnode->beneficiaryID != 0)
					userID = newnode->beneficiaryID;
				else
					userID = newnode->userID;

				floorrequest = newnode->floorrequest;
*/
				delete_node = 1;
				traverse = traverse_temp;
			} else
				floor = floor->next;
		}
		if((traverse != NULL) && (delete_node != 1))
			traverse = traverse->next;
	}

	return 0;
}

/* Change position in queue to a FloorRequest */
int BFCP_LinkList::bfcp_change_queue_position(bfcp_queue *conference, UINT16 floorRequestID, UINT16 queue_position)
{
	if(conference == NULL)
		return 0;

	pnode traverse;
	traverse = conference->head;

	while(traverse && (traverse->floorRequestID != floorRequestID))
		traverse = traverse->next;

	if(!traverse || (traverse->floorRequestID != floorRequestID))
		/* This node is not in the list */
		return 0;
	else {
		if(queue_position > traverse->queue_position)
			traverse->queue_position = queue_position;
	}

	return 0;
}

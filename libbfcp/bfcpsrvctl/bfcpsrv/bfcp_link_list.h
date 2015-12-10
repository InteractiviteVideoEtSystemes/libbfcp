/**
 *
 * \brief BFCP Request list management  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_link_list.h
 *
 * \version $Revision: 2505 $
 *
 * \date $Date: 2015-10-30 19:23:46 +0100 (Fri, 30 Oct 2015) $
 *
 * \remarks :
 */
 #ifndef _BFCP_LINK_LIST_H
#define _BFCP_LINK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The BFCP messages building/parsing library */
#include "bfcp_messages.h"
#include "bfcp_floor_list.h"
#include "bfcp_user_list.h"
#include "bfcp_threads.h"


/* FloorRequestQuery instance (to notify about request events) */
typedef struct floor_request_query {
	UINT16 userID;		/* User to notify */
	int fd;					/* File descriptor of the user's connection */
	int transport;
	struct floor_request_query *next;	/* Next FloorRequestQuery in the list */
} floor_request_query;

/* Floor information */
typedef struct bfcp_floor {
	UINT16 floorID;	/* FloorID in this request */
	e_floor_state status;			/* Floor state as defined in bfcp_floor_list.h */
	char *chair_info;		/* Chair-provided text about ChairActions */
	BFCP_THREAD_HANDLE pID;			/* Thread handling this request */
	struct bfcp_floor *next;	/* Next Floor in the list */
} bfcp_floor;

/* Pointer to a specific instance */
typedef bfcp_floor *pfloor;

/** \brief FloorRequest information */
/** \struct bfcp_node */
typedef struct bfcp_node {
	UINT16 floorRequestID;
	UINT16 userID;
	UINT16 beneficiaryID;
	e_bfcp_priority priority;					/** \brief  Priority in the Pending queue */
	UINT16 queue_position;				/** \brief Queue Position in the Accepted list */
	char *participant_info;				/** \brief Participant-provided text */
	char *chair_info;				/** \brief Chair-provided text about ChairActions */
	struct floor_request_query *floorrequest;	/** \brief Array of queries for this request */
	struct bfcp_floor *floor;			/** \brief List of floors in this request */
	struct bfcp_node *next, *prev;			/** \brief This is a double-linked list */
} bfcp_node;
/* Pointer to a specific instance */
typedef bfcp_node *pnode;


/*
A BFCP queue is structured as follows:

		NULL  <----------- prev  <----------- prev
	head ---> object1      object2       object3 <--- tail
		(struct bfcp_node) (struct bfcp_node) (struct bfcp_node)
        next ------------> next ------------> NULL
        */
typedef struct bfcp_queue {
    pnode head;  /* The first element in the list */
    pnode tail;  /* The last element in the list */
} bfcp_queue;

class BFCP_LinkList 
{

public:
    BFCP_LinkList( );
    virtual ~BFCP_LinkList(void);
    virtual bfcp_user_information* BFCP_LinkList_show_user_information(lusers list_users, UINT16 userID) = 0;
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel,const  char* pcFormat, ...) = 0;
    
protected:

    // List-related methods 
    /* Create a new linked list of BFCP queues */
    struct bfcp_queue *bfcp_create_list(void);
    /* Initialize a new FloorRequest node */
    struct bfcp_node *bfcp_init_request(UINT16 userID, UINT16 beneficiaryID, e_bfcp_priority priority, char *text, UINT16 floorID);
    /* Add a floor to an existing FloorRequest */
    int bfcp_add_floor_to_request(pnode newnode, UINT16 floorID);
    /* Add an existing FloorRequest to a BFCP queue */
    int bfcp_insert_request(bfcp_queue *conference, pnode newnode, UINT16 floorRequestID, char *chair_info);
    /* Return the UserID of the user who made the request */
    UINT16 bfcp_give_user_of_request(bfcp_queue *conference, UINT16 floorRequestID);
    /* Change status to a floor in a request */
    int bfcp_change_status(bfcp_queue *conference, UINT16 floorID, UINT16 floorRequestID, e_floor_state status, char *floor_chair_info);
    /* Check if the overall status is actually the status of every floor in the request (?) */
    int bfcp_all_floor_status(bfcp_queue *conference, UINT16 floorRequestID, e_floor_state status);
    /* Check if the pthread identifier is valid (?) */
    int bfcp_all_floor_pID(pnode newnode);
    /* Remove a floor from a floor request information (?) */
    int bfcp_delete_node_with_floorID(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list);
    /* Remove all elements related to an user from a floor request information (?) */
    int bfcp_delete_node_with_userID(bfcp_queue *conference, UINT16 userID, bfcp_list_floors *lfloors);
    /* Remove a FloorRequest from the BFCP queues */
    bfcp_floor *bfcp_delete_request(bfcp_queue *conference, UINT16 floorRequestID, int type_queue);
    /* Get a FloorRequest from one of the BFCP queues */
    bfcp_node *bfcp_extract_request(bfcp_queue *conference, UINT16 floorRequestID);
    /* Setup a FloorRequest so that it is to be sent in a BFCP message (?) */
    int bfcp_floor_request_query_server(bfcp_queue *conference, UINT16 floorRequestID, UINT16 userID, int sockfd, int transport);
    /* Remove all requests from a list */
    int bfcp_clean_request_list(bfcp_queue *conference);
    /* Free a linked list of requests */
    int bfcp_remove_request_list(bfcp_queue **conference);
    /* Kill all the running threads handling a specific FloorRequest */
    int bfcp_kill_threads_request_with_FloorRequestID(bfcp_queue *conference, UINT16 floorRequestID);
    /* Convert a 'bfcp_node' info to 'bfcp_floor_request_information' (bfcp_messages.h) */
    bfcp_floor_request_information *bfcp_show_floorrequest_information(bfcp_queue *conference, lusers users, UINT32 FloorRequestID, int type_queue);


    /******************/
    /* Helper methods */
    /******************/

    /* Create a new linked list of floors */
    bfcp_floor *create_floor_list(UINT16 floorID, e_floor_state status, char *floor_chair_info);
    /* Add floors to a list in order */
    bfcp_floor *add_floor_list(bfcp_floor *floor_list, UINT16 floorID, e_floor_state status, char *floor_chair_info);
    /* Free a linked list of requests */
    int remove_floor_list(bfcp_floor *floor_list);
    /* Remove the list of requests from a request node */
    int remove_request_list_of_node(floor_request_query *floorrequest);
    /* Add a request to a request node */
    int add_request_to_the_node(pnode traverse, UINT16 userID, int sockfd, int transport);
    /* Request a request from a request node */
    int remove_request_from_the_node(pnode traverse, UINT16 userID);
    /* ?? */
    int bfcp_accepted_pending_node_with_floorID(UINT32 conferenceID, bfcp_queue *accepted, bfcp_queue *conference, UINT16 floorID, bfcp_list_floors *lfloors, int type_list);
    /* Change position in queue to a FloorRequest */
    int bfcp_change_queue_position(bfcp_queue *conference, UINT16 floorRequestID, UINT16 queue_position);
};
#endif

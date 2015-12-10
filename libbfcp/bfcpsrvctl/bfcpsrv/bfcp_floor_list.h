/**
 *
 * \brief Floor list management  
 *
 * \author Lorenzo Miniero 
 *
 * \file bfcp_floor_list.h
 *
 * \version $Revision: 2172 $
 *
 * \date $Date: 2014-01-27 09:08:19 +0100 (Mon, 27 Jan 2014) $
 *
 * \remarks :
 */
 #ifndef _BFCP_FLOOR_LIST_H
#define _BFCP_FLOOR_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "bfcp_messages.h"

typedef enum  floor_state {
    BFCP_FLOOR_STATE_WAITING=0,
    BFCP_FLOOR_STATE_ACCEPTED,
    BFCP_FLOOR_STATE_GRANTED
} e_floor_state;


/* FloorQuery instance (to notify about floor events) */
typedef struct floor_query {
	UINT16 userID;	/* User to notify */
	int fd;				/* File descriptor of the user's connection */
	struct floor_query *next;	/* Next FloorQuery in the list */
} floor_query;

/* Floor */
typedef struct bfcp_floors {
	UINT16 floorID;		/* Floor ID */
	UINT16 chairID;		/* UserID of the Chair for this floor */
	e_floor_state floorState;		/* Current state of the floor (free or not) */
	UINT16 limit_granted_floor;	/* Number of users this floor can be granted to at the same time */
	struct floor_query *floorquery;		/* Users interested in events related to this floor (FloorQuery) */
} bfcp_floors;
/* Pointer to a Floor instance */
typedef bfcp_floors *floors;

/* Linked list of floors */
typedef struct bfcp_list_floors {
	UINT16 number_floors;		/* The maximum allowed number of floors in this conference */
	UINT16 actual_number_floors;	/* The currently available floors in this conference */
	struct bfcp_floors *floors;			/* List of floors */
} bfcp_list_floors;
/* Pointer to a list of floors */
typedef bfcp_list_floors *lfloors;


#if defined __cplusplus
	extern "C" {
#endif
/*************************/
/* Floor-related methods */
/*************************/

/* Create a new linked list of floors */
struct bfcp_list_floors *bfcp_create_floor_list(UINT16 Max_Num);
/* Add a floor (and its chair, if present) to a list of floors */
int bfcp_insert_floor(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID);
/* Get the number of currently available floors in a list */
int bfcp_return_number_floors(bfcp_list_floors *lfloors);
/* Change the maximum number of allowed floors in a conference */
int bfcp_change_number_floors(bfcp_list_floors *lfloors, UINT16 Num);
/* Check if a floor exists in a conference */
int bfcp_exist_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Remove a floor from a floors list */
int bfcp_delete_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Change the chair's userID for a floor (setting chair to 0 removes it) */
int bfcp_change_chair(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 chairID);
/* Get the maximum number of users that can be granted this floor at the same time */
int bfcp_return_number_granted_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Change the maximum number of users that can be granted this floor at the same time */
int bfcp_change_number_granted_floor(bfcp_list_floors *lfloors, UINT16 floorID, UINT16 limit_granted_floor);
/* Change the current status of a floor */
int bfcp_change_state_floor(bfcp_list_floors *lfloors, UINT16 floorID, e_floor_state state);
/* Get the current status of a floor */
e_floor_state bfcp_return_state_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Get the position of this floor in the list */
int bfcp_return_position_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Return the BFCP UserID of the chair of this floor */
UINT16 bfcp_return_chair_floor(bfcp_list_floors *lfloors, UINT16 floorID);
/* Check if the chair's BFCP UserID exists (i.e. if it's valid) */
int bfcp_exist_user_as_a_chair(bfcp_list_floors *lfloors, UINT16 chairID);
/* Remove all floors from a list */
int bfcp_clean_floor_list(bfcp_list_floors *lfloors);
/* Free a linked list of floors */
int bfcp_remove_floor_list(bfcp_list_floors **lfloorsp);


/******************/
/* Helper methods */
/******************/

/* Remove a user from notifications related to floor events */
int remove_request_from_the_floor(bfcp_floors *floors, UINT16 userID);
#if defined __cplusplus
	}
#endif

#endif

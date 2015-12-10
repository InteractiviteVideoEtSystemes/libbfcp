/**
 *
 * \brief User list management  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_user_list.cpp
 *
 * \version $Revision: 2588 $
 *
 * \date $Date: 2015-11-13 19:24:09 +0100 (Fri, 13 Nov 2015) $
 *
 * \remarks :
 */
 
#include "../../bfcp_threads.h"
#include "bfcp_messages.h"
#include "bfcp_user_list.h"
#include "BFCPexception.h"



BFCP_UserList::BFCP_UserList(){
}

BFCP_UserList::~BFCP_UserList(void){
}

/* Create a new linked list of users */
struct bfcp_list_users *BFCP_UserList::bfcp_create_user_list (UINT16 Max_Number_Floor_Request, UINT16 Num_floors)
{
	bfcp_list_users *lusers;

	if(Max_Number_Floor_Request <= 0)
		Max_Number_Floor_Request = 1;
	if(Num_floors <= 0)
		Num_floors = 1;

	/* Allocate a new list of users */
	lusers = (bfcp_list_users *)calloc(1, sizeof(bfcp_list_users));

	/* Initialize the list */
	if(lusers == NULL)
		return(NULL);
	else {
		lusers->max_number_floor_request = Max_Number_Floor_Request;
		lusers->maxnumberfloors = --Num_floors;
		lusers->users = NULL;
	}

	return(lusers);
}

/* Check ifparticipant with such userID exists in this list */
int BFCP_UserList::bfcp_existence_user(lusers list_users, UINT16 userID)
{
	users temp_list_users;

	if(list_users == NULL)
		return -1;
	if(userID <= 0)
		return -1;

	temp_list_users= list_users->users;
	
	while(temp_list_users && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;

	if(temp_list_users && (temp_list_users->userID == userID))
		/* This user is in the list */
		return 0;
	else
		/* This user is NOT in the list */
		return -1;
}

UINT16 BFCP_UserList::find_user_by_sockfd(lusers list_users, BFCP_SOCKET s)
{
	users temp_list_users;

	if (list_users == NULL || s == INVALID_SOCKET)
		return 0;

	temp_list_users = list_users->users;
	while(temp_list_users)
	{
		if ( temp_list_users->sockFd == s)
		{
			return temp_list_users->userID;
		}
		temp_list_users = temp_list_users->next;
	}
	return 0;
}

/* Change the allowed number of per-floor requests for this list */
int BFCP_UserList::bfcp_change_user_req_floors(lusers list_users, UINT16 Max_Number_Floor_Request)
{
	if(list_users == NULL)
		return -1;

	list_users->max_number_floor_request = Max_Number_Floor_Request;

	return 0;
}

/* Change the allowed number of floors in the conference for this list */
int BFCP_UserList::bfcp_change_number_users_floors(lusers list_users, UINT16 Num_floors)
{
	users user = NULL;
	int *list_floors = NULL, i = 0;

	if(list_users == NULL)
		return -1;
	if(Num_floors <= 0)
		return -1;

	for(user = list_users->users; user; user= user->next) {
		if(list_users->maxnumberfloors >= Num_floors) {
			for(i = Num_floors; i <= list_users->maxnumberfloors; i++)
				user->numberfloorrequest[i] = 0;
		}

		list_floors = (int *)realloc(user->numberfloorrequest, (Num_floors)*sizeof(int));
		if(list_floors == NULL)
			return -1;

		user->numberfloorrequest= list_floors;
		
		if(Num_floors > list_users->maxnumberfloors) {
			for(i = list_users->maxnumberfloors+1; i < Num_floors; i++)
				user->numberfloorrequest[i]=0;
		}
	}

	list_users->maxnumberfloors = --Num_floors;

	return 0;
}

/* Set sock fd to user to this list */
int BFCP_UserList::bfcp_set_user_socket(lusers list_users, UINT16 userID, BFCP_SOCKET p_sockfd, int transport )
{
	users user = NULL;
	if(list_users == NULL)
		return -1;
	if(userID <= 0)
		return -1;


	/* First we check if a user with the same ID already exists in the list */
	for (user = list_users->users; user; user = user->next)
	{
	    if(user->userID == userID)
	    {
		user->sockFd = p_sockfd;
		user->bfcp_transport = transport;
		return 0;
	    }
	}
	return -1;
}

BFCP_SOCKET BFCP_UserList::bfcp_get_user_socket(lusers list_users, UINT16 userID, int * p_transport )
{
	users  user = NULL;
	if(list_users == NULL)
		return INVALID_SOCKET;
	if(userID <= 0)
		return INVALID_SOCKET;


	/* First we check if a user with the same ID already exists in the list */
	for (user = list_users->users; user; user = user->next)
	{
		if(user->userID == userID)
		{
			*p_transport = user->bfcp_transport;
			return user->sockFd ;
		}
	}
	return INVALID_SOCKET;
}


/* Add a new user to this list */
int BFCP_UserList::bfcp_add_user(lusers list_users, UINT16 userID,  char *user_URI, char *user_display_name)
{
	users ini_user_list = NULL, user = NULL, node_user = NULL;
	size_t dLen = 0;
	if(list_users == NULL)
		return -1;
	if(userID <= 0)
		return -1;


	/* First we check if a user with the same ID already exists in the list */
	for(user = list_users->users; user; user = user->next) {
		if(user->userID == userID)
			/* This user already exists in the list */
			return -1;
	}

	/* Create a new user instance */
	node_user = (bfcp_user *)calloc(1, sizeof(bfcp_user));

	/* Initialize the new user */
	if(node_user == NULL)
		return -1;
	else {
		node_user->userID = userID;
		node_user->sockFd = INVALID_SOCKET ;
		/* Add the CSP URI text */
		if(user_URI != NULL) {
			dLen = strlen(user_URI);
			if(dLen != 0) {
				node_user->user_URI = (char *)calloc(1, dLen*sizeof(char)+1);
				if(node_user->user_URI == NULL)
					return -1;
				memcpy(node_user->user_URI, user_URI, dLen+1);
			}
		} else	/* No CSP URI for this user */
			node_user->user_URI = NULL;

		/* Add the Display Name text */
		if(user_display_name != NULL) {
			dLen = strlen(user_display_name);
			if(dLen != 0) {
				node_user->user_display_name = (char *)calloc(1, dLen*sizeof(char)+1);
				if(node_user->user_display_name == NULL)
					return -1;
				memcpy(node_user->user_display_name, user_display_name, dLen+1);
			}
		} else	/* No Display Name for this user */
			node_user->user_display_name = NULL;

		/* Create a list for floor requests by this user */
		node_user->numberfloorrequest = (int *)calloc(list_users->maxnumberfloors + 1, sizeof(int));
		if(node_user->numberfloorrequest == NULL)
			return -1;

		if(list_users->users == NULL) {
			node_user->next = list_users->users;
			list_users->users = node_user;
		} else if(list_users->users->userID < userID) {
			node_user->next = list_users->users;
			list_users->users = node_user;	
		} else {
			ini_user_list = list_users->users;
			while(ini_user_list->next && (ini_user_list->next->userID > userID)) {
				ini_user_list = ini_user_list->next;
			}
			node_user->next = ini_user_list->next;
			ini_user_list->next = node_user;	
		}
	}

	return(0);
}

/* Delete an existing user from this list */
int BFCP_UserList::bfcp_delete_user(lusers list_users, UINT16 userID)
{
	users temp_list_users, temp_node_user;
	if(list_users == NULL)
		return 0;
	if(userID <= 0)
		return -1;


	temp_list_users = list_users->users;
	if(temp_list_users == NULL)
		/* The users' list is empty */
		return 0;
	else {
		if(temp_list_users->userID == userID)
			list_users->users = temp_list_users->next;
		else {
			while((temp_list_users->next != NULL) && (temp_list_users->next->userID != userID))
				temp_list_users = temp_list_users->next;
			if(temp_list_users->next!=NULL) {
				temp_node_user = temp_list_users;
				temp_list_users = temp_list_users->next;
				temp_node_user->next = temp_list_users->next;
			}
		}
	}
	
	/* This node is not in the list */
	if((temp_list_users == NULL) || (temp_list_users->userID != userID))
		/* This user does not exist in the conference */
		return 0;
	
	/* Free the user node */
	free(temp_list_users->user_URI);
	temp_list_users->user_URI = NULL;
	free(temp_list_users->user_display_name);
	temp_list_users->user_display_name = NULL;
	free(temp_list_users->numberfloorrequest);
	temp_list_users->numberfloorrequest = NULL;
	free(temp_list_users);
	temp_list_users = NULL;

	return(0);
}

/* Add a new FloorRequest to the list of requests made by this user */
int BFCP_UserList::bfcp_add_user_request(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y)
{
	users temp_list_users;
	if(userID <= 0)
		return -1;
	if(position_floor < 0)
		return -1;
	if(list_users == NULL)
		return -1;


	if(position_floor >list_users->maxnumberfloors)
		/* This floor is not in the conference */
		return -1;
	
	temp_list_users= list_users->users;
	while((temp_list_users != NULL) && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;
	
	/* ifthe node is in the list, print it */
	if((temp_list_users != NULL) && (temp_list_users->userID == userID)) 
	{
		if((temp_list_users->numberfloorrequest[position_floor]) >= list_users->max_number_floor_request)
		{
			char errortext[200];
			sprintf(errortext, "User %d has already reached the maximum allowed number of requests (%i) for the same floor in Conference %d", userID, list_users->max_number_floor_request, ConferenceID);
			BFCP_UserList_error_code(ConferenceID, userID, TransactionID, BFCP_MAX_FLOORREQUESTS_REACHED, errortext, NULL, sockfd, y, temp_list_users->bfcp_transport);
			return -1;
		} else
			temp_list_users->numberfloorrequest[position_floor] = temp_list_users->numberfloorrequest[position_floor]+1;
	} else
		/* This user is not in the list */
		return -1;
	
	return 0;
}

/* Check ifthis user has already reached the max number of requests that can be made for this floor */
int BFCP_UserList::bfcp_is_floor_request_full(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y, int transport)
{
	users temp_list_users;

	if(userID <= 0)
		return -1;
	if(position_floor < 0)
		return -1;
	if(list_users == NULL)
		return -1;

	if(position_floor > list_users->maxnumberfloors)
		/* This floor is not in the conference */
		return -1;

	temp_list_users = list_users->users;
	if(temp_list_users==NULL)
		return -1;

	while((temp_list_users != NULL) && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;

	/* ifthe node is in the list, print it */
	if((temp_list_users != NULL) && (temp_list_users->userID == userID)) {
		if(temp_list_users->numberfloorrequest[position_floor] >= list_users->max_number_floor_request) {
			char errortext[200];
			sprintf(errortext, "User %hu has already reached the maximum allowed number of requests (%i) for the same floor in Conference %d", userID, list_users->max_number_floor_request, ConferenceID);
			BFCP_UserList_error_code(ConferenceID, userID, TransactionID, BFCP_MAX_FLOORREQUESTS_REACHED, errortext, NULL, sockfd, y, transport);
			return -1;
		}
	}
	return(0);
}

/* Clean all requests made by all users of this list regarding a specific floor */
int BFCP_UserList::bfcp_clean_all_users_request_of_a_floor(lusers list_users, UINT16 floorID)
{

	users temp_list_users;
	if(list_users == NULL)
		return -1;
	if(floorID <= 0)
		return -1;

	if(floorID > list_users->maxnumberfloors+1)
		/* This floor is not in the conference */
		return -1;
	
	temp_list_users = list_users->users;
	
	for(temp_list_users = list_users->users; temp_list_users; temp_list_users = temp_list_users->next)
		temp_list_users->numberfloorrequest[floorID-1] = 0;
	
	return(0);
}

/* Stop handling a specific floor in this list and remove it */
int BFCP_UserList::bfcp_delete_a_floor_from_user_list(lusers list_users, UINT16 floorID)
{
	users temp_list_users;
	int i;
	int *list_floors;
	if(list_users == NULL)
		return -1;

	
	if(floorID>list_users->maxnumberfloors+1)
		/* This floor is not in the conference */
		return -1;
	
	temp_list_users = list_users->users;

	for(temp_list_users = list_users->users; temp_list_users; temp_list_users = temp_list_users->next) {
		for(i = floorID + 1; i < list_users->maxnumberfloors; i++)
			temp_list_users->numberfloorrequest[i-1] = temp_list_users->numberfloorrequest[i];
		temp_list_users->numberfloorrequest[i-1] = 0;

		list_floors = (int *)realloc(temp_list_users->numberfloorrequest, (list_users->maxnumberfloors+1)*sizeof(int));
		if(list_floors == NULL)
			return -1;
	}

	list_users->maxnumberfloors = list_users->maxnumberfloors - 1;

	return(0);
}

/* Decrease the number of requests made by a user for a floor */
int BFCP_UserList::bfcp_deleted_user_request(lusers list_users, UINT16 userID, int position_floor)
{
	users temp_list_users;
	if(list_users == NULL)
		return -1;
	if(userID <= 0)
		return -1;
	if(position_floor < 0)
		return -1;


	if(position_floor>list_users->maxnumberfloors)
		/* This floor is not in this list */
		return -1;

	temp_list_users = list_users->users;
	
	while(temp_list_users && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;

	if(temp_list_users && (temp_list_users->userID == userID)) {
		if(temp_list_users->numberfloorrequest[position_floor] > 0)
			temp_list_users->numberfloorrequest[position_floor] = temp_list_users->numberfloorrequest[position_floor] -1;
	} else
		/* This user is not in the list */
		return -1;

	return(0);
}

/* Remove all users from a list */
int BFCP_UserList::bfcp_clean_user_list(lusers list_users)
{
	users temp_list_users, temp;
	if(list_users == NULL)
		return -1;


	temp_list_users= list_users->users;
	if(temp_list_users == NULL)
		return 0;

	while(temp_list_users) {
		temp = temp_list_users;
		temp_list_users = temp_list_users->next;
		free(temp->user_URI);
		temp->user_URI = NULL;
		free(temp->user_display_name);
		temp->user_display_name = NULL;
		free(temp->numberfloorrequest);
		temp->numberfloorrequest = NULL;
		free(temp);
		temp = NULL;
	}

	list_users->users=NULL;
	return(0);
}

/* Free a linked list of users */
int BFCP_UserList::bfcp_remove_user_list(bfcp_list_users **lusers_p)
{
	int error;
	bfcp_list_users *lusers = *lusers_p;
	if(lusers_p == NULL)
		return 0;


	error = bfcp_clean_user_list(lusers);

	if(error == 0) {
		free(lusers);
		lusers = NULL;
		*lusers_p = NULL;
	} else
		return -1;

	return(0);

}

/* Convert a 'bfcp_user' info to 'bfcp_user_information' (bfcp_messages.h) */
bfcp_user_information* BFCP_UserList::bfcp_show_user_information(lusers list_users, UINT16 userID)
{
	users temp_list_users;
	bfcp_user_information *user_info;
	if(list_users == NULL)
		return NULL;
	if(userID <= 0)
		return NULL;

	
	temp_list_users = list_users->users;
	
	while(temp_list_users && temp_list_users->userID!= userID)
		temp_list_users = temp_list_users->next;
	
	/* ifthe node is in the list, convert it to a 'bfcp_user_information' */
	if(temp_list_users && (temp_list_users->userID == userID))
		user_info = bfcp_new_user_information(temp_list_users->userID, temp_list_users->user_display_name, temp_list_users->user_URI);
	else
		/* This user is not in the list */
		return NULL;
	
	return user_info;
}

/* Get the CSP URI for this BFCP UserID */
char *BFCP_UserList::bfcp_obtain_userURI(lusers list_users, UINT16 userID)
{
	users temp_list_users;
	if(userID <= 0)
		return NULL;
	if(list_users == NULL)
		return NULL;


	temp_list_users= list_users->users;
	while((temp_list_users != NULL) && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;

	/* ifthe node is in the list, return the URI information */
	if((temp_list_users != NULL) && (temp_list_users->userID == userID))
		return temp_list_users->user_URI;
	else
		return NULL;
}

/* Get the Display Name for this BFCP UserID */
char *BFCP_UserList::bfcp_obtain_user_display_name(lusers list_users, UINT16 userID)
{
	users temp_list_users;
	if(userID <= 0)
		return NULL;
	if(list_users == NULL)
		return NULL;


	temp_list_users= list_users->users;
	while((temp_list_users != NULL) && (temp_list_users->userID != userID))
		temp_list_users = temp_list_users->next;

	if((temp_list_users != NULL) && (temp_list_users->userID == userID))
		return temp_list_users->user_display_name;
	else
		return NULL;
}

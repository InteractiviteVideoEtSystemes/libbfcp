/**
 *
 * \brief User list management  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_user_list.h
 *
 * \version $Revision: 2583 $
 *
 * \date $Date: 2015-11-13 11:17:55 +0100 (Fri, 13 Nov 2015) $
 *
 * \remarks :
 */
#ifndef _BFCP_USER_LIST_H
#define _BFCP_USER_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef SUPPORT_SSL
/* Needed for TCP/TLS/BFCP support */
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#endif


enum chair_type {NO_CHAIR = 0, CHAIR};

/* BFCP Participant (User) */
typedef struct bfcp_user 
{
    UINT16 userID;		/* UserID */
    char *user_URI;		/* Call Signaling Protocol URI */
    char *user_display_name;	/* User-friendly Display Name */
    int *numberfloorrequest;	/* Number of floor requests made by this user for each floor in the conference */
    BFCP_SOCKET sockFd ;
    int bfcp_transport;		/* transport used by sock fd associated with user */   
    struct bfcp_user *next;	/* Next user in the list */
}
bfcp_user;
/* Pointer to a specific user */
typedef bfcp_user *users;

/* List of participants to the conference */
typedef struct bfcp_list_users
{
    UINT16 max_number_floor_request;	/* Policy regarding the max allowed number of requests each user can make for a specific floor */
    UINT16 maxnumberfloors;		/* The max number of allowed floors in this conference */
    struct bfcp_user *users;	/* The linked list of all users in the conference */
} bfcp_list_users;
/* Pointer to a specific list of users */
typedef bfcp_list_users *lusers;

class BFCP_UserList 
{
public:
    BFCP_UserList();
    virtual ~BFCP_UserList(void);
    virtual int BFCP_UserList_error_code(UINT32 conferenceID, UINT16 userID, UINT16 TransactionID, e_bfcp_error_codes code, char *error_info, bfcp_unknown_m_error_details *details, int sockfd, int i, int transport)=0 ;
  

protected:
    
    /************************/
    /* User-related methods */
    /************************/
    /* Create a new linked list of users */
    struct bfcp_list_users *bfcp_create_user_list (UINT16 Max_Number_Floor_Request, UINT16 Num_floors);
    /* Check if participant with such userID exists in this list */
    int bfcp_existence_user(lusers list_users, UINT16 userID);
    
    UINT16 find_user_by_sockfd(lusers list_users, BFCP_SOCKET s);
    
    /* Change the allowed number of per-floor requests for this list */
    int bfcp_change_user_req_floors(lusers list_users, UINT16 Max_Number_Floor_Request);
    /* Change the allowed number of floors in the conference for this list */
    int bfcp_change_number_users_floors(lusers list_users, UINT16 Num_floors);
    /* Add a new user to this list */
    int bfcp_add_user(lusers list_users, UINT16 userID, char *user_URI, char *user_display_name);
    int bfcp_set_user_socket(lusers list_users, UINT16 userID, BFCP_SOCKET p_sockfd, int transport );
    BFCP_SOCKET bfcp_get_user_socket(lusers list_users, UINT16 userID, int * p_transport );
    /* Delete an existing user from this list */
    int bfcp_delete_user(lusers list_users, UINT16 userID);
    /* Add a new FloorRequest to the list of requests made by this user */
    int bfcp_add_user_request(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y);
    /* Check if this user has already reached the max number of requests that can be made for this floor */
    int bfcp_is_floor_request_full(UINT32 ConferenceID, UINT16 TransactionID, lusers list_users, UINT16 userID, int position_floor, int sockfd, int y, int transport);
    /* Clean all requests made by all users of this list regarding a specific floor */
    int bfcp_clean_all_users_request_of_a_floor(lusers list_users, UINT16 floorID);
    /* Stop handling a specific floor in this list and remove it */
    int bfcp_delete_a_floor_from_user_list(lusers list_users, UINT16 floorID);
    /* Decrease the number of requests made by a user for a floor */
    int bfcp_deleted_user_request(lusers list_users, UINT16 userID, int position_floor);
    /* Remove all users from a list */
    int bfcp_clean_user_list(lusers list_users);
    /* Free a linked list of users */
    int bfcp_remove_user_list(bfcp_list_users **lusers_p);
    /* Convert a 'bfcp_user' info to 'bfcp_user_information' (bfcp_messages.h) */
    bfcp_user_information* bfcp_show_user_information(lusers list_users, UINT16 userID);


    /******************/
    /* Helper methods */
    /******************/

    /* Get the CSP URI for this BFCP UserID */
    char *bfcp_obtain_userURI(lusers list_users, UINT16 userID);
    /* Get the Display Name for this BFCP UserID */
    char *bfcp_obtain_user_display_name(lusers list_users, UINT16 userID);

};

#endif

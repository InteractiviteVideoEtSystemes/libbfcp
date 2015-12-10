/*===========================================================================*/
/* Unpublished Confidential Information of IVES Do not disclose.             */
/* Copyright (c) 2000-2014 IVES  All Rights Reserved.                        */
/*---------------------------------------------------------------------------*/
/*!
 * COMPANY  : IVES
 *
 * MODULE   : libbfcp
 *
 * \author  : Philippe Verney
 *
 * \file    : bfcp_strings.c
 *
 * \brief   : String definitions for BFCP numeric values
 *
 * \version : $Revision: 2655 $
 *
 * \date    : $Date: 2015-12-03 22:57:58 +0100 (Thu, 03 Dec 2015) $
 *
 * \remarks :
 *
 * ------------------------------------------------------------------------- */

/* ==========================================================================*/
/* File identification                                                       */
/* ==========================================================================*/

/* ==========================================================================*/
/* include(s)                                                                */
/* ==========================================================================*/
#include "bfcp_strings.h"

/* ==========================================================================*/
/* Code                                                                      */
/* ==========================================================================*/

struct _bfcp_primitive
{
	int primitive;
	const char *description;
};

static const struct _bfcp_primitive _bfcp_primitives[] = 
{
	{ 0 ,"Unknown primitive" },
	{ e_primitive_FloorRequest, "FloorRequest" },
	{ e_primitive_FloorRelease, "FloorRelease" },
	{ e_primitive_FloorRequestQuery, "FloorRequestQuery" },
	{ e_primitive_FloorRequestStatus, "FloorRequestStatus" },
	{ e_primitive_UserQuery, "UserQuery" },
	{ e_primitive_UserStatus, "UserStatus" },
	{ e_primitive_FloorQuery, "FloorQuery" },
	{ e_primitive_FloorStatus, "FloorStatus" },
	{ e_primitive_ChairAction, "ChairAction" },
	{ e_primitive_ChairActionAck, "ChairActionAck" },
	{ e_primitive_Hello, "Hello" },
	{ e_primitive_HelloAck, "HelloAck" },
	{ e_primitive_Error, "Error" },
	{ e_primitive_FloorRequestStatusAck, "FloorRequestStatusAck" },
	{ e_primitive_ErrorAck, "ErrorAck" },
	{ e_primitive_FloorStatusAck, "FloorStatusAck" },
	{ e_primitive_Goodbye, "GoodBye" },
	{ e_primitive_GoodbyeAck, "GoodbyeAck" }
};


static const struct _bfcp_primitive _cisco_primitives[] =
{
	{ e_primitive_Cisco90, "Prop Cisco (90)" },
	{ e_primitive_Cisco91, "Prop Cisco (91)" },
	{ e_primitive_Cisco92, "Prop Cisco (92)" },
	{ e_primitive_Cisco93, "Prop Cisco (93)" },
	{ e_primitive_Cisco94, "Prop Cisco (94)" },
	{ e_primitive_Cisco95, "Prop Cisco (95)" }
};


const char* getBfcpDescPrimitive( e_bfcp_primitives p)
{
    if ( p >= e_primitive_FloorRequest || p <= e_primitive_GoodbyeAck )
    {
	return _bfcp_primitives[p].description ;
    }
    
    if ( p >= e_primitive_Cisco90 || p <= e_primitive_Cisco95 )
    {
	p = p - e_primitive_Cisco90;
	return _cisco_primitives[p].description ;
    }
    
    p = e_primitive_InvalidPrimitive ;
    return _bfcp_primitives[p].description ;
}

static const struct _bfcp_attributes {
	int attribute;
	const char *description;
} _bfcp_attribute[] = {
    { 0 ,"Unknown attribute" },
	{ BENEFICIARY_ID, "BENEFICIARY-ID" },
	{ FLOOR_ID, "FLOOR-ID" },
	{ FLOOR_REQUEST_ID, "FLOOR-REQUEST-ID" },
	{ PRIORITY, "PRIORITY" },
	{ REQUEST_STATUS, "REQUEST-STATUS" },
	{ ERROR_CODE, "ERROR-CODE" },
	{ ERROR_INFO, "ERROR-INFO" },
	{ PARTICIPANT_PROVIDED_INFO, "PARTICIPANT-PROVIDED-INFO" },
	{ STATUS_INFO, "STATUS-INFO" },
	{ SUPPORTED_ATTRIBUTES, "SUPPORTED-ATTRIBUTES" },
	{ SUPPORTED_PRIMITIVES, "SUPPORTED-PRIMITIVES" },
	{ USER_DISPLAY_NAME, "USER-DISPLAY-NAME" },
	{ USER_URI, "USER-URI" },
	{ BENEFICIARY_INFORMATION, "BENEFICIARY-INFORMATION" },
	{ FLOOR_REQUEST_INFORMATION, "FLOOR-REQUEST-INFORMATION" },
	{ REQUESTED_BY_INFORMATION, "REQUESTED-BY-INFORMATION" },
	{ FLOOR_REQUEST_STATUS, "FLOOR-REQUEST-STATUS" },
	{ OVERALL_REQUEST_STATUS, "OVERALL-REQUEST-STATUS" },
	{ NONCE, "NONCE" },
	{ DIGEST, "DIGEST" },
};


const char* getBfcpAttribute( e_bfcp_attibutes p){
    if ( p < BENEFICIARY_ID || p > DIGEST )
        p=INVALID_ATTRIBUTE;
    return _bfcp_attribute[p].description ;
}

static const struct _bfcp_statuses {
	int status;
	const char *description;
} _bfcp_status[] = {
    { 0 ,"" },
	{ BFCP_PENDING, "Pending" },
	{ BFCP_ACCEPTED, "Accepted" },
	{ BFCP_GRANTED, "Granted" },
	{ BFCP_DENIED, "Denied" },
	{ BFCP_CANCELLED, "Cancelled" },
	{ BFCP_RELEASED, "Released" },
	{ BFCP_REVOKED, "Revoked" },
};

const char* getBfcpStatus( e_bfcp_status p){
    if ( p < BFCP_PENDING || p > BFCP_REVOKED )
        p=BFCP_INVALID_STATUS;
    return _bfcp_status[p].description ;
}

static const struct _bfcp_priorities {
	int priority;
	const char *description;
} _bfcp_priority[] = {
	{ BFCP_LOWEST_PRIORITY, "Lowest" },
	{ BFCP_LOW_PRIORITY, "Low" },
	{ BFCP_NORMAL_PRIORITY, "Normal" },
	{ BFCP_HIGH_PRIORITY, "High" },
	{ BFCP_HIGHEST_PRIORITY, "Highest" },
};

const char* getBfcpPriority( e_bfcp_priority p){
    if ( p < BFCP_LOWEST_PRIORITY || p > BFCP_HIGHEST_PRIORITY )
        p=BFCP_LOWEST_PRIORITY;
    return _bfcp_priority[p].description ;
}

static const struct _bfcp_error_types {
	int error;
	const char *description;
} _bfcp_error_type[] = {
    { 0 ,"Unknown error type" },
	{ BFCP_CONFERENCE_DOES_NOT_EXIST, "Conference does not Exist"},
	{ BFCP_USER_DOES_NOT_EXIST, "User does not Exist"},
	{ BFCP_UNKNOWN_PRIMITIVE, "Unknown Primitive"},
	{ BFCP_UNKNOWN_MANDATORY_ATTRIBUTE, "Unknown Mandatory Attribute"},
	{ BFCP_UNAUTHORIZED_OPERATION, "Unauthorized Operation"},
	{ BFCP_INVALID_FLOORID, "Invalid Floor ID"},
	{ BFCP_FLOORREQUEST_DOES_NOT_EXIST, "Floor Request ID Does Not Exist"},
	{ BFCP_MAX_FLOORREQUESTS_REACHED, "You have Already Reached the Maximum Number of Ongoing Floor Requests for this Floor"},
	{ BFCP_USE_TLS, "Use TLS"},
	{ BFCP_DIGEST_ATTRIBUTE_REQUIRED, "Digest Attribute Required"},
	{ BFCP_INVALID_NONCE, "Invalid Nonce"},
	{ BFCP_AUTHENTICATION_FAILED, "Authentication Failed"},
};

const char* getBfcpErrorType( e_bfcp_error_codes p){
    if ( p < BFCP_CONFERENCE_DOES_NOT_EXIST || p > BFCP_AUTHENTICATION_FAILED )
        p=BFCP_INVALID_ERROR_CODES;
    return _bfcp_error_type[p].description ;
}

static const struct _bfcp_parsing_errors {
	int error;
	const char *description;
} _bfcp_parsing_error[] = {
    { 0 ,"Unknown parsing error" },
	{ BFCP_WRONG_VERSION, "Wrong Version Bit" },
	{ BFCP_RESERVED_NOT_ZERO, "Reserved bits not zeroed" },
	{ BFCP_UNKNOWN_PRIMITIVE, "Unknown Primitive" },
	{ BFCP_UNKNOWN_ATTRIBUTE, "Unknown Attribute" },
	{ BFCP_WRONG_LENGTH, "Wrong Length" },
	{ BFCP_PARSING_ERROR, "Parsing Error" },
};

const char* getBfcpParsingErrors( e_bfcp_specific_error_codes p){
    if ( p < BFCP_WRONG_VERSION || p > BFCP_PARSING_ERROR )
        p=BFCP_INVALID_SPECIFIC_ERROR_CODES;
    return _bfcp_parsing_error[p].description ;
}

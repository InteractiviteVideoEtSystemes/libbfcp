/**
 *
 * \brief String definitions for BFCP numeric values
 *
 * \author Philippe Verney
 *
 * \file bfcp_string.h
 *
 * \version $Revision: 2172 $
 *
 * \date $Date: 2014-01-27 09:08:19 +0100 (Mon, 27 Jan 2014) $
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \remarks :
 */
#ifndef _BFCP_STRINGS_H
#define _BFCP_STRINGS_H
#include "bfcp_messages.h"
#ifdef __cplusplus
extern "C" {
#endif  
/**
 * return string correspondant of primitive code
 * @param p value of BFCP primitive
 * @return primitive string
 */
const char* getBfcpDescPrimitive( e_bfcp_primitives p);
/**
 * return string correspondant of attribute code
 * @param p value of bfcp attribute
 * @return attribute string 
 */
const char* getBfcpAttribute( e_bfcp_attibutes p);
/**
 * return string correspondant of status code
 * @param p value of BFCP status 
 * @return status string 
 */
const char* getBfcpStatus( e_bfcp_status p);
/**
 * return string correspondant of priority code
 * @param p priority value
 * @return priority string 
 */
const char* getBfcpPriority( e_bfcp_priority p);
/**
 * return string correspondant of error code
 * @param p error value
 * @return error string 
 */
const char* getBfcpErrorType( e_bfcp_error_codes p);
/**
 * return string correspondant of parsing error code
 * @param p parsing error code value
 * @return parsing error code string 
 */
const char* getBfcpParsingErrors( e_bfcp_specific_error_codes p);
#ifdef __cplusplus
} // extern "C"
#endif



#endif


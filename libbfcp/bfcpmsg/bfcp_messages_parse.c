/**
 *
 * \brief Methodes for decoding messages  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_messages_parse.c
 *
 * \version $Revision: 2652 $
 *
 * \date $Date: 2015-12-03 22:54:12 +0100 (Thu, 03 Dec 2015) $
 *
 * \remarks :
 */
#include "bfcp_messages.h"
#include "bfcp_strings.h"

/* ==========================================================================*/
/* Code                                                                      */
/* ==========================================================================*/

static void dump_msg(const unsigned char * buf, unsigned int len)
{
	char line[200];
	unsigned int i, j;
	
	BFCP_msgLog(INF, "Dump: ------------------");
	for (i = 0; i< len; i+= 8)
	{
	    for (j=0; j<8 && j+i < len; j++)
	    {
		sprintf(line + (j*5), "0x%02x ", buf[i+j] );
	    }
	    BFCP_msgLog(INF, "%04d: %s", i, line);
	}
	BFCP_msgLog(INF, "Dump: ------------------");
}

static int parse_common_header1( void * buffer, int * version, int * reserved, e_bfcp_primitives * primitive, UINT16 * msg_length )
{
    if ( buffer )
    {
	UINT32  ch32;		/* 32 bits */
	
	memcpy(&ch32, buffer, 4);	/* We copy the first 4 octets of the header */
	ch32 = ntohl(ch32);
	if (version) *version = ((ch32 & 0xE0000000) >> 29);
	if (primitive) *primitive = (e_bfcp_primitives)((ch32 & 0x00FF0000) >> 16);
	if (reserved) *reserved = ((ch32 & 0x1F000000) >> 24);
	if (msg_length) *msg_length = (ch32 & 0x0000FFFF);	/* We get the Lenght of the message */
	return 1;
    }
    return 0;
}
UINT16  bfcp_get_length(bfcp_message *message)
{
    if( message && message->length >= 4 )
    {
	UINT16  length;
	
	if ( parse_common_header1(message->buffer, NULL, NULL, NULL, &length) ) return length;
    }
    return 0;
}
 
e_bfcp_primitives bfcp_get_primitive(bfcp_message *message)
{
    if( message && message->length >= 4 )
    {
	e_bfcp_primitives primitive;
	
	if ( parse_common_header1(message->buffer, NULL, NULL, &primitive, NULL) ) 
	{
	    BFCP_msgLog(INF,"< primitive[%d / 0x%x] [%s] ",primitive,primitive,getBfcpDescPrimitive(primitive));
	    return primitive;
	}
    }
    return e_primitive_InvalidPrimitive;
}
 
UINT32 bfcp_get_conferenceID(bfcp_message *message)
{
	if(!message)
		return 0;
		else {
	UINT32  ch32;		/* 32 bits */
	UINT32  conferenceID;	/* 32 bits */
	unsigned char *buffer = message->buffer + 4;
	memcpy(&ch32, buffer, 4);	/* We skip the first 4 octets of the header and copy */
	conferenceID = ntohl(ch32);	/* We get the conferenceID of the message */
	BFCP_msgLog(INF,"< conferenceID[0x%x]",conferenceID);
	return conferenceID;
	}
}

UINT16  bfcp_get_transactionID(bfcp_message *message)
{
	if(!message)
		return 0;
		else {
	UINT16  ch16;			/* 16 bits */
	UINT16  transactionID;	/* 16 bits */
	unsigned char *buffer = message->buffer + 8;
	memcpy(&ch16, buffer, 2);		/* We skip the first 8 octets of the header and copy */
	transactionID = ntohs(ch16);		/* We get the transactionID of the message */
	BFCP_msgLog(INF,"< transactionID[0x%x]",transactionID);
	return transactionID;
	}
}

UINT16  bfcp_get_userID(bfcp_message *message)
{
    if(!message)
        return 0;
    else {
        UINT32  ch16;		/* 16 bits */
        UINT16  userID;	/* 16 bits */
        unsigned char *buffer = message->buffer + 10;
        memcpy(&ch16, buffer, 2);	/* We skip the first 10 octets of the header and copy */
        userID = ntohs(ch16);		/* We get the userID of the message */
        BFCP_msgLog(INF,"< userID[0x%x]",userID);
        return userID;
    }
}

bfcp_received_message *bfcp_new_received_message(void)
{
	bfcp_received_message *recvM = (bfcp_received_message *)calloc(1, sizeof(bfcp_received_message));
	if (!recvM)	/* We could not allocate the memory, return with a failure */
	{
		return NULL;
	}
	else 
	{
		recvM->arguments = NULL;
		recvM->version = 0;
		recvM->reserved = 0;
		recvM->length = 0;
		recvM->primitive = e_primitive_InvalidPrimitive;
		recvM->entity = bfcp_new_entity(0, 0, 0);
		recvM->first_attribute = NULL;
		recvM->errors = NULL;
		return recvM;
	}
}

int bfcp_free_received_message(bfcp_received_message *recvM)
{
	int res = 0;	/* We keep track here of the results of the sub-freeing methods*/
	if(!recvM)	/* There's nothing to free, return with a failure */
		return -1;
	if(recvM->arguments)
		res += bfcp_free_arguments(recvM->arguments);
	if(recvM->entity)
		res += bfcp_free_entity(recvM->entity);
	if(recvM->first_attribute)
		res += bfcp_free_received_attribute(recvM->first_attribute);
	if(recvM->errors)
		res += bfcp_free_received_message_errors(recvM->errors);
	free(recvM);
	if(!res)	/* No error occurred, succesfully freed the structure */
		return 0;
	else		/* res was not 0, so some error occurred, return with a failure */
		return -1;
}

bfcp_received_message_error *bfcp_received_message_add_error(bfcp_received_message_error *error, e_bfcp_primitives  attribute, e_bfcp_error_codes code)
{
	bfcp_received_message_error *temp, *previous;
	
	/* temp = (bfcp_received_message_error *) = malloc( sizeof(bfcp_received_message_error) ); */
	temp = malloc( sizeof(bfcp_received_message_error) );
	if ( temp == NULL ) return NULL; /* We could not allocate the memory, return with a failure */
	temp->attribute = attribute;
	temp->code = code;
	temp->next = NULL;
	
	if (error != NULL)
	{
		previous = error;
		while ( (error = error->next) != NULL ) 
		{	/* We search the last added error */
			previous = error;
		}
		previous->next = temp;	/* Update the old last link in the list */
		return error;
	}
	return temp;
}

int bfcp_free_received_message_errors(bfcp_received_message_error *errors)
{
    if(!errors)	/* There's nothing to free, return with a failure */
        return -1;
    else {
        bfcp_received_message_error *next = NULL, *temp = errors;
        while(temp) {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return 0;
}

bfcp_received_attribute *bfcp_new_received_attribute(void)
{
	bfcp_received_attribute *recvA = (bfcp_received_attribute *)calloc(1, sizeof(bfcp_received_attribute));
	if(!recvA)	/* We could not allocate the memory, return with a failure */
		return NULL;
	recvA->type = INVALID_ATTRIBUTE;
	recvA->mandatory_bit = 0;
	recvA->length = 0;
	recvA->position = 0;
	recvA->valid = 1;	/* By default we mark the attribute as valid */
	recvA->next = NULL;
	return recvA;
}

int bfcp_free_received_attribute(bfcp_received_attribute *recvA)
{
    if(!recvA)	/* There's nothing to free, return with a failure */
        return -1;
    else {
        bfcp_received_attribute *next = NULL, *temp = recvA;
        while(temp) {
            next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return 0;
}

bfcp_received_message * bfcp_parse_message(bfcp_message *message)
{
	bfcp_received_attribute *temp1 = NULL, *temp2 = NULL, *previous = NULL;
	unsigned char *buffer;
	UINT16  ch16;	/* 16 bits */
	UINT32  ch32 ;		/* 32 bits */
	bfcp_received_message *recvM = bfcp_new_received_message();
	if(!recvM)	/* We could not allocate the memory, return with a failure */
		return NULL;
	
	/* First we read the Common Header and we parse it */
	buffer = message->buffer;
	if( message && message->length >= 12 )
	{
	    UINT16 length;
	    
	    if ( parse_common_header1(message->buffer, &recvM->version, &recvM->reserved, &recvM->primitive, &length) )
	    {
		if ( recvM->version != 1 ) 
		{	/* Version is wrong, return with an error */
		     BFCP_msgLog(ERR,"Unsupported protocol version %d", recvM->version);
		     recvM->errors = bfcp_received_message_add_error(recvM->errors, 0, BFCP_WRONG_VERSION);
		     if(! recvM->errors ) return NULL;	/* An error occurred while recording the error, return with failure */
		}
		
		BFCP_msgLog(INF,"< primitive %s(%d) ", getBfcpDescPrimitive(recvM->primitive), recvM->primitive);
		recvM->length = length*4 + 12;
		
		if ( recvM->length != message->length )
		{
		    BFCP_msgLog(ERR, "Error: payload length does not match data read from network. ");
		    BFCP_msgLog(ERR, "We read %u bytes from network while message length calculated from mayload length  is %u.",
		                 message->length, recvM->length );
		    recvM->errors = bfcp_received_message_add_error(recvM->errors, 0, BFCP_WRONG_LENGTH);
		    if ( recvM->errors == NULL ) return NULL;	/* An error occurred while recording the error, return with failure */	 
		}
		
		if ( (message->length%4) != 0 )
		{
		    BFCP_msgLog(ERR, "Error: message length %u is not a multiple of 4. Invalid message", message->length );
		    recvM->errors = bfcp_received_message_add_error(recvM->errors, 0, BFCP_WRONG_LENGTH);
		    if ( recvM->errors == NULL ) return NULL;	/* An error occurred while recording the error, return with failure */	 
		    
		}
	    }
	    else
	    {
		/* todo: free message ! memory leak */
		BFCP_msgLog(ERR, "Message ist too short. Cannot read common header. Discarding !");
		return NULL;
	    }
	}
 		
	if(recvM->errors)	/* There are errors in the header, we won't proceed further */
	{
		dump_msg(message->buffer, message->length);
		return recvM;
	}
	
	buffer += 4;
	memcpy(&ch32, buffer, 4);	/* Conference ID */
	recvM->entity->conferenceID = ntohl(ch32);
	
	buffer += 4;
	memcpy(&ch16, buffer, 2);	/* Transaction ID */
	recvM->entity->transactionID = ntohs(ch16);
	
	buffer += 2;
	memcpy(&ch16, buffer, 2);	/* User ID */
	recvM->entity->userID = ntohs(ch16);
	
	buffer += 2;
	
	BFCP_msgLog(INF,"< conferenceID: [%u], userID: [%u], transactionID: [0x%x / %u]",
	            recvM->entity->conferenceID,
		    recvM->entity->userID,
		    recvM->entity->transactionID, recvM->entity->transactionID );
	
	message->position = 12;	/* We've read the Common Header */
	while ( message->position < recvM->length )
	{
		/* We start parsing attributes too */
		temp1 = bfcp_parse_attribute(message);
		
		/* We could not parse the attribute, return with a failure */
		if (!temp1)	
			return NULL;

		if (!(recvM->first_attribute))
		{
			/**
			 * This is the first attribute we read 
			 * Let's save it as first attribute    
			 **/
			recvM->first_attribute = temp1;	
			recvM->first_attribute->next = NULL;
			temp2 = temp1;
		}
		else 
		{	/* It's not the first attribute, let's manage the list */
			temp2->next = temp1;
			temp1->next = NULL;
			previous = temp2;
			temp2 = temp1;
		}

		if (temp1->length == 0) 
		{
			/* If the length of the attribute is 0 we have to stop, we'd fall in an eternal loop
			   We save this error regarding this attribute (temp1 -> Wrong Lenght)
			   and we save it for the attribute before (temp2) too, since it lead us here */
			   
			temp1->valid = 0;		/* We mark the attribute as not valid */
			recvM->errors = bfcp_received_message_add_error(recvM->errors, temp1->type, BFCP_WRONG_LENGTH);
			if(!(recvM->errors))
				return NULL;	/* An error occurred while recording the error, return with failure */
			if(previous) {	/* Only add the error if there's an attribute before */
				previous->valid = 0;	/* We mark the attribute as not valid */
				recvM->errors = bfcp_received_message_add_error(recvM->errors, previous->type, BFCP_WRONG_LENGTH);
				if(!(recvM->errors))
					return NULL;	/* An error occurred while recording the error, return with failure */
			}
			message->position = recvM->length;	/* We don't go on parsing, since we can't jump this attribute */
		}
	}
	if ( bfcp_parse_arguments(recvM, message) == -1 )
	{
		/* We could not parse the arguments of the message */
		BFCP_msgLog(ERR, "Failed to parse BFCP message arguments");
		dump_msg(message->buffer, message->length);
		return NULL;			/* Return with a failure */
	}
		
	recvM->length = recvM->length-12;	/* Before leaving, we remove the Common Header Lenght (12 bytes) */
						/* from the Payload Lenght of the message */
	if (recvM->errors)
	{
		BFCP_msgLog(ERR, "Error condition detected during parsing");
		dump_msg(message->buffer, message->length);
	}
	return recvM;
}

bfcp_received_attribute *bfcp_parse_attribute(bfcp_message *message)
{
    int padding = 0;
    unsigned char *buffer;
    UINT16  ch16;	/* 16 bits */
    bfcp_received_attribute *recvA = bfcp_new_received_attribute();
    if(!recvA)	/* We could not allocate the memory, return with a failure */
        return NULL;
    recvA->position = message->position;	/* The position of the attribute in the buffer */
    buffer = message->buffer+recvA->position;
    memcpy(&ch16, buffer, 2);		/* TLV: Attribute Header */
    ch16 = ntohs(ch16);
    recvA->type = (e_bfcp_attibutes)((ch16 & 0xFE00) >> 9);		/* Type */
    recvA->mandatory_bit = ((ch16 & 0x0100) >> 8);	/* M */
    recvA->length = (ch16 & 0x00FF);		/* Lenght */
    buffer = buffer+2;
    if(((recvA->length)%4) != 0) 	/* There's padding stuff to jump too */
        padding = 4-((recvA->length)%4);
    message->position = message->position+recvA->length +	/* There could be some padding */
        padding;	 		/* (which is not signed in length) */
    return recvA;
}

int bfcp_parse_arguments(bfcp_received_message *recvM, bfcp_message *message)
{
    bfcp_received_attribute *temp = recvM->first_attribute;
    if(!recvM)	/* We could not allocate the memory, return with a failure */
        return -1;
    else {
        int floorID;
        bfcp_floor_id_list *tempID = NULL;	/* To manage the FLOOR-ID List */
        bfcp_floor_request_information *tempInfo = NULL, *previousInfo = NULL;/* FLOOR-REQUEST-INFORMATION list */
        recvM->arguments = bfcp_new_arguments();
        recvM->arguments->primitive = recvM->primitive;	/* Primitive */
	
	/* Entity, we copy it to avoid a doubl free */
        recvM->arguments->entity = bfcp_new_entity(recvM->entity->conferenceID, 
						   recvM->entity->transactionID, 
						   recvM->entity->userID);	/* to risk a double free()  */
        if(!(recvM->arguments))		/* We could not allocate the memory, return with a failure */
            return -1;
        while(temp) 
	{
            if(!(temp->valid)) 
	    {
		/* If the attribute is marked as not valid, we skip it... */
                temp = temp->next;
                continue;
            } 
	    else
	    {
                //BFCP_msgLog(INF,"< attribute [%s] (%d) ", getBfcpAttribute(temp->type), temp->type);
                switch(temp->type)
		{	/* ...if it's valid, we parse it */
		    case BENEFICIARY_ID:
			recvM->arguments->bID = bfcp_parse_attribute_BENEFICIARY_ID(message, temp);
			if ( !recvM->arguments->bID ) {	/* An error occurred in parsing this attribute */
			    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
			    if (! recvM->errors ) return -1;
			}
			break;
			
		     case FLOOR_ID:
		            floorID = bfcp_parse_attribute_FLOOR_ID(message, temp);
			    //BFCP_msgLog(INF,"< floorID [%d]", floorID);
			    if (!floorID)
			    {
				recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
				if (! recvM->errors ) return -1;
				break;
			    }
			    
			    tempID = recvM->arguments->fID;
			    if ( !tempID ) 
			    {
				/* Create a list, it's the first ID we add */
				recvM->arguments->fID = bfcp_new_floor_id_list(floorID, 0);
			    }
			    else 
			    {	/* We already have a list, add the new FloorID to it */
				if (bfcp_add_floor_id_list(tempID, floorID, 0) == -1) return -1;
			    }
			    break;
			    
			case FLOOR_REQUEST_ID:
			    recvM->arguments->frqID = bfcp_parse_attribute_FLOOR_REQUEST_ID(message, temp);
			    BFCP_msgLog(INF,"< FLOOR_REQUEST_ID [%d]",recvM->arguments->frqID);
			    
			    if (!recvM->arguments->frqID) {	/* An error occurred in parsing this attribute */
				recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
				if ( !recvM->errors ) return -1;	/* An error occurred while recording the error, return with failure */
			    }
			    break;
            case PRIORITY:
                recvM->arguments->priority = bfcp_parse_attribute_PRIORITY(message, temp);
                if(recvM->arguments->priority>4) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case REQUEST_STATUS:
                recvM->arguments->rs = bfcp_parse_attribute_REQUEST_STATUS(message, temp);
                //BFCP_msgLog(INF,"< REQUEST_STATUS[%d / 0x%x]",recvM->arguments->rs,recvM->arguments->rs);
                if(!(recvM->arguments->rs)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case ERROR_CODE:
                recvM->arguments->error = bfcp_parse_attribute_ERROR_CODE(message, temp);
                //BFCP_msgLog(INF,"< ERROR_CODE[%d / 0x%x]",recvM->arguments->error,recvM->arguments->error);
                if(!(recvM->arguments->error)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case ERROR_INFO:
                recvM->arguments->eInfo = bfcp_parse_attribute_ERROR_INFO(message, temp);
                if(!(recvM->arguments->eInfo)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case PARTICIPANT_PROVIDED_INFO:
                recvM->arguments->pInfo = bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO(message, temp);
                BFCP_msgLog(INF,"< PARTICIPANT_PROVIDED_INFO[%s]",recvM->arguments->pInfo?recvM->arguments->pInfo:"");
                if(!(recvM->arguments->pInfo)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case STATUS_INFO:
                recvM->arguments->sInfo = bfcp_parse_attribute_STATUS_INFO(message, temp);
                BFCP_msgLog(INF,"< STATUS_INFO[%s]",recvM->arguments->sInfo?recvM->arguments->sInfo:"");
                if(!(recvM->arguments->sInfo)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case SUPPORTED_ATTRIBUTES:
                recvM->arguments->attributes = bfcp_parse_attribute_SUPPORTED_ATTRIBUTES(message, temp);
                if(!(recvM->arguments->attributes)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case SUPPORTED_PRIMITIVES:
                recvM->arguments->primitives = bfcp_parse_attribute_SUPPORTED_PRIMITIVES(message, temp);
                if(!(recvM->arguments->primitives))
		{	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case USER_DISPLAY_NAME:
                return -1;	/* We can't have this Attribute directly in a primitive */
            case USER_URI:
                return -1;	/* We can't have this Attribute directly in a primitive */
            case BENEFICIARY_INFORMATION:
                recvM->arguments->beneficiary = bfcp_parse_attribute_BENEFICIARY_INFORMATION(message, temp);
                if(!(recvM->arguments->beneficiary)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case FLOOR_REQUEST_INFORMATION:
                if(!tempInfo) {	/* Create a list, it's the first F.R.Info we add */
                    recvM->arguments->frqInfo = bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION(message, temp);
                    if(!(recvM->arguments->frqInfo)) {	/* An error occurred in parsing this attribute */
                        recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                        if(!(recvM->errors))
                            return -1;	/* An error occurred while recording the error, return with failure */
                    }
                    tempInfo = previousInfo = recvM->arguments->frqInfo;
                    break;
                } else {
                    tempInfo = bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION(message, temp);
                    if(!tempInfo) {	/* An error occurred in parsing this attribute */
                        recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                        if(!(recvM->errors))
                            return -1;	/* An error occurred while recording the error, return with failure */
                    }
                    tempInfo->next = NULL;
                    previousInfo->next = tempInfo;
                    previousInfo = tempInfo;
                    break;
                }
                break;
            case REQUESTED_BY_INFORMATION:
                return -1;	/* We can't have this Attribute directly in a primitive */
            case FLOOR_REQUEST_STATUS:
                return -1;	/* We can't have this Attribute directly in a primitive */
            case OVERALL_REQUEST_STATUS:
                return -1;	/* We can't have this Attribute directly in a primitive */
            case NONCE:
                recvM->arguments->nonce = bfcp_parse_attribute_NONCE(message, temp);
                if(!recvM->arguments->nonce) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            case DIGEST:
                recvM->arguments->digest = bfcp_parse_attribute_DIGEST(message, temp);
                if(!(recvM->arguments->digest)) {	/* An error occurred in parsing this attribute */
                    recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_PARSING_ERROR);
                    if(!(recvM->errors))
                        return -1;	/* An error occurred while recording the error, return with failure */
                }
                break;
            default:	/* An unrecognized attribute, remember it */
                recvM->errors = bfcp_received_message_add_error(recvM->errors, temp->type, BFCP_UNKNOWN_ATTRIBUTE);
                if(!(recvM->errors))
                    return -1;	/* An error occurred while recording the error, return with failure */
                temp->valid = 0;	/* We mark the attribute as not valid */
                break;
                }
            }
            temp = temp->next;
        }
        return 0;
    }
}

/* In parsing the attributes, we return 0 (or NULL) if something is WRONG, and return the value if all is ok */
/* This is necessary since many arguments are unsigned, so cannot return -1 to notify that an error happened */
/* In parsing the priority, an error is not 0, but a return value more than 4 (since priority is [0, 4]) */
int bfcp_parse_attribute_BENEFICIARY_ID(bfcp_message *message, bfcp_received_attribute *recvA)
{
    if(recvA->length != 4)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(ERR,"< parse attribute BENEFICIARY_ID length [%d] is incorrect. Should be 4", recvA->length );
        return 0;
    }
    else 
    {
        UINT16  ch16;	/* 16 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        BFCP_msgLog(INF,"< BENEFICIARY_ID [%d] ", ch16);
        return ch16;
    }
}

int bfcp_parse_attribute_FLOOR_ID(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if(recvA->length != 4)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< Wrong FLOOR_ID length [%d]. Should be 4 ", recvA->length );
        return 0;
    }
    else {
        UINT16  ch16;	/* 16 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        BFCP_msgLog(INF,"< FLOOR_ID = [%d] ", ch16 );
        return ch16;
    }
}

int bfcp_parse_attribute_FLOOR_REQUEST_ID(bfcp_message *message, bfcp_received_attribute *recvA)
{
    if(recvA->length != 4)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(ERR,"< parse attribute FLOOR_REQUEST_ID length [%d] is not correct. Should be 4", recvA->length );
        return 0;
    }
    else {
        UINT16  ch16;	/* 16 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        BFCP_msgLog(INF,"< FLOOR_REQUEST_ID [%d] ", ch16 );
        return ch16;
    }
}

e_bfcp_priority bfcp_parse_attribute_PRIORITY(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if(recvA->length != 4)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute PRIORITY length [%d] incorrect. Should be 4", recvA->length );
        return BFCP_LOWEST_PRIORITY;
    }
    else {
        UINT16  ch16;	/* 16 bits */
        e_bfcp_priority prio = BFCP_LOWEST_PRIORITY ;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        if((ch16 & (0x1FFF)) != 0)	/* The Reserved bits are not 0 */
            return prio;		/* Return with a failure */
        prio = (e_bfcp_priority)((ch16 & (0xE000)) >> 13) ;
        if ( prio > BFCP_HIGHEST_PRIORITY )
            return BFCP_LOWEST_PRIORITY;	
        BFCP_msgLog(INF,"< PRIORITY [%s] (%d)", getBfcpPriority(prio), prio);
        return prio ;
    }
}

bfcp_request_status *bfcp_parse_attribute_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA)
{
    if(recvA->length != 4)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute REQUEST_STATUS length [%d] is not correct. Should be 4", recvA->length );
        return NULL;
    }
    else
    {
        bfcp_request_status *rs;
        UINT16  ch16;	/* 16 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        rs = bfcp_new_request_status(
            ((ch16 & (0xFF00)) >> 8), 	/* Request Status */
            (ch16 & (0x00FF)));		/* Queue Position */
        if(!rs)		/* An error occurred when creating the new Request Status */
            return NULL;	/* Return with a failure */
        BFCP_msgLog(INF,"< REQUEST_STATUS request Status [%s] Queue Position [%d]", 
            getBfcpStatus(rs->rs) , rs->qp );
        return rs;
    }
}

bfcp_error *bfcp_parse_attribute_ERROR_CODE(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if (recvA->length < 3)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute ERROR_CODE length [%d] is incorrect. Should be at lease 3.", recvA->length );
        return NULL;
    }
    else {
        bfcp_error *error = bfcp_new_error(BFCP_INVALID_ERROR_CODES, NULL);
        bfcp_unknown_m_error_details *previous, *next;
	
        if(!error)	/* An error occurred when creating a new Error Code */
            return NULL;	/* Return with a failure */
        else {
            char ch = 0;	/* 8 bits */
            int i = 0 ;
            int number = 0;	/* The number of specific details we might find */
            unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
            ch = buffer[0];
            error->code = (e_bfcp_error_codes)ch;	/* We get the Error Code*/
            BFCP_msgLog(INF,"< ERROR_CODE [%s] (%d)",getBfcpErrorType(error->code), error->code);
            switch(error->code) 
	    {
		case BFCP_UNKNOWN_MANDATORY_ATTRIBUTE:
		    /* For now, the only error that has more details is error 4 */
		    number = recvA->length-3;	/* Each error detail takes 1 byte */
		    if (number == 0)
		    {
			/* There has to be AT LEAST one error detail, for error 4*/
			
			BFCP_msgLog(ERR, "Missing error code detailed information");
			return NULL;
		    }
		    
		    previous = NULL;
		    error->details = NULL;
		    for (i= 0; i < number; i++)
		    {
			next = (bfcp_unknown_m_error_details *) calloc(1, sizeof(bfcp_unknown_m_error_details));
			if (! next)
			{
			    BFCP_msgLog(INF,"< parse attribute ERROR_CODE details. Failed to allocate memory");
			    return error;
			}
			
			ch = buffer[i];			
			next->unknown_type = ((ch & (0xFE)) >> 1);	/* The Unknown Attribute, 7 bits */
			next->reserved = (ch & (0x01));			/* The Reserved bit */
			next->next = NULL;

			if (error->details == NULL) error->details = next;
			if (previous) previous->next = next;
			previous = next;
		    }
		    break;

                default:	/* All the others have none, so we can ignore it */
		    break;
            }
            return error;
        }
    }
}

char *bfcp_parse_attribute_ERROR_INFO(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute ERROR_INFO length[%d] ", recvA->length );
    if(recvA->length<2)	/* The length of this attribute is wrong */
        return NULL;
    else {
        char ch = '\0';
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        char *eInfo = (char*) calloc(recvA->length-1, sizeof(char));	/* Lenght is TLV Header too */
        memcpy(eInfo, buffer, recvA->length-2);
        memcpy(eInfo+(recvA->length-2), &ch, 1);	/* We add a terminator char to the string */
        BFCP_msgLog(INF,"< parse attribute ERROR_INFO [%s] ", eInfo?eInfo:"NULL" );
        return eInfo;
    }
}

char *bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute PARTICIPANT_PROVIDED_INFO length[%d] ", recvA->length );
    if(recvA->length<2)	/* The length of this attribute is wrong */
        return NULL;
    else {
        char ch = '\0';
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        char *pInfo = (char*) calloc(recvA->length-1, sizeof(char));	/* Lenght is TLV Header too */
        memcpy(pInfo, buffer, recvA->length-2);
        memcpy(pInfo+(recvA->length-2), &ch, 1);	/* We add a terminator char to the string */
        BFCP_msgLog(INF,"< parse attribute PARTICIPANT_PROVIDED_INFO [%s] ", pInfo?pInfo:"NULL" );
        return pInfo;
    }
}

char *bfcp_parse_attribute_STATUS_INFO(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if(recvA->length<2)
    {
	/* The length of this attribute is wrong */
	BFCP_msgLog(ERR,"< parse attribute STATUS_INFO length [%d] is incorrect, should be at least 2", recvA->length );
        return NULL;
    }
    else {
        char ch = '\0';
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        char *sInfo =  (char*) calloc(recvA->length-1, sizeof(char));	/* Lenght is TLV Header too */
        memcpy(sInfo, buffer, recvA->length-2);
        memcpy(sInfo+(recvA->length-2), &ch, 1);	/* We add a terminator char to the string */
        BFCP_msgLog(INF,"< STATUS_INFO [%s] ", sInfo?sInfo:"NULL" );
        return sInfo;
    }
}

bfcp_supported_list *bfcp_parse_attribute_SUPPORTED_ATTRIBUTES(bfcp_message *message, bfcp_received_attribute *recvA)
{
    if (recvA->length < 3)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(ERR,"< parse attribute SUPPORTED_ATTRIBUTES length [%d] incorrect should be at lease 3", recvA->length );
        return NULL;
    }
    else
    {
        int i;
        bfcp_supported_list *first, *previous, *next = NULL ;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        int number = (recvA->length-2);	/* Each supported attribute takes 2 bytes */
        BFCP_msgLog(INF,"< SUPPORTED_ATTRIBUTES number of attributes %d",number);
        if (!number) return NULL;	/* No supported attributes? */
    
	first = NULL;
	previous = NULL;
        for (i=0; i< number; i++)
	{
	    next = (bfcp_supported_list *) calloc(1, sizeof(bfcp_supported_list));
	    if (next == NULL)
	    {
		/* Memory leak here. Previously parsed elemnts should be freed */
		BFCP_msgLog(ERR, "Failed to allocate memory to parse SUPPORTED_ATTRIBUTES at index %d", i);
		return NULL;
	    }
	    next->element = buffer[0];
	    BFCP_msgLog(INF,"< SUPPORTED_ATTRIBUTE: [%s] (%d) ", getBfcpAttribute((e_bfcp_attibutes)next->element), next->element);
	    if (!first) first = next;
	    if (previous) previous->next = next;
	}
	next->next = NULL;
        return first;
    }
}

bfcp_supported_list *bfcp_parse_attribute_SUPPORTED_PRIMITIVES(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if (recvA->length<3)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute SUPPORTED_PRIMITIVES invalid length [%d]. Should be more than 3", recvA->length );
        return NULL;
    }
    else {
        int i;
        bfcp_supported_list *first = NULL, *previous = NULL, *next = NULL ;
        int number = 0 ;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        number = (recvA->length-2);	/* Each supported primitive takes 2 bytes */
        BFCP_msgLog(INF,"< parse attribute SUPPORTED_PRIMITIVES number of primitives %d",number);
 	
	/* Let's parse each other supported primitive we find */
        for(i = 0; i<number; i++) 
	{
                next = (bfcp_supported_list *) calloc(1, sizeof(bfcp_supported_list));
                if(!next)	/* An error occurred in creating a new Supported Attributes list */
                    return NULL;
                next->element = buffer[i];
		if ( previous ) previous->next = next;
		if ( first == NULL ) first = next;
		previous = next;
                BFCP_msgLog(INF,"< parse attribute SUPPORTED_PRIMITIVES [%d / %s] ", next->element, getBfcpDescPrimitive((e_bfcp_primitives)next->element) );
        }
        return first;
    }
}

char *bfcp_parse_attribute_USER_DISPLAY_NAME(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute USER_DISPLAY_NAME length[%d] ", recvA->length );
    if(recvA->length<3)	/* The length of this attribute is wrong */
        return NULL;
    else {
        char ch = '\0';
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        char *display =(char*)calloc(recvA->length-1, sizeof(char));	/* Lenght is TLV Header too */
        memcpy(display, buffer, recvA->length-2);
        memcpy(display+(recvA->length-2), &ch, 1);	/* We add a terminator char to the string */
        BFCP_msgLog(INF,"< parse attribute USER_DISPLAY_NAME [%s] ", display?display:"NULL" );
        return display;
    }
}

char *bfcp_parse_attribute_USER_URI(bfcp_message *message, bfcp_received_attribute *recvA)
{

    if(recvA->length < 3)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute USER_URI length [%d] should not be empty if present", recvA->length );
        return NULL;
    }
    else {
        char ch = '\0';
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        char *uri = (char*)calloc(recvA->length-1, sizeof(char));	/* Lenght is TLV Header too */
        memcpy(uri, buffer, recvA->length-2);
        memcpy(uri+(recvA->length-2), &ch, 1);	/* We add a terminator char to the string */
        BFCP_msgLog(INF,"< USER_URI [%s] ", uri?uri:"NULL" );
        return uri;
    }
}

bfcp_user_information *bfcp_parse_attribute_BENEFICIARY_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute BENEFICIARY_INFORMATION length[%d] ", recvA->length );
    if(recvA->length<3)	/* The length of this attribute is wrong */
        return NULL;
    else {
        int position;
        bfcp_received_attribute *attribute = NULL;
        bfcp_user_information *beneficiary = NULL;
        UINT16 ch16, bID = 0 ;	/* 16 bits */
        char *display = NULL, *uri = NULL;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        bID = ntohs(ch16);	/* The first value, BeneficiaryID */
                    BFCP_msgLog(INF,"< BENEFICIARY_INFORMATION Beneficiary ID[%d] ", bID ); 
        /* Display and URI are not compulsory, they might not be in the message, let's check it */
        message->position = recvA->position+4;
        while(recvA->length>((message->position)-(recvA->position))) {
            position = message->position;	/* Remember where message was before attribute parsing */
            attribute = bfcp_parse_attribute(message);
            if(!attribute)	/* An error occurred while parsing this attribute */
                return NULL;
            switch(attribute->type) {
            case USER_DISPLAY_NAME:
                display = bfcp_parse_attribute_USER_DISPLAY_NAME(message, attribute);
                if(!display)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case USER_URI:
                uri = bfcp_parse_attribute_USER_URI(message, attribute);
                if(!uri)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            default:	/* There's an attribute that shouldn't be here... */
                break;
            }
            message->position = position+attribute->length;
            if(((attribute->length)%4) != 0)
                message->position = message->position+4-((attribute->length)%4);
            bfcp_free_received_attribute(attribute);
        }
        beneficiary = bfcp_new_user_information(bID, display, uri);
        if(!beneficiary)	/* An error occurred in creating a new Beneficiary User Information */
            return NULL;
        if(display)
            free(display);
        if(uri)
            free(uri);
        message->position = recvA->position+recvA->length;
        if(((recvA->length)%4) != 0)
            message->position = message->position+4-((recvA->length)%4);
        return beneficiary;
    }
}

bfcp_floor_request_information *bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA)
{
    if(recvA->length<3)	/* The length of this attribute is wrong */
    {
	 BFCP_msgLog(INF,"< parse attribute FLOOR_REQUEST_INFORMATION length [%d] is incorred. Should be at least 3.", recvA->length );
        return NULL;
    }
    else {
        int position;
        UINT16  frqID ;
	e_bfcp_priority priority = BFCP_LOWEST_PRIORITY;
        bfcp_floor_request_information *frqInfo = NULL;
        bfcp_received_attribute *attribute = NULL;
        UINT16  ch16 = 0 ; /* 16 bits */
        bfcp_overall_request_status *oRS = NULL;
        bfcp_floor_request_status *fRS = NULL, *tempRS = NULL;
        bfcp_user_information *beneficiary = NULL, *requested_by = NULL;
        char *pInfo = NULL;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        frqID = ntohs(ch16);	/* The first value, FloorRequestID */
        /* Some attributes are not compulsory, they might not be in the message, let's check it */
        /* FLOOR-REQUEST-STATUS has 1* multiplicity, there has to be AT LEAST one, */
        /* So remember to check its presence outside, in server/client */
        BFCP_msgLog(INF,"< FLOOR_REQUEST_INFORMATION Floor request ID[%d] ", frqID );
        message->position = recvA->position+4;
        while(recvA->length>((message->position)-(recvA->position))) {
            position = message->position;	/* Remember where message was before attribute parsing */
            attribute = bfcp_parse_attribute(message);
            if(!attribute)	/* An error occurred while parsing this attribute */
                return NULL;
            BFCP_msgLog(INF,"< parse attribute FLOOR_REQUEST_INFORMATION Floor request ID[%d] information[%d / %s ]", frqID ,
                attribute->type,getBfcpAttribute(attribute->type));
            switch(attribute->type) {
            case OVERALL_REQUEST_STATUS:
                oRS = bfcp_parse_attribute_OVERALL_REQUEST_STATUS(message, attribute);
                if(!oRS)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case FLOOR_REQUEST_STATUS:
                if(!fRS) {	/* Create a list, it's the first FLOOR-REQUEST-STATUS we add */
                    fRS = bfcp_parse_attribute_FLOOR_REQUEST_STATUS(message, attribute);
                    if(!fRS)	/* An error occurred while parsing this attribute */
                        return NULL;
                    break;
                } else {	/* We already have a list, add the new FLOOR-REQUEST-STATUS to it */
                    tempRS = bfcp_parse_attribute_FLOOR_REQUEST_STATUS(message, attribute);
                    if(!tempRS)	/* An error occurred while parsing this attribute */
                        return NULL;
                    if(bfcp_add_floor_request_status_list(fRS, tempRS, NULL) == -1)
                        return NULL;
                    break;
                }
            case BENEFICIARY_INFORMATION:
                beneficiary = bfcp_parse_attribute_BENEFICIARY_INFORMATION(message, attribute);
                if(!beneficiary)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case REQUESTED_BY_INFORMATION:
                requested_by = bfcp_parse_attribute_REQUESTED_BY_INFORMATION(message, attribute);
                if(!requested_by)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case PRIORITY:
                priority = bfcp_parse_attribute_PRIORITY(message, attribute);
                if(priority>4)		/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case PARTICIPANT_PROVIDED_INFO:
                pInfo = bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO(message, attribute);
                if(!pInfo)		/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            default:	/* There's an attribute that shouldn't be here... */
                break;
            }
            message->position = position+attribute->length;
            if(((attribute->length)%4) != 0)
                message->position = message->position+4-((attribute->length)%4);
            bfcp_free_received_attribute(attribute);
        }
        frqInfo = bfcp_new_floor_request_information(frqID, oRS, fRS, beneficiary, requested_by, priority, pInfo);
        if(!frqInfo)	/* An error occurred in creating a new Floor Request Information */
            return NULL;
        if(pInfo)
            free(pInfo);
        message->position = recvA->position+recvA->length;
        if(((recvA->length)%4) != 0)
            message->position = message->position+4-((recvA->length)%4);
        return frqInfo;
    }
}

bfcp_user_information *bfcp_parse_attribute_REQUESTED_BY_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute REQUESTED_BY_INFORMATION length[%d] ", recvA->length );
    if(recvA->length<3)	/* The length of this attribute is wrong */
        return NULL;
    else {
        int position = 0;
        bfcp_received_attribute *attribute = NULL;
        bfcp_user_information *requested_by = NULL;
        UINT16  ch16, rID;	/* 16 bits */
        char *display = NULL, *uri = NULL;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        rID = ntohs(ch16);	/* The first value, ReceivedByID */
        BFCP_msgLog(INF,"< parse attribute REQUESTED_BY_INFORMATION Requested by ID[%d] ", rID );
        /* Display and URI are not compulsory, they might not be in the message, let's check it */
        message->position = recvA->position+4;
        while(recvA->length>((message->position)-(recvA->position))) {
            position = message->position;	/* Remember where message was before attribute parsing */
            attribute = bfcp_parse_attribute(message);
            if(!attribute)	/* An error occurred while parsing this attribute */
                return NULL;
            BFCP_msgLog(INF,"< parse attribute REQUESTED_BY_INFORMATION Requested by ID[%d] type[%d / %s]", rID ,
                attribute->type,getBfcpAttribute(attribute->type)); 

            switch(attribute->type) {
            case USER_DISPLAY_NAME:
                display = bfcp_parse_attribute_USER_DISPLAY_NAME(message, attribute);
                if(!display)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case USER_URI:
                uri = bfcp_parse_attribute_USER_URI(message, attribute);
                if(!uri)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            default:	/* There's an attribute that shouldn't be here... */
                break;
            }
            message->position = position+attribute->length;
            if(((attribute->length)%4) != 0)
                message->position = message->position+4-((attribute->length)%4);
            bfcp_free_received_attribute(attribute);
        }
        requested_by = bfcp_new_user_information(rID, display, uri);
        if(!requested_by)	/* An error occurred in creating a new Beneficiary User Information */
            return NULL;
        if(display)
            free(display);
        if(uri)
            free(uri);
        message->position = recvA->position+recvA->length;
        if(((recvA->length)%4) != 0)
            message->position = message->position+4-((recvA->length)%4);
        return requested_by;
    }
}

bfcp_floor_request_status *bfcp_parse_attribute_FLOOR_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA)
{
    
    if(recvA->length<3)	/* The length of this attribute is wrong */
    {
	BFCP_msgLog(INF,"< parse attribute FLOOR_REQUEST_STATUS length [%d] is incorrect. Should be at lease 3", recvA->length );
        return NULL;
    }
    else {
        int position;
        UINT16  fID;
        bfcp_received_attribute *attribute = NULL;
        bfcp_floor_request_status *fRS = NULL;
        UINT16  ch16;	/* 16 bits */
        bfcp_request_status *rs = NULL;
        char *sInfo = NULL;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        fID = ntohs(ch16);	/* The first value, FloorID */
        BFCP_msgLog(INF,"< FLOOR_REQUEST_STATUS floorId [%d] ", fID );
        /* Some attributes are not compulsory, they might not be in the message, let's check it */
        message->position = recvA->position+4;
        while(recvA->length>((message->position)-(recvA->position))) {
            position = message->position;	/* Remember where message was before attribute parsing */
            attribute = bfcp_parse_attribute(message);
            if(!attribute)	/* An error occurred while parsing this attribute */
                return NULL;

            /* BFCP_msgLog(INF,"< parse attribute FLOOR_REQUEST_STATUS Requested by floorId[%d] type[%d / %s]", fID ,
			attribute->type,getBfcpAttribute(attribute->type));  */

            switch(attribute->type)
	    {
            case REQUEST_STATUS:
                rs = bfcp_parse_attribute_REQUEST_STATUS(message, attribute);
                if(!rs)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case STATUS_INFO:
                sInfo = bfcp_parse_attribute_STATUS_INFO(message, attribute);
                if(!sInfo)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            default:	/* There's an attribute that shouldn't be here... */
	        BFCP_msgLog(INF,"< FLOOR_REQUEST_STATUS - unexpected attribute type [%d] [%s]", fID ,
			    attribute->type,getBfcpAttribute(attribute->type));
                break;
            }
            message->position = position+attribute->length;
            if(((attribute->length)%4) != 0)
                message->position = message->position+4-((attribute->length)%4);
            bfcp_free_received_attribute(attribute);
        }
        fRS = bfcp_new_floor_request_status(fID, rs->rs, rs->qp, sInfo);
        if(!fRS)	/* An error occurred in creating a new Floor Request Information */
            return NULL;
        if(rs)
            bfcp_free_request_status(rs);
        if(sInfo)
            free(sInfo);
        message->position = recvA->position+recvA->length;
        if(((recvA->length)%4) != 0)
            message->position = message->position+4-((recvA->length)%4);
        return fRS;
    }
}

bfcp_overall_request_status *bfcp_parse_attribute_OVERALL_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute OVERALL_REQUEST_STATUS length[%d] ", recvA->length );
    if(recvA->length<3)	/* The length of this attribute is wrong */
        return NULL;
    else {
        int position;
        UINT16  frqID;
        bfcp_received_attribute *attribute = NULL;
        bfcp_overall_request_status *oRS = NULL;
        UINT16  ch16;	/* 16 bits */
        bfcp_request_status *rs = NULL;
        char *sInfo = NULL;
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        frqID = ntohs(ch16);	/* The first value, FloorID */
        BFCP_msgLog(INF,"< parse attribute OVERALL_REQUEST_STATUS FloorRequestId[%d] ", frqID );
        /* Some attributes are not compulsory, they might not be in the message, let's check it */
        message->position = recvA->position+4;
        while(recvA->length>((message->position)-(recvA->position))) {
            position = message->position;	/* Remember where message was before attribute parsing */
            attribute = bfcp_parse_attribute(message);
            if(!attribute)	/* An error occurred while parsing this attribute */
                return NULL;
            BFCP_msgLog(INF,"< parse attribute OVERALL_REQUEST_STATUS Requested by type[%d / %s]",
                attribute->type,getBfcpAttribute(attribute->type)); 

            switch(attribute->type) {
            case REQUEST_STATUS:
                rs = bfcp_parse_attribute_REQUEST_STATUS(message, attribute);
                if(!rs)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            case STATUS_INFO:
                sInfo = bfcp_parse_attribute_STATUS_INFO(message, attribute);
                if(!sInfo)	/* An error occurred while parsing this attribute */
                    return NULL;
                break;
            default:	/* There's an attribute that shouldn't be here... */
                break;
            }
            message->position = position+attribute->length;
            if(((attribute->length)%4) != 0)
                message->position = message->position+4-((attribute->length)%4);
            bfcp_free_received_attribute(attribute);
        }
        oRS = bfcp_new_overall_request_status(frqID, rs->rs, rs->qp, sInfo);
        if(!oRS)	/* An error occurred in creating a new Floor Request Information */
            return NULL;
        if(rs)
            bfcp_free_request_status(rs);
        if(sInfo)
            free(sInfo);
        message->position = recvA->position+recvA->length;
        if(((recvA->length)%4) != 0)
            message->position = message->position+4-((recvA->length)%4);
        return oRS;
    }
}

int bfcp_parse_attribute_NONCE(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute NONCE length[%d] ", recvA->length );
    if(recvA->length != 4)	/* The length of this attribute is wrong */
        return -1;
    else {
        UINT16  ch16;	/* 16 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch16, buffer, 2);
        ch16 = ntohs(ch16);
        BFCP_msgLog(INF,"< parse attribute NONCE [%d] ", ch16 );
        return ch16;
    }
}

bfcp_digest *bfcp_parse_attribute_DIGEST(bfcp_message *message, bfcp_received_attribute *recvA)
{
    BFCP_msgLog(INF,"< parse attribute DIGEST length[%d] ", recvA->length );
    if(recvA->length<4)	/* The length of this attribute is wrong */
        return NULL;
    else {
        char ch;	/* 8 bits */
        unsigned char *buffer = message->buffer+recvA->position+2;	/* Skip the Header */
        memcpy(&ch, buffer, 1);
        {
            bfcp_digest *digest = bfcp_new_digest((UINT16 /* UINT16 */)ch);	/* Algorithm */
            buffer = buffer+1;	/* Skip the Algorithm byte */
            digest->text = (char*)calloc(recvA->length-2, sizeof(char));	/* Lenght is TLV + Algorithm byte too */
            if(!digest)	/* An error occurred in creating a new Digest */
                return NULL;
            memcpy(digest->text, buffer, recvA->length-3);
            ch = '\0';
            memcpy((digest->text)+(recvA->length-3), &ch, 1);	/* We add a terminator char to the string */
            BFCP_msgLog(INF,"< parse attribute DIGEST text[%s] ", digest->text );
            return digest;
        }
    }
}

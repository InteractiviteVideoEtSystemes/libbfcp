/**
 *
 * \brief Definitions of BFCP packet format and methodes for encoding and decoding messages  
 *
 * \author Lorenzo Miniero & Philippe Verney
 *
 * \file bfcp_messages.h
 *
 * \version $Revision: 2652 $
 *
 * \date $Date: 2015-12-03 22:54:12 +0100 (Thu, 03 Dec 2015) $
 *
 * \remarks :
 */

#ifndef _BFCP_MESSAGES_H
#define _BFCP_MESSAGES_H

#ifdef WIN32
#include <basetsd.h>
#else

#ifndef INT8
#define INT8 int8_t
#endif

#ifndef UINT8
#define UINT8 uint8_t
#endif

#ifndef INT16
#define INT16 int16_t
#endif

#ifndef UINT16
#define UINT16 uint16_t
#endif

#ifndef INT32
#define INT32 int32_t
#endif

#ifndef UINT32
#define UINT32 uint32_t
#endif

#ifndef INT64
#define INT64 int64_t
#endif

#ifndef UINT64
#define UINT64 uint64_t
#endif
#endif

#ifndef INF
#define INF __FILE__, __LINE__, 0
#endif

#ifndef WAR
#define WAR __FILE__, __LINE__, 1
#endif

#ifndef ERR
#define ERR __FILE__, __LINE__, 2
#endif

#ifndef WIN32
#include <arpa/inet.h>	/*     For htonl and htons */
#define BFCP_SOCKET int 
#define INVALID_SOCKET -1
//#ifdef _UNICODE
//#define _T(x) L ## x
//#define ft_tcsncpy wcsncpy
//#else
#define ft_tcsncpy strncpy
#define _T(x) x
//#endif
#else  // WIN32
#include <winsock2.h>	/*     For htonl and htons (Win32) */
#define BFCP_SOCKET SOCKET
#endif

#include <stdarg.h>	/*     For functions with variable arguments */
#include <stdlib.h>	/*     For calloc */
#include <string.h>	/*     For memcpy */
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif    


/*! \brief pointeur de fonction de trace */
typedef void (*tLog_callback)(char*     pcFile, int iLine, int iErrLevel, char*     pcFormat, ...);

/*!  
 *      \brief  Affectation d'un pointeur de fonction
 *      \param  trace_function     Fonction attribuer aux system de trace PS app.
 *      \retval void
 */
void BFCP_msg_LogCallback(tLog_callback trace_function);


/*     Debug Methods */
void BFCP_msgLog(char*     pcFile, int iLine, int iErrLevel , char*     pcFormat, ...);
void DumpBfcpBuff(char*     txt , unsigned char*     dp , int sz );


/**     \brief BFCP primitives
 *
 *      \enum  e_bfcp_primitives 
 *      \ref BFCP-COMMON-HEADER
 *
 *       Primitive: This 8-bit field identifies the main purpose of the
 *       message.  The following primitive values are defined:
 *       
 *       +-------+--------------------+------------------+
 *
 *       | Value | Primitive          | Direction        |
 *
 *       +-------+--------------------+------------------+
 *
 *       |   1   | FloorRequest       | P -> S           |
 *
 *       |   2   | FloorRelease       | P -> S           |
 *
 *       |   3   | FloorRequestQuery  | P -> S ; Ch -> S |
 *
 *       |   4   | FloorRequestStatus | P <- S ; Ch <- S |
 *
 *       |   5   | UserQuery          | P -> S ; Ch -> S |
 *
 *       |   6   | UserStatus         | P <- S ; Ch <- S |
 *
 *       |   7   | FloorQuery         | P -> S ; Ch -> S |
 *
 *       |   8   | FloorStatus        | P <- S ; Ch <- S |
 *
 *       |   9   | ChairAction        | Ch -> S          |
 *
 *       |   10  | ChairActionAck     | Ch <- S          |
 *
 *       |   11  | Hello              | P -> S ; Ch -> S |
 *
 *       |   12  | HelloAck           | P <- S ; Ch <- S |
 *
 *       |   13  | Error              | P <- S ; Ch <- S |
 *
 *       +-------+--------------------+------------------+
 *
 *       S:  Floor Control Server
 *
 *       P:  Floor Participant
 *
 *       Ch: Floor Chair
 *
 */
			     
typedef enum{
    e_primitive_InvalidPrimitive = 0,
    e_primitive_FloorRequest=1,
    e_primitive_FloorRelease=2,
    e_primitive_FloorRequestQuery=3,
    e_primitive_FloorRequestStatus=4,
    e_primitive_UserQuery=5,
    e_primitive_UserStatus=6,
    e_primitive_FloorQuery=7,
    e_primitive_FloorStatus=8,
    e_primitive_ChairAction=9,
    e_primitive_ChairActionAck=10,
    e_primitive_Hello=11,
    e_primitive_HelloAck=12,
    e_primitive_Error=13,
    e_primitive_FloorRequestStatusAck=14,
    e_primitive_ErrorAck=15,
    e_primitive_FloorStatusAck=16,
    e_primitive_Goodbye=17,
    e_primitive_GoodbyeAck=18,
    e_primitive_Cisco90=90,
    e_primitive_Cisco91=91,
    e_primitive_Cisco92=92,
    e_primitive_Cisco93=93,
    e_primitive_Cisco94=94,
    e_primitive_Cisco95=95
} e_bfcp_primitives;

/**     \brief BFCP attributes
 *      \see BFCP-COMMON-HEADER
 *      \enum  e_bfcp_attibutes 
 *
 *       
 *       +------+---------------------------+---------------+
 *
 *       | Type | Attribute                 | Format        |
 *
 *       +------+---------------------------+---------------+
 *
 *       |   1  | BENEFICIARY-ID            | Unsigned16    |
 *
 *       |   2  | FLOOR-ID                  | Unsigned16    |
 *
 *       |   3  | FLOOR-REQUEST-ID          | Unsigned16    |
 *
 *       |   4  | PRIORITY                  | OctetString16 |
 *
 *       |   5  | REQUEST-STATUS            | OctetString16 |
 *
 *       |   6  | ERROR-CODE                | OctetString   |
 *
 *       |   7  | ERROR-INFO                | OctetString   |
 *
 *       |   8  | PARTICIPANT-PROVIDED-INFO | OctetString   |
 *
 *       |   9  | STATUS-INFO               | OctetString   |
 *
 *       |  10  | SUPPORTED-ATTRIBUTES      | OctetString   |
 *
 *       |  11  | SUPPORTED-PRIMITIVES      | OctetString   |
 *
 *       |  12  | USER-DISPLAY-NAME         | OctetString   |
 *
 *       |  13  | USER-URI                  | OctetString   |
 *
 *       |  14  | BENEFICIARY-INFORMATION   | Grouped       |
 *
 *       |  15  | FLOOR-REQUEST-INFORMATION | Grouped       |
 *
 *       |  16  | REQUESTED-BY-INFORMATION  | Grouped       |
 *
 *       |  17  | FLOOR-REQUEST-STATUS      | Grouped       |
 *
 *       |  18  | OVERALL-REQUEST-STATUS    | Grouped       |
 *
 *       +------+---------------------------+---------------+
 *       
  */
typedef enum {
    INVALID_ATTRIBUTE = 0 ,
    BENEFICIARY_ID=1,
    FLOOR_ID=2,
    FLOOR_REQUEST_ID=3,
    PRIORITY=4,
    REQUEST_STATUS=5,
    ERROR_CODE=6,
    ERROR_INFO=7,
    PARTICIPANT_PROVIDED_INFO=8,
    STATUS_INFO=9,
    SUPPORTED_ATTRIBUTES=10,
    SUPPORTED_PRIMITIVES=11,
    USER_DISPLAY_NAME=12,
    USER_URI=13,
    BENEFICIARY_INFORMATION=14,
    FLOOR_REQUEST_INFORMATION=15,
    REQUESTED_BY_INFORMATION=16,
    FLOOR_REQUEST_STATUS=17,
    OVERALL_REQUEST_STATUS=18,
    NONCE=19,
    DIGEST=20
}e_bfcp_attibutes ;

/**     \brief REQUEST-STATUS format
 *
 *       Request Status: This 8-bit field contains the status of the request,
 *       as described in the following table.
 *
 *                               +-------+-----------+
 *                               | Value | Status    |
 *                               +-------+-----------+
 *                               |   1   | Pending   |
 *                               |   2   | Accepted  |
 *                               |   3   | Granted   |
 *                               |   4   | Denied    |
 *                               |   5   | Cancelled |
 *                               |   6   | Released  |
 *                               |   7   | Revoked   |
 *                               +-------+-----------+
 */
/** \enum e_bfcp_status */
typedef enum {
    BFCP_INVALID_STATUS=0,
    BFCP_PENDING=1,
    BFCP_ACCEPTED=2,
    BFCP_GRANTED=3,
    BFCP_DENIED=4,
    BFCP_CANCELLED=5,
    BFCP_RELEASED=6,
    BFCP_REVOKED=7
}
e_bfcp_status ; 

/**     \brief PRIORITY
 *
 *                               +-------+----------+
 *                               | Value | Priority |
 *                               +-------+----------+
 *                               |   0   | Lowest   |
 *                               |   1   | Low      |
 *                               |   2   | Normal   |
 *                               |   3   | High     |
 *                               |   4   | Highest  |
 *                               +-------+----------+
 *
 *     
 */
typedef enum {
    BFCP_LOWEST_PRIORITY=0,
    BFCP_LOW_PRIORITY=1,
    BFCP_NORMAL_PRIORITY=2,
    BFCP_HIGH_PRIORITY=3,
    BFCP_HIGHEST_PRIORITY=4
}e_bfcp_priority ;


/*     Error Codes */
typedef enum {
    BFCP_INVALID_ERROR_CODES=0,
    BFCP_CONFERENCE_DOES_NOT_EXIST=1,
    BFCP_USER_DOES_NOT_EXIST=2,
    BFCP_UNKNOWN_PRIMITIVE=3,
    BFCP_UNKNOWN_MANDATORY_ATTRIBUTE=4,
    BFCP_UNAUTHORIZED_OPERATION=5,
    BFCP_INVALID_FLOORID=6,
    BFCP_FLOORREQUEST_DOES_NOT_EXIST=7,
    BFCP_MAX_FLOORREQUESTS_REACHED=8,
    BFCP_USE_TLS=9,
    BFCP_DIGEST_ATTRIBUTE_REQUIRED=10,
    BFCP_INVALID_NONCE=11,
    BFCP_AUTHENTICATION_FAILED=12,
    BFCP_UNABLE_TO_PARSE=10,
    BFCP_USE_DTLS=11,
    BFCP_UNSUPPORTED_VERSION=12,
    BFCP_INCORRECT_MESSAGE_LENGTH=13,
    BFCP_GENERIC_ERROR=14
} e_bfcp_error_codes ;

/* Parsing-specific Error Codes */
typedef enum {
    BFCP_INVALID_SPECIFIC_ERROR_CODES=0,
    BFCP_WRONG_VERSION=1,
    BFCP_RESERVED_NOT_ZERO=2,
    //BFCP_UNKNOWN_PRIMITIVE=3,
    BFCP_UNKNOWN_ATTRIBUTE=4,
    BFCP_WRONG_LENGTH=5,
    BFCP_PARSING_ERROR=6
}e_bfcp_specific_error_codes;


/* Maximum allow size for BFCP messages is 64Kbytes, since the Payload Length in the header is 16 bit */
#define BFCP_MAX_ALLOWED_SIZE	65535
#define BFCP_MAX_RG             256 

#ifdef WRP_STRING_SIZE
#define BFCP_STRING_SIZE  WRP_STRING_SIZE
#else 
#define BFCP_STRING_SIZE  256
#endif

/**
 *     \section BFCP-MESSAGES 
 *     
 *     BFCP packets consist of a 12-octet common header followed by
 *     attributes.  All the protocol values MUST be sent in network byte
 *     order.
 *
 *     \subsection BFCP-COMMON-HEADER BFCP common header Format
 *
 *      The following is the format of the common header.
 *
 *       0                   1                   2                   3
 *
 *       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *       | Ver |Reserved |  Primitive    |        Payload Length         |
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *       |                         Conference ID                         |
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *       |         Transaction ID        |            User ID            |
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *       \li Ver: The 3-bit version field MUST be set to 1 to indicate this
 *       version of BFCP.
 *       
 *       \li Reserved: At this point, the 5 bits in the reserved field SHOULD be
 *       set to zero by the sender of the message and MUST be ignored by the
 *       receiver.
 *       
 *       \subsection Primitive: This 8-bit field identifies the main purpose of the
 *       message.  The following primitive values are defined
 *
 *       \li Payload Length: This 16-bit field contains the length of the message
 *       in 4-octet units, excluding the common header.
 *       
 *       \li  Conference ID: This 32-bit field identifies the conference the
 *       message belongs to.
 *       
 *       \li Transaction ID: This field contains a 16-bit value that allows users
 *       to match a given message with its response.  The value of the
 *       Transaction ID in server-initiated transactions is 0 (see Section 8).
 *       
 *       \li User ID: This field contains a 16-bit value that uniquely identifies
 *       a participant within a conference.
 *       
 *       The identity used by a participant in BFCP, which is carried in
 *       the User ID field, is generally mapped to the identity used by the
 *       same participant in the session establishment protocol (e.g., in
 *       SIP).  The way this mapping is performed is outside the scope of
 *       this specification.
 *     
 *      \section BFCP-ATTRIBUTES attributes Format
 *
 *       BFCP attributes are encoded in TLV (Type-Length-Value) format.
 *       Attributes are 32-bit aligned.
 *       
 *       0                   1                   2                   3
 *
 *       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *        |    Type     |M|    Length     |                               |
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
 *
 *       |                                                               |
 *
 *       /                       Attribute Contents                      /
 *
 *       /                                                               /
 *
 *       |                                                               |
 *
 *       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *       
 *       \li Type: This 7-bit field contains the type of the attribute.  Each
 *       attribute, identified by its type, has a particular format.  The
 *       attribute formats defined are:
 *       
 *       Unsigned16: The contents of the attribute consist of a 16-bit
 *       unsigned integer.
 *       
 *       OctetString16: The contents of the attribute consist of 16 bits of
 *       arbitrary data.
 *       
 *       OctetString: The contents of the attribute consist of arbitrary
 *       data of variable length.
 *       
 *       Grouped: The contents of the attribute consist of a sequence of
 *       attributes.
 *       
 *       Note that extension attributes defined in the future may define
 *       new attribute formats.
 *       M: The 'M' bit, known as the Mandatory bit, indicates whether support
 *       of the attribute is required.  If an unrecognized attribute with the
 *       'M' bit set is received, the message is rejected.  The 'M' bit is
 *       significant for extension attributes defined in other documents only.
 *       All attributes specified in this document MUST be understood by the
 *       receiver so that the setting of the 'M' bit is irrelevant for these.
 *       In all other cases, the unrecognised attribute is ignored but the
 *       message is processed.
 *       
 *       \li Length: This 8-bit field contains the length of the attribute in
 *       octets, excluding any padding defined for specific attributes.  The
 *       length of attributes that are not grouped includes the Type, 'M' bit,
 *       and Length fields.  The Length in grouped attributes is the length of
 *       the grouped attribute itself (including Type, 'M' bit, and Length
 *       fields) plus the total length (including padding) of all the included
 *       attributes.
 *       
 *       \li Attribute Contents: The contents of the different attributes are
 *       defined in the following sections.
 *     
 *       \section BENEFICIARY-ID
 *       
 *          The following is the format of the BENEFICIARY-ID attribute.
 *       
 *             0                   1                   2                   3
 *
 *             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *            |0 0 0 0 0 0 1|M|0 0 0 0 0 1 0 0|        Beneficiary ID         |
 *
 *            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *        
 *       \li Beneficiary ID: This field contains a 16-bit value that uniquely
 *       identifies a user within a conference.
 *       
 *             Note that although the formats of the Beneficiary ID and of the
 *             User ID field in the common header are similar, their semantics
 *       are different.  The Beneficiary ID is used in third-party floor
 *       requests and to request information about a particular
 *       participant.
 *       
 *     
 *       \section FLOOR-ID
 *       
 *       The following is the format of the FLOOR-ID attribute.
 *
 *          0                   1                   2                   3
 *
 *          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *         |0 0 0 0 0 1 0|M|0 0 0 0 0 1 0 0|           Floor ID            |
 *
 *         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *      \li Floor ID: This field contains a 16-bit value that uniquely identifies
 *      a floor within a conference.
 *
 *       \section   REQUEST-STATUS
 *
 *       The following is the format of the REQUEST-STATUS attribute.
 *
 *          0                   1                   2                   3
 *
 *          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *         |0 0 0 0 1 0 1|M|0 0 0 0 0 1 0 0|Request Status |Queue Position |
 *
 *         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *
 *
 *       \li Queue Position: This 8-bit field contains, when applicable, the
 *       position of the floor request in the floor request queue at the
 *       server.  If the Request Status value is different from Accepted, if
 *       the floor control server does not implement a floor request queue, or
 *       if the floor control server does not want to provide the client with
 *       this information, all the bits of this field SHOULD be set to zero.
 *
 *       \li A floor request is in Pending state if the floor control server needs
 *       to contact a floor chair in order to accept the floor request, but
 *       has not done it yet.  Once the floor control chair accepts the floor
 *       request, the floor request is moved to the Accepted state.
 *
 *
 *       \section   FLOOR-REQUEST-ID
 *
 *   The following is the format of the FLOOR-REQUEST-ID attribute.
 *
 *      0                   1                   2                   3
 *
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *    |0 0 0 0 0 1 1|M|0 0 0 0 0 1 0 0|       Floor Request ID        |
 *
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *   \li Floor Request ID: This field contains a 16-bit value that identifies
 *   a floor request at the floor control server.
 *
 *       \section   PRIORITY
 *
 *       The following is the format of the PRIORITY attribute.
 *
 *          0                   1                   2                   3
 *
 *          0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 *         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *         |0 0 0 0 1 0 0|M|0 0 0 0 0 1 0 0|Prio |         Reserved        |
 *
 *         +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *       \li Prio: This field contains a 3-bit priority value, as shown in
 *       Table 3.  Senders SHOULD NOT use values higher than 4 in this field.
 *       Receivers MUST treat values higher than 4 as if the value received
 *       were 4 (Highest).  The default priority value when the PRIORITY
 *       attribute is missing is 2 (Normal).
 *
 *       \li Reserved: At this point, the 13 bits in the reserved field SHOULD be
 *       set to zero by the sender of the message and MUST be ignored by the
 *       receiver.
 *
 */


/** \section BFCP-PROTOCOL-TRANSACTION 
  *
  *
  *   In BFCP, there are two types of transactions: client-initiated
  *   transactions and server-initiated transactions (notifications).
  *   Client-initiated transactions consist of a request from a client to a
  *   floor control server and a response from the floor control server to
  *   the client.  The request carries a Transaction ID in its common
  *   header, which the floor control server copies into the response.
  *   Clients use Transaction ID values to match responses with previously
  *   issued requests.
  *
  *    \li  Server-initiated transactions consist of a single message from a
  *   floor control server to a client.  Since they do not trigger any
  *   response, their Transaction ID is set to 0.
  *    \li  Client Behavior
  *
  *   \li A client starting a client-initiated transaction MUST set the
  *   Conference ID in the common header of the message to the Conference
  *   ID for the conference that the client obtained previously.
  *
  *   \li The client MUST set the Transaction ID value in the common header to
  *   a number that is different from 0 and that MUST NOT be reused in
  *   another message from the client until a response from the server is
  *   received for the transaction.  The client uses the Transaction ID
  *   value to match this message with the response from the floor control
  *   server.
  */

/**     \struct s_bfcp_msg_event */
typedef struct {
    e_bfcp_primitives           Event ; /**     @brief  primitive */
    e_bfcp_status               Status ; /**     @brief  Request Status */
    e_bfcp_status               FloorStatus ; /**     @brief  Floor Status  */
    e_bfcp_attibutes            Attibutes;/**     @brief  attributes of request  */
    e_bfcp_priority             Priority;/**     @brief  priority of request   */
    e_bfcp_error_codes          Error_codes;/**     @brief   error code  */
    e_bfcp_specific_error_codes Specific_error_codes;/**     @brief  specifiques error code   */
    UINT16  TransactionID ; /**     @brief  transaction ID of request  \ref BFCP-PROTOCOL-TRANSACTION */
    UINT16  userID ;  /**     @brief   user ID of request \ref BFCP-COMMON-HEADER */
    UINT32  conferenceID ;/**     @brief  conference ID of request \ref BFCP-COMMON-HEADER  */
    UINT16  FloorID ;/**     @brief   floor id of request \ref FLOOR-ID */
    UINT16  FloorRequestID ;/**     @brief  floor request id \ref FLOOR-REQUEST-ID  */
    UINT16  QueuePosition ; /**    @brief   queue position \ref  REQUEST-STATUS  */
    UINT16  BeneficiaryID ;/**     @brief   benficiary ID of request  \ref BENEFICIARY-ID */
    BFCP_SOCKET   sockfd ;/**     @brief  socket fille desc receving this request  */
    UINT16  i_parm ;/**     @brief   integer for variables paramters  */
    char    c_param[BFCP_STRING_SIZE] ;/**     @brief  char table for or variables paramters    */
    void*       pt_param ;/**     @brief  pointer  or variables paramters   */
    UINT8    Support_primitives[BFCP_MAX_RG];/**     @brief  binary table of supported primitive by FCS   \ref e_bfcp_primitives */
    UINT8    Support_attributes[BFCP_MAX_RG];/**     @brief   binary table of supported attributes by FCS  \ref e_bfcp_attributes */
    int transport;
}s_bfcp_msg_event ;


/*     BFCP Message */
typedef struct  bfcp_message {
	unsigned char *buffer;		/*  @brief    The buffer containing the message */
	UINT16 position;	/*  @brief    The position indicator for the buffer */
	UINT16 length;	/*  @brief    The length of the message */
} bfcp_message;

/*     Helping Structures for bit masks and so on */
typedef struct bfcp_entity {
	UINT32 conferenceID;
	UINT16 transactionID;
	UINT16 userID;
} bfcp_entity;

typedef struct bfcp_floor_id_list {	/*   @brief   FLOOR-ID list, to manage the multiple FLOOR-ID attributes */
	UINT16 ID;			/*   @brief   FLOOR-ID */
	struct bfcp_floor_id_list *next;	/*    @brief   Pointer to next FLOOR-ID instance */
} bfcp_floor_id_list;

typedef struct bfcp_supported_list {	/*   @brief   list to manage all the supported attributes and primitives */
	UINT8 element;		/*   @brief   Element (Attribute/Primitive) */
	struct bfcp_supported_list *next;	/*  @brief    Pointer to next supported element instance */
} bfcp_supported_list;

typedef struct bfcp_request_status {
	e_bfcp_status rs;	/* @brief    Request Status */
	UINT8 qp;	/*   @brief   Queue Position */
} bfcp_request_status;

typedef struct bfcp_unknown_m_error_details {	/*     These are specific details for error 4: UNKNOWN_M */
	UINT16 unknown_type;	/*     7-bits to specify the unknown received mandatory attribute */
	UINT16 reserved;		/*     A reserved bit, which must be set to 0 and ignored, at the moment */
	struct bfcp_unknown_m_error_details *next;	/*     This is a linked list */
} bfcp_unknown_m_error_details;

typedef struct bfcp_error {
	e_bfcp_error_codes code;	/*     Error Code */
	bfcp_unknown_m_error_details *details;			/*     Error Details */
} bfcp_error;

typedef struct bfcp_user_information {	/*     Help structure for BENEFICIARY-INFORMATION and REQUESTED-BY-INFORMATION */
	UINT16 ID;		/*     For the INFORMATION-HEADER */
	char *display;			/*     USER-DISPLAY-NAME, optional */
	char *uri;			/*     USER-URI, optional */
} bfcp_user_information;

typedef struct bfcp_floor_request_status {	/*     Help structure for FLOOR-REQUEST-STATUS */
	UINT16 fID;			/*     FLOOR-REQUEST-STATUS-HEADER */
	bfcp_request_status *rs;		/*     REQUEST-STATUS, optional */
	char *sInfo;				/*     STATUS-INFO, optional */
	struct bfcp_floor_request_status *next;	/*     pointer to next instance (to manage lists) */
} bfcp_floor_request_status;

typedef struct bfcp_overall_request_status {	/*     Help structure for OVERALL-REQUEST-STATUS */
	UINT16 frqID;		/*     OVERALL-REQUEST-STATUS-HEADER */
	bfcp_request_status *rs;		/*     REQUEST-STATUS, optional */
	char *sInfo;				/*     STATUS-INFO, optional */
} bfcp_overall_request_status;

typedef struct bfcp_floor_request_information {		/*     Help structure for FLOOR-REQUEST-INFORMATION */
	UINT16 frqID;			/*     FLOOR-REQUEST-INFORMATION-HEADER */
	bfcp_overall_request_status *oRS;		/*     OVERALL-REQUEST-STATUS, optional */
	bfcp_floor_request_status *fRS;			/*     FLOOR-REQUEST-STATUS list */
	bfcp_user_information *beneficiary;		/*     BENEFICIARY-INFORMATION, optional */
	bfcp_user_information *requested_by;		/*     REQUESTED-BY-INFORMATION, optional */
	e_bfcp_priority priority;			/*     PRIORITY, optional */
	char *pInfo;					/*     PARTICIPANT-PROVIDED-INFO, optional */
	struct bfcp_floor_request_information *next;	/*     pointer to next instance (to manage lists) */
} bfcp_floor_request_information;

typedef struct bfcp_digest {
	UINT16 algorithm;	/*     (currently UNUSED) */
	char *text;			/*     (currently UNUSED) */
} bfcp_digest;

typedef struct bfcp_arguments {
	e_bfcp_primitives primitive;			/*     Message Primitive */
	bfcp_entity *entity;				/*     Conference ID, Transaction ID, User ID */
	bfcp_floor_id_list *fID;			/*     Floor ID list */
	UINT16 frqID;			/*     Floor Request ID */
	UINT16 bID;				/*     Beneficiary ID */
	e_bfcp_priority priority;			/*     Priority */
	bfcp_floor_request_information *frqInfo;	/*     Floor Request Information */
	bfcp_user_information *beneficiary;		/*     Beneficiary Information */
	bfcp_request_status *rs;			/*     Request Status */
	char *pInfo;					/*     Participant Provided Info */
	char *sInfo;					/*     Status Info */
	bfcp_error *error;				/*     Error Code & Details */
	char *eInfo;					/*     Error Info */
	bfcp_supported_list *primitives;		/*     Supported Primitives list */
	bfcp_supported_list *attributes;		/*     Supported Primitives list */
	UINT16 nonce;			/*     Nonce (currently UNUSED) */
	bfcp_digest *digest;				/*     Digest Algorithm & Text */
	int unreliable;					/*     Whether transport is reliable or not */
} bfcp_arguments;

/*     Parsing Help Structures */
typedef struct bfcp_received_attribute {	/*     A chained list to manage all attributes in a received message */
	e_bfcp_attibutes type;				/*     The attribute type */
	int mandatory_bit;			/*     The Mandatory Bit */
	int length;				/*     The length of the attribute */
	int position;				/*     Its position in the message buffer */
	int valid;				/*     If errors occur in parsing, the attribute is marked as not valid */
	struct bfcp_received_attribute *next;	/*     Pointer to next attribute in the message */
} bfcp_received_attribute;

typedef struct bfcp_received_message {
	bfcp_arguments *arguments;			/*     The message unpacked in its original arguments */
	int version;					/*     The version of the received message */
	int reserved;					/*     The reserved bits */
	e_bfcp_primitives primitive;					/*     The primitive of the message */
	int length;					/*     The length of the message */
	bfcp_entity *entity;				/*     The entities of the message (IDs) */
	bfcp_received_attribute *first_attribute;	/*     A list of all attributes in the message */
	struct bfcp_received_message_error *errors;	/*     If errors occur, we write them here */
	int transport;
} bfcp_received_message;

typedef struct bfcp_received_message_error {
	e_bfcp_primitives attribute;					/*     The attribute where the error happened */
	e_bfcp_error_codes code;					/*     The Parsing-specific Error Code */
	struct bfcp_received_message_error *next;	/*     There could be more errors, it's a linked list */
} bfcp_received_message_error;

/*     Creating and Freeing Methods for the Structures */
/*     Create a New Arguments Structure */
bfcp_arguments *bfcp_new_arguments(void);
/*     Free an Arguments Structure */
int bfcp_free_arguments(bfcp_arguments *arguments);

/*     Create a New Message (if buffer is NULL, creates an empty message) */
bfcp_message *bfcp_new_message(unsigned char *buffer, UINT16 length);
/*     Create a Copy of a Message */
bfcp_message *bfcp_copy_message(bfcp_message *message);
/*     Free a Message */
int bfcp_free_message(bfcp_message *message);

/*     Create a New Entity (Conference ID, Transaction ID, User ID) */
bfcp_entity *bfcp_new_entity(UINT32 conferenceID, UINT16 transactionID, UINT16 userID);
/*     Free an Entity */
int bfcp_free_entity(bfcp_entity *entity);

/*     Create a new Floor ID list (first argument must be a valid ID, last argument MUST be 0) */
bfcp_floor_id_list *bfcp_new_floor_id_list(UINT16 fID, ...);
/*     Add IDs to an existing Floor ID list (last argument MUST be 0) */
int bfcp_add_floor_id_list(bfcp_floor_id_list *list, UINT16 fID, ...);
/*     Free a Floor ID list */
int bfcp_free_floor_id_list(bfcp_floor_id_list *list);

/*     Create a new Supported (Primitives/Attributes) list (last argument MUST be 0) */
bfcp_supported_list *bfcp_new_supported_list(UINT8 element, ...);
/*     Free a Supported (Primitives/Attributes) list */
int bfcp_free_supported_list(bfcp_supported_list *list);

/*     Create a New Request Status (RequestStatus/QueuePosition) */
bfcp_request_status *bfcp_new_request_status(UINT16 rs, UINT16 qp);
/*     Free a Request Status (RequestStatus/QueuePosition) */
int bfcp_free_request_status(bfcp_request_status *request_status);

/*     Create a New Error (Code/Details) */
bfcp_error *bfcp_new_error(e_bfcp_error_codes code, bfcp_unknown_m_error_details *details);
/*     Free an Error (Code/Details) */
int bfcp_free_error(bfcp_error *error);

/*     Create a New Error Details list (for Error 4: UNKNOWN_M) (last argument MUST be 0) */
bfcp_unknown_m_error_details *bfcp_new_unknown_m_error_details_list(UINT16 attribute, ...);
/*     Add Attributes to an existing Error Details list (for Error 4: UNKNOWN_M) (last argument MUST be 0) */
int bfcp_add_unknown_m_error_details_list(bfcp_unknown_m_error_details *list, UINT16 attribute, ...);
/*     Free an Error Details list */
int bfcp_free_unknown_m_error_details_list(bfcp_unknown_m_error_details *details);

/*     Create a New User (Beneficiary/RequestedBy) Information */
bfcp_user_information *bfcp_new_user_information(UINT16 ID, char *display, char *uri);
/*     Free an User (Beneficiary/RequestedBy) Information */
int bfcp_free_user_information(bfcp_user_information *info);

/*     Create a new Floor Request Information */
bfcp_floor_request_information *bfcp_new_floor_request_information(UINT16 frqID, bfcp_overall_request_status *oRS, bfcp_floor_request_status *fRS, bfcp_user_information *beneficiary, bfcp_user_information *requested_by, e_bfcp_priority priority ,char *pInfo);
/*     Create a Floor Request Information list (last argument MUST be NULL) */
int bfcp_list_floor_request_information(bfcp_floor_request_information *frqInfo, ...);
/*     Add elements to an existing Floor Request Information list (last argument MUST be NULL) */
int bfcp_add_floor_request_information_list(bfcp_floor_request_information *list, ...);
/*     Free a Floor Request Information list */
int bfcp_free_floor_request_information_list(bfcp_floor_request_information *frqInfo);

/*     Create a New Floor Request Status (FloorID/RequestStatus/QueuePosition/StatusInfo) */
bfcp_floor_request_status *bfcp_new_floor_request_status(UINT16 fID, UINT16 rs, UINT16 qp, char *sInfo);
/*     Create a Floor Request Status list (last argument MUST be NULL) */
int bfcp_list_floor_request_status(bfcp_floor_request_status *fRS, ...);
/*     Add elements to an existing Floor Request Status list (last argument MUST be NULL) */
int bfcp_add_floor_request_status_list(bfcp_floor_request_status *list, ...);
/*     Free a Floor Request Status list */
int bfcp_free_floor_request_status_list(bfcp_floor_request_status *floor_request_status);

/*     Create a New Overall Request Status (FloorRequestID/RequestStatus/QueuePosition/StatusInfo) */
bfcp_overall_request_status *bfcp_new_overall_request_status(UINT16 frqID, UINT16 rs, UINT16 qp, char *sInfo);
/*     Free an Overall Request Status */
int bfcp_free_overall_request_status(bfcp_overall_request_status *overall_request_status);

/*     Create a New Digest */
bfcp_digest *bfcp_new_digest(UINT16 algorithm);
/*     Free a Digest */
int bfcp_free_digest(bfcp_digest *digest);


/*     Build Methods */
/*     Generic BuildMessage Method */
bfcp_message *bfcp_build_message(bfcp_arguments*     arguments);
/*     Build Headers */
void bfcp_build_commonheader(bfcp_message *message, bfcp_entity *entity, e_bfcp_primitives primitive, int unreliable);
void bfcp_build_attribute_tlv(bfcp_message *message, UINT16 position, UINT16 type, UINT16 mandatory_bit, UINT16 length);

/*     Build Specific Messages */
bfcp_message *bfcp_build_message_FloorRequest(bfcp_entity *entity, bfcp_floor_id_list *fID, UINT16 bID, char *pInfo, e_bfcp_priority priority, int unreliable);
bfcp_message *bfcp_build_message_FloorRelease(bfcp_entity *entity, UINT16 frqID, int unreliable);
bfcp_message *bfcp_build_message_FloorRequestQuery(bfcp_entity *entity, UINT16 frqID, int unreliable);
bfcp_message *bfcp_build_message_FloorRequestStatus(bfcp_entity *entity, bfcp_floor_request_information *frqInfo, int unreliable);
bfcp_message *bfcp_build_message_UserQuery(bfcp_entity *entity, UINT16 bID, int unreliable);
bfcp_message *bfcp_build_message_UserStatus(bfcp_entity *entity, bfcp_user_information *beneficiary, bfcp_floor_request_information *frqInfo, int unreliable);
bfcp_message *bfcp_build_message_FloorQuery(bfcp_entity *entity, bfcp_floor_id_list *fID, int unreliable);
bfcp_message *bfcp_build_message_FloorStatus(bfcp_entity *entity, bfcp_floor_id_list *fID, bfcp_floor_request_information *frqInfo, int unreliable);
bfcp_message *bfcp_build_message_ChairAction(bfcp_entity *entity, bfcp_floor_request_information *frqInfo, int unreliable);
bfcp_message *bfcp_build_message_ChairActionAck(bfcp_entity *entity);
bfcp_message *bfcp_build_message_Hello(bfcp_entity *entity, int unreliable);
bfcp_message *bfcp_build_message_HelloAck(bfcp_entity *entity, bfcp_supported_list *primitives, bfcp_supported_list *attributes);
bfcp_message *bfcp_build_message_Error(bfcp_entity *entity, bfcp_error *error, char *eInfo, int unreliable);

/* BFCP over UDP */
bfcp_message *bfcp_build_message_FloorRequestStatusAck(bfcp_entity *entity);
bfcp_message *bfcp_build_message_ErrorAck(bfcp_entity *entity);
bfcp_message *bfcp_build_message_FloorStatusAck(bfcp_entity *entity);
bfcp_message *bfcp_build_message_Goodbye(bfcp_entity *entity, int unreliable);
bfcp_message *bfcp_build_message_GoodbyeAck(bfcp_entity *entity);



/*     Build Attributes */
int bfcp_build_attribute_BENEFICIARY_ID(bfcp_message *message, UINT16 bID);
int bfcp_build_attribute_FLOOR_ID(bfcp_message *message, UINT16 fID);
int bfcp_build_attribute_FLOOR_REQUEST_ID(bfcp_message *message, UINT16 frqID);
int bfcp_build_attribute_PRIORITY(bfcp_message *message, e_bfcp_priority priority);
int bfcp_build_attribute_REQUEST_STATUS(bfcp_message *message, bfcp_request_status *rs);
int bfcp_build_attribute_ERROR_CODE(bfcp_message *message, bfcp_error *error);
int bfcp_build_attribute_ERROR_INFO(bfcp_message *message, char *eInfo);
int bfcp_build_attribute_PARTICIPANT_PROVIDED_INFO(bfcp_message *message, char *pInfo);
int bfcp_build_attribute_STATUS_INFO(bfcp_message *message, char *sInfo);
int bfcp_build_attribute_SUPPORTED_ATTRIBUTES(bfcp_message *message, bfcp_supported_list *attributes);
int bfcp_build_attribute_SUPPORTED_PRIMITIVES(bfcp_message *message, bfcp_supported_list *primitives);
int bfcp_build_attribute_USER_DISPLAY_NAME(bfcp_message *message, char *display);
int bfcp_build_attribute_USER_URI(bfcp_message *message, char *uri);
int bfcp_build_attribute_BENEFICIARY_INFORMATION(bfcp_message *message, bfcp_user_information *beneficiary);
int bfcp_build_attribute_FLOOR_REQUEST_INFORMATION(bfcp_message *message, bfcp_floor_request_information *frqInfo);
int bfcp_build_attribute_REQUESTED_BY_INFORMATION(bfcp_message *message, bfcp_user_information *requested_by);
int bfcp_build_attribute_FLOOR_REQUEST_STATUS(bfcp_message *message, bfcp_floor_request_status *fRS);
int bfcp_build_attribute_OVERALL_REQUEST_STATUS(bfcp_message *message, bfcp_overall_request_status *oRS);
int bfcp_build_attribute_NONCE(bfcp_message *message, UINT16 nonce);
int bfcp_build_attribute_DIGEST(bfcp_message *message, bfcp_digest *digest);


/*     Parse Methods */
UINT16 bfcp_get_length(bfcp_message *message);
e_bfcp_primitives bfcp_get_primitive(bfcp_message *message);
UINT32 bfcp_get_conferenceID(bfcp_message *message);
UINT16 bfcp_get_transactionID(bfcp_message *message);
UINT16 bfcp_get_userID(bfcp_message *message);
bfcp_received_message *bfcp_new_received_message(void);
int bfcp_free_received_message(bfcp_received_message *recvM);
bfcp_received_message_error *bfcp_received_message_add_error(bfcp_received_message_error *error, e_bfcp_primitives attribute, e_bfcp_error_codes code);
int bfcp_free_received_message_errors(bfcp_received_message_error *errors);
bfcp_received_attribute *bfcp_new_received_attribute(void);
int bfcp_free_received_attribute(bfcp_received_attribute *recvA);
bfcp_received_message *bfcp_parse_message(bfcp_message *message);
bfcp_received_attribute *bfcp_parse_attribute(bfcp_message *message);
int bfcp_parse_arguments(bfcp_received_message *recvM, bfcp_message *message);
int bfcp_parse_attribute_BENEFICIARY_ID(bfcp_message *message, bfcp_received_attribute *recvA);
int bfcp_parse_attribute_FLOOR_ID(bfcp_message *message, bfcp_received_attribute *recvA);
int bfcp_parse_attribute_FLOOR_REQUEST_ID(bfcp_message *message, bfcp_received_attribute *recvA);
e_bfcp_priority bfcp_parse_attribute_PRIORITY(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_request_status *bfcp_parse_attribute_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_error *bfcp_parse_attribute_ERROR_CODE(bfcp_message *message, bfcp_received_attribute *recvA);
char *bfcp_parse_attribute_ERROR_INFO(bfcp_message *message, bfcp_received_attribute *recvA);
char *bfcp_parse_attribute_PARTICIPANT_PROVIDED_INFO(bfcp_message *message, bfcp_received_attribute *recvA);
char *bfcp_parse_attribute_STATUS_INFO(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_supported_list *bfcp_parse_attribute_SUPPORTED_ATTRIBUTES(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_supported_list *bfcp_parse_attribute_SUPPORTED_PRIMITIVES(bfcp_message *message, bfcp_received_attribute *recvA);
char *bfcp_parse_attribute_USER_DISPLAY_NAME(bfcp_message *message, bfcp_received_attribute *recvA);
char *bfcp_parse_attribute_USER_URI(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_user_information *bfcp_parse_attribute_BENEFICIARY_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_floor_request_information *bfcp_parse_attribute_FLOOR_REQUEST_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_user_information *bfcp_parse_attribute_REQUESTED_BY_INFORMATION(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_floor_request_status *bfcp_parse_attribute_FLOOR_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_overall_request_status *bfcp_parse_attribute_OVERALL_REQUEST_STATUS(bfcp_message *message, bfcp_received_attribute *recvA);
int bfcp_parse_attribute_NONCE(bfcp_message *message, bfcp_received_attribute *recvA);
bfcp_digest *bfcp_parse_attribute_DIGEST(bfcp_message *message, bfcp_received_attribute *recvA);

#ifdef __cplusplus
} // extern "C"
#endif


#endif

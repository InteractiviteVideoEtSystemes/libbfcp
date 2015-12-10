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
 * \file    : BFCPexception.h
 *
 * \brief   :  BFCP exceptions
 *
 * \version : $Revision: 2483 $
 *
 * \date    : $Date: 2015-10-23 15:23:21 +0200 (Fri, 23 Oct 2015) $
 *
 * \remarks :
 *
 * ------------------------------------------------------------------------- */

/* ==========================================================================*/
/* File identification                                                       */
/* ==========================================================================*/

/* ==========================================================================*/
/* System include(s)                                                         */
/* ==========================================================================*/

#ifndef _BFCP_EXCEPTION_H
#define _BFCP_EXCEPTION_H

#ifndef WIN32
#include <sstream>
#include <iostream>
#include <stdexcept>

class BFCPException : public std::exception
{
public:
    BFCPException( const char * file , const int line , bool fatal , const char* reason="Unknown" , const char* comment="" )
    {
        std::ostringstream oss;
        oss << file << ":(" << line << ") - exception: " << reason;
	if (comment && comment[0] != 0) oss << ". " << comment;
        this->msg = oss.str();
    }
    
    BFCPException( )
    {
        std::ostringstream oss;
        oss <<  "BFCPException "  ;
        this->msg = oss.str();
    }
 
    virtual ~BFCPException() throw()
    {
 
    }
 
    virtual const char * what() const throw()
    {
        return this->msg.c_str();
    }
 
private:
    std::string msg;
};
#else
#include "FTCException.h" 
#define BFCPException FTCException
#endif

class InterruptedException: public BFCPException {
public:
	InterruptedException(): BFCPException() {}
	InterruptedException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "InterruptedException", message) {
	}
};


class UnknownHostException: public BFCPException {
public:
	UnknownHostException(): BFCPException() {}
	UnknownHostException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "UnknownHostException", message) {
	}
};


class FileNotFoundException: public BFCPException {
public:
	FileNotFoundException(): BFCPException() {}
	FileNotFoundException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "FileNotFoundException", message) {
	}
};


class InvalidParameterException: public BFCPException {
public:
	InvalidParameterException(): BFCPException() {}
	InvalidParameterException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "InvalidParameterException", message) {
	}
};

class OpenFileErrorException: public BFCPException {
public:
	OpenFileErrorException(): BFCPException() {}
	OpenFileErrorException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "OpenFileErrorException", message) {
	}
};

class IOException: public BFCPException {
public:
	IOException(): BFCPException() {}
	IOException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "IOException", message) {
	}
};

class IllegalArgumentException: public BFCPException {
public:
	IllegalArgumentException(): BFCPException() {}
	IllegalArgumentException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "IllegalArgumentException", message) {
	}
};

class ParseException : public BFCPException {
public:
	ParseException(): BFCPException() {}
	ParseException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "ParseException", message) {
	}
};

class BadParameterException: public BFCPException {
public:
	BadParameterException(): BFCPException() {}
	BadParameterException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "BadParameterException", message) {
	}
};

class SessionCondemnedException : public BFCPException {
public:
	SessionCondemnedException(): BFCPException() {}
	SessionCondemnedException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "SessionCondemnedException", message) {
	}
};


class RequestMethodException: public BFCPException {
public:
	RequestMethodException(): BFCPException() {}
	RequestMethodException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "RequestMethodException", message) {
	}
};
class PayloadOverflowException: public BFCPException {
public:
	PayloadOverflowException(): BFCPException() {}
	PayloadOverflowException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "PayloadOverflowException", message) {
	}
};

class MessageMissformedException : public BFCPException {
public:
	MessageMissformedException(): BFCPException() {}
	MessageMissformedException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "MessageMissformedException", message) {
	}
};

class BadMessageSchemeException : public BFCPException {
public:
	BadMessageSchemeException(): BFCPException() {}
	BadMessageSchemeException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "BadMessageSchemeException", message) {
	}
};

class InternalProgramError: public BFCPException {
public:
	InternalProgramError(): BFCPException() {}
	InternalProgramError(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "InternalProgramError", message) {
	}
};

class InvalidFieldException: public BFCPException {
public:
	InvalidFieldException(): BFCPException() {}
	InvalidFieldException(const char* message) :
		BFCPException(__FILE__,__LINE__,false, "InvalidFieldException", message) {
	}
};

#endif

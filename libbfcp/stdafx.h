
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
 * \file    : stdafx.h
 *
 * \brief   :  BFCP logs and windows definitions
 *
 * \version : $Revision: 2172 $
 *
 * \date    : $Date: 2014-01-27 09:08:19 +0100 (Mon, 27 Jan 2014) $
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
#ifndef _BFCP_STDAFX_H
#define _BFCP_STDAFX_H

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN		// Exclure les en-t�tes Windows rarement utilis�s

#define snprintf _snprintf
#define strcasecmp _stricmp

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows�95 et Windows NT�4 ou version ult�rieure.
#define WINVER 0x0501		// Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�98 et Windows�2000 ou version ult�rieure.
#endif

#ifndef _WIN32_WINNT		// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows NT�4 ou version ult�rieure.
#define _WIN32_WINNT 0x0501		// Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�98 et Windows�2000 ou version ult�rieure.
#endif						

#ifndef _WIN32_WINDOWS		// Autorise l'utilisation des fonctionnalit�s sp�cifiques � Windows�98 ou version ult�rieure.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropri�e � cet �l�ment pour cibler Windows�Me ou version ult�rieure.
#endif

#ifndef _WIN32_IE			// Autorise l'utilisation des fonctionnalit�s sp�cifiques � IE�4.0 ou version ult�rieure.
#define _WIN32_IE 0x0500	// Attribuez la valeur appropri�e � cet �l�ment pour cibler IE�5.0 ou version ult�rieure.
#endif



#include <afxwin.h>
#include <afxext.h>
#include <afxmt.h>
#include <afxcmn.h>
#include "ftcore.h"
#include "ftcplateform.h"
#include "ftccharconv.h"
#include <sstream>
#include <list>
#include <map>
#include <afxwin.h>
#include "ftplayerver.h"

// #include <tchar.h>


#ifdef DEBUG
#define new DEBUG_NEW
#endif

#if defined(UNDER_CE)

unsigned long time(void* data);

#endif // UNDER_CE

#ifdef __linux__
#define _atoi64 atoll
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#endif // WIN32


#if defined(__NO_LOG__)
#define Log(a,b,c,d) ((void)0)
#define LogInit() ((void)0)
#define LogClose() ((void)0)
#else
void LogInit();
void LogClose();
void eConfLog(const  char* pcFile, int iLine, int iErrLevel, const  char* pcFormat, ...);
#endif

#endif

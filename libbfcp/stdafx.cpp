
#include "stdafx.h"
#include <stdarg.h>

// TODO�: faites r�f�rence aux en-t�tes suppl�mentaires n�cessaires dans STDAFX.H
// absents de ce fichier
#ifndef __NO_LOG__

#ifdef WIN32
static FTCLogger iBfcpLogger = FTCLogger((char*) "BfcpLogger", (unsigned int) 8192, true);
#endif

void LogInit() {
#ifdef WIN32
    iBfcpLogger.LoadFromFile(NULL);
#endif
}

void LogClose() {
#ifdef WIN32
#endif
}

void eConfLog(const  char* pcFile, int iLine, int iErrorLevel,const   char* pcFormat, ...) {
#ifdef WIN32
    if (!iBfcpLogger.IsLogEnabled(iErrorLevel))
        return;

    va_list arg;
    char s[3000];

    va_start(arg,pcFormat);
    vsprintf(s,pcFormat,arg);
    va_end(arg);

    iBfcpLogger.LogIt((char*)pcFile, iLine, iErrorLevel, "%s", s);
#endif
}
#endif // __NO_LOG__

#if defined(UNDER_CE)

#ifdef WIN32
#include <winbase.h>
// Define the time function for compatibility
unsigned long time(void* data) {
    unsigned long	result		= 0;
    unsigned long	nSecInDay	= 24 * 60 * 60;
    SYSTEMTIME		systemTime;

    GetSystemTime(&systemTime);

    result = ( ((systemTime.wYear - 1970) * (unsigned long) (365.25 * nSecInDay )) +
               ((systemTime.wMonth - 1) * 30 * nSecInDay) +
               (systemTime.wDay * nSecInDay) +
               (systemTime.wHour * 60 * 60) +
               (systemTime.wMinute * 60 ) +
               systemTime.wSecond );

    return result;
}
#endif 

#endif // UNDER_CE

#ifndef _BFCP_THREADS_
#define _BFCP_THREADS_


#ifndef WIN32
#include <limits.h>
#include <pthread.h>
typedef pthread_mutex_t bfcp_mutex_t;

#if 0
#define bfcp_mutex_init(a,b) pthread_mutex_init(&a,b)
#define bfcp_mutex_destroy(a)  { char msg[256] ; sprintf(msg,"%s(%d) ----- destroy %p\n",__FILE__,__LINE__,&a);fprintf(stdout,msg) ; pthread_mutex_destroy(&a) ;}
#define bfcp_mutex_lock(a) { char msg[256] ; sprintf(msg,"%s(%d) >>>>> lock %p\n",__FILE__,__LINE__,&a);fprintf(stdout,msg) ;  pthread_mutex_lock(&a); }
#define bfcp_mutex_unlock(a)  { char msg[256] ; sprintf(msg,"%s(%d) <<<<< unlock %p\n",__FILE__,__LINE__,&a);fprintf(stdout,msg) ; pthread_mutex_unlock(&a) ;}
#else
#define bfcp_mutex_init(a,b) pthread_mutex_init(&a,b)
#define bfcp_mutex_destroy(a) pthread_mutex_destroy(&a)
#define bfcp_mutex_lock(a) pthread_mutex_lock(&a)
#define bfcp_mutex_unlock(a) pthread_mutex_unlock(&a)
#endif

#define BFCP_THREAD_HANDLE pthread_t
#define BFCP_THREAD_START(threadID,ThreadFunc,arg)  pthread_create(&threadID , NULL,  ThreadFunc,(void*) arg); 
#define BFCP_THREAD_KILL(HThread)    pthread_cancel(HThread);  
#define BFCP_NULL_THREAD_HANDLE 0 
#define BFCP_SLEEP(x) usleep(x*1000)

#else // WIN32
#if !defined(_MT)
#error _beginthreadex requires a multithreaded C run-time library.
#endif
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH 
#endif
#include "ftcmutex.h"
#include <process.h>
typedef FTCMutex*  bfcp_mutex_t;
#define bfcp_mutex_init(a,b)  a=new FTCMutex()
#define bfcp_mutex_destroy(a) if ( a )  { char msg[256] ; sprintf(msg,"%s(%d) ----- destroy %p\n",__FILE__,__LINE__,a);OutputDebugString(msg) ;delete a ; a=NULL;};
#define bfcp_mutex_lock(a) { char msg[256] ; sprintf(msg,"%s(%d) >>>>> lock %p\n",__FILE__,__LINE__,a);OutputDebugString(msg) ; a->Lock();};
#define bfcp_mutex_unlock(a) { char msg[256] ; sprintf(msg,"%s(%d) <<<<< unlock %p\n",__FILE__,__LINE__,a);OutputDebugString(msg);a->Unlock();};
#define BFCP_THREAD_HANDLE HANDLE
#define close(fd)  closesocket(fd)
#define BFCP_THREAD_HANDLE HANDLE
#define BFCP_THREAD_START(threadID,ThreadFunc,arg)  threadID = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, arg,0,NULL); 
#define BFCP_THREAD_KILL(HThread)    TerminateThread(HThread,-1);CloseHandle(HThread);  
#define BFCP_NULL_THREAD_HANDLE NULL
#define BFCP_SLEEP(x) Sleep(x)
#endif
#endif


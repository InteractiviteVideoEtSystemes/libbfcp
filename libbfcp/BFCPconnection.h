/**
 *
 * \brief BFCP network connection
 * 
 * Manages either a connection between a sender local
 * endpoint and a receiver remote endpoint or a receiver local endpoint only.
 * The stack is TCP/IP based on. A connection usually has an input socket and an
 * output socket. Both are opened for defined ports. 
 *
 * \remarks :
 * In the first release , server is only passive. 
 *
 * In the first release TLS mode isn't supported.
 *
 * \copyright Unpublished Confidential Information of IVES Do not disclose. 
 * Copyright (c) 2000-2014 IVES  All Rights Reserved.     
 *
 * \author Philippe Verney
 *
 * \file BFCPconnection.h
 *
 * \version $Revision: 2630 $
 *
 * \date $Date: 2015-11-25 17:47:27 +0100 (Wed, 25 Nov 2015) $
 *
 */
#ifndef BFCP_CONNECTION_H
#define BFCP_CONNECTION_H

#include <sys/time.h>
#include <string>
#include <map>
#include <list>

#ifdef WIN32
#include <winsock2.h>
#endif

#ifdef SUPPORT_SSL
/* Needed for TCP/TLS/BFCP support */
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
/* The library supports both TCP/BFCP and TCP/TLS/BFCP */
#endif

#include "bfcp_messages.h"
#include "bfcp_threads.h"

#define BFCP_OVER_TCP	0
#define BFCP_OVER_TLS	1
#define BFCP_OVER_UDP	2

#define BFCP_FCS_DEFAULT_PORT	2345	/** @brief The default port the Floor Control Server will bind to */
#define BFCP_MAX_CONNECTIONS 	1000	/** @brief  The default value for how many connections the server can hold at the same time */

/**
 * @class BFCPConnectionRole
 */
class BFCPConnectionRole
{
public:
    BFCPConnectionRole(void);
public:
    virtual ~BFCPConnectionRole(void);

    static const int ACTIVE;
    static const int PASSIVE;
};

/**
 *
 * @class BFCPConnection
 * @brief This class implements network connection and session routing.
 * 
 */
class BFCPConnection
{
public:
    /**
     * Default constructor 
     * @param  void
     * @return  new instance 
     */
    BFCPConnection(void);
    /**
     * Default destructor 
     * @param  void 
     * @return 
     */
    virtual ~BFCPConnection(void);
    /**
     * This virtual callback is called when you recevied a message .
     * @param socket recevied socket 
     * @return -1 , socket are closed , null sucess .
     */
    virtual int ProcessBFCPmessage(bfcp_received_message * m, BFCP_SOCKET s) = 0 ;
    /**
     * This virtual callback is called when you are connected 
     * @param socket connected socket 
     * @param RemoteIp remote ip connected
     * @param remotePort remote port connected 
     * @return true sucess , false failed .
     */
    virtual bool OnBFCPConnected(BFCP_SOCKET socket, const char* RemoteIp , int remotePort) = 0;
    /**
     * This virtual callback is called when you are disconnected 
     * @param socket disconnected socket 
     * @param RemoteIp  remote ip disconnected
     * @param remotePort remote port disconnected 
     * @return true sucess , false failed .
     */
    virtual bool OnBFCPDisconnected(BFCP_SOCKET sockets) = 0;
    /**
     * \brief Virtual log and traces callback , for better traces integration on your process 
     * @param pcFile file reference 
     * @param iLine  line refernce 
     * @param iErrorLevel error level \ref INF debug \ref WAR warning \ref ERR error 
     * @param pcFormat char formated traces 
     */
    virtual void Log(const  char* pcFile, int iLine, int iErrorLevel, const  char* pcFormat, ...);
    /**
     * Return connected state 
     * @return true connected , false not connected .
     */
    bool isConnected() { return m_bConnected; };
    /**
     * Return if network thread is started .
     * @return true network thread started , false not started .
     */
    bool isStarted() { return m_isStarted; };
    /**
     * Set local network connection informations 
     * @param localAddress local ip local IP V4 address,  you can use NULL to listen all interface  
     * @param port  local port, if you use 0 you dont bind . 
     * @param eRole BFCPConnectionRole::PASSIVE server else client.
     * @return 
     */
    bool SelLocalConnection( const char* localAddress, UINT16 port, int eRole);

    /**
     * Return the local configured endpoint socket address
     * 
     * @return the local configured endpoint socket address
     */
    const char* getLocalAdress();
    /**
    * Return the local configured endpoint socket port
     * 
     * @return the local configured endpoint socket port
     */
    UINT16   getLocalPort();
    /**
     * Return the remote configured connection endpoint address
     * 
     * @return  the remote configured connection endpoint address
     */
    const char* getRemoteAdress();
    
    /**
     * Return the remote configured connection endpoint port
     * @return the remote configured connection endpoint port
     */
    UINT16      getRemotePort();

    /**
     * Instanciate the remote endpoint
     *
     * @param  address Address of endpoint
     * @param  port    Port number
     * @return true sucess , false failed 
     */
    bool setRemoteEndpoint(const char* address, UINT16 port);

    /**
     * Remember an active session using the connection ( futur use ) 
     * 
     * @param sessionId
     *            the session ID
     */
    void addSession(const std::string& sessionId);

    /**
     * Remove a terminated session using the connection. If there is no more
     * session for the connection, the connection is closed.
     * 
     */
    void removeSession();

    /**
     * Push Bsender stack. The connection thread will then
     * take care of these chunks.
     * 
     * @param client_sock socket used by the client 
     * @param message BFCP message 
     * \return true on success, false on error
     */
    
    
    /**
     * Push a bfcp message on socket. If the message initiate a transaction,
     * add it in the transaction table to manage rentransmission when using
     * UDP transport. 
     *
     * @param client_sock client socket
     * @param message BFCP message
     * @param donotresend true: this should not be resent (on unreliable transport). false: manage retransmission
     * 
     * @return  1 = success
     *          0 = could not send transport error
     *	       -1 = duplicate transaction ID
     */
    int sendBFCPmessage(BFCP_SOCKET client_sock , bfcp_message *message, bool donotresend = false);

    /**
     * Open the connection and starts the transmit loop.
     */
    int connect();

    /**
     * Close all the connection 
     */
    void disconnect();
    

    /**
     * Return the  current  ip and port for the server socket. 
     * @param localIp ip listening by server
     * @param localPort port listening by server 
     * @return true success , false failed .
     * @remarks : local ip must have BFCP_STRING_SIZE  size 
     */
    bool GetServerInfo(char * localIp , int* localPort);
     
    
    
protected:
    /**
     * Add a new client. Can be active, passive TCP or TLS client. Can be UDP client.
     * WARNING : only UDP client are supported for the moment.
     * @param transport to use for BCP protocol
     **/
    BFCP_SOCKET AddClient(int transport, int role, char * localAddress = NULL, UINT16 port = 0);
    
    /**
     * Remove client and close socket synchronously
     **/
    bool RemoveClient( BFCP_SOCKET s );

    /**
     * Return main socket of server 
     * @return 
     */
    BFCP_SOCKET getServerSocket() {return m_Socket; }; 


    bool GetConnectionLocalInfo(BFCP_SOCKET s, char * localIp , int* localPort);

    bool IsClientActive(BFCP_SOCKET s);
    
    bool SetRemoteAddressAndPort(BFCP_SOCKET s, const char *remoteIp, UINT16 remotePort);
    
#ifdef WIN32
    static unsigned  __stdcall EntryPoint(void* pParam);
    static unsigned  __stdcall ManageRetransmission(void* pParam);
#else
    static void * EntryPoint(void* pParam);
    static void * ManageRetransmission(void* pParam);
#endif

private:
    /** Handling outgoing retransmission for unreliable transport */
    class Transaction
    {
    public:
	Transaction();
	Transaction(BFCP_SOCKET s, bfcp_message * m);
	virtual ~Transaction();
	
	Transaction& operator = (const Transaction& other);

	/**
	 * -1 - T1 expired
	 *  0 - need to retransmit
	 *  1 - retransmit
	 **/
	int CheckTimerT1(struct timeval * waituntil, unsigned int * duration);
	void MarkTransmission();

    public:
	bfcp_message * message; /* <! message that created the transaction and need to be resent if no ack is received 
				 * this can also be the answer to resend in case of retranmission of a request by a remote party
	                         */
	BFCP_SOCKET m_sockfd;

    private:
	struct timeval timerExpiration;
	unsigned int timerDuration;

    };

    /** context for a socket **/
    class Client2ServerInfo 
    {
    private:
	void Init();

    public:
        Client2ServerInfo() : m_bfcp_transport(BFCP_OVER_TCP)
	{
	    m_role = BFCPConnectionRole::PASSIVE;
	    Init();
	}
	
        Client2ServerInfo(int transport, int role = BFCPConnectionRole::PASSIVE) : m_role(role), m_bfcp_transport(transport)
	{
	    Init();
	}
	
	Client2ServerInfo(const Client2ServerInfo & other)
	{
	    m_role = other.m_role;
	    m_bfcp_transport = other.m_bfcp_transport;
	   
	    strcpy(m_remoteAddressAndPort, other.m_remoteAddressAndPort);
	    strcpy(m_remoteAddressStr, other.m_remoteAddressAndPort);
	    m_remotePort = other.m_remotePort;
	    strcpy(m_localAddressStr, other.m_localAddressStr);
	    m_localPort = other.m_localPort;
	    
	    m_localAddress = other.m_localAddress;
	    m_addrlen = other.m_addrlen;
	    m_remoteAddress = other.m_remoteAddress;
	    m_remoteAddrLen = other.m_remoteAddrLen;
	    
	    /* Do not copy message parsing state */
	    recvidx = 0;
	    msgsize = 0;
	
	    message = NULL;
	    parsed_msg = NULL;
	    //return *this;
	}
	
	/**
	 * Store remote client address. 
	 * @param addr: sockaddr containing the remote address.
	 * @param addrlen size of adress (depends on network protocol used)
	 **/
	void SetRemoteAddress(sockaddr * addr, size_t addrlen);

	inline void SetRemoteAddres(struct sockaddr_storage * addr, socklen_t addrlen)
	{
	    SetRemoteAddress( (struct sockaddr *) addr, addrlen);
	}

	/** 
	 * Set remote address of connection context.
	 * Same as above but can use string addresses. Return false if
	 **/
	bool SetRemoteAddress(const char * addr, UINT16 port);
	

	/** 
	 * Set local address of connection context.
	 * Same as above but can use string addresses. Return false if
	 **/
	bool SetLocalAddress(const char * addr, UINT16 port);
	
	void SetLocalAddress(sockaddr * addr, size_t addrlen);

	int GetRole()
	{
	    return m_role;
	}
	
	void SetRole(int role)
	{
	    m_role = role;
	}
	
	/**
	 * Create file descriptior according to characteriscts requested
	 *
	 **/
	BFCP_SOCKET CreateSocket();
	
	/**
	 * Connect an active socket to the remote host
	 * 
	 **/
	int Connect ( BFCP_SOCKET s );

	/** 
	 * Obdtain local and remote address info from a corrected TCP socket.
	 **/
	bool GetSockInfo(BFCP_SOCKET s);

	/**
	 * Read data from a socket and parse a message
	 * @return 1 - message parsed and ready
	 *         0 - need more data
	 *        -1 - failed to parse message.
	 *        -2 - message too big discarded
	 *        -3 - transport error. Please close.
	 **/
	int ReadData( BFCPConnection * c, BFCP_SOCKET s );
	
	/**
	 * Read data from a socket and parse a message
	 * @return 
	 *         0 - message sent
	 *        -1 - invalid fd or null message
	 *        -2 - no destination address available
	 *        -3 - transport error.
	 **/
	int SendData( BFCPConnection * c, BFCP_SOCKET s, bfcp_message * m );
	
	static int CloseSocket( BFCP_SOCKET s );

	const char * GetLocalAddr() { return m_localAddressStr; }
	UINT16	     GetLocalPort() { return m_localPort; }

	const char * GetRemoteAddr() { return m_remoteAddressStr; }
	UINT16       GetRemotePort() { return m_remotePort; }
	const char * GetRemoteAddrAndPort() { return m_remoteAddressAndPort; }
	
	/**
	 * Obtain the transport used by the main socket
	 **/
	int GetTransport() { return m_bfcp_transport; }
	
	/**
	 * Check whether the transport is reliable
	 **/
	bool HasReliableTransport() { return GetTransport() == BFCP_OVER_TCP || GetTransport() == BFCP_OVER_TLS; }

	void CleanupRead();
	
        /**
         * Handle incoming request retransmission (unreliable transport)
         * resend the same answer !
         *
         * @return: true if this was a rentransmission. 
         *
         * Expire answers after T1 timer !
         **/
    
        bool HandleRemoteRetrans( BFCPConnection * c, BFCP_SOCKET s, bfcp_message * m );
 
	/**
	 * Check answer expiration for unreliable transport and cal on OnBFCPDisconnected
	 * if this was a GoodByeAck answer
	 *
	 * @return 1 : at lease one transaction has expired. Rerun. 0 : no transaction expired
	 *             -1 - special case where GoodByeAck transaction has expired.
	 * 
	 **/
 
	int  CheckExpiredAnswers( BFCPConnection * c );
 
    private:
        /**
	 * Utility method that translate and IP address / port into a sockaddr struct
	 * 
	 **/
        static bool SetAddress(const char * addrstr, UINT16 port, struct sockaddr * addr, socklen_t & addrlen);
	static void PrintAddress(const struct sockaddr * addr, char * p_addrstr, UINT16 & p_port);
	
    private:
	/* type of socket for connected transports */
	int m_role;
	int m_bfcp_transport;

	/* Socket address information */
        char m_remoteAddressAndPort[PATH_MAX];
	char m_remoteAddressStr[PATH_MAX];
	UINT16 m_remotePort;

	char m_localAddressStr[PATH_MAX];
	UINT16 m_localPort;
	
	struct sockaddr_storage m_localAddress;
	struct sockaddr_storage m_remoteAddress;

	/* Incoming messages handling */
	unsigned char recvBuffer[BFCP_MAX_ALLOWED_SIZE];
	int recvidx;
	int msgsize;
	
	/* Answers */
	std::map<UINT16, Transaction> answerMap; 
   	
#ifdef WIN32
	size_t m_addrlen;
	size_t m_remoteAddrLen;
#else
	socklen_t m_addrlen;
	socklen_t m_remoteAddrLen;
#endif
	
    public:
	bfcp_message * message;
	bfcp_received_message *parsed_msg;
    };


    /**
     * Remove transaction from list if the message is an answer
     * from a server initiated transaction
     * @param s: socket FD on which the transaction was open
     * @param m: incoming message (need the header to be complete at least)
     **/
    int CloseOutgoingTransaction( BFCP_SOCKET s, bfcp_message * m );
    
    
    std::map<UINT16, Transaction> transactionMap;
    
    /**
     * This method continues reading the local endpoint and processing chunk if
     * there is one then sending to remote endpoint the first chunk pushed on
     * the chunk stack. As the chunks is sent out, it is pops of the stack.
     */
    void RunLoop();
        
    unsigned long availableBytes(BFCP_SOCKET p_sock);
    

private:
    /** mutex for connect function */
    bfcp_mutex_t m_mutConnect;

    /** mutex for m_mapSessions */
    bfcp_mutex_t m_SessionMutex;

    
    /** The remote socket map */
    std::map <BFCP_SOCKET,Client2ServerInfo > m_ClientSocket;

    /** The socket to way out */
    BFCP_SOCKET m_Socket;
    
    /** Network thread */
    BFCP_THREAD_HANDLE m_thread ;
    //fd_set m_rset ;
    fd_set m_wset ;

    /**
     * Initially false, this tag is set to true if the close connection request
     * happened. When close is set to true, it puts an end to running connection
     * threads.
     */
    bool m_bClose;


    /**
     * this variable defines the connection role: ConnectionRole.ACTIVE means
     * the connection is set between a local endpoint to a remote endpoint.
     * ConnectionRole.PASSIVE means the connection is only set to listen for
     * incoming messages.
     */
    int m_eRole;

    /**
     * Local endpoint IP socket address of the connection. null until the local
        * endpoint is set.
        */
    char m_localAdress[PATH_MAX];
    UINT16 m_localPort ;

    /**
     * Remote endpoint IP socket address of an active connection. This parameter
     * is null for a passive connection or until the connection is set
     */
    Client2ServerInfo m_remoteClient; 

    /**
     * true if the connection is established, false if closed
     */
    bool m_bConnected;
   /**
     * true if the network thread are started 
     */
    bool m_isStarted ;
    
    fd_set allSet;
    int pipefd[2];
    
    BFCP_THREAD_HANDLE m_timer_thread;
    pthread_cond_t m_timer_cond;
};

#endif // BFCP_CONNECTION_H

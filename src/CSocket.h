/*
 * CSocket.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef CSOCKET_H_
#define CSOCKET_H_

#include "IncludeFile.h"
#include "Structures.h"

using namespace std;

class CSocket {
	// store messages
	char m_szMsg[MAX_PATH];
	// host information
	char m_szHostName[MAX_PATH];
	short m_nHostPort;
	int m_nConnType; // TCP or UDP

	// socket
	int m_nSocket;

public:
	// used short because ports are 16bit only
	// nType specifies if TCP(0) or UDP(1)
	CSocket(const char *szHost, const short nPort, int nConnType);
	virtual ~CSocket();

	// start listening on the specified port
	bool startListen(PAYLOAD &oPayload);

	// bind to a port
	bool bindToListen();
	bool bindToSend();

	// listen to the binded port
	bool listen(PAYLOAD &oPayload, int nTimeOut = 0);
	bool send(const PAYLOAD &oPayload);

	// send a message
	bool sendMessage(const PAYLOAD &oPayload);

	// gets the message, in case of errors.
	char* getMessage() {
		return m_szMsg;
	}

	// type of ports we may use
	static const int TYPE_TCP = 0;
	static const int TYPE_UDP = 1;

	static bool getIP(const char* szHostName, char* szIP, int nIPLen);
};

#endif /* CSOCKET_H_ */

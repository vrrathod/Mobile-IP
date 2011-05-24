/*
 * CSocket.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#include "CSocket.h"

CSocket::CSocket(const char *szHost, const short nPort, int nConnType) {
	// clean up the members
	bzero(m_szMsg, sizeof m_szMsg);
	if (szHost)
		strncpy(m_szHostName, szHost, sizeof m_szHostName);
	else
		bzero(m_szHostName, sizeof(m_szHostName));

	m_nHostPort = nPort;
	m_nConnType = nConnType;

	// try creating socket based on this.
	int nSocketType = (m_nConnType) ? (SOCK_DGRAM) : (SOCK_STREAM);
	m_nSocket = socket(AF_INET, nSocketType, 0);

	if (m_nSocket < 0) {
		throw "Failed to create socket";
	}
}

CSocket::~CSocket() {
	if (m_nSocket >= 0) {
		close(m_nSocket);
		m_nSocket = 0;
	}
}

// bind to a port
bool CSocket::bindToListen() {
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = INADDR_ANY;
	dest.sin_port = htons(m_nHostPort);

	if (bind(m_nSocket, (struct sockaddr*) &dest, sizeof(dest)) < 0) {
		snprintf(m_szMsg, sizeof m_szMsg - 1, "Error binding on port %d",
				m_nHostPort);
		return false;
	}

	strncpy(m_szMsg, "", sizeof m_szHostName);

	return true;
}

bool CSocket::bindToSend() {
	struct sockaddr_in src;

	// 2. bind
	src.sin_family = AF_INET;
	src.sin_addr.s_addr = INADDR_ANY;
	src.sin_port = 0;

	if (bind(m_nSocket, (struct sockaddr*) &src, sizeof(src)) < 0) {
		snprintf(m_szMsg, sizeof m_szMsg - 1, "Error binding on port %d",
				m_nHostPort);
		return false;
	}

	return true;
}

// listen to the binded port
bool CSocket::listen(PAYLOAD &oPayload, int nTimeOut) {
	bool bRet = false;
	struct sockaddr_in src;
	int nRet = 0;
	socklen_t nSrcLen = 0;
	bool bTimeout = false;
	time_t currTime = time(NULL);

	bzero(&oPayload, sizeof(PAYLOAD));
	cout << ".";
	while ((nRet = recvfrom(m_nSocket, (void *) &oPayload, sizeof(PAYLOAD),
			MSG_DONTWAIT, (struct sockaddr*) &src, &nSrcLen)) < 0) {
		if ((nTimeOut) && ((time(NULL) - currTime) > nTimeOut)) {
			bTimeout = true;
			break;
		}
	}
	if (bTimeout == false)
		bRet = true;

	if (bRet) // so we don't have any error message
		strncpy(m_szMsg, "", sizeof m_szMsg);

	return bRet;
}

bool CSocket::send(const PAYLOAD &oPayload) {
	bool bRet = false;
	struct sockaddr_in dest;
	struct hostent *hp;
	int rval = 0;
	// 3. get destination parameters;
	dest.sin_family = AF_INET;
	hp = gethostbyname(m_szHostName);
	if (hp == NULL) {
		strncpy(m_szMsg, "Invalid host name passed.", sizeof m_szMsg);
		return false;
	}

	bcopy(hp->h_addr, &dest.sin_addr, hp->h_length);
	dest.sin_port = htons(m_nHostPort);

	// 4. send the packet.
	rval = sendto(m_nSocket, (void*) &oPayload, sizeof(PAYLOAD), 0,
			(struct sockaddr *) &dest, sizeof dest);
	if (rval < 0) {
		strncpy(m_szMsg, "Error sending packet ", sizeof m_szMsg);
	} else {
		strncpy(m_szMsg, "", sizeof m_szMsg);
		bRet = true;
	}
	return bRet;

}
bool CSocket::getIP(const char* szHostName, char* szIP, int nIPLen) {
	bool bRet = false;

	struct hostent *hp = gethostbyname(szHostName);
	struct sockaddr_in target;
	bcopy(hp->h_addr, &target.sin_addr, hp->h_length);

	int ipAddr = target.sin_addr.s_addr;
	try {
		snprintf(szIP, nIPLen, "%u.%u.%u.%u", (ipAddr & 0x000000ff), (ipAddr
				& 0x0000ff00) >> 8, (ipAddr & 0x00ff0000) >> 16, (ipAddr
				& 0xff000000) >> 24);

		bRet = true;
	} catch (...) {
	}

	return bRet;
}

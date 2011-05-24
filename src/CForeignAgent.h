/*
 * CAgent.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef CAGENT_H_
#define CAGENT_H_

#include "CSocket.h"

class CForeignAgent {
	// socket to listen incoming data.
	CSocket *m_pSockListen;
	// socket to send location updates
	CSocket *m_pSockSend;
	char m_szMN[MAX_PATH];
	int  m_nPort;
	// sequence numbers for sending
	int m_nSeqNum_send;
	// sequence numbers for receiving
	int m_nSeqNum_recv;
public:
	CForeignAgent(short nListenPort, const char* szSendHost, short nSendPort, short nType = CSocket::TYPE_UDP);
	virtual ~CForeignAgent();

	// its store and forward
	void startlistening();
};

#endif /* CAGENT_H_ */

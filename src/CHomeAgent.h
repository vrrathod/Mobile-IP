/*
 * CHomeAgent.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef CHOMEAGENT_H_
#define CHOMEAGENT_H_

#include "CSocket.h"
#include <map>

class CHomeAgent {
	// socket to listen incoming data.
	CSocket *m_pSockListenData;

	// socket to send location updates
	//map<const char*, CSocket*> m_mapSockets;
	CSocket* m_mapSockets[2];
	char     m_mapHostName[2][MAX_PATH];
	int		 m_mapPort[2];
	// connection type
	int m_nConnType;

	// current association of MN with FA
	int m_nFAID;

	// sequence numbers for sending
	int m_nSeqNum_send;
	// sequence numbers for receiving
	int m_nSeqNum_recv;
public:
	CHomeAgent(short nListenPort, short nType = CSocket::TYPE_UDP);
	virtual ~CHomeAgent();

	bool addForeignAgent(int id, const char* szHost, const short nPort);

	bool listenNForward();

};

#endif /* CHOMEAGENT_H_ */

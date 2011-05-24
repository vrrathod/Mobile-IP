/*
 * CMobileNode.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef CMOBILENODE_H_
#define CMOBILENODE_H_

#include "CSocket.h"

class CMobileNode {
	// socket to listen incoming data.
	CSocket *m_pSockListen;
	// socket to send location updates
	CSocket *m_pSockSend;
	// current fa
	int m_nCurrentFA;
	// sequence numbers for sending
	int m_nSeqNum_send;
	// sequence numbers for receiving
	int m_nSeqNum_recv;
public:
	CMobileNode(short nListenPort, const char* szSendHost, short nSendPort, short nType = CSocket::TYPE_UDP);
	virtual ~CMobileNode();

	void startlistening();

	void sendChange();

	// registration timeout, sec
	int m_nRegTimeOut;
};

#endif /* CMOBILENODE_H_ */

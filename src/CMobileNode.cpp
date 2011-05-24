/*
 * CMobileNode.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#include "CMobileNode.h"

CMobileNode::CMobileNode(short nListenPort, const char* szSendHost,
		short nSendPort, short nType) {
	m_nCurrentFA = 0;
	m_nRegTimeOut = 5; // seconds

	m_pSockListen = new CSocket(NULL, nListenPort, nType);

	if (m_pSockListen == NULL) {
		throw "[MobileNode] Failed to create listener socket";
	}

	m_pSockSend = new CSocket(szSendHost, nSendPort, nType);
	if (m_pSockSend == NULL) {
		delete m_pSockListen;
		m_pSockListen = NULL;
		throw "[MobileNode] Failed to create sender socket";
	}
}

CMobileNode::~CMobileNode() {

	if (m_pSockListen != NULL) {
		delete m_pSockListen;
		m_pSockListen = NULL;
	}
	if (m_pSockSend != NULL) {
		delete m_pSockSend;
		m_pSockSend = NULL;
	}
}

void CMobileNode::startlistening() {
	PAYLOAD oPayload;

	// it has to listen continuously
	// while listening, it may move from one FA to another
	// so it has to send the change notification every 5 sec
	if ((m_pSockListen == NULL) || (m_pSockListen->bindToListen() == false))
		return;

	if ((m_pSockSend == NULL) || (m_pSockSend->bindToSend() == false))
		return;

	time_t start = time(NULL);
	do {
		bzero(&oPayload, sizeof oPayload);
		// lets give time out to 5 sec. this will allow us to send
		// registration packets even if mn is not receiving data.
		if (m_pSockListen->listen(oPayload, m_nRegTimeOut)) {
			oPayload.print();
		}

		if ((time(NULL) - start) % m_nRegTimeOut== 0) {
			// send change notification.
			cout <<"Registration changed. " << endl ;
			sendChange();
		}

	} while (true);
}

void CMobileNode::sendChange() {
	PAYLOAD oPayload;
	oPayload.cType = PAYLOAD_TYPE_REG;

	oPayload.nSeq = ++m_nSeqNum_send;
	m_nCurrentFA ^= 1;
	oPayload.nData = m_nCurrentFA;
	// alter between 0 and 1. //0 = FA0, 1 = FA1
	m_pSockSend->send(oPayload);
}

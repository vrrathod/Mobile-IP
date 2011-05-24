/*
 * CForeignAgent.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#include "CForeignAgent.h"

CForeignAgent::CForeignAgent(short nListenPort, const char* szSendHost, short nSendPort,
		short nType) {
	m_pSockListen = new CSocket(NULL, nListenPort, nType);

	if (m_pSockListen == NULL) {
		throw "[Agent] Failed to create listener socket";
	}

	m_pSockSend = new CSocket(szSendHost, nSendPort, nType);
	if (m_pSockSend == NULL) {
		delete m_pSockListen;
		m_pSockListen = NULL;
		throw "[Agent] Failed to create sender socket";
	}
	//strncpy(m_szMN, szSendHost, sizeof (m_szMN));
	CSocket::getIP(szSendHost, m_szMN, sizeof m_szMN);
	m_nPort = nSendPort;
}

CForeignAgent::~CForeignAgent() {
	if (m_pSockListen != NULL) {
		delete m_pSockListen;
		m_pSockListen = NULL;
	}
	if (m_pSockSend != NULL) {
		delete m_pSockSend;
		m_pSockSend = NULL;
	}
}

void CForeignAgent::startlistening() {
	PAYLOAD oPayload;

	// it has to listen continuously
	// while listening, it may move from one FA to another
	// so it has to send the change notification every 5 sec
	if ((m_pSockListen == NULL) || (m_pSockListen->bindToListen() == false))
		return;

	if ((m_pSockSend == NULL) || (m_pSockSend->bindToSend() == false))
		return;

	do {
		bzero(&oPayload, sizeof oPayload);
		if (m_pSockListen->listen(oPayload)) {
			cout << "Forwarded to : " << m_szMN << "/" << m_nPort << " -> ";
			oPayload.print();
			m_pSockSend->send(oPayload);
		}
	} while (true);
}

/*
 * CHomeAgent.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#include "CHomeAgent.h"

CHomeAgent::CHomeAgent(short nListenPort, short nType) {
	m_pSockListenData = new CSocket(NULL, nListenPort, nType);
	m_nConnType = nType;
	m_nFAID = 0;

	if (m_pSockListenData == NULL) {
		throw "[Agent] Failed to create listener socket";
	}
}

CHomeAgent::~CHomeAgent() {
	if (m_pSockListenData != NULL) {
		delete m_pSockListenData;
		m_pSockListenData = NULL;
	}

	delete m_mapSockets[0];
	m_mapSockets[0] = NULL;

	delete m_mapSockets[1];
	m_mapSockets[1] = NULL;
}

bool CHomeAgent::addForeignAgent(int id, const char* szHost, short nPort) {
	if (szHost && id < 2) {
		CSocket *pSock = new CSocket(szHost, nPort, m_nConnType);
		if (pSock != NULL) {
			pSock->bindToSend();
			m_mapSockets[id] = pSock;
			// store info
			CSocket::getIP(szHost, m_mapHostName[id], sizeof m_mapHostName[id]);
			m_mapPort[id] = nPort;
			return true;
		}
	}
	return false;
}

bool CHomeAgent::listenNForward() {

	if ((m_pSockListenData == NULL) || (m_pSockListenData->bindToListen()
			== false))
		return false;

	PAYLOAD oPayload;

	do {
		bzero(&oPayload, sizeof oPayload);
		if (m_pSockListenData->listen(oPayload)) {
			// check payload type
			if (oPayload.cType == PAYLOAD_TYPE_REG) {
				m_nFAID = oPayload.nData;
				cout << "registration changed to FA" << m_nFAID << endl;
			} else {
				cout << "Forwarded to : " << m_mapHostName[m_nFAID] << "/"
						<< m_mapPort[m_nFAID] << " ->d ";
				m_mapSockets[m_nFAID]->send(oPayload);
				oPayload.print();
			}
		}
	} while (true);
}

/*
 * CDataSource.cpp
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#include "CDataSource.h"

CDataSource::CDataSource(const char* szHost, short nPort, short nType) {
	CSocket::getIP(szHost, m_szHostName, sizeof m_szHostName);
	m_nPort = nPort;
	m_pSocket = new CSocket(szHost, nPort, nType);
	if (m_pSocket == NULL)
		throw "Failed to create Data source object";
	m_nSeqNum = 0;
}

CDataSource::~CDataSource() {
	if (m_pSocket != NULL) {
		// in case of valid sockets,
		// clean up
		delete m_pSocket;
		m_pSocket = NULL;
	}
}

void CDataSource::startSending() {
	PAYLOAD oPayload;
	oPayload.cType = PAYLOAD_TYPE_DATA;
	if ((m_pSocket == NULL) || (m_pSocket->bindToSend() == false)) {
		cout << "Failed to bind";
		return;
	}

	do {
		oPayload.nSeq = ++m_nSeqNum;
		oPayload.nData = time(NULL);

		if (m_pSocket->send(oPayload)) {
			cout << "sending : to :" << m_szHostName << "/" << m_nPort << ": ->";
			oPayload.print();
			sleep(1);
		}
	} while (true);
}

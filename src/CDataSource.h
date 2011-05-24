/*
 * CDataSource.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef CDATASOURCE_H_
#define CDATASOURCE_H_

#include "CSocket.h"

// a data source sends packet at a regular interval
// it should require a host & port #
class CDataSource {
	// socket to communicate
	CSocket *m_pSocket;
	// sequence numbers
	int m_nSeqNum;
	// host name
	char m_szHostName[MAX_PATH];
	// port number
	int m_nPort;
public:
	CDataSource(const char* szHost, short nPort, short nType = CSocket::TYPE_UDP);
	virtual ~CDataSource();

	void startSending();
};

#endif /* CDATASOURCE_H_ */

/*
 * Structures.h
 *
 *  Created on: Jun 2, 2010
 *      Author: viral
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include "IncludeFile.h"

static const int MAX_PATH = 256;

static const int PAYLOAD_TYPE_DATA = 0;
static const int PAYLOAD_TYPE_REG = 1;

typedef struct _payload {
	int nSeq;
	char cType;
	int nData;

	_payload() :
		nSeq(0), cType(0), nData(0) {
	}
	_payload(int a, char b, int c) :
		nSeq(a), cType(b), nData(c) {
	}

	void print() {
		char *pcTime = gettimeofday_1(nData);
		cout << "Time: [" << pcTime << "] Seq = " << nSeq << endl;
				// " : Type = " << getTypeName(cType)
				// << ": Data = " << nData << endl;
		delete pcTime;
		pcTime = NULL;
	}

	char * gettimeofday_1(int nTime) {
		int lTime = nTime % (24*3600);

		// to adjust to PDT, GMT - 7 hrs
		lTime -= (7*3600);

		int lHr = lTime / 3600;  lTime %= 3600;

		int lMin = lTime / 60;    lTime %= 60;

		int lSec =lTime;

		char *pTime = new char[10];
		sprintf(pTime, "%0d:%0d:%0d", lHr, lMin, lSec);
		return pTime;
	}

	inline const char* getTypeName(char type) {
		switch (type) {
		case PAYLOAD_TYPE_DATA:
			return "PAYLOAD_TYPE_DATA";
			break;
		case PAYLOAD_TYPE_REG:
			return "PAYLOAD_TYPE_REG";
			break;
		}
	}
} PAYLOAD;

#endif /* STRUCTURES_H_ */

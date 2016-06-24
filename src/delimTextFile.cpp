#include "delimTextFile.h"

#include <iostream>
#include "misc/debugMsgs.h"

delimTextFile::delimTextFile() {
}

delimTextFile::delimTextFile(string strFilename, char delim, char qualifier) :	textFile(strFilename),
																									m_chDelim(delim),
																									m_chQualifier(qualifier) {
}

bool delimTextFile::open(string strFilename, char delim, char qualifier) {
	m_chDelim = delim;
	m_chQualifier = qualifier;
	return textFile::open(strFilename);
}

bool delimTextFile::getNextRow(delimTextRow* pRow) {
	bool rv = false;

	if (pRow) {	
		string strData;
		if (textFile::getNextRow(&strData)) {
			pRow->setData(strData);
			pRow->setDelim(m_chDelim);
			pRow->setQualifier(m_chQualifier);
			rv = true;
		} else {
			DEBUG_ERROR("delimTextFile::getNextRow() Failure getting line of data.");
		}
	} else {
		DEBUG_ERROR("delimTextFile::getNextRow() Invalid destination row pointer.");
	}

	return rv;
}

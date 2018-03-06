// Copyright 2007 Matthew A. Kucenski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// #define _DEBUG_
#include "misc/debugMsgs.h"
#include "misc/errMsgs.h"

#include "delimTextFile.h"

#include <iostream>

delimTextFile::delimTextFile() {
}

delimTextFile::delimTextFile(string strFilename, char delim, char qualifier) :	textFile(strFilename),
																											m_chDelim(delim),
																											m_chQualifier(qualifier) {
}

bool delimTextFile::open(string strFilename, char delim, char qualifier) {
	bool rv = false;
	m_chDelim = delim;
	m_chQualifier = qualifier;
	if (textFile::open(strFilename)) {
		rv = true;
	} else {
		ERROR("delimTextFile::open() Failure opening file.");
	}

	return rv;
}

bool delimTextFile::setHeader(string strHeader) {
	bool rv = false;

	if (strHeader.length() > 0) {
		rv = m_clsHeader.loadRow(strHeader, m_chDelim, m_chQualifier);
	} else {
		ERROR("delimTextFile::loadFirstRow() Zero-length header row.");
	}

	return rv;
}

bool delimTextFile::getNextRow(delimTextRow* pRow) {
	bool rv = false;

	if (pRow) {	
		string strData;
		if (textFile::getNextRow(&strData)) {
			rv = pRow->loadRow(strData, m_chDelim, m_chQualifier);
		} else {
			ERROR("delimTextFile::getNextRow() Failure getting line of data.");
		}
	} else {
		ERROR("delimTextFile::getNextRow() Invalid destination row pointer.");
	}

	return rv;
}


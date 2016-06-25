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

// Copyright 2016 Matthew A. Kucenski
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

#include "textFile.h"

#include <iostream>
#include "misc/debugMsgs.h"

textFile::textFile()	:	m_pFilestream(NULL),
								m_pInputstream(NULL) {
}

textFile::textFile(string strFilename)	:	m_pFilestream(NULL),
													m_pInputstream(NULL) {
	open(strFilename);
}

bool textFile::open(string strFilename) {
	bool rv = false; 
	
	if (close()) {
		m_pFilestream = NULL;
		m_pInputstream = NULL;
	
		if (strFilename.length() > 0) {
			m_pFilestream = new ifstream(strFilename.c_str(), fstream::in);
			if (!m_pFilestream->fail()) {
				m_pInputstream = m_pFilestream;
				rv = true;
			} else {
				DEBUG_ERROR("textFile::open() Failure opening file stream for " << (strFilename.length() > 0 ? strFilename : "STDIN") << ".");
			}
		} else {
			m_pInputstream = &cin;
			rv = true;
		}
	} else {
		DEBUG_ERROR("textFile::open() Failure closing previous file stream.");
	}
	
	return rv;	
}

bool textFile::close() {
	bool rv = true;
	
	if (m_pFilestream && m_pFilestream->is_open()) {
		m_pFilestream->close();
		if (m_pFilestream->fail()) {
			rv = false;
			DEBUG_ERROR("textFile::close() Failure closing file stream.");
		}
		delete m_pFilestream;
		m_pFilestream = NULL;
	}
	
	return rv;
}

textFile::~textFile() {
	close();
}

bool textFile::getNextRow(string* pStr) {
	bool rv = false;
	
	if (m_pInputstream) {
		if (pStr) {
			*pStr = "";
			char buffer[256];
			while (m_pInputstream->good()) {
				char peekChar = m_pInputstream->peek();
				if (peekChar == '\n') {								//TODO This should handle more than just \n, it should handle DOS, UNIX, Mac line endings.
					m_pInputstream->read(buffer, 1);
					break;
				} else if (peekChar == -1) {
					break;
				} else {
					m_pInputstream->get(buffer, 256, '\n');
					if (!m_pInputstream->fail()) {
						pStr->append(buffer);
					} else {
						DEBUG_ERROR("textFile::getNextRow() Failure reading data into buffer.");
					}
				}
			}
			
			if (pStr->length() > 0) {
				rv = true;
			} else {
				DEBUG_WARNING("textFile::getNextRow() Zero length string.");
			}
		} else {
			DEBUG_ERROR("textFile::getNextRow() Invalid destination pointer.");
		}
	} else {
		DEBUG_ERROR("textFile::getNextRow() Invalid file pointer.");
	}

	return rv;
}

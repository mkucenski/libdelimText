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

#include "textFile.h"
#include "textUtils.h"

#include <iostream>
using namespace std;

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
				ERROR("textFile::open() Failure opening file stream for " << (strFilename.length() > 0 ? strFilename : "STDIN") << ".");
			}
		} else {
			m_pInputstream = &cin;
			rv = true;
		}
	} else {
		ERROR("textFile::open() Failure closing previous file stream.");
	}
	
	return rv;	
}

bool textFile::close() {
	bool rv = true;
	
	if (m_pFilestream && m_pFilestream->is_open()) {
		m_pFilestream->close();
		if (m_pFilestream->fail()) {
			rv = false;
			ERROR("textFile::close() Failure closing file stream.");
		}
		delete m_pFilestream;
		m_pFilestream = NULL;
	}
	m_pInputstream = NULL;
	
	return rv;
}

textFile::~textFile() {
	close();
}

bool textFile::getNextRow(string* pStr) {
	bool rv = false;

	if (m_pInputstream) {
		if (pStr) {
			string strRow;
			readline(*m_pInputstream, strRow);
			if (strRow.length() > 0) {
				*pStr = strRow;
				rv = true;
			}
		} else {
			ERROR("textFile::getNextRow() Invalid destination pointer.");
		}
	} else {
		ERROR("textFile::getNextRow() Invalid file pointer.");
	}

	return rv;
}

bool textFile::getFirstRow(string* pStr) {
	bool rv = false;

	if (m_pInputstream) {
		// Save the current file position
		u_int64_t rpos = m_pInputstream->tellg();
		if (rpos != -1) {
			// Move to the beginning of the file
			m_pInputstream->seekg(0, m_pInputstream->beg);
			if (!m_pInputstream->eof() && !m_pInputstream->fail()) {
				// Get the first row
				rv = getNextRow(pStr);

				// Move back to the original file position
				m_pInputstream->seekg(rpos, m_pInputstream->beg);
				if (m_pInputstream->eof() || m_pInputstream->fail()) {
					ERROR("textFile::getFirstRow() Unable to return to previous position of file.");
				}
			} else {
				ERROR("textFile::getFirstRow() Unable to move to beginning of file.");
			}
		} else {
			ERROR("textFile::getFirstRow() Unable to store current file position.");
		}
	} else {
		ERROR("textFile::getFirstRow() Invalid file pointer.");
	}

	return rv;
}


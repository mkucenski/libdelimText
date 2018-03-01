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

#ifndef _DELIMTEXTFILE_H_
#define _DELIMTEXTFILE_H_

#include "textFile.h"
#include "delimTextRow.h"

#include <string>
#include <fstream>
using namespace std;

class delimTextFile : public textFile {
	public:
		delimTextFile();
		delimTextFile(string strFilename, char delim, char qualifier = '\0');
		
		bool open(string strFilename, char delim, char qualifier = '\0');
				
		delimTextRow getHeader() { return m_clsHeader; };
		bool setHeader(string strHeader);

		bool getColumnByName(string strName, int* p_iColumn) { return m_clsHeader.getColumnByValue(strName, p_iColumn); };
		int getColumnByName(string strName) { int rv = -1; getColumnByName(strName, &rv); return rv; };

		bool getNextRow(delimTextRow* pRow);
	
	private:
		char m_chDelim;
		char m_chQualifier;
		delimTextRow m_clsHeader;
};

#endif //_DELIMTEXTFILE_H_

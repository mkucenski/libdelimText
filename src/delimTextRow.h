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

#ifndef _DELIMTEXTROW_HPP_
#define _DELIMTEXTROW_HPP_

#include <string>
using namespace std;

class delimTextRow {
	public:
		delimTextRow();
		delimTextRow(string strData, char delim, char qualifier = NULL);
		delimTextRow(delimTextRow* pDelimTextRowObj);// { m_DelimChar = pDelimTextRowObj->m_DelimChar; m_strData = pDelimTextRowObj->m_strData; m_TextQualifier = pDelimTextRowObj->m_TextQualifier; };
		~delimTextRow();
		
		string getData() { return m_strData; };
		bool getData(string* pstrData);
		bool setData(string& strData) { m_strData = strData; return true; };
		
		char getDelim() { return m_chDelim; };
		bool getDelim(char* pDelim);
		bool setDelim(char delim);

		char getQualifier() { return m_chQualifier; };
		bool getQualifier(char* pQualifier);
		bool setQualifier(char qualifier);

		unsigned int getFieldCount();
		bool getFieldCount(unsigned int* pCount);

		string getField(unsigned int field);
		bool getField(unsigned int field, string* pstrValue);
		
		long getFieldAsLong(unsigned int field);
		bool getFieldAsLong(unsigned int field, long* plValue);

	private:
		char m_chDelim;
		char m_chQualifier;
		string m_strData;
};

#endif //_DELIMTEXTROW_H_

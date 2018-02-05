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

//#define _DEBUG_

#ifndef _DELIMTEXTROW_HPP_
#define _DELIMTEXTROW_HPP_

#include <string>
using namespace std;

class delimTextRow {
	public:
		delimTextRow();
		delimTextRow(string strData, char delim, char qualifier = '\0');
		delimTextRow(delimTextRow* pDelimTextRowObj);
		~delimTextRow();
		
		bool getData(string* pstrData);
		string getData() { return m_strData; };
		bool getDelim(char* pDelim);
		char getDelim() { return m_chDelim; };
		bool getQualifier(char* pQualifier);
		char getQualifier() { return m_chQualifier; };

		bool loadRow(string strData, char delim, char qualifier = '\0') { setData(strData); setDelim(delim); setQualifier(qualifier); return true; };
		bool setData(string& strData) { m_strData = strData; return true; };
		bool setDelim(char delim) { m_chDelim = delim; return true; };
		bool setQualifier(char qualifier) {m_chQualifier = qualifier; return true; };

		unsigned int getColumnCount() { unsigned int rv = 0; getColumnCount(&rv); return rv; };
		bool getColumnCount(unsigned int* p_iCount);

		string getValue(unsigned int iColumn) { string rv; getValue(iColumn, &rv); return rv; };
		bool getValue(unsigned int iColumn, string* p_strValue);
		
		long getValueAsLong(unsigned int iColumn) { long rv = 0; getValueAsLong(iColumn, &rv); return rv; };
		bool getValueAsLong(unsigned int iColumn, long* p_lValue);

		unsigned int getColumnByValue(string strValue) { unsigned int rv = 0; getColumnByValue(strValue, &rv); return rv; };
		bool getColumnByValue(string strValue, unsigned int* p_iColumn);

		//DEPRECATED; keep for backward compatibility. Nomenclature of column/value is more descriptive and clear.
		string getField(unsigned int field) { return getValue(field); };
		bool getField(unsigned int field, string* pstrValue) { return getValue(field, pstrValue); };
		long getFieldAsLong(unsigned int field) { return getValueAsLong(field); };
		bool getFieldAsLong(unsigned int field, long* plValue) { return getValueAsLong(field, plValue); };
		unsigned int getFieldCount() { return getColumnCount(); };
		bool getFieldCount(unsigned int* pCount) { return getColumnCount(pCount); };

	private:
		char m_chDelim;
		char m_chQualifier;
		string m_strData;
};

#endif //_DELIMTEXTROW_H_

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

#include "delimTextRow.h"

#include "delimTextFile.h"
#include "boost/lexical_cast.hpp"

delimTextRow::delimTextRow() {
}

delimTextRow::delimTextRow(string strData, char delim, char qualifier)	:	m_chDelim(delim),
																									m_chQualifier(qualifier),
																									m_strData(strData) {
}

delimTextRow::delimTextRow(delimTextRow* pDelimTextRowObj)	:	m_chDelim(pDelimTextRowObj->m_chDelim),
																					m_chQualifier(pDelimTextRowObj->m_chQualifier),
																					m_strData(pDelimTextRowObj->m_strData) {
}

delimTextRow::~delimTextRow() {
}
		
bool delimTextRow::getValue(int iColumn, string* p_strValue) {
	DEBUG("delimTextRow::getValue(int iColumn = " << iColumn << ", string* p_strValue" << *p_strValue << ")"); 

	bool rv = false;
	
	if (iColumn >= 0) {
		DEBUG("delimTextRow::getValue() m_chDelim: '" << m_chDelim << "'");
		DEBUG("delimTextRow::getValue() m_chQualifier: '" << m_chQualifier << "'");
	
		if (p_strValue) {
			char searchFor[3];
			searchFor[0] = m_chDelim;
			searchFor[1] = m_chQualifier;
			searchFor[2] = '\0';
			
			//TODO	This code should be smarter with qualifiers.  For example 'test|"testing"tes|ting"|test' will fail because there is a lone '"' in the middle of a field.
			//			I think that the qualifier search should be looking for delimiter/qualifier pairs.  For example '|"' and '"|'.  Lone qualifiers should not count... Maybe...
			
			//TODO	Also, this code should not include the qualifiers in the output.  The qualifiers should be considered formatting characters that define the fields, not
			//			part of the field data.  They should be filtered out... Maybe...
			
			DEBUG("delimTextRow::getValue() Searching for column" + boost::lexical_cast<string>(iColumn) + " within <" + m_strData + ">; length = " << m_strData.length() << ".");
			
			size_t beginPos = 0;
			for (unsigned int i=0; i<iColumn; i++) {										//Loop past all of the previous columns to the one requested
				beginPos = m_strData.find_first_of(searchFor, beginPos);
				if (beginPos != string::npos) {
					if (m_strData[beginPos] == m_chQualifier) {						//If I find a qualifier
						beginPos = m_strData.find(m_chQualifier, beginPos+1);		//Then nothing else counts until I find the closing qualifier
						if (beginPos != string::npos) {
							beginPos = m_strData.find(m_chDelim, beginPos+1);		//Now find the next delimiter
							if (beginPos != string::npos) {
								beginPos++;														//Increase by one to the beginning of the requested column 
							} else {
								break;
							}
						} else {
							break;
						}
					} else {																		//If I found a delimiter
						beginPos++;																//Then increase by one to the beginning of the requested column
					}
				} else {
					break;
				}
			}
			
			DEBUG("delimTextRow::getValue() Found column" + boost::lexical_cast<string>(iColumn) + "; searching for end of column...");
	
			if (beginPos != string::npos) {
				size_t endPos = m_strData.find_first_of(searchFor, beginPos);
				DEBUG("delimTextRow::getValue() Starting @ " << beginPos << " found first indicator @ " << endPos); 
				if (endPos != string::npos) {
					if (m_strData[endPos] == m_chQualifier) {							//If I find a qualifier
						endPos = m_strData.find(m_chQualifier, endPos+1);			//Then nothing else counts until I find the closing qualifier
						if (endPos != string::npos) {
							endPos = m_strData.find(m_chDelim, endPos+1);			//Now find the next delimiter to mark the end of this column 
							if (endPos != string::npos) {
								*p_strValue = m_strData.substr(beginPos, endPos-beginPos);
							} else {
								*p_strValue = m_strData.substr(beginPos);
							}
						} else {
							*p_strValue = m_strData.substr(beginPos);
						}
					} else {
						*p_strValue = m_strData.substr(beginPos, endPos-beginPos);
					}
				} else {
					*p_strValue = m_strData.substr(beginPos);
				}
				DEBUG("delimTextRow::getValue() Retrieved string <" + *p_strValue + ">.");			
				rv = true;
			} else {
				DEBUG("delimTextRow::getValue() Not enough columns in this row to retrieve the requested column.");
			}
		} else {
			ERROR("delimTextRow::getValue() Invalid destination pointer.");
		}
	} else {
		DEBUG("delimTextRow::getValue() Invalid column value (" << iColumn << ")");
	}

	return rv;
}

bool delimTextRow::getValueAsLong(int iColumn, long* p_lValue) {
	DEBUG("delimTextRow::getValueAsLong(" << iColumn << ")");

	bool rv = false;
	
	if (p_lValue) {
		string strValue;
		if (getValue(iColumn, &strValue)) {
			if (strValue.length() > 0) {
				*p_lValue = strtol(strValue.c_str(), NULL, 10);
				rv = true;
			} else {
				DEBUG("delimTextRow::getValueAsLong() Zero length string.");
			}
		} else {
			ERROR("delimTextRow::getValueAsLong() Failure retrieving string value.");
		}
	} else {
		ERROR("delimTextRow::getValueAsLong() Invalid destination pointer.");
	}

	return rv;
}

bool delimTextRow::getColumnCount(unsigned int* pCount) {
	DEBUG("delimTextRow::getColumnCount(unsigned int* pCount)"); 
	bool rv = false;

	if (pCount) {
		*pCount = 0;
		string strTmp;
		while (getValue(*pCount, &strTmp)) {
			(*pCount)++;
		}
		rv = true;
	} else {
		ERROR("delimTextRow::getColumnCount() Invalid destination pointer.");
	}

	DEBUG("delimTextRow::getColumnCount(unsigned int* pCount) -> rv = " << rv << "; pCount = " << *pCount); 
	return rv;
}

bool delimTextRow::getData(string* p_strData) { 
	bool rv = false;

	if (p_strData) {
		*p_strData = m_strData; 
		rv = true;
	} else {
		ERROR("delimTextRow::getData() Invalid destination pointer.");
	}

	return rv;
};

bool delimTextRow::getDelim(char* pDelim) { 
	bool rv = false;
	
	if (pDelim) {
		*pDelim = m_chDelim; 
		rv = true; 
	} else {
		ERROR("delimTextRow::getDelim() Invalid destination pointer.");
	}
	
	return rv;
}

bool delimTextRow::getQualifier(char* pQualifier) {
	bool rv = false;
	
	if (pQualifier) {
		*pQualifier = m_chQualifier; 
		rv = true; 
	} else {
		ERROR("delimTextRow::getQualifier() Invalid destination pointer.");
	}
	
	return rv;
}

bool delimTextRow::getColumnByValue(string strValue, int* p_iColumn) {
	DEBUG("delimTextRow::getColumnByValue(string strValue = " << strValue << ", int* p_iColumn = " << *p_iColumn << ")"); 

	bool rv = false;

	for (int i=0; i<getColumnCount(); i++) {
		if (strValue == getValue(i)) {
			*p_iColumn = i;
			rv = true;
			break;
		}
	}

	DEBUG("delimTextRow::getColumnByValue(string strValue = " << strValue << ", int* p_iColumn = " << *p_iColumn << ") -> rv = " << rv << "; p_iColumn = " << *p_iColumn); 
	return rv;
}


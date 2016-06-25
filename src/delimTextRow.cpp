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

#include "delimTextRow.h"

#include "boost/lexical_cast.hpp"

#include "misc/debugMsgs.h"

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
		
bool delimTextRow::getField(unsigned int field, string* pstrValue) {
	bool rv = false;
	
	DEBUG_INFO("delimTextRow::getField() m_chDelim: '" << m_chDelim << "'");
	DEBUG_INFO("delimTextRow::getField() m_chQualifier: '" << m_chQualifier << "'");
	
	if (pstrValue) {
		char searchFor[3];
		searchFor[0] = m_chDelim;
		searchFor[1] = m_chQualifier;
		searchFor[2] = '\0';
		
		//TODO	This code should be smarter with qualifiers.  For example 'test|"testing"tes|ting"|test' will fail because there is a lone '"' in the middle of a field.
		//			I think that the qualifier search should be looking for delimiter/qualifier pairs.  For example '|"' and '"|'.  Lone qualifiers should not count... Maybe...
		
		//TODO	Also, this code should not include the qualifiers in the output.  The qualifiers should be considered formatting characters that define the fields, not
		//			part of the field data.  They should be filtered out... Maybe...
		
		DEBUG_INFO("delimTextRow::getField() Searching for field " + boost::lexical_cast<string>(field) + " within <" + m_strData + ">.");
		
		unsigned int beginPos = 0;
		for (unsigned int i=0; i<field; i++) {										//Loop past all of the previous fields to the one requested
			beginPos = m_strData.find_first_of(searchFor, beginPos);
			if (beginPos != string::npos) {
				if (m_strData[beginPos] == m_chQualifier) {						//If I find a qualifier
					beginPos = m_strData.find(m_chQualifier, beginPos+1);		//Then nothing else counts until I find the closing qualifier
					if (beginPos != string::npos) {
						beginPos = m_strData.find(m_chDelim, beginPos+1);		//Now find the next delimiter
						if (beginPos != string::npos) {
							beginPos++;														//Increase by one to the beginning of the requested field
						} else {
							break;
						}
					} else {
						break;
					}
				} else {																		//If I found a delimiter
					beginPos++;																//Then increase by one to the beginning of the requested field
				}
			} else {
				break;
			}
		}
		
		if (beginPos != string::npos) {
			unsigned int endPos = m_strData.find_first_of(searchFor, beginPos);
			if (endPos != string::npos) {
				if (m_strData[endPos] == m_chQualifier) {							//If I find a qualifier
					endPos = m_strData.find(m_chQualifier, endPos+1);			//Then nothing else counts until I find the closing qualifier
					if (endPos != string::npos) {
						endPos = m_strData.find(m_chDelim, endPos+1);			//Now find the next delimiter to mark the end of this field
						if (endPos != string::npos) {
							*pstrValue = m_strData.substr(beginPos, endPos-beginPos);
						} else {
							*pstrValue = m_strData.substr(beginPos);
						}
					} else {
						*pstrValue = m_strData.substr(beginPos);
					}
				} else {
					*pstrValue = m_strData.substr(beginPos, endPos-beginPos);
				}
			} else {
				*pstrValue = m_strData.substr(beginPos);
			}
			DEBUG_INFO("delimTextRow::getField() Retrieved string <" + *pstrValue + ">.");			
			rv = true;
		} else {
			DEBUG_INFO("delimTextRow::getField() Not enough fields in this row to retrieve the requested field.");
		}
	} else {
		DEBUG_ERROR("delimTextRow::getField() Invalid destination pointer.");
	}
	
	return rv;
}

bool delimTextRow::getFieldAsLong(unsigned int field, long* plValue) {
	bool rv = false;
	
	if (plValue) {
		string strValue;
		if (getField(field, &strValue)) {
			if (strValue.length() > 0) {
				*plValue = strtol(strValue.c_str(), NULL, 10);
				rv = true;
			} else {
				DEBUG_WARNING("delimTextRow::getFieldAsLong() Zero length string.");
			}
		} else {
			DEBUG_ERROR("delimTextRow::getFieldAsLong() Failure retrieving string value.");
		}
	} else {
		DEBUG_ERROR("delimTextRow::getFieldAsLong() Invalid destination pointer.");
	}

	return rv;
}

string delimTextRow::getField(unsigned int field) {
	string rv;
	getField(field, &rv);
	return rv;
}

long delimTextRow::getFieldAsLong(unsigned int field) {
	long rv = 0;
	getFieldAsLong(field, &rv);
	return rv;
}

bool delimTextRow::getFieldCount(unsigned int* pCount) {
	bool rv = false;

	if (pCount) {
		*pCount = 0;
		string strTmp;
		while (getField(*pCount, &strTmp)) {
			(*pCount)++;
		}
		rv = true;
	} else {
		DEBUG_ERROR("delimTextRow::getFieldCount() Invalid destination pointer.");
	}

	return rv;
}

unsigned int delimTextRow::getFieldCount() {
	unsigned int rv = 0;
	getFieldCount(&rv);
	return rv;
}

bool delimTextRow::getData(string* pstrData) { 
	bool rv = false;

	if (pstrData) {
		*pstrData = m_strData; 
		rv = true;
	} else {
		DEBUG_ERROR("delimTextRow::getData() Invalid destination pointer.");
	}

	return rv;
};

bool delimTextRow::getDelim(char* pDelim) { 
	bool rv = false;
	
	if (pDelim) {
		*pDelim = m_chDelim; 
		rv = true; 
	} else {
		DEBUG_ERROR("delimTextRow::getDelim() Invalid destination pointer.");
	}
	
	return rv;
}

bool delimTextRow::setDelim(char delim) { 
	m_chDelim = delim; 
	return true; 
}

bool delimTextRow::getQualifier(char* pQualifier) {
	bool rv = false;
	
	if (pQualifier) {
		*pQualifier = m_chQualifier; 
		rv = true; 
	} else {
		DEBUG_ERROR("delimTextRow::getQualifier() Invalid destination pointer.");
	}
	
	return rv;
}

bool delimTextRow::setQualifier(char qualifier) {
	m_chQualifier = qualifier; 
	return true; 
}

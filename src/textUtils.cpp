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

#include "textUtils.h"

#include "misc/debugMsgs.h"

string findSubString(const string& str, uint32_t uiStartPos, const string& strStartsWith, const string& strEndsWith, bool bInclusive) {
	string rv;
	
	if (str.length() > 0) {
		int startPos = uiStartPos;
		if (strStartsWith.length() > 0) {
			startPos = str.find(strStartsWith, uiStartPos);
		}
		if (startPos >= 0) {
			if (!bInclusive) {
				startPos += strStartsWith.length();
			}
			
			if (strEndsWith.length() > 0) {
				int endPos = str.find(strEndsWith, startPos);
				if (endPos > startPos) {
					if (bInclusive) {
						endPos += strEndsWith.length();
					}
					endPos--;
					
					rv = string(str, startPos, endPos - startPos + 1);
				} else {
					DEBUG_ERROR("textUtils::findSubString() Required ending string (" << strEndsWith << ") not found.");
				}
			} else {
				rv = string(str, startPos);
			}
		} else {
			DEBUG_WARNING("textUtils::findSubString() Starting string (" << strStartsWith << ") not found.");
		} 
	} else {
		DEBUG_ERROR("textUtils::findSubString() Search string has zero length.");
	}
	
	return rv;
}

string findSubString(const string& str, uint32_t uiStartPos, const string& strStartsWith, uint32_t uiLength, bool bInclusive) {
	string rv;
	
	if (str.length() > 0 && uiLength > 0) {
		int startPos = 0;
		if (strStartsWith.length() > 0) {
			startPos = str.find(strStartsWith, uiStartPos);
		}
		if (startPos >= 0) {
			if (!bInclusive) {
				startPos += strStartsWith.length();
			}
			
			rv = string(str, startPos, uiLength);
		} else {
			DEBUG_WARNING("textUtils::findSubString() Starting string (" << strStartsWith << ") not found.");
		} 
	} else {
		DEBUG_ERROR("textUtils::findSubString() Search string has zero length or requested length equals 0.");
	}
	
	return rv;
}

string stripQualifiers(const string& str, char chQualifier) {
	string rv;
	
	if (str.length() > 0 && chQualifier != '\0') {
		int startPos = 0;
		int endPos = str.length()-1;

		if (str.find(chQualifier, 0) == 0) {					//str starts with a qualifier
			startPos++;
		}

		if (str.find(chQualifier, endPos) == endPos) {		//str ends with a qualifier
			endPos--;
		}

		rv = string(str, startPos, endPos-startPos+1);

		if (startPos != 0 || endPos !=str.length()) {		//Changes were made, debug output
			DEBUG_INFO("Qualifiers Removed: Changing <" << str << "> to <" << rv << ">.");
		}

	} else {
		DEBUG_ERROR("textUtils::stripQualifiers() Search string has zero length or requested qualifier is NULL.");
	}
	
	return rv;
}

string addQualifiers(const string& str, char chQualifier) {
	return string(chQualifier + str + chQualifier);
}


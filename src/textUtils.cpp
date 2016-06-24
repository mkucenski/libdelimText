#include "textUtils.h"

#include "misc/debugMsgs.h"

string findSubString(const string& str, u_int32_t uiStartPos, const string& strStartsWith, const string& strEndsWith, bool bInclusive) {
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

string findSubString(const string& str, u_int32_t uiStartPos, const string& strStartsWith, u_int32_t uiLength, bool bInclusive) {
	string rv;
	
	if (str.length() > 0 && uiLength > 0) {
		int startPos = 0;
		if (strStartsWith.length() > 0) {
			str.find(strStartsWith, uiStartPos);
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

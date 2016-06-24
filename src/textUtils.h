#ifndef TEXTUTILS_H_
#define TEXTUTILS_H_

#include <string>
using namespace std;

string findSubString(const string& str, u_int32_t uiStartPos, const string& strStartsWith, const string& strEndsWith, bool bInclusive = false);
string findSubString(const string& str, u_int32_t uiStartPos, const string& strStartsWith, u_int32_t uiLength, bool bInclusive = false);

#endif /*TEXTUTILS_H_*/

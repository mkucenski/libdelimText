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

#ifndef TEXTUTILS_H_
#define TEXTUTILS_H_

#include <string>
using namespace std;

string findSubString(const string& str, uint32_t uiStartPos, const string& strStartsWith, const string& strEndsWith, bool bInclusive = false);
string findSubString(const string& str, uint32_t uiStartPos, const string& strStartsWith, uint32_t uiLength, bool bInclusive = false);

string stripQualifiers(const string& str, char chQualifier);
string addQualifiers(const string& str, char chQualifier);

#endif /*TEXTUTILS_H_*/

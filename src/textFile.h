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

#ifndef _TEXTFILE_H_
#define _TEXTFILE_H_

#include <string>
#include <fstream>
using namespace std;

class textFile {
	public:
		textFile();
		textFile(string strFilename);
		~textFile();
		
		bool open(string strFilename);
		bool close();
		
		bool getNextRow(string* pStr);
		string getNextRow() { string rv; getNextRow(&rv); return rv; };

		bool getFirstRow(string* pStr);
		string getFirstRow() { string rv; getFirstRow(&rv); return rv; };
	
	private:
		ifstream* m_pFilestream;
		istream* m_pInputstream;
};

#endif //_TEXTFILE_H_

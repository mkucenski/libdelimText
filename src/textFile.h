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
	
	private:
		ifstream* m_pFilestream;
		istream* m_pInputstream;
};

#endif //_TEXTFILE_H_

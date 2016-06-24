#ifndef _DELIMTEXTFILE_H_
#define _DELIMTEXTFILE_H_

#include "textFile.h"
#include "delimTextRow.h"

#include <string>
#include <fstream>
using namespace std;

class delimTextFile : public textFile {
	public:
		delimTextFile();
		delimTextFile(string strFilename, char delim, char qualifier = NULL);
		
		bool open(string strFilename, char delim, char qualifier = NULL);
				
		bool getNextRow(delimTextRow* pRow);
	
	private:
		char m_chDelim;
		char m_chQualifier;
};

#endif //_DELIMTEXTFILE_H_

// Parser.h: interface for the Parser class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_PARSER_H__D34ED5EE_2FF9_433B_97ED_6AAFB48C80CB__INCLUDED_)
//#define AFX_PARSER_H__D34ED5EE_2FF9_433B_97ED_6AAFB48C80CB__INCLUDED_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#ifndef __PARSER_H
#define __PARSER_H

#include "PTBlock.h"
#include <vector>
#include <stack>
#include "Scanner.h"	// Added by ClassView
#include "CodeGenerator.h"	// Added by ClassView
#include "stack"
using namespace std;
class Parser  
{
public:

	Parser(char* PTFilename, char* inputFile);
	virtual ~Parser();
	void	Parse();
    stack<string> ss;
private:
	CodeGenerator m_CodeGenerator;
	Scanner* m_Scanner;
	int FindSymbolID(string symbol);
	typedef vector<PTBlock*> PTBLOCKVECTOR;
	typedef vector<PTBLOCKVECTOR> PTType;
	typedef vector<string> STRINGVECTOR;
	typedef stack<int> INTSTACK;
	char* m_PTFile;
	PTType m_ParseTable;
	STRINGVECTOR m_SymbolNames;
	INTSTACK m_ParseStack;
	void LoadPT();
};

class CParseErrorException
{
	// Add your code here to enrich CParseErrorException (Optional)
public:
	CParseErrorException();
};

#endif // !defined(AFX_PARSER_H__D34ED5EE_2FF9_433B_97ED_6AAFB48C80CB__INCLUDED_)

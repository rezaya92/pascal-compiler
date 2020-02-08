// Scanner.h: interface for the Scanner class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_SCANNER_H__AC71A705_D73F_40AF_B0E7_1C253EAC7016__INCLUDED_)
//#define AFX_SCANNER_H__AC71A705_D73F_40AF_B0E7_1C253EAC7016__INCLUDED_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#ifndef __SCANNER_H
#define __SCANNER_H

#include <FlexLexer.h>
#include <fstream>
using namespace std;

class Scanner  
{
public:
	static string text;
	string NextToken();
	Scanner(char* filename);
	virtual ~Scanner();

private:
	ifstream inF;
	char* m_InputFile;
	FlexLexer* lexer; 
};

#endif // !defined(AFX_SCANNER_H__AC71A705_D73F_40AF_B0E7_1C253EAC7016__INCLUDED_)

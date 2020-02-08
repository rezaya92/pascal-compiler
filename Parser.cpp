#ifndef __PGEN_PARSER__
#define __PGEN_PARSER__
// Parser.cpp: implementation of the Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "Parser.h"
#include <fstream>
#include <iostream>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Parser::~Parser()
{
	delete m_Scanner;
}

stack<int> ps;
string Scanner::text = "init";

Parser::Parser(char* PTFile, char* inputFile)
{
	m_PTFile = PTFile;
	m_Scanner = new Scanner(inputFile);
	cout << "here";
	LoadPT();
}

void Parser::LoadPT()
{
	ifstream inF(m_PTFile);
	int rowSize, colSize, i, j;
	ACTIONTYPE action;
	int tmpAction;
	int index;
	string sem;
	
	inF >> rowSize >> colSize;
	m_SymbolNames.reserve(colSize);
	for(i = 0; i < colSize; i++) {
		string symbol;
		inF >> symbol;
		m_SymbolNames.push_back(symbol);
		cout << i <<": " << symbol << endl;
	}

	m_ParseTable.resize(rowSize);
	for(i = 0; i < rowSize; i++) {
		for(j = 0; j < colSize; j++) {
			inF >> tmpAction >> index >> sem;
			action = (ACTIONTYPE) tmpAction;
			PTBlock* ptb = new PTBlock();
			ptb->SetAction(action);
			ptb->SetIndex(index);
			ptb->SetSem(sem);
			m_ParseTable[i].push_back(ptb);
		}
	}
	inF.close();
}

void Parser::Parse()
{
	int curNode, tokenID;
	string token;

	curNode = 0;
	token = m_Scanner->NextToken();
	tokenID = FindSymbolID(token);
	
	while(true) {
		PTBlock* ptb = m_ParseTable[curNode][tokenID];
		ACTIONTYPE action = ptb->GetAction();
		int index = ptb->GetIndex();
		string sem = ptb->GetSem();
		cout << endl << endl<< curNode << " text:" << Scanner::text << endl << endl;
		switch(action) {
			case ERR :
				throw new CParseErrorException();

			case SHIFT :
				ss.push(token);
				m_CodeGenerator.Generate(sem);
				token = m_Scanner->NextToken();
				tokenID = FindSymbolID(token);
				curNode = index;
				break;

			case PUSHGOTO :
				m_ParseStack.push(curNode);
				curNode = index;
				break;

			case RET :
				curNode = m_ParseStack.top();
				m_ParseStack.pop();
				ptb = m_ParseTable[curNode][index];
				m_CodeGenerator.Generate(ptb->GetSem());
				curNode = ptb->GetIndex();
				break;

			case ACC :
				return;
			default:
				break;
		}
	}
}



int Parser::FindSymbolID(string symbol)
{
	for(int i = 0; i < m_ParseTable.size(); i++) {
		if(symbol == m_SymbolNames[i]) {
			return i;
		}
	}
}

CParseErrorException::CParseErrorException()
{
	cout << "Error" << endl;
}
#endif

// CodeGenerator.h: interface for the CodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_ODEGENERATOR_H__580AD3AE_2D1B_444A_BCCE_5A6252CA0DF0__INCLUDED_)
//#define AFX_ODEGENERATOR_H__580AD3AE_2D1B_444A_BCCE_5A6252CA0DF0__INCLUDED_
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <string>
#include "Scanner.h"
#include "stack"
#include <map>
using namespace std;

struct FuncProperties{
	string argument[10];
	string returnType;
};


class CodeGenerator  
{
public:
	stack<string> sstack;
	string code[100000];
	string stringConsts[100];
	int lastTemp;
	int lastStringConst;
	int pc;
	string currentfunc;
	map<string, string> symtab;
	map<string, FuncProperties> functab;
   	void Generate(string sem);
	void createVar(string name, string type);
	void assignToVariable(string variableName, string variableType, string valueName, string valueType);
	void loadVar(string type, string variableName, string valueName);
	CodeGenerator();
	virtual ~CodeGenerator();

};

#endif // !defined(AFX_ODEGENERATOR_H__580AD3AE_2D1B_444A_BCCE_5A6252CA0DF0__INCLUDED_)

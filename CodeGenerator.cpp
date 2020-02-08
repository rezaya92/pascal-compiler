// odeGenerator.cpp: implementation of the CodeGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenerator.h"
#include <iostream>
#include <stdexcept>
#include <bits/stdc++.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CodeGenerator::CodeGenerator()
{
    pc = 0;
    code[pc++] = "target datalayout = \"e-m:e-i64:64-f80:128-n8:16:32:64-S128\"";
    code[pc++] = "target triple = \"x86_64-pc-linux-gnu\"";
	code[pc++] = "define void @write(i8* %toprint) {";
	code[pc++] = "%1 = alloca i8*, align 8";
	code[pc++] = "store i8* %toprint, i8** %1, align 8";
	code[pc++] = "%2 = load i8*, i8** %1, align 8";
	code[pc++] = "%3 = call i32 (i8*, ...) @printf(i8* %2)"; 
	code[pc++] = "ret void";
	code[pc++] = "}";
    code[pc++] = "declare i32 @printf(i8*, ...)";
	lastTemp = 1;
	lastStringConst = 1;
	FuncProperties writeProperties;
	writeProperties.argument[0] = "i8*";
	writeProperties.returnType = "void";
	functab.insert(make_pair("write", writeProperties));
}

CodeGenerator::~CodeGenerator()
{
    for (int j = 1; j < lastStringConst; ++j) {
        cout << stringConsts[j] << endl;
    }
    for (int i=0; i<pc; i++){
        cout << code[i] << endl;
    }
}

void CodeGenerator::Generate(string sem)
{
    for (int j = 1; j < lastStringConst; ++j) {
        cout << stringConsts[j] << endl;
    }
    for (int i=0; i<pc; i++) {
        cout << code[i] << endl;
    }
	if(sem != "NoSem"){
		if (sem == "@pushID"){
			sstack.push(Scanner::text);
		}
		else if (sem == "@startFuncDef"){
			code[pc] = "@" + Scanner::text + "(";
            currentfunc = Scanner::text;
		}
		else if (sem == "@funcType"){
			code[pc] = "define " + sstack.top() + " " + code[pc] + " )";
            FuncProperties funcProperties;
            funcProperties.returnType = sstack.top();
            functab.insert(make_pair(currentfunc, funcProperties));
            sstack.pop();
			pc++;
		}
		else if (sem == "@typeInt"){	 
			sstack.push("i32");
		}
		else if (sem == "@typeChar"){
			sstack.push("i8");
		}
		else if (sem == "@typeStr"){
			sstack.push("i8*");
		}
		else if (sem == "@typeBool"){
			sstack.push("i1");
		}
		else if (sem == "@typeLong"){
			sstack.push("i64");
		}
		else if (sem == "@typeReal"){
			sstack.push("float");
		}
		else if (sem == "@beginBlock"){
			code[pc] = "{";
			pc++;
		}
		else if (sem == "@endBlock"){
			code[pc] = "}";
			pc++;
		}
		else if (sem == "@pcInc"){
			pc++;
		}
		else if (sem == "@icConst"){
			createVar(to_string(lastTemp), "i32");
			assignToVariable("i32","%" + to_string(lastTemp), Scanner::text);
            lastTemp++;
            loadVar("i32", to_string(lastTemp), to_string(lastTemp-1));
			lastTemp++;
		}
		else if (sem == "@rcConst"){
			createVar(to_string(lastTemp), "float");
			float rcConstVal = stof(Scanner::text);
			char rcConstHex[16];
			sprintf(rcConstHex, "%x", *(unsigned int*)&rcConstVal);
            string rcConstHexStr(rcConstHex);
			assignToVariable("float","%" + to_string(lastTemp), "0x"+rcConstHexStr+"00000000");
            lastTemp++;
            loadVar("float", to_string(lastTemp), to_string(lastTemp-1));
			lastTemp++;
		}
		else if (sem == "@chConst"){
			createVar(to_string(lastTemp), "i8");
			assignToVariable("i8","%" + to_string(lastTemp), to_string((int)Scanner::text[1]));
            lastTemp++;
            loadVar("i8", to_string(lastTemp), to_string(lastTemp-1));
			lastTemp++;
		}
		else if (sem == "@boolConst"){
			createVar(to_string(lastTemp), "i1");
			assignToVariable("i1","%" + to_string(lastTemp), Scanner::text);
            lastTemp++;
            loadVar("i1", to_string(lastTemp), to_string(lastTemp-1));
			lastTemp++;
		}
		else if (sem == "@strConst"){
			string strConst = Scanner::text.substr(1, Scanner::text.size() - 2);
			stringConsts[lastStringConst] = "@.str." + to_string(lastStringConst) + " = private unnamed_addr constant ";
			stringConsts[lastStringConst] += "[" + to_string(strConst.size()+1) + " x i8] c\"" + strConst + "\\00\", align 1";
			createVar(to_string(lastTemp), "i8*");
			string getStrConstCommand = "getelementptr inbounds ([" + to_string(strConst.size()+1) + " x i8], [" + to_string(strConst.size()+1) + " x i8]* @.str." + to_string(lastStringConst) + ", i32 0, i32 0)";
			assignToVariable("i8*","%" + to_string(lastTemp), getStrConstCommand);
            lastTemp++;
            loadVar("i8*", to_string(lastTemp), to_string(lastTemp-1));
			lastStringConst++;
			lastTemp++;
		}
		else if (sem == "@pushLastTemp"){
			sstack.push(to_string(lastTemp-1));
		}
		else if (sem == "@callFunc"){
			stack<string> callArgs;
			char* isID;
			string lastArg = sstack.top();
            sstack.pop();
			long converted = strtol(lastArg.c_str(), &isID, 10);
			while (!*isID){
				callArgs.push(lastArg);
				lastArg = sstack.top();
                sstack.pop();
				converted = strtol(lastArg.c_str(), &isID, 10);
			}
			string funcName = lastArg;
			if (functab.count(funcName) == 0)
				throw invalid_argument("no function with this name:" + funcName);
			code[pc] = "call " + functab[funcName].returnType + " @" + funcName + "(";
			int i = 0;
			while(!callArgs.empty()) {
                lastArg = callArgs.top();
                callArgs.pop();
                if (functab[funcName].argument[i] != symtab[lastArg])
                    throw invalid_argument("argument type mismatch");
                code[pc] += symtab[lastArg] + " %" + lastArg + ",";
            }
			if (code[pc][code[pc].size()-1] == ',')
				code[pc][code[pc].size()-1] = ')';
			else
				code[pc] += ')';
            pc++;
		}
        else if (sem == "@return"){
            if (functab[currentfunc].returnType != symtab[to_string(lastTemp-1)])
                throw invalid_argument("invalid return type" + functab[currentfunc].returnType);
            code[pc] = "ret " + functab[currentfunc].returnType + " %" + to_string(lastTemp-1);
            pc++;
        }
        else if (sem == "@makeVariable"){
            string varType = sstack.top();
            sstack.pop();
            string varName = sstack.top();
            createVar(varName, varType);
        }
        else if (sem == "@makeAssignment"){
            string variableName = sstack.top();
            assignToVariable(symtab[variableName], "%" + variableName, to_string(lastTemp-1));
        }
        else if (sem == "@popID"){
            sstack.pop();
        }
        else throw invalid_argument("no sem like this man" + sem);
	}
}

void CodeGenerator::createVar(string name, string type) {
	if (symtab.count(name) != 0)
		throw invalid_argument("symbol redeclaration");
	code[pc] = "%" + name + " = alloca " + type +", align 1";
	symtab.insert(make_pair(name, type));
	pc++;
}

void CodeGenerator::assignToVariable(string type, string variableName, string valueName) {
	code[pc] = "store " + type + " " + valueName + ", " + type + "* " + variableName + ", align 1";
    pc++;
}

void CodeGenerator::loadVar(string type, string variableName, string valueName) {
    if (symtab.count(variableName) != 0)
        throw invalid_argument("symbol redeclaration");
    code[pc] = "%" + variableName + " = load " + type +", " + type + "* %" + valueName + ", align 1";
    symtab.insert(make_pair(variableName, type));
    pc++;
}
// PTBlock.h: interface for the PTBlock class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_PTBLOCK_H__2028002C_F778_4B97_B93D_11B5325E9393__INCLUDED_)
//#define AFX_PTBLOCK_H__2028002C_F778_4B97_B93D_11B5325E9393__INCLUDED_
//
//
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#ifndef __PTBLOCK_H
#define __PTBLOCK_H

#include <string>
using namespace std;

enum ACTIONTYPE {ERR, SHIFT, GOTO, PUSHGOTO, RET, ACC};

class PTBlock  
{
public:
	void SetIndex(const int);
	void SetSem(const string);
	void SetAction(const ACTIONTYPE);
	int GetIndex() const;
	string GetSem() const;
	ACTIONTYPE GetAction() const;
	PTBlock();
	virtual ~PTBlock();

private:
	string m_sem;
	int m_index;
	ACTIONTYPE m_action;
};

#endif // !defined(AFX_PTBLOCK_H__2028002C_F778_4B97_B93D_11B5325E9393__INCLUDED_)


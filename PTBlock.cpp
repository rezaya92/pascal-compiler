// PTBlock.cpp: implementation of the PTBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "PTBlock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PTBlock::PTBlock()
{

}

PTBlock::~PTBlock()
{

}

ACTIONTYPE PTBlock::GetAction() const { return m_action; }

string PTBlock::GetSem() const { return m_sem; }


int PTBlock::GetIndex() const { return m_index; }


void PTBlock::SetAction(const ACTIONTYPE action)
{
	m_action = action;
}

void PTBlock::SetSem(const string sem)
{
	m_sem = sem;
}

void PTBlock::SetIndex(const int index)
{
	m_index = index;
}


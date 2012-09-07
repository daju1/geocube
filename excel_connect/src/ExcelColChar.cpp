// ExcelColChar.cpp: implementation of the ExcelColChar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "lab.h"
#include "ExcelColChar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void ExcelColChar::Init(char c)
{
	C = c;
	C0 = 'A'-1;
	use_C0 = false;
}

ExcelColChar::ExcelColChar(char c)
{
	Init(c);
}

ExcelColChar::~ExcelColChar()
{

}
ExcelColChar ExcelColChar::operator+ (size_t n)
{
	ExcelColChar ecc(*this);

	for (size_t i = 0; i < n; i++)
	{
		ecc.Increment();
	}
	return ecc;
}

void ExcelColChar::Init(const ExcelColChar& ob)
{
	this->C			= ob.C;
	this->C0		= ob.C0;
	this->use_C0	= ob.use_C0;
}

ExcelColChar::ExcelColChar(const ExcelColChar& ob)
{
	this->Init(ob);
}

ExcelColChar& ExcelColChar::operator=(const ExcelColChar& ob)
{
	if (this == &ob)
		return *this;

	this->Init(ob);

	return *this;
}
CString ExcelColChar::Get()
{
	CString s;
	if (use_C0)
		s.Format("%c%c", C0, C);
	else
		s.Format("%c", C);
	return s;
}
CString ExcelColChar::Get(size_t iv)
{
	ExcelColChar ecc(*this);
	for (size_t i = 0; i < iv; i++)
	{
		ecc.Increment();
	}
	return ecc.Get();
}
void ExcelColChar::Increment()
{
	if(C == 'Z')
	{
		C0++;
		use_C0 = true;
		C = 'A' - 1;
	}

	C++;
}
// ExcelColChar.h: interface for the ExcelColChar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELCOLCHAR_H__6E76C941_8EDC_42D6_B03B_303C64A83F94__INCLUDED_)
#define AFX_EXCELCOLCHAR_H__6E76C941_8EDC_42D6_B03B_303C64A83F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExcelColChar
{
	char C0, C;
	bool use_C0;
public:
	ExcelColChar(char c);
	~ExcelColChar();
	void Init(char c);

	void Init(const ExcelColChar& ob);
	ExcelColChar(const ExcelColChar& ob);
	ExcelColChar& operator=(const ExcelColChar& ob);


	CString Get();
	CString Get(size_t iv);

	ExcelColChar operator+ (size_t n);

	void Increment();
};

#endif // !defined(AFX_EXCELCOLCHAR_H__6E76C941_8EDC_42D6_B03B_303C64A83F94__INCLUDED_)

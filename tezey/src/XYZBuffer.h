// XYZBuffer.h: interface for the XYZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XYZBUFFER_H__0463682D_0B4E_4157_A0BE_41B5FFC91941__INCLUDED_)
#define AFX_XYZBUFFER_H__0463682D_0B4E_4157_A0BE_41B5FFC91941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
struct XYZ
{
	SYSTEMTIME time;
	unsigned long x;
	unsigned long y;
	unsigned long z;
//	CString time_str;
};
class XYZBuffer  
{
	unsigned long 
		x,
		y,
		z;
	bool toSolve;
	SYSTEMTIME time;
	HANDLE  hEventOutputReady;
	HANDLE  hEventInputReady;

public:
//	CString m_sErrorString;
//	void ReadErrorString(CString& s);
//	void WriteErrorString(CString& s);
	void Read(LPSYSTEMTIME ptime, unsigned long & _x, unsigned long & _y, unsigned long & _z, bool &_toSolve);
	void Write(LPSYSTEMTIME ptime, unsigned long & _x, unsigned long & _y, unsigned long & _z, bool &_toSolve);
	XYZBuffer();
	virtual ~XYZBuffer();

};

#endif // !defined(AFX_XYZBUFFER_H__0463682D_0B4E_4157_A0BE_41B5FFC91941__INCLUDED_)

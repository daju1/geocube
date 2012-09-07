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
	int x;
	int y;
	int z;
//	CString time_str;
};
class XYZBuffer  
{
	int
		x,
		y,
		z;
	bool toSolve;
	CString time_str;
	HANDLE  hEventOutputReady;
	HANDLE  hEventInputReady;

public:
	CString m_sErrorString;
	void ReadErrorString(CString& s);
	void WriteErrorString(CString& s);
	void Read(CString &_time_str, int& _x, int& _y, int& _z, bool &_toSolve);
	void Write(CString &_time_str, int& _x, int& _y, int& _z, bool &_toSolve);
	XYZBuffer();
	virtual ~XYZBuffer();

};

#endif // !defined(AFX_XYZBUFFER_H__0463682D_0B4E_4157_A0BE_41B5FFC91941__INCLUDED_)

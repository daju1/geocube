// XYZBuffer.cpp: implementation of the XYZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "XYZBuffer.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

XYZBuffer::XYZBuffer()
{
	// событие - "входной Ready" - сигнальное
	hEventInputReady = CreateEvent( NULL, TRUE, TRUE, "InputReadyEvent" );
	// событие - "выходной Ready" - сигнальное
	hEventOutputReady = CreateEvent( NULL, TRUE, FALSE, "OutputReadyEvent" );

}

XYZBuffer::~XYZBuffer()
{

}

void XYZBuffer::Write(LPSYSTEMTIME ptime, unsigned long &_x, unsigned long &_y, unsigned long &_z, bool &_toSolve)
{
	WaitForSingleObject( hEventInputReady, INFINITE );
	ResetEvent(hEventInputReady);
	time = *ptime;
	x = _x;
	y = _y;
	z = _z;
	toSolve = _toSolve;
	SetEvent(hEventOutputReady);
}

void XYZBuffer::Read(LPSYSTEMTIME ptime, unsigned long &_x, unsigned long &_y, unsigned long &_z, bool &_toSolve)
{
	WaitForSingleObject( hEventOutputReady, INFINITE );
	ResetEvent(hEventOutputReady);
	*ptime = time;
	_x = x;
	_y = y;
	_z = z;
	_toSolve = toSolve;
	SetEvent(hEventInputReady);
}
/*
void XYZBuffer::WriteErrorString(CString &s)
{
	WaitForSingleObject( hEventInputReady, INFINITE );
	ResetEvent(hEventInputReady);
	m_sErrorString = s;
	SetEvent(hEventOutputReady);
}

void XYZBuffer::ReadErrorString(CString &s)
{
	WaitForSingleObject( hEventOutputReady, INFINITE );
	ResetEvent(hEventOutputReady);
	s = m_sErrorString;
	SetEvent(hEventInputReady);
}
*/
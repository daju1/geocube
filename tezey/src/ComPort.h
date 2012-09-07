// ComPort.h: interface for the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(COMPORT_H__71C7533F_D004_4C9C_85CD_7D84786FF281__INCLUDED_)
#define COMPORT_H__71C7533F_D004_4C9C_85CD_7D84786FF281__INCLUDED_
#include "XYZBuffer.h"	// Added by ClassView
#include "RoomQueueItem.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComPort  
{
	int m_nPortNumber;
	int m_z;
	int m_y;
	int m_x;
public:
	int StartHandling();
	bool m_bTerminatedHandlingThread;
	bool m_bTerminatedXYZBufferThread;
	bool m_bTerminatedCOMThread;
	bool m_bIsConnected;

	HANDLE  m_hEventFrameReady;
	CRoomQueueItem m_queue;
	XYZBuffer m_XYZBuffer;
	HWND m_hWndOwner;
	
	HANDLE m_hHandlingThread;
	HANDLE m_hReadingFromXYZBufferThread;
	HANDLE m_hReadingFromCOMThread;
	HANDLE m_hCommHandle;
	int ManualConnect();
//	CMainFrame* m_pMainFrame;
//	int SetWindowOwner(CMainFrame* pMainFrame, HWND hWnd);

	void ReadFromCOM();
	int CloseConnection();
	int DoConnect(int _nPortNumber);
	CComPort();
	CComPort(int nPortNumber);
	virtual ~CComPort();

};

#endif // !defined(COMPORT_H__71C7533F_D004_4C9C_85CD_7D84786FF281__INCLUDED_)

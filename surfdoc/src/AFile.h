#pragma once
#ifdef _MSC_VER
#include <windows.h>
#else
#include "mywindows.h"
#include <QFile>
#endif

class AFile
{
public:
#if defined (_MSC_VER)
	HANDLE m_hFile;
#else
       QFile m_file;
#endif
	AFile(void);
	AFile(LPCTSTR filename, DWORD dwAccess, DWORD dwCreationDispostion = OPEN_ALWAYS);
	virtual ~AFile(void);
	void Close(void);
	void Flush(void);
	bool Open(LPCTSTR filename, DWORD dwAccess, DWORD dwCreationDispostion );
	DWORD Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead);
	DWORD Write(LPCVOID  lpBuff, DWORD dwNumberOfBytesToWrite);
	void SeekToBegin(void);
	void SeekToEnd(void);
	LONG Seek(long lOff, DWORD dwMoveMethod);
};

#pragma once
#ifdef _MSC_VER
#include <windows.h>
#else
#endif

class AFile
{
public:
	HANDLE m_hFile;
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

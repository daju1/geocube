#include "stdafx.h"
#include "AFile.h"
#include "../../tools/src/errorexit.h"

AFile::AFile(void)
{
	m_hFile = NULL;
}

AFile::AFile(LPCTSTR filename, DWORD dwAccess, DWORD dwCreationDispostion )
{
	this->Open(filename, dwAccess, dwCreationDispostion);
}

AFile::~AFile(void)
{
	if (this->m_hFile)
		this->Close();
}

void AFile::Close(void)
{
	if (this->m_hFile) {
		this->Flush();
		CloseHandle(this->m_hFile);
		this->m_hFile=NULL;
	}
}

void AFile::Flush(void)
{
	if (this->m_hFile) {
		FlushFileBuffers(this->m_hFile);
	}
}

bool AFile::Open(LPCTSTR filename, DWORD dwAccess, DWORD dwCreationDispostion )
{
	// dwAccess : GENERIC_READ or GENERIC_WRITE
	// dwCreationDispostion:
	//		CREATE_NEW Creates a new file. The function fails if the specified file already exists. 
	//		CREATE_ALWAYS Creates a new file. If the file exists, the function overwrites the file and clears the existing attributes. 
	//		OPEN_EXISTING Opens the file. The function fails if the file does not exist. 
	//					See the Remarks section for a discussion of why you should use the OPEN_EXISTING flag if you are using the CreateFile function for devices, including the console. 
	//		OPEN_ALWAYS Opens the file, if it exists. If the file does not exist, the function creates the file as if dwCreationDisposition were CREATE_NEW. 
	//		TRUNCATE_EXISTING Opens the file. Once opened, the file is truncated so that its size is zero bytes. The calling process must open the file with at least GENERIC_WRITE access. The function fails if the file does not exist. 

	this->m_hFile = CreateFile(filename,dwAccess,0,0,dwCreationDispostion,FILE_ATTRIBUTE_NORMAL,NULL);
	if (this->m_hFile != INVALID_HANDLE_VALUE)
	{
		return true;
	}
	else
	{
		this->m_hFile = NULL;
		return false;
	}
}

DWORD AFile::Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead)
{
//printf("DWORD AFile::Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead = %d)\n", dwNumberOfBytesToRead);
	DWORD dwNumberOfBytesRead;
	if (ReadFile(this->m_hFile, lpBuffer, dwNumberOfBytesToRead, &dwNumberOfBytesRead, NULL))
	{
//printf("DWORD AFile::Read(return dwNumberOfBytesRead = %d)\n", dwNumberOfBytesRead);
		return dwNumberOfBytesRead;
	}
	else
	{
//printf("DWORD AFile::Read(return 0)\n");
		ErrorPrint("ReadFile");
		return 0;
	}
}

DWORD AFile::Write(LPCVOID  lpBuff, DWORD dwNumberOfBytesToWrite)
{
	DWORD dwNumberOfBytesWritten;
	WriteFile(this->m_hFile, lpBuff, dwNumberOfBytesToWrite, &dwNumberOfBytesWritten, NULL);
	return dwNumberOfBytesWritten;
}

void AFile::SeekToBegin(void)
{
	SetFilePointer(this->m_hFile, 0, 0, FILE_BEGIN);
}

void AFile::SeekToEnd(void)
{
	SetFilePointer(this->m_hFile, 0, 0, FILE_END);
}

LONG AFile::Seek(long lOff, DWORD dwMoveMethod)
{
	// dwMoveMethod : FILE_BEGIN or FILE_CURRENT or FILE_END
	return SetFilePointer(this->m_hFile, lOff, 0, dwMoveMethod);
}

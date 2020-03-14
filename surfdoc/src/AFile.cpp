#include "stdafx.h"
#include "AFile.h"
#include "../../tools/src/errorexit.h"
#if defined (_MSC_VER) && !defined (QT_VERSION)
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
		ErrorPrint(_T("ReadFile"));
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

#else
AFile::AFile(void)
{
}

AFile::AFile(LPCTSTR filename, DWORD dwAccess, DWORD dwCreationDispostion )
{
    this->Open(filename, dwAccess, dwCreationDispostion);
}

AFile::~AFile(void)
{
    this->Close();
}

void AFile::Close(void)
{
    m_file.close();
}

void AFile::Flush(void)
{
    m_file.flush();
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


    //enum OpenModeFlag {
    //    NotOpen = 0x0000,
    //    ReadOnly = 0x0001,
    //    WriteOnly = 0x0002,
    //    ReadWrite = ReadOnly | WriteOnly,
    //    Append = 0x0004,
    //    Truncate = 0x0008,
    //    Text = 0x0010,
    //    Unbuffered = 0x0020
    //};

    QString newName = filename;
    m_file.link(newName);
    QIODevice::OpenModeFlag OpenMode = QIODevice::NotOpen;

    switch (dwCreationDispostion)
    {
    case CREATE_NEW:
        break;
    case CREATE_ALWAYS:
        break;
    case OPEN_EXISTING:
        break;
    case OPEN_ALWAYS:
        break;
    case TRUNCATE_EXISTING:
        OpenMode = QIODevice::Truncate;
        break;

    }

    switch (dwAccess)
    {
    case GENERIC_READ:
        OpenMode = QIODevice::ReadOnly;
        break;
    case GENERIC_WRITE:
        OpenMode = QIODevice::WriteOnly;
        break;
    }

    return m_file.open(OpenMode);
}

DWORD AFile::Read(LPVOID lpBuffer, DWORD dwNumberOfBytesToRead)
{
    return m_file.read((char *)lpBuffer, dwNumberOfBytesToRead);
}

DWORD AFile::Write(LPCVOID  lpBuff, DWORD dwNumberOfBytesToWrite)
{
    return m_file.write((const char *)lpBuff, dwNumberOfBytesToWrite);
}

void AFile::SeekToBegin(void)
{
    m_file.seek(0);
}

void AFile::SeekToEnd(void)
{
    m_file.atEnd();
}

bool AFile::Seek(long lOff, DWORD dwMoveMethod)
{
    switch (dwMoveMethod)
    {
    case FILE_BEGIN:
    {
        return m_file.seek(lOff);
    }
    case FILE_CURRENT:
    {
        qint64 pos = m_file.pos();
        return m_file.seek(pos + lOff);
    }
    case FILE_END:
    {
        qint64 sz = m_file.size();
        return m_file.seek(sz - lOff);
    }
    }
    return false;
}
#endif

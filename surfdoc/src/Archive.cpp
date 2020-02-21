#include "stdafx.h"
#include "Archive.h"
#include "points.h"
#include "Layer.h"
#include "Grid.h"
#include "ProfileAttachPoint.h"
#include "BrokenPlane3D.h"

bool Archive::OpenFileAsImport = false;

Archive::Archive(AFile * pFile, Archive::mode amode, int nBufSize, void * lpBuff)
{
	this->m_pFile	= pFile;
	this->m_mode	= amode;
	this->m_nBufSize= nBufSize;

	this->m_use_base_version		= 0;
	this->m_use_object_version		= 0;
	this->m_use_primitive_version	= 0;

	this->pDocument	= NULL;

	if (lpBuff)
	{
		this->m_lpBuff = (unsigned char *)lpBuff;
		this->m_myBuff = false;
	}
	else
	{
		this->m_lpBuff = new unsigned char[this->m_nBufSize];
		this->m_myBuff = true;
	}
	sumFlushedToFile	= 0;//Сколько байт сброшено в файл 
	sumWroteToArchive	= 0;//Сколько байт записано в архив

	freeInBuffer		= this->m_nBufSize; //свободное место в буфере
	wroteInBuffer		= 0; // занятое место в буфере

	readFromBuffer		= 0; // прочитано из буфера
	remainedToReadFromBuffer		= 0; // осталось прочитать 
}


Archive::~Archive(void)
{
	if (this->m_myBuff && this->m_lpBuff) delete [] this->m_lpBuff;
}
DWORD Archive::ReWrite(unsigned char * from, DWORD to_BytesFromBegin, DWORD count)
{
	// три варианта
	if (to_BytesFromBegin + count <= this->sumFlushedToFile)
	{
		return this->ReWriteToFile(from, to_BytesFromBegin, count);
	}
	else
	{
		if(this->sumFlushedToFile <= to_BytesFromBegin)
		{
			return this->ReWriteToBuffer(from, to_BytesFromBegin - this->sumFlushedToFile, count);
		}
		else
		{
			DWORD countForFile = this->sumFlushedToFile - to_BytesFromBegin;

			DWORD rez = this->ReWriteToFile(from, to_BytesFromBegin, countForFile);
			rez += this->ReWriteToBuffer(from + countForFile, 0, count - countForFile);
			return rez;
		}
	}
}
DWORD Archive::ReWriteToBuffer(unsigned char * from, DWORD to_BytesFromBegin, DWORD count)
{
	// копируем в буфер	
	if (this && m_lpBuff && from) 
	{
		if (to_BytesFromBegin + count <= wroteInBuffer)
		{
			memcpy(m_lpBuff + to_BytesFromBegin, from, count);
			return count;
		}
	}
	return 0;


}
DWORD Archive::ReWriteToFile(unsigned char * from, DWORD to_BytesFromBegin, DWORD count)
{
	DWORD rez = 0;
	if (this && this->m_pFile && from)
	{
		this->m_pFile->Seek((long)to_BytesFromBegin, FILE_BEGIN);
		rez = this->m_pFile->Write(from, count);
		this->m_pFile->SeekToEnd();
	}
	return rez;
}

DWORD Archive::Write(unsigned char * from, DWORD count)
{
	if (!IsStoring()) return 0;

	DWORD 
		remained = count,
		sum_wrote = 0, 
		wrote;
	do
	{
		if (this && from) wrote = WriteToBuffer(from + sum_wrote, remained);
		else return 0;
		sum_wrote += wrote;
		remained  -= wrote;
	}
	while(remained > 0 && wrote > 0);
	this->sumWroteToArchive += sum_wrote;
	return sum_wrote;
}
DWORD Archive::WriteToBuffer(unsigned char * from, DWORD count)
{
	if (!IsStoring()) return 0;
	bool full_buffer = freeInBuffer <= count; // заполнится ли входной буфер полностью
	// определяем, сколько можно записать во входной буфер и замисываем
	DWORD countToWrite = full_buffer ? freeInBuffer : count;
	// копируем в буфер, сколько можно
	if (this && m_lpBuff && from) 
		memcpy(m_lpBuff + wroteInBuffer, from, countToWrite);
	// корректируем показатели заполненности буфера
	freeInBuffer -= countToWrite;
	wroteInBuffer += countToWrite;
	// если буфер полностью заполнен
	if (this && full_buffer)
	{
		// сбрасываем данные из буфера в файл
		this->Flush();
	}
	// возвращаем фактическое число записанных символов
	return countToWrite;
}
DWORD Archive::Read(unsigned char * to, DWORD count)
{
	DWORD 
		remained = count,
		sum_read = 0, 
		read;
	do
	{
		if (this && to) read = ReadFromBuffer(to + sum_read, remained);
		else return 0;
		sum_read += read;
		remained -= read;
	}
	while(remained > 0 && read > 0);
	if (remained > 0)
	{
		char str_error[1024];
		sprintf_s(str_error, 1024, "DWORD Archive::Read(unsigned char * to, DWORD count = %d) error: remained = %d\n", count, remained);
		printf (str_error);
		printf("remainedToReadFromBuffer = %d\n", remainedToReadFromBuffer);
		printf("readFromBuffer = %d\n", readFromBuffer);
		//MessageBox(0, str_error, "Archive::Read", 0);
		throw (str_error);
	}
	return sum_read;
}
DWORD Archive::ReadFromBuffer(unsigned char * to, DWORD count)
{
//printf("DWORD Archive::ReadFromBuffer(unsigned char * to, DWORD count = %d)\n", count);
	// "осталось прочитать из буфера" remainedToRead - это сколько 
	// байт прочитано из файла в буфер, но не вычитано из буфера
	// если remainedToRead == 0, тогда надо прочитать из файла в буфер,
	// а в переменную remainedToRead записать - сколько на самом деле 
	// прочитано из файла в буфер
	if (remainedToReadFromBuffer == 0) 
	{
//printf("DWORD Archive::ReadFromBuffer(remainedToReadFromBuffer == 0)\n");
		if (this && this->m_pFile)
			remainedToReadFromBuffer = this->m_pFile->Read(this->m_lpBuff, this->m_nBufSize);
//printf("DWORD Archive::ReadFromBuffer(remainedToReadFromBuffer = %d)\n", remainedToReadFromBuffer);
		// readFromBuffer - это позиция в буфере, с которой надо начинать считываение из буфера
		// после заполнения буфера данными из файла устанавливаем этот указатель в нулевую позицию
		readFromBuffer = 0;
		// если всё же из файла не удалось прочитать ни одного байта - выходим с результатом нуль
		if (remainedToReadFromBuffer == 0)
		{
			printf("DWORD Archive::ReadFromBuffer(remainedToReadFromBuffer == 0) return 0; !!!!!!\n");
			return 0;
		}
	}
	
	bool all_will_be_read = remainedToReadFromBuffer <= count; // всё ли будет прочитано
	// устанавливаем сколько надо прочитать и читаем
	DWORD countToRead = all_will_be_read ? remainedToReadFromBuffer : count;
	if (this && this->m_lpBuff && to)
	{
		memcpy(to, this->m_lpBuff + readFromBuffer, countToRead);
	}
	remainedToReadFromBuffer -= countToRead;
	readFromBuffer += countToRead;
	// возвращаем фактическое число прочитанных символов
//printf("DWORD Archive::ReadFromBuffer(return countToRead = %d)\n", countToRead);
	return countToRead;
}

void Archive::Flush(void)
{
	if (this->IsStoring())
	{
		// сбрасываем данные из буфера в файл
		if (this && this->m_lpBuff && this->m_pFile){
			DWORD dwNumberOfBytesWritten = this->m_pFile->Write(this->m_lpBuff, wroteInBuffer);;
			this->sumFlushedToFile += dwNumberOfBytesWritten;
			
			if (dwNumberOfBytesWritten < wroteInBuffer)
				throw "Can not write the file\ndisk space not enough";
			
			//this->m_pFile->Flush();
			// устанавливаем показатели заполненности буфера
			freeInBuffer = this->m_nBufSize;//свободное место во входном буфере
			wroteInBuffer = 0; // занятое место во входном буфере
		}
	}
}

void Archive::ClearReadBuffer(void)
{
	remainedToReadFromBuffer = 0;
	readFromBuffer = 0;
}
void Archive::ClearWriteBuffer(void)
{
	freeInBuffer		= this->m_nBufSize; //свободное место в буфере
	wroteInBuffer		= 0; // занятое место в буфере
}
void Archive::Close(void)
{
	this->Flush();
}

DWORD Archive::WriteString(LPCTSTR str)
{
	DWORD wrote = Write((unsigned char *)str, (DWORD)strlen(str));
	LPCTSTR s0 = "\0";
	wrote += Write((unsigned char *)s0, 1);
	return wrote;
}

LPTSTR Archive::ReadString(LPTSTR lpsz, DWORD nMax)
{
	DWORD n = 0;
	DWORD read;
	do
	{
		read = Read((unsigned char *)lpsz + n, 1);
		if (read > 0)
		{
			if (lpsz[n] == '\0')
				break;
			n++;
		}
	}
	while (n < nMax && read > 0);
	if (n > 0 && read > 0)
		return LPTSTR(lpsz);
	else
		return NULL;
}


// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Archive& Archive::operator <<(BYTE by)
{
	Write((unsigned char *)&by,sizeof(BYTE));
	return *this;
}

Archive& Archive::operator <<(WORD w)
{
	Write((unsigned char *)&w, sizeof(WORD));
	return *this;
}

Archive& Archive::operator <<(LONG l)
{
	//printf("Archive& Archive::operator <<(LONG l = %d)\n", l);
	Write((unsigned char *)&l, sizeof(LONG));
	return *this;
}

Archive& Archive::operator <<(DWORD dw)
{
	//printf("Archive& Archive::operator <<(DWORD dw = %lu)\n", dw);
	Write((unsigned char *)&dw, sizeof(DWORD));
	return *this;
}

Archive& Archive::operator <<(float f)
{
	Write((unsigned char *)&f, sizeof(float));
	return *this;
}

Archive& Archive::operator <<(double d)
{
	Write((unsigned char *)&d, sizeof(double));
	return *this;
}

Archive& Archive::operator <<(int i)
{
	//printf("Archive& Archive::operator <<(int i = %d)\n", i);
	Write((unsigned char *)&i, sizeof(int));
	return *this;
}

Archive& Archive::operator <<(short w)
{
	//printf("Archive& Archive::operator <<(short w = %d)\n", w);
	Write((unsigned char *)&w, sizeof(short));
	return *this;
}

Archive& Archive::operator <<(char ch)
{
	Write((unsigned char *)&ch, sizeof(char));
	return *this;
}


#if USE_SIZE_T_IN_ARCHIVE
/*
Archive& Archive::operator <<(__w64 unsigned u)
{
	Write((unsigned char *)&u, sizeof(__w64 unsigned));
	return *this;
}*/

Archive& Archive::operator <<(size_t u)
{
	Write((unsigned char *)&u, sizeof(size_t));
	return *this;
}
#else
Archive& Archive::operator <<(unsigned u)
{
	Write((unsigned char *)&u, sizeof(unsigned));
	return *this;
}
#endif
Archive& Archive::operator <<(bool b)
{
//	printf("Archive& Archive::operator <<(bool b = %d)\n", b);
	Write((unsigned char *)&b, sizeof(bool));
	return *this;
}
Archive& Archive::operator <<(ULONGLONG dwdw)
{
	Write((unsigned char *)&dwdw, sizeof(ULONGLONG));
	return *this;
}
Archive& Archive::operator <<(LONGLONG dwdw)
{
	Write((unsigned char *)&dwdw, sizeof(LONGLONG));
	return *this;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

Archive& Archive::operator >>(BYTE& by)
{
	Read((unsigned char *)&by,sizeof(BYTE));
	return *this;
}

Archive& Archive::operator >>(WORD& w)
{
	Read((unsigned char *)&w, sizeof(WORD));
	return *this;
}

Archive& Archive::operator >>(LONG& l)
{
	Read((unsigned char *)&l, sizeof(LONG));
	//printf("Archive& Archive::operator >>(LONG& l = %d)\n", l);
	return *this;
}

Archive& Archive::operator >>(DWORD& dw)
{
	Read((unsigned char *)&dw, sizeof(DWORD));
	//printf("Archive& Archive::operator >>(DWORD& dw = %lu)\n", dw);
	return *this;
}

Archive& Archive::operator >>(float& f)
{
	Read((unsigned char *)&f, sizeof(float));
	return *this;
}

Archive& Archive::operator >>(double& d)
{
	Read((unsigned char *)&d, sizeof(double));
	return *this;
}

Archive& Archive::operator >>(int& i)
{
	Read((unsigned char *)&i, sizeof(int));
	//printf("Archive& Archive::operator >>(int& i = %d)\n", i);
	return *this;
}

Archive& Archive::operator >>(short& w)
{
	Read((unsigned char *)&w, sizeof(short));
	//printf("Archive& Archive::operator >>(short& w = %d)\n", w);
	return *this;
}

Archive& Archive::operator >>(char& ch)
{
	Read((unsigned char *)&ch, sizeof(char));
	return *this;
}


#if USE_SIZE_T_IN_ARCHIVE
/*
Archive& Archive::operator >>(__w64 unsigned& u)
{
	Read((unsigned char *)&u, sizeof(__w64 unsigned));
	return *this;
}*/

Archive& Archive::operator >>(size_t& u)
{
	Read((unsigned char *)&u, sizeof(size_t));
	return *this;
}
#else
Archive& Archive::operator >>(unsigned& u)
{
	Read((unsigned char *)&u, sizeof(unsigned));
	return *this;
}
#endif

Archive& Archive::operator >>(bool& b)
{
	Read((unsigned char *)&b, sizeof(bool));
	//printf("Archive& Archive::operator >>(const bool& b = %d)\n", b);
	return *this;
}
Archive& Archive::operator >>(ULONGLONG& dwdw)
{
	Read((unsigned char *)&dwdw, sizeof(ULONGLONG));
	return *this;
}
Archive& Archive::operator >>(LONGLONG& dwdw)
{
	Read((unsigned char *)&dwdw, sizeof(LONGLONG));
	return *this;
}
//------------------------------------------------------

Archive& operator <<(Archive& ar, CPoint4& point)
{
	ar << point.bVisible;
	ar << point.x;
	ar << point.y;
	ar << point.z;
	ar << point.v;
	return ar;
}
Archive& operator <<(Archive& ar, CPoint3& point)
{
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)\n");
	ar << point.flag;
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)point.flag = %ld\n", point.flag);
	ar << point.bVisible;
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)point.bVisible = %d\n", point.bVisible);
	ar << point.x;
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)point.x = %f\n", point.x);
	ar << point.y;
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)point.y = %f\n", point.y);
	ar << point.z;
//printf("Archive& operator <<(Archive& ar, const CPoint3& point)point.z = %f\n", point.z);
	return ar;
}
Archive& operator <<(Archive& ar, CPoint2& point)
{
	ar << point.bVisible;
	ar << point.x;
	ar << point.y;
	return ar;
}
Archive& operator <<(Archive& ar, ProfileAttachPoint& pa)
{
	ar << pa.bAttached;
	ar << pa.xMap;
	ar << pa.xProfile;
	ar << pa.yMap;
	return ar;
}

Archive& operator <<(Archive& ar, SurfLineIntersectPoint& p)
{
	ar << p.i_surf1;
	ar << p.back;
	ar << p.dist_to_end;

	ar << p.i1_1;
	ar << p.i2_1;

	ar << p.i_surf2;
	ar << p.i1_2;
	ar << p.i2_2;
	ar << p.unvisibles;
	ar << p.dst_to_vis;

	ar << p.with_krovlja;

	ar << p.point;

	return ar;
}

Archive& operator <<(Archive& ar, TWO& two)
{
	ar << two.i1;
	ar << two.i2;
	return ar;
}
Archive& operator <<(Archive& ar, TRIA& tria)
{
	ar << tria.i1;
	ar << tria.i2;
	ar << tria.i3;
	return ar;
}
//***********************************************************
Archive& operator >>(Archive& ar, CPoint4& point)
{
	ar >> point.bVisible;
	ar >> point.x;
	ar >> point.y;
	ar >> point.z;
	ar >> point.v;
	return ar;
}
Archive& operator >>(Archive& ar, CPoint3& point)
{
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)\n");
	ar >> point.flag;
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)point.flag = %ld\n", point.flag);
	ar >> point.bVisible;
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)point.bVisible = %d\n", point.bVisible);
	ar >> point.x;
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)point.x = %f\n", point.x);
	ar >> point.y;
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)point.y = %f\n", point.y);
	ar >> point.z;
//printf("Archive& operator >>(Archive& ar, const CPoint3& point)point.z = %f\n", point.z);
	return ar;
}
Archive& operator >>(Archive& ar, CPoint2& point)
{
	ar >> point.bVisible;
	ar >> point.x;
	ar >> point.y;
	return ar;
}
Archive& operator >>(Archive& ar, ProfileAttachPoint& pa)
{
	ar >> pa.bAttached;
	ar >> pa.xMap;
	ar >> pa.xProfile;
	ar >> pa.yMap;
	return ar;
}
Archive& operator >>(Archive& ar, SurfLineIntersectPoint& p)
{
	ar >> p.i_surf1;
	ar >> p.back;
	ar >> p.dist_to_end;

	ar >> p.i1_1;
	ar >> p.i2_1;

	ar >> p.i_surf2;
	ar >> p.i1_2;
	ar >> p.i2_2;
	ar >> p.unvisibles;
	ar >> p.dst_to_vis;

	ar >> p.with_krovlja;

	ar >> p.point;

	return ar;
}
Archive& operator >>(Archive& ar, TWO& two)
{
	ar >> two.i1;
	ar >> two.i2;
	return ar;
}
Archive& operator >>(Archive& ar, TRIA& tria)
{
	ar >> tria.i1;
	ar >> tria.i2;
	ar >> tria.i3;
	return ar;
}
//-----------------------------------------------------------

Archive& operator <<(Archive& ar, RECT& rect)
{
	ar << rect.left;
	ar << rect.top;
	ar << rect.right;
	ar << rect.bottom;
	return ar;
}
Archive& operator <<(Archive& ar, POINT point)
{
	ar << point.x;
	ar << point.y;
	return ar;
}
Archive& operator <<(Archive& ar, SIZE size)
{
	ar << size.cx;
	ar << size.cy;
	return ar;
}




Archive& operator >>(Archive& ar, RECT& rect)
{
	ar >> rect.left;
	ar >> rect.top;
	ar >> rect.right;
	ar >> rect.bottom;
	return ar;
}
Archive& operator >>(Archive& ar, POINT& point)
{
	ar >> point.x;
	ar >> point.y;
	return ar;
}
Archive& operator >>(Archive& ar, SIZE& size)
{
	ar >> size.cx;
	ar >> size.cy;
	return ar;
}

Archive& operator >>(Archive& ar, Trace& tr)
{
	ar >> tr.iFirst;
	ar >> tr.nPts;
	return ar;
}

Archive& operator <<(Archive& ar, Trace& tr)
{
	ar << tr.iFirst;
	ar << tr.nPts;
	return ar;
}

Archive& operator <<(Archive& ar, Vertex& vx)
{
	ar << vx.x;
	ar << vx.y;
	return ar;
}

Archive& operator >>(Archive& ar, Vertex& vx)
{
	ar >> vx.x;
	ar >> vx.y;
	return ar;
}


bool Archive::ReadFileBlockHeader(FileBlockInfo& fbi)
{
	DWORD read = 0;
	read += Read((unsigned char *)&fbi.blockStartID, sizeof(LONG));
	if (read == sizeof(LONG))
	{
		if (fbi.blockStartID == fbi.fileEndID)
		{
			printf ("this is end of file\n");
			return false;
		}		
		if (fbi.blockStartID != 0x5395ab52)
		{
			printf ("warning: this is not blockStartID\n");
			return false;
		}
		read += Read((unsigned char *)&fbi.blockType, sizeof(LONG));
		read += Read((unsigned char *)&fbi.blockVersion, sizeof(LONG));
		read += Read((unsigned char *)&fbi.blockSize, sizeof(DWORD));
		DWORD sizeof_fbi = 3*sizeof(LONG) + sizeof(DWORD);
		if (read == sizeof_fbi)
			return true;
		else 
			return false;
	}
	else
		return false;
		

}

Archive& operator <<(Archive& ar, FileBlockInfo& fbi)
{
	ar << fbi.blockStartID;
	ar << fbi.blockType;
	ar << fbi.blockVersion;
	fbi.m_blockSize_filePointer = ar.GetFileSize();
	if (fbi.m_blockSize_filePointer == 0xffffffff)
	{
		printf ("warning: can not set block size\n");
		fbi.m_toSetBlockSizes = false;
	}
	ar << fbi.blockSize;
	return ar;
}
FileBlockInfo::FileBlockInfo()
{
	this->blockStartID	= 0x5395ab52;
	this->fileEndID		= 0xab525395;
	this->blockType		= 0;
	this->blockVersion	= 0;
	this->blockSize		= 0;

	this->m_blockSize_filePointer = 0xffffffff;
	//this->m_toSetBlockSizes = true;
	this->m_toSetBlockSizes = false;
}


void FileBlockInfo::InitFileBlockHeader(long& type, long& version, DWORD size)
{
	this->blockType		= type;
	this->blockVersion	= version;
	this->blockSize		= size;
	printf("FileBlockInfo::InitFileBlockHeader this->blockType %d this->blockVersion %d\n", this->blockType, this->blockVersion);
}
Archive& operator <<(Archive& ar, const std::string& s)
{
	ar << s.size();
	for (size_t i = 0; i < s.size(); i++)
		ar << s[i];
	//ar << ob.sID.size();
	//ar.WriteString(ob.sID.c_str());
	return ar;
}
Archive& operator <<(Archive& ar, std::string& s)
{
	ar << s.size();
	for (size_t i = 0; i < s.size(); i++)
		ar << s[i];
	//ar << ob.sID.size();
	//ar.WriteString(ob.sID.c_str());
	return ar;
}
Archive& operator >>(Archive& ar, std::string& s)
{
	size_t len;
	ar >> len;
	s.resize(len);
	for (size_t i = 0; i < len; i++)
		ar >> s[i];
	//ar >> len;
	//ob.sID.resize(len+1);
	//ar.ReadString((char *)ob.sID.c_str(), len);

	return ar;
}

#if !defined(AFX_ARCHIVE_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_)
#define AFX_ARCHIVE_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_

#pragma once
#include "AFile.h"

class CPoint4;
class CPoint3;
class CPoint2;
class Layer;

class Poligon3D;

struct ProfileAttachPoint;
struct SurfLineIntersectPoint;
struct TWO;
struct TRIA;

struct Trace;
struct Vertex;

#include <map>
using namespace std ;

class FileBlockInfo
{
	//назначение этого класса состоит в том, чтобы при сохранении документа в файл организовать блочную структуру файла, которая позволяла бы отделить друг от друга логически различные блоки файла
	//заголовок каждого блока файла должен начинаться со следующей структуры
public:
	long fileEndID;
	long blockStartID;
	long blockType;
	long blockVersion;
	DWORD blockSize;

	// В зависимости от типа и версии блока 
	// класс документа должен вызывать 
	// необходимый код записи и чтения файла
	// путём использования вложенных контрукций switch 
	// внутри функций 
	// bool ReadFileBlock(FileBlockInfo& fbi, Archive& ar)
	// WriteFileBlock(FileBlockInfo& fbi, Archive& ar)
	DWORD m_blockSize_filePointer;
	bool m_toSetBlockSizes;
	FileBlockInfo();
	void InitFileBlockHeader(long& type, long& version, DWORD size = 0);
};
//first was 0 !!!
#if !defined( _WIN64) && defined (_MSC_VER)
#define USE_SIZE_T_IN_ARCHIVE 1
#endif
class Archive
{
	AFile * m_pFile;
	int m_nBufSize;
	unsigned char * m_lpBuff;
	bool m_myBuff;

	DWORD sumFlushedToFile;//Сколько байт сброшено в файл 
	DWORD sumWroteToArchive;//Сколько байт записано в архив

	DWORD freeInBuffer;//свободное место во входном буфере
	DWORD wroteInBuffer; // занятое место во входном буфере

	DWORD readFromBuffer;// прочитано из выходного буфера
	DWORD remainedToReadFromBuffer; // осталось прочитать 

	DWORD ReWriteToBuffer(unsigned char * from, DWORD to_BytesFromBegin, DWORD count);
	DWORD ReWriteToFile(unsigned char * from, DWORD to_BytesFromBegin, DWORD count);

	DWORD WriteToBuffer(unsigned char * from, DWORD count);
	DWORD ReadFromBuffer(unsigned char * to, DWORD count);
public:
	void * pDocument;
	DWORD m_use_base_version;//версия объекта Object которую надо использовать при сохранении той или иной версии документа
	DWORD m_use_object_version;//версия объекта - потомка от класса Object которую надо использовать при сохранении той или иной версии документа
	DWORD m_use_primitive_version;//версия объекта - потомка от класса Primitive которую надо использовать при сохранении той или иной версии документа
	enum mode {load, store} ;
private:
	mode m_mode;
public:
	Archive(AFile * pFile, Archive::mode amode, int nBufSize = 4096, void * lpBuff = NULL);
	virtual ~Archive(void);
	bool IsStoring(){ return this->m_mode == Archive::store;}
	bool IsLoading(){ return this->m_mode == Archive::load;}
	AFile * GetFile() {return this->m_pFile;}

	DWORD ReWrite(unsigned char * from, DWORD to_BytesFromBegin, DWORD count);
	DWORD Write(unsigned char * from, DWORD count);
        DWORD Read(unsigned char * to, DWORD count);
	void Flush(void);
	void Close(void);

	void ClearReadBuffer(void);
	void ClearWriteBuffer(void);

	DWORD WriteString(LPCTSTR str);
	LPTSTR ReadString(LPTSTR lpsz, DWORD nMax);

	template <class T> size_t ReadStdVectorAsImport(std::vector<T>& v);
	template <class K, class T> void ReadStdMapAsImport(std::map<K,T>& m);

	DWORD GetFileSize(){return sumWroteToArchive;}

	bool ReadFileBlockHeader(FileBlockInfo& fbi);
	friend Archive& operator <<(Archive& ar, FileBlockInfo& fbi);

	Archive& operator <<(BYTE by);
	Archive& operator <<(WORD w);
	Archive& operator <<(LONG l);
	Archive& operator <<(DWORD dw);
//	Archive& operator <<(LONG_PTR lp);
	Archive& operator <<(float f);
	Archive& operator <<(double d);
	Archive& operator <<(int i);
	Archive& operator <<(short w);
	Archive& operator <<(char ch);
#if USE_SIZE_T_IN_ARCHIVE
//	Archive& operator <<(__w64 unsigned u);
	Archive& operator <<(size_t u);
#else
	Archive& operator <<(unsigned u);
#endif
	Archive& operator <<(bool b);
#if defined (_MSC_VER)
	Archive& operator <<(ULONGLONG dwdw);
	Archive& operator <<(LONGLONG dwdw);
#endif
	friend Archive& operator <<(Archive& ar, RECT& rect);
	friend Archive& operator <<(Archive& ar, POINT point);
	friend Archive& operator <<(Archive& ar, SIZE size);
	friend Archive& operator <<(Archive& ar, CPoint4& point);
	friend Archive& operator <<(Archive& ar, CPoint3& point);
	friend Archive& operator <<(Archive& ar, CPoint2& point);
	friend Archive& operator <<(Archive& ar, ProfileAttachPoint& pa);
	friend Archive& operator <<(Archive& ar, SurfLineIntersectPoint& pa);
	friend Archive& operator <<(Archive& ar, TWO& two);
	friend Archive& operator <<(Archive& ar, TRIA& tria);

	Archive& operator >>(BYTE& by);
	Archive& operator >>(WORD& w);
	Archive& operator >>(LONG& l);
	Archive& operator >>(DWORD& dw);
//	Archive& operator >>(LONG_PTR& lp);
	Archive& operator >>(float& f);
	Archive& operator >>(double& d);
        Archive& operator >>(int& i);
        Archive& operator >>(short& w);
	Archive& operator >>(char& ch);
#if USE_SIZE_T_IN_ARCHIVE
//	Archive& operator >>(__w64 unsigned& u);
	Archive& operator >>(size_t & u);
#else
	Archive& operator >>(unsigned& u);
#endif
	Archive& operator >>(bool& b);
#if defined (_MSC_VER)
	Archive& operator >>(ULONGLONG& dwdw);
	Archive& operator >>(LONGLONG& dwdw);
#endif
	friend Archive& operator >>(Archive& ar, RECT& rect);
	friend Archive& operator >>(Archive& ar, POINT& point);
	friend Archive& operator >>(Archive& ar, SIZE& size);
	friend Archive& operator >>(Archive& ar, CPoint4& point);
	friend Archive& operator >>(Archive& ar, CPoint3& point);
	friend Archive& operator >>(Archive& ar, CPoint2& point);
	friend Archive& operator >>(Archive& ar, ProfileAttachPoint& pa);
	friend Archive& operator >>(Archive& ar, SurfLineIntersectPoint& pa);
	friend Archive& operator >>(Archive& ar, TWO& two);
	friend Archive& operator >>(Archive& ar, TRIA& tria);

	friend Archive& operator >>(Archive& ar, Trace& tr);
	friend Archive& operator <<(Archive& ar, Trace& tr);
	friend Archive& operator <<(Archive& ar, Vertex& vx);
	friend Archive& operator >>(Archive& ar, Vertex& vx);
	
	friend Archive& operator <<(Archive& ar, const std::string& s);
	friend Archive& operator <<(Archive& ar, std::string& s);
	friend Archive& operator >>(Archive& ar, std::string& s);


	friend Archive& operator <<(Archive& ar, std::vector<Poligon3D *>& v);
	friend Archive& operator >>(Archive& ar, std::vector<Poligon3D *>& v);


	static bool OpenFileAsImport;
};

#if 0
template <class T> Archive& operator <<(Archive& ar, std::vector<T *>& v)
{
	ar << v.size();

	bool allocated = false;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i])
		{
			allocated = true; 
			ar << allocated;
			ar << (*v[i]);
		}
		else
		{
			allocated = false;
			ar << allocated;
		}
	}
	return ar;
}
template <class T> Archive& operator >>(Archive& ar, std::vector<T *>& v)
{
	size_t len;
	ar >> len;

	v.resize(len);

	bool allocated = false;
	for (size_t i = 0; i < v.size(); i++)
	{
		ar >> allocated;
		if (allocated)
		{
			v[i] = new T;
			ar >> (*v[i]);
		}
		else
		{
			v[i] = NULL;
		}
	}
	return ar;
}


#endif
template <class T> Archive& operator <<(Archive& ar, std::vector<T>& v)
{

	ar << v.size();

	for (size_t i = 0; i < v.size(); i++)
	{
		ar << v[i];

	}
	return ar;
}
template <class T> Archive& operator >>(Archive& ar, std::vector<T>& v)
{
	//printf("Archive& operator >>(Archive& ar, std::vector<T>& v)\n");
	size_t len;
	ar >> len;
	//printf("Archive& operator >>(Archive& ar, std::vector<T>& v) len = %u\n", len);
	v.resize(len);
	for (size_t i = 0; i < v.size(); i++)
	{
		ar >> v[i];
		//printf("i = %u len = %u\n", i, len);
	}
	return ar;
}


template <class K, class T> Archive& operator <<(Archive& ar, std::map<K,T>& m)
{
	ar << m.size();
    typename std::map <K, T>::const_iterator m1_Iter;
	for ( m1_Iter = m.begin( ); m1_Iter != m.end( ); m1_Iter++ )
	{
		ar << m1_Iter -> first;
		ar << m1_Iter -> second;
	}
	return ar;
}
template <class K, class T> Archive& operator >>(Archive& ar, std::map<K,T>& m)
{
	size_t len;
	ar >> len;
	K key;
	T val;		
	m.clear();
	for ( size_t i = 0; i < len; i++ )
	{
		ar >> key;
		ar >> val;
		m.insert( pair <K, T>( key, val ) );
	}
	return ar;
}


template <class T> size_t Archive::ReadStdVectorAsImport(std::vector<T>& v)
{

	size_t len0 = v.size();
	size_t len;		
	(*this) >> len;

	v.resize(len+len0);
	for (size_t i = 0; i < len; i++)
	{
		(*this) >> v[i+len0];
		//printf("i = %u len = %u\n", i, len);
	}
	return len+len0;
}
	
template <class K, class T> void Archive::ReadStdMapAsImport(std::map<K,T>& m)
{
	size_t len;
	(*this) >> len;
	K key;
	T val;		
	for ( size_t i = 0; i < len; i++ )
	{
		(*this) >> key;
		(*this) >> val;
		m.insert( pair <K, T>( key, val ) );
	}
}
#if defined (_MSC_VER)
#include "Object.h"

class VersionException
{
	DWORD							m_version;
public:
	enum version_exception_type		{cannot_load, cannot_store};
	version_exception_type			m_ex_type;
	Object::object_type				m_object_type;

	VersionException(DWORD v, VersionException::version_exception_type ex_type, Object::object_type ob_type)
	{
		m_version			= v;
		m_ex_type			= ex_type;
		m_object_type		= ob_type;
	}

	string Explane()
	{
		string s = "";
		switch(m_ex_type)
		{
		case cannot_load:
			{
				s += "Cannot load ";
			}
			break;
		case cannot_store:
			{
				s += "Cannot store ";
			}
			break;
		}
		s += Object::ObjectTypeToString(this->m_object_type);
		s += " of version ";
		string sv;
		sv.resize(32);
		sprintf_s((char *)sv.data(), 32, "%d", m_version);
		s += sv;
		return s;
	}
};
#endif




#endif //!defined(AFX_ARCHIVE_H__5BDF9CA3_180D_4A9B_8116_BD24AC493B65__INCLUDED_)

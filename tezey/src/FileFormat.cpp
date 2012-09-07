#include "FileFormat.h"
#include "StdAfx.h"
#include "generic.h"
#include "raporto.h"

//typedef unsigned short WORD;
//typedef unsigned int   DWORD;
#include "GraphsDoc.h"
#include "GraphsView.h"
#include "XYZBuffer.h"

extern Vector<CGraphsDoc> vDoc;
extern char szPath[];
extern double datenum(int y, int mo, int d, int h, int mi, int s, int milli);
extern void datevec(double dn, int& y, int& mo, int& d, int& h, int& mi, int& s, int& milli);
extern void datevec(double dn, SYSTEMTIME& tm);
extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);

// СТРУКТУРА, КОТОРАЯ ПИШЕТСЯ В САМОЕ НАЧАЛО ФАЙЛА И СЛУЖИТ ДЛЯ ОПРЕДЕЛЕНИЯ ВЕРСИИ ФАЙЛА, РАЗМЕРА ШАПКИ, ХАРАКТЕРНОЙ ДЛЯ ЭТОЙ ВЕРСИИ
struct VARIATIONS_FILE_VERSION
{
	WORD	wVersion;
	DWORD	dwHeaderSize;
	bool	bIsFileEncrypted;
	BYTE	Reserved;
	BYTE	szReserved[3];
};
// СТРУКТУРА ШАПКИ ФАЙЛА ВАРИАЦИЙ ВЕРСИИ 1
struct VARIATIONS_FILE_HEADER_1
{
	struct RESEARCH_DATE
	{
		WORD wYear;
		WORD wMonth;
		WORD wDay;
		WORD wDayOfWeek;
	}DateOfResearch;
	struct START_RECORD_TIME
	{
		WORD wHour;
		WORD wMinute;
		WORD wSecond;
		WORD wMilliseconds;
	}BeginTime;
	struct RECORD_TIME
	{
		WORD wHour;
		WORD wMinute;
		WORD wSecond;
		WORD wMilliseconds;
	}FinishTime;
	WORD	wInstrumentNumber;//номер прибора
	WORD	wSizeOfRecord;
	DWORD	dwNumberOfWroteRecords;
	DWORD	dwNumberOfWroteCorrectRecords;
	char	szNameOfResearchPoint[172];
	double	LatitudeOfResearchPoint;//Широта точки наблюдения
	double	LognitudeOfResearchPoint;// Долгота точка наблюдения
	DWORD	dwReserved;
	BYTE	Reserved[10];
};

struct RECORD
{
	BYTE time[3];
	BYTE data[8];
};

BOOL WriteRecord( HANDLE hFile, LPVOID lpRecord, DWORD sizeof_header, DWORD sizeof_Record, DWORD dwRecord, BOOL bFlush )
{
   DWORD  dwWritten;
   BOOL   bRet;

   // Заблокировать область файла, в которой должны быть внесены изменения.
   //...............................
   if ( !LockFile( hFile, sizeof_header + dwRecord*sizeof_Record, 0, sizeof_Record, 0 ) )
      return( FALSE );

   // Записать данные.
   //..................
   SetFilePointer( hFile, sizeof_header + dwRecord*sizeof_Record, 0, FILE_BEGIN );
   bRet = WriteFile( hFile, lpRecord, sizeof_Record, &dwWritten, NULL );

	if (bRet)
	{
		if(dwWritten != sizeof_Record)
			bRet = FALSE;
	}
   // Выполнить очистку буферов файла в случае необходимости.
   //.............................
   if ( bFlush )
      FlushFileBuffers( hFile );

   // Разблокировать обновляемую область файла.
   //.................................
   UnlockFile( hFile, sizeof_header + dwRecord*sizeof_Record, 0, sizeof_Record, 0 );

   return( bRet );
}

BOOL ReadRecord( HANDLE hFile, LPVOID lpRecord, DWORD sizeof_header, DWORD sizeof_Record, DWORD dwRecord)
{
   DWORD  dwRealRead;
   BOOL   bRet;

   // Заблокировать область файла, в которой должны быть внесены изменения.
   //...............................
   if ( !LockFile( hFile, sizeof_header + dwRecord*sizeof_Record, 
	   0, sizeof_Record, 0 ) )
      return( FALSE );

   // Read данные.
   //..................
   SetFilePointer( hFile, sizeof_header + dwRecord*sizeof_Record, 
	   0, FILE_BEGIN );
   bRet = ReadFile( hFile, lpRecord, sizeof_Record, &dwRealRead, NULL );
	if (bRet)
	{
		if(dwRealRead != sizeof_Record)
			bRet = FALSE;
	}
   // Разблокировать обновляемую область файла.
   //.................................
   UnlockFile( hFile, sizeof_header + dwRecord*sizeof_Record, 0, sizeof_Record, 0 );

   return( bRet );
}


void DecodeTimeOfDay(BYTE time_of_day_string[], WORD& h, WORD& mi, WORD& s, WORD &milli)
{
	BYTE B, b;
	WORD W;

	B = time_of_day_string[2];
	B &= 0x7F; //0x01111111b;
	W = (WORD)B;
	milli = 10*W;
	//-----------------------
	B = time_of_day_string[2];
	B >>= 7;
	b = time_of_day_string[1];
	b &= 0x1F; //0x00011111b;
	b <<= 1;
	B |= b;
	s = (WORD)B;
	//-----------------------
	B = time_of_day_string[1];
	B >>= 5;
	b = time_of_day_string[0];
	b &= 0x07; //0x00000111b;
	b <<= 3;
	B |= b;
	mi = (WORD)B;
	//-----------------------
	B = time_of_day_string[0];
	B >>= 3;
	h = (WORD)B;
	//-----------------------
}

void CodeTimeOfDay(SYSTEMTIME& tm, BYTE time_of_day_string[])
{
	BYTE h		= (BYTE)(tm.wHour);
	BYTE mi		= (BYTE)(tm.wMinute);
	BYTE s		= (BYTE)(tm.wSecond);
	BYTE santi	= (BYTE)((tm.wMilliseconds+5)/10);

	if(santi == 100)
	{
		santi = 0;
		s++;
		if(s == 60)
		{
			s = 0;
			mi++;
			if(mi == 60)
			{
				mi = 0;
				h++;
			}
		}
	}

	BYTE B, buff;
	B = 0;
	h <<=3;
	B |= h;
	
	buff = mi;
	buff >>= 3;
	B |= buff;

	time_of_day_string[0] = B;

	B = 0;
	buff = mi;
	buff <<= 5;
	B |= buff;

	buff = s;
	buff >>= 1;
	B |= buff;

	time_of_day_string[1] = B;

	B = 0;
	buff = s;
	buff <<= 7;
	B |= buff;

	buff = santi;
	B |= buff;

	time_of_day_string[2] = B;

}
void compress_key(unsigned char keystring[], unsigned char* compressed_keystring)
{
	//BYTE B;
	int i, iByte;
//	for(iByte = 0; iByte <=8; iByte++)
//	{
		// выбираем очередной байт
		//B = (BYTE)(keystring[iByte]);
//		printf_bits(keystring[iByte]);
//		if(iByte!=8)printf(" ");
//	}
	// printf("\n");
	//--------------------------------------------
	// сжатие на 8-й бит каждого байта
	// организуем цикл по байтам буфера
	for(iByte = 0; iByte <=8; iByte++)
	{
		// выбираем очередной байт
		// B = (BYTE)(keystring[iByte]);
		// устанавливаем его в соответствующее место в сжатой строке
		compressed_keystring[iByte] = keystring[iByte];
		// смещаем его влево на 1 бит, 
		// таким образом во всех байтах 
		// принудительно включенный  восьмой бит удаляется
		compressed_keystring[iByte] <<= 1;
	}
//	for(iByte = 0; iByte <=8; iByte++)
//	{
		// выбираем очередной байт
		// B = (BYTE)(compressed_keystring[iByte]);
//		printf_bits(compressed_keystring[iByte], 7);
//		if(iByte!=8)printf(" ");
//	}
	for(iByte = 1; iByte <=8; iByte++)
	{
		// 
		for(i=iByte;i<=8;i++)
		{
			// если старший бит байта включён, 
			if( compressed_keystring[i] & 0x80)
				// включаем младший бит у предыдущего байта
				compressed_keystring[i-1] |= 0x01;
		}
		for(i=iByte;i<=8;i++)
		{
			// смещаем текущий байт влево на 1 бит
			compressed_keystring[i] <<= 1;
		}
	}
	
	//--------------------------------------------
	//printf("\n");
//	for(iByte = 0; iByte <=8; iByte++)
//	{
		// выбираем очередной байт
		// B = (BYTE)(compressed_keystring[iByte]);
//		printf_bits(compressed_keystring[iByte]);
//		if(iByte!=8)printf(" ");
//	}
//	printf("\n");

}
bool decrypt_compressed(unsigned char compressed_string[], DWORD &x, DWORD &y, DWORD &z)
{
	bool bIsCorrectData = compressed_string[7] & 0x01;
	//--------------------------------------------
	// Пусть в несжатой строке имелся n-й бит (n != 8) m-го байта 
	// нумерацию битов и байтов начнём с 1-цы
	// Выведем формулу определения новых номеров 
	// n2 бита и m2 байта в этой строке
	// 
	//   N  = (m-1)*7 + (8-n);
	//   m2 = 1 + (N-1)/8;
	//   n2 = 1 + 8 - (N - (m2-1)*8);
	//--------------------------------------------
	int i,j;

	// определяем номер используемого ключевого слова
	unsigned char nKey = 0;
	// если включены 7-ые биты в 7-ом,8-ом и 9-ом байте 
	// включаем 1,2,3-й биты в nKey 
	// при этом определяем номера ключевого слова в интервале 0-7
	// затем обнуляем седьмой бит
	// --------------------------------------------
	//	таблица пересчёта кодировки номера ключа
	// --------------------------------------------
	//		m		n		N		m2		n2
	// --------------------------------------------
	//		7		7		43		6-1		6
	//		8		7		50		7-1		7
	//		9		7		57		8-1		8
	// --------------------------------------------

	if (compressed_string[5] & 0x20)	//00100000b
		nKey |= 0x01;
	compressed_string[5] &= 0xDF;		//11011111b

	if (compressed_string[6] & 0x40)	//01000000b
		nKey |= 0x02;
	compressed_string[6] &= 0xBF;		//10111111b01111111b

	if (compressed_string[7] & 0x80)	//10000000b
		nKey |= 0x04;
	compressed_string[7] &= 0x7F;		//

//	printf(" nKey3 = %d ", nKey);
//return;
	// ключевое слово кодировки должно состоять из символов <= 127 
	// и иметь длину равную числу байт данных * 8
	// композитное ключевое слово состоит из 8-ми ключевых слов по 11 байт каждое
	unsigned char keystring[] = "b3defg9o3mrq8ue98v63fwajh68urw1kib4t7re6fjwbt7h3bd98tgc896j9uicf69bcx64";
	int sizeof_keystring = sizeof(keystring);//72
//	printf("sizeof_keystring = %d\n",sizeof_keystring);
	// проверяем чтобы 8-й бит в каждом байте ключевого слова был выключен
	for (i = 0; i < sizeof_keystring; i++)
		keystring[i] &= 0x7F; //01111111b
	// проверяем чтобы 7-й бит в 6,7,8 байте каждого ключевого слова в составе композитного был выключен
	for (j = 0; j < 8; j++)
		for (i = 6; i < 9; i++)
			keystring[9*j+i] &= 0x3F; //00111111b
	// сжимаем ключевое слово
	unsigned char compressed_keystring[65];
	for (j = 0; j < 8; j++)
		compress_key(keystring + 9*j, compressed_keystring + 8*j);
//	printf("compressed_keystring = %s\n", compressed_keystring);
	
	// раскодировка
	for (i = 0; i < 8; i++)
		compressed_string[i] ^= compressed_keystring[nKey*8+i];
//	printf("compressed_string = %s\n", compressed_string);

	DWORD xbuff;
	DWORD ybuff;
	DWORD zbuff;

	x = 0;
	y = 0;
	z = 0;

	// --------------------------------------------
	//	таблица пересчёта старших семи бит x, y, z
	// --------------------------------------------
	//		m		n		N		m2		n2
	// --------------------------------------------
	// x1	7		1		49		7-1		8
	// x2	7		7		43		6-1		6
	//
	// y1	8		1		56		7-1		1
	// y2	8		7		50		7-1		7
	//
	// z2	9		1		63		8-1		2
	// z2	9		7		57		8-1		8
	// --------------------------------------------
	
	zbuff = 0;
	memset(&zbuff,compressed_string[7],1);
	zbuff &= 0xFE; //11111110b
	z |= zbuff;
	z<<=6;

	ybuff = 0;
	memset(&ybuff,compressed_string[6],1);
	ybuff &= 0x7F; //01111111b
	y |= ybuff;
	y<<=7;

	xbuff = 0;
	memset(&xbuff,compressed_string[5],1);
	xbuff &= 0x3F; //00111111b
	xbuff <<= 1;
	if (compressed_string[6] & 0x80)
		xbuff |= 0x01;
	x |= xbuff;
	x<<=7;
	// --------------------------------------------
	//	таблица пересчёта средних семи бит x, y, z
	// --------------------------------------------
	//		m		n		N		m2		n2
	// --------------------------------------------
	// x1	4		1		28		4-1		5
	// x2	4		7		22		3-1		3
	//
	// y1	5		1		35		5-1		6
	// y2	5		7		29		4-1		4
	//
	// z1	6		1		42		6-1		7
	// z2	6		7		36		5-1		5
	// --------------------------------------------

	zbuff = 0;
	memset(&zbuff,compressed_string[4],1);
	zbuff &= 0x1F; //00011111b
	zbuff <<=2;
	z |= zbuff;
	zbuff = 0;
	memset(&zbuff,compressed_string[5],1);
	zbuff &= 0xC0; //11000000b
	zbuff >>=6;
	z |= zbuff;
	z<<=7;
	
	ybuff = 0;
	memset(&ybuff,compressed_string[3],1);
	ybuff &= 0x0F; //00001111b
	ybuff <<= 3;
	y |= ybuff;
	ybuff = 0;
	memset(&ybuff,compressed_string[4],1);
	ybuff &= 0xE0; //11100000b
	ybuff >>= 5;
	y |= ybuff;
	y<<=7;
	
	xbuff = 0;
	memset(&xbuff,compressed_string[2],1);
	xbuff &= 0x07; //00000111b
	xbuff <<= 4;
	x |= xbuff;
	xbuff = 0;
	memset(&xbuff,compressed_string[3],1);
	xbuff &= 0xF0; //11110000b
	xbuff >>= 4;
	x |= xbuff;
	x<<=7;

	// --------------------------------------------
	//	таблица пересчёта младших семи бит x, y, z
	// --------------------------------------------
	//		m		n		N		m2		n2
	// --------------------------------------------
	// x1	1		1		7		1-1		2
	// x2	1		7		1		1-1		8
	//
	// y1	2		1		14		2-1		3
	// y2	2		7		8		1-1		1
	//
	// z1	3		1		21		3-1		4
	// z2	3		7		15		2-1		2
	// --------------------------------------------

	zbuff = 0;
	memset(&zbuff,compressed_string[1],1);
	zbuff &= 0x03; //00000011b
	zbuff <<= 5;
	z |= zbuff;
	zbuff = 0;
	memset(&zbuff,compressed_string[2],1);
	zbuff &= 0xF8; //11111000b
	zbuff >>= 3;
	z |= zbuff;

	ybuff = 0;
	memset(&ybuff,compressed_string[0],1);
	ybuff &= 0x01; //00000001b
	ybuff <<= 6;
	y |= ybuff;
	ybuff = 0;
	memset(&ybuff,compressed_string[1],1);
	ybuff &= 0xFC; //11111100b
	ybuff >>= 2;
	y |= ybuff;

	xbuff = 0;
	memset(&xbuff,compressed_string[0],1);
	xbuff &= 0xFE; //11111110b
	xbuff >>= 1;
	x |= xbuff;
	return bIsCorrectData;
}



int openVarFile(bool bIsSignal2Checked)
{
//MessageBox(0, szPath, "open", 
//	MB_OK | MB_ICONINFORMATION);
WriteRaporto("import 1\n");
	WORD d, mo, h, mi, s, milli, year;
	DWORD X, Y, Z;
	int rez;
	DWORD maxX, minX, 
		maxY, minY,
		maxZ, minZ;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "var") == 0)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;

		if (p)
		{
			rez = sscanf(p,"%s%d_%d_%d.csv",
				&szBuff, &d, &mo, &year);
			if (rez == 4 && rez != EOF)
			{
				//char str[100];
				//sprintf(str, "%s%d_%d_%d.csv", szBuff, &d, &mo, &year);
				//MessageBox(0,str,"",0);

				year/=100;
				year*=100;
			}
			else
			{
				//MessageBox(0,"2000","",0);
				year = 2000;
			}
		}
		RECORD Record;
		// СТРУКТУРА, КОТОРАЯ ПИШЕТСЯ В САМОЕ НАЧАЛО ФАЙЛА И СЛУЖИТ ДЛЯ ОПРЕДЕЛЕНИЯ ВЕРСИИ ФАЙЛА, РАЗМЕРА ШАПКИ, ХАРАКТЕРНОЙ ДЛЯ ЭТОЙ ВЕРСИИ
		VARIATIONS_FILE_VERSION vfVersion;
		// СТРУКТУРА ШАПКИ ФАЙЛА ВАРИАЦИЙ ВЕРСИИ 1
		VARIATIONS_FILE_HEADER_1 vfHeader1;


		HANDLE hFile;
		if(INVALID_HANDLE_VALUE==(hFile = 
			CreateFile(szPath,
			GENERIC_READ, 
			FILE_SHARE_READ,//0,
			0, OPEN_EXISTING,
			0,0)))
		{
			MessageBox(0, szPath, "file did not opened\nCreateFile",0);
		}
		else
		{
			// Если открыт уже существующий файл
			// Читаем структуру заголовка
			if (ReadRecord(hFile, &vfVersion,
				0,
				sizeof(VARIATIONS_FILE_VERSION), 
				0))
			{
				switch (vfVersion.wVersion)
				{
				case 1:
					{
						if (vfVersion.dwHeaderSize !=
							sizeof(VARIATIONS_FILE_HEADER_1))
							MessageBox(0,
							"Размер заголовка не соответствует номеру версии\nHeader size does not correspond to version number","",0);
						if(ReadRecord(hFile, 
							&vfHeader1,
							sizeof(VARIATIONS_FILE_VERSION),
							// vfVersion.dwHeaderSize,
							sizeof(VARIATIONS_FILE_HEADER_1),
							0))
						{
							char str[1024];
							sprintf(str,"vfHeader1.DateOfResearch.wDay(%d)\nvfHeader1.DateOfResearch.wDayOfWeek(%d)\nvfHeader1.DateOfResearch.wMonth(%d)\nvfHeader1.DateOfResearch.wYear(%d)\n",
								vfHeader1.DateOfResearch.wDay,
								vfHeader1.DateOfResearch.wDayOfWeek,
								vfHeader1.DateOfResearch.wMonth, 
								vfHeader1.DateOfResearch.wYear);
							//MessageBox(0,str,"",0);
							sprintf(str,"vfHeader1.BeginTime.wHour(%d)\nvfHeader1.BeginTime.wMinute(%d)\nvfHeader1.BeginTime.wSecond(%d)\nvfHeader1.BeginTime.wMilliseconds(%d)\nvfHeader1.FinishTime.wHour(%d)\nvfHeader1.FinishTime.wMinute(%d)\nvfHeader1.FinishTime.wSecond(%d)\nvfHeader1.FinishTime.wMilliseconds(%d)",
								vfHeader1.BeginTime.wHour,
								vfHeader1.BeginTime.wMinute,
								vfHeader1.BeginTime.wSecond,
								vfHeader1.BeginTime.wMilliseconds,
								vfHeader1.FinishTime.wHour,
								vfHeader1.FinishTime.wMinute,
								vfHeader1.FinishTime.wSecond,
								vfHeader1.FinishTime.wMilliseconds);
							//MessageBox(0,str,"",0);
							sprintf(str,"vfHeader1.dwReserved = %d\nvfHeader1.dwNumberOfWroteRecords	= %d\nvfHeader1.dwNumberOfWroteCorrectRecords = %d\nvfHeader1.wSizeOfRecord	= %d\nvfHeader1.wInstrumentNumber = %d\nvfHeader1.szNameOfResearchPoint = %s\nvfHeader1.LatitudeOfResearchPoint	= %g\nvfHeader1.LognitudeOfResearchPoint	= %g\n",
									
								vfHeader1.dwReserved,

								vfHeader1.dwNumberOfWroteRecords,
								vfHeader1.dwNumberOfWroteCorrectRecords,
								vfHeader1.wSizeOfRecord,
								vfHeader1.wInstrumentNumber,
								
								vfHeader1.szNameOfResearchPoint,
								vfHeader1.LatitudeOfResearchPoint,
								vfHeader1.LognitudeOfResearchPoint);

							//MessageBox(0,str,"",0);
							for (int iDoc = 0; iDoc < 3; iDoc++)
							{
								if (bIsSignal2Checked)
								{
									vDoc[iDoc].resize2(vfHeader1.dwNumberOfWroteCorrectRecords);
									vDoc[iDoc].m_nInstrumentNumber2 = vfHeader1.wInstrumentNumber;

								}
								else
								{
									vDoc[iDoc].resize(vfHeader1.dwNumberOfWroteCorrectRecords);
									vDoc[iDoc].m_nInstrumentNumber1 = vfHeader1.wInstrumentNumber;
								}
							}
							DWORD iRecord = 0; 

							DWORD i = 0;
							// записываем структуру данных в файл
							while(iRecord < vfHeader1.dwNumberOfWroteRecords && 
								ReadRecord(hFile, &Record,
								sizeof(VARIATIONS_FILE_VERSION)+vfVersion.dwHeaderSize,
								sizeof(RECORD), iRecord))
							{
								DecodeTimeOfDay(Record.time, h, mi, s, milli);
								if( decrypt_compressed(Record.data, X, Y, Z) )
								{
									double t = datenum(vfHeader1.DateOfResearch.wYear, vfHeader1.DateOfResearch.wMonth, vfHeader1.DateOfResearch.wDay, h, mi, s, milli);
									if (i == 0)
									{
										maxX=X;
										minX=X;

										maxY=Y;
										minY=Y;

										maxZ=Z;
										minZ=Z;
									}
									else
									{
										maxX=maxX>X?maxX:X;
										minX=minX<X?minX:X;

										maxY=maxY>Y?maxY:Y;
										minY=minY<Y?minY:Y;

										maxZ=maxZ>Z?maxZ:Z;
										minZ=minZ<Z?minZ:Z;
									}
									if (bIsSignal2Checked)
									{
										vDoc[0].m_t2[i]=t;
										vDoc[1].m_t2[i]=t;
										vDoc[2].m_t2[i]=t;

										vDoc[0].m_T2[i] = X;

										vDoc[1].m_T2[i] = Y;

										vDoc[2].m_T2[i] = Z;
									}
									else
									{

										vDoc[0].m_t[i]=t;
										vDoc[1].m_t[i]=t;
										vDoc[2].m_t[i]=t;

										vDoc[0].m_T[i] = X;

										vDoc[1].m_T[i] = Y;

										vDoc[2].m_T[i] = Z;
									}
									i++;
								}
								iRecord++;
								//sprintf(str,"%d %d",i,iRecord);
								//MessageBox(0,str,"",0);
							}

						}
						else
						{
							MessageBox(0,"Заголовок файла не прочитан\nHeader of the file was not read\n","",0);
						}

					}
					break;
				default:
					{
						MessageBox(0,"Версия файла не поддерживается\nFile version not supported\n", "",0);
					}
				}
			}
			else
				MessageBox(0,"Структура версии файла не прочитана\nFile version structure was not read\n", "",0);

			CloseHandle(hFile);			

			sprintf(szDate,"%d.%02d.%d \0", vfHeader1.DateOfResearch.wDay, vfHeader1.DateOfResearch.wMonth, vfHeader1.DateOfResearch.wYear);
			//MessageBox(0,szDate,"szDate",0);

			strcpy(vDoc[0].m_sTitle,  "Суточный график активности геополяритонного поля  \0");
			strcpy(vDoc[1].m_sTitle,  "Суточный график активности геополяритонного поля  \0");
			strcpy(vDoc[2].m_sTitle,  "Суточный график активности геополяритонного поля \0");

			strcat(vDoc[0].m_sTitle, szDate);
			strcat(vDoc[1].m_sTitle, szDate);
			strcat(vDoc[2].m_sTitle, szDate);

			strcat(vDoc[0].m_sTitle, "  X - компонента\0");
			strcat(vDoc[1].m_sTitle, "  Y - компонента\0");
			strcat(vDoc[2].m_sTitle, "  Z - компонента\0");

			strcpy(vDoc[0].m_sXLabel, "время суток");
			strcpy(vDoc[0].m_sYLabel, "Активность в отсчётах в сенкуду");
			strcpy(vDoc[1].m_sXLabel, "время суток");
			strcpy(vDoc[1].m_sYLabel, "Активность в отсчётах в сенкуду");
			strcpy(vDoc[2].m_sXLabel, "время суток");
			strcpy(vDoc[2].m_sYLabel, "Активность в отсчётах в сенкуду");

		if (bIsSignal2Checked)
		{
			vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,"Сигнал 2 X", "", "", true,true,1,false);
			vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,"Сигнал 2 Y", "", "", true,true,1,false);
			vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,"Сигнал 2 Z", "", "", true,true,1,false);
		}
		else
		{
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, vDoc[0].m_sTitle, "", "", true,true,0,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, vDoc[1].m_sTitle, "", "", true,true,0,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, vDoc[2].m_sTitle, "", "", true,true,0,false);
		}
WriteRaporto("import 5\n");

//		vDoc[0].ReinitVectorsPoints();
//		vDoc[1].ReinitVectorsPoints();
//		vDoc[2].ReinitVectorsPoints();
//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
		}
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
WriteRaporto("import end\n");
	return 1;
}
// здесь надо выбрать один из трёх способов шифрования
// а остальные два закомментировать
// самый надёжный USE_RAND_ENCRYPTING
//#define USE_SIMPLE_ENCRYPTING
//#define USE_PARITY_ENCRYPTING
#define USE_RAND_ENCRYPTING

void encrypt(DWORD x, DWORD y, DWORD z, WORD nPribor, unsigned char outstring[])
{
	int i,j;
	DWORD X = x;
	DWORD Y = y;
	DWORD Z = z;
	WORD N = nPribor;
#ifdef USE_PARITY_ENCRYPTING
	// определяем чётность x,y,z
	BYTE xChet = 0x01;
	for(i = 0; i < 20;i++)
	{
		if((X >> i) & 0x01)
			xChet ^= 0x01;
	}
	BYTE yChet = 0x01;
	for(i = 0; i < 20;i++)
	{
		if((Y >> i) & 0x01)
			yChet ^= 0x01;
	}
	BYTE zChet = 0x01;
	for(i = 0; i < 20;i++)
	{
		if((X >> i) & 0x01)
			zChet ^= 0x01;
	}
#endif
	// unsigned char outstring[14];
	// ключевое слово кодировки должно состоять из символов <= 127 
	// и иметь длину равную числу байт данных * 8
	// композитное ключевое слово состоит из 8-ми ключевых слов по 11 байт каждое
	unsigned char keystring[] = "b3defg9o3mrq8ue98v63fwajh68urw1kib4t7re6fjwbt7h3bd98tgc896j9uicf69bcx64";
	int sizeof_keystring = sizeof(keystring);//72
//	printf("sizeof_keystring = %d\n",sizeof_keystring);
	// проверяем чтобы 8-й бит в каждом байте ключевого слова был выключен
	for (i = 0; i < sizeof_keystring; i++)
		keystring[i] &= 0x7F; //01111111b
//	printf("%s\n",keystring);
	// проверяем чтобы 7-й бит в 6,7,8 байте каждого ключевого слова в составе композитного был выключен
	for (j = 0; j < 8; j++)
		for (i = 6; i < 9; i++)
			keystring[9*j+i] &= 0x3F; // 00111111b

//	printf("%s\n",keystring);

	// символ начала строки
	outstring[0]='^';
	// копируем 3 младших байта x,y,z в outstring
	for (i = 0; i < 3 ; i++)
	{
		// копируем младший байт из четырёх байтовой переменной
		memset(outstring+1+3*i,X,1);
		memset(outstring+2+3*i,Y,1);
		memset(outstring+3+3*i,Z,1);
		// включаем старший (8-й) бит в строковых байтах
		outstring[1+3*i] |= 0x80; //10000000b
		outstring[2+3*i] |= 0x80; //10000000b
		outstring[3+3*i] |= 0x80; //10000000b
		// сдвигаем на семь бит вправо - в сторону младшего байта
		X >>= 7;
		Y >>= 7;
		Z >>= 7;
	}
#ifdef USE_RAND_ENCRYPTING
	unsigned char nKey = (unsigned char)(rand()%8);
	if (nKey & 0x01)		  //00000001b
		outstring[7] |= 0x40; //01000000b
	if (nKey & 0x02)		  //00000010b
		outstring[8] |= 0x40; //01000000b
	if (nKey & 0x04)		  //00000100b
		outstring[9] |= 0x40; //01000000b
#endif
#ifdef USE_PARITY_ENCRYPTING
	
	// кодируем номер используемого ключевого слова
	unsigned char nKey = 0;
	// если включены 1-ые биты в 1-ом,2-ом и 3-ем байте, 
	// тогда включаем 7-ые биты в 7-ом,8-ом и 9-ом байте соответственно
	// иначе
	// обнуляем 7-й бит в 7,8,9 строковых байтах
	// при этом осуществляем выбор номера ключевого слова в интервале 0-7
	if (xChet & 0x01)
	{
		outstring[7] |= 0x40; //01000000b
		nKey |= 0x01;		  //00000001b
	}
	else
		outstring[7] &= 0xBF; //10111111b

	if (yChet & 0x01)
	{
		outstring[8] |= 0x40; //01000000b
		nKey |= 0x02;		  //00000010b
	}
	else
		outstring[8] &= 0xBF; //10111111b

	if (zChet & 0x01)
	{
		outstring[9] |= 0x40; //01000000b
		nKey |= 0x04;		  //00000100b
	}
	else
		outstring[9] &= 0xBF; //10111111b
#endif
#ifdef USE_SIMPLE_ENCRYPTING
	
	// кодируем номер используемого ключевого слова
	unsigned char nKey = 0;
	// если включены 1-ые биты в 1-ом,2-ом и 3-ем байте, 
	// тогда включаем 7-ые биты в 7-ом,8-ом и 9-ом байте соответственно
	// иначе
	// обнуляем 7-й бит в 7,8,9 строковых байтах
	// при этом осуществляем выбор номера ключевого слова в интервале 0-7
	if (outstring[0] & 0x01)
	{
		outstring[7] |= 0x40; //01000000b
		nKey |= 0x01;		  //00000001b
	}
	else
		outstring[7] &= 0xBF; //10111111b

	if (outstring[1] & 0x01)
	{
		outstring[8] |= 0x40; //01000000b
		nKey |= 0x02;		  //00000010b
	}
	else
		outstring[8] &= 0xBF; //10111111b

	if (outstring[2] & 0x01)
	{
		outstring[9] |= 0x40; //01000000b
		nKey |= 0x04;		  //00000100b
	}
	else
		outstring[9] &= 0xBF; //10111111b
#endif
//	printf(" nKey = %d ", nKey);

	// копируем младший байт номера прибора
	memset(outstring+10,N,1);
	// включаем старший (8-й) бит в строковом байте
	outstring[10] |= 0x80; //10000000b
	// сдвигаем на семь бит вправо - в сторону младшего байта
	N >>= 7;
	// копируем младший байт номера прибора
	memset(outstring+11,N,1);
	// включаем старший (8-й) бит в строковом байте
	outstring[11] |= 0x80; //10000000b

	// кодировка
	for (i = 0; i < 9; i++)
		outstring[i+1] ^= keystring[nKey*9+i];
	//-------------------------------------------
	// вычисление контрольной суммы CRC16
	WORD Result;
	BYTE B;
	Result = 0xFFFF;
	// организуем цикл по байтам буфера
	for(int iByte = 1; iByte <=11; iByte++)
	{
		// выбираем очередной байт
		B = (BYTE)(outstring[iByte]);
		// вычисление очередного CRC 
		Result = (Result & 0xFF00) + (B ^ LOBYTE(Result));
		for (int i = 0; i < 8; i++)
		{
			if ((Result & 0x0001) != 0)
				Result = (Result >> 1) ^ 0xA001;
			else
				Result >>= 1;
		}
	}
	//--------------------------------------------
	// под контрольную сумму выделено 3 байта 
	outstring[12] = HIBYTE(Result);
	outstring[13] = LOBYTE(Result);
	outstring[14] = 0xFF;
	// восьмые биты принудительно включаем, 
	// поэтому для сохранения их значений 
	// используем первые два бита третьего байта
	if(!(outstring[12] & 0x80))
	{
		// если восьмой бит нулевой,
		// выключаем соответствующий бит третьего байта
		outstring[14] &= 0xFE; //(~0x01);
		// включаем восьмой бит
		outstring[12] |= 0x80; //10000000b
	}
	if(!(outstring[13] & 0x80))
	{
		// если восьмой бит нулевой,
		// выключаем соответствующий бит третьего байта
		outstring[14] &= 0xFD; //(~0x02);
		// включаем восьмой бит
		outstring[13] |= 0x80; //10000000b
	}
	//--------------------------------------------

	// символ конца строки
	outstring[15]='$';
	outstring[16]='\0';

}



bool test_and_compress_encrypted(unsigned char outstring[], unsigned char* compressed_string, 	WORD &n, bool bCorrectParity)
{
	// ----------------------------------------------------
	// проверка контрольной суммы
	//-------------------------------------------
	// вычисление контрольной суммы CRC16
	WORD Result;
	BYTE B;
	int iByte, i;
	Result = 0xFFFF;
	// организуем цикл по байтам буфера
	for(iByte = 1; iByte <=11; iByte++)
	{
		// выбираем очередной байт
		B = (BYTE)(outstring[iByte]);
		// вычисление очередного CRC 
		Result = (Result & 0xFF00) + (B ^ LOBYTE(Result));
		for (int i = 0; i < 8; i++)
		{
			if ((Result & 0x0001) != 0)
				Result = (Result >> 1) ^ 0xA001;
			else
				Result >>= 1;
		}
	}
	//--------------------------------------------
	// под контрольную сумму выделено 3 байта 
	BYTE byte12 = HIBYTE(Result);
	BYTE byte13 = LOBYTE(Result);
	BYTE byte14 = 0xFF;
	// восьмые биты принудительно включаем, 
	// поэтому для сохранения их значений 
	// используем первые два бита третьего байта
	if(!(byte12 & 0x80))
	{
		// если восьмой бит нулевой,
		// выключаем соответствующий бит третьего байта
		byte14 &= 0xFE; //(~0x01);
		// включаем восьмой бит
		byte12 |= 0x80; //10000000b
	}
	if(!(byte13 & 0x80))
	{
		// если восьмой бит нулевой,
		// выключаем соответствующий бит третьего байта
		byte14 &= 0xFD; //(~0x02);
		// включаем восьмой бит
		byte13 |= 0x80; //10000000b
	}
	bool result = 
		byte12 == outstring[12] &&
		byte13 == outstring[13] &&
		byte14 == outstring[14];
	//--------------------------------------------
	// определяем номер прибора
	WORD nbuff;
	n = 0;
	memset(&nbuff,outstring[11],1);
	// обнуляем старший бит в байте
	nbuff &= 0x7F; //01111111b
	n |= nbuff;
	n<<=7;
	memset(&nbuff,outstring[10],1);
	// обнуляем старший бит в байте
	nbuff &= 0x7F; //01111111b
	n |= nbuff;
	//--------------------------------------------
//	printf("\n");
//	for(iByte = 0; iByte <=8; iByte++)
//	{
		// выбираем очередной байт
		// B = (BYTE)(outstring[iByte+1]);
//		printf_bits(outstring[iByte+1]);
//		if(iByte!=8)printf(" ");
//	}
	// printf("\n");
	//--------------------------------------------
	// сжатие на 8-й бит каждого байта
	// организуем цикл по байтам буфера
	for(iByte = 0; iByte <=8; iByte++)
	{
		// выбираем очередной байт
		// B = (BYTE)(outstring[iByte+1]);
		// устанавливаем его в соответствующее место в сжатой строке
		compressed_string[iByte] = outstring[iByte+1];
		// смещаем его влево на 1 бит, 
		// таким образом во всех байтах 
		// принудительно включенный  восьмой бит удаляется
		compressed_string[iByte] <<= 1;
	}
//	for(iByte = 0; iByte <=8; iByte++)
//	{
//		// выбираем очередной байт
//		// B = (BYTE)(compressed_string[iByte]);
//		printf_bits(compressed_string[iByte], 7);
//		if(iByte!=8)printf(" ");
//	}
	for(iByte = 1; iByte <=8; iByte++)
	{
		// 
		for(i=iByte;i<=8;i++)
		{
			// если старший бит байта включён, 
			if( compressed_string[i] & 0x80)
				// включаем младший бит у предыдущего байта
				compressed_string[i-1] |= 0x01;
		}
		for(i=iByte;i<=8;i++)
		{
			// смещаем текущий байт влево на 1 бит
			compressed_string[i] <<= 1;
		}
	}
	// если проверка контрольной суммы прошла успешно
	if (result && bCorrectParity)
		// включаем первый бит восьмого байта сжатой зашифрованной строки
		compressed_string[7] |= 0x01;
	//--------------------------------------------
//	printf("\n");
//	for(iByte = 0; iByte < 8; iByte++)
//	{
//		// выбираем очередной байт
//		// B = (BYTE)(compressed_string[iByte]);
//		printf_bits(compressed_string[iByte]);
//		if(iByte!=8)printf(" ");
//	}
//	printf("\n");
	//--------------------------------------------
	///Sleep(100000);
	return result;
}

int SaveAs(LPSAVEASFILEDLGDATA lpSaveAsFileDlgData)
{
	if(vDoc[0].m_t.Length() < 2)
	{
		MessageBox(0,"Документ пуст", "Экспорт",0);
		return 0;
	}
	char str[255];
	double t0 = datenum(1900,1,1,0,0,0,0)-2;



	wsprintf(str, "Do you want to export to file:\noutput filename = %s",
		lpSaveAsFileDlgData->szPath);


	if (MessageBox(0, str, "createCommonFile", 
		MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		return 0;
	switch(lpSaveAsFileDlgData->SaveAsFileType)
	{
	case 0: // var
		{
			// номер прибора
			WORD n = 1;
			bool bCorrectCRC16;
			bool bCorrectParity = true;
			unsigned char outstring[18];
			RECORD Record;
			SYSTEMTIME tm;
			if (vDoc[0].m_t.Length() > 0 )
				datevec(vDoc[0].m_t[0],tm);
			// СТРУКТУРА, КОТОРАЯ ПИШЕТСЯ В САМОЕ НАЧАЛО ФАЙЛА И СЛУЖИТ ДЛЯ ОПРЕДЕЛЕНИЯ ВЕРСИИ ФАЙЛА, РАЗМЕРА ШАПКИ, ХАРАКТЕРНОЙ ДЛЯ ЭТОЙ ВЕРСИИ
			VARIATIONS_FILE_VERSION vfVersion;
			// СТРУКТУРА ШАПКИ ФАЙЛА ВАРИАЦИЙ ВЕРСИИ 1
			VARIATIONS_FILE_HEADER_1 vfHeader1;
		
			
			HANDLE hFile;
			if(INVALID_HANDLE_VALUE==(hFile = 
				CreateFile(lpSaveAsFileDlgData->filename,
				GENERIC_READ | GENERIC_WRITE, 
				FILE_SHARE_READ,//0,
				0, CREATE_ALWAYS,
				0,0)))
			{
				ErrorExit("CreateFile");
				break;
			}
			else
			{
				if (ERROR_ALREADY_EXISTS != GetLastError())
				{
					// printf("File was created\n");
					// Если файл только что создан, формируем структуру версии файла
					vfVersion.wVersion			= 1;
					vfVersion.bIsFileEncrypted	= true;
					vfVersion.dwHeaderSize		= sizeof(VARIATIONS_FILE_HEADER_1);
					vfVersion.Reserved			= 0;
					memset(vfVersion.szReserved,0,
						sizeof(vfVersion.szReserved));
					// записываем структуру версии файла в файл
					WriteRecord(hFile, &vfVersion,
						0,
						sizeof(VARIATIONS_FILE_VERSION), 
						0, 
						true );
					// формируем сруктуру заголовка файла
					vfHeader1.DateOfResearch.wDay			= tm.wDay;
					vfHeader1.DateOfResearch.wDayOfWeek		= tm.wDayOfWeek;
					vfHeader1.DateOfResearch.wMonth			= tm.wMonth;
					vfHeader1.DateOfResearch.wYear			= tm.wYear;

					vfHeader1.BeginTime.wHour				= tm.wHour;
					vfHeader1.BeginTime.wMinute				= tm.wMinute;
					vfHeader1.BeginTime.wSecond				= tm.wSecond;
					vfHeader1.BeginTime.wMilliseconds		= tm.wMilliseconds;

					vfHeader1.FinishTime.wHour				= tm.wHour;
					vfHeader1.FinishTime.wMinute			= tm.wMinute;
					vfHeader1.FinishTime.wSecond			= tm.wSecond;
					vfHeader1.FinishTime.wMilliseconds		= tm.wMilliseconds;


					vfHeader1.dwReserved					= 0;

					vfHeader1.dwNumberOfWroteRecords		= 0;
					vfHeader1.dwNumberOfWroteCorrectRecords = 0;
					vfHeader1.wSizeOfRecord					= sizeof(RECORD);
					vfHeader1.wInstrumentNumber				= n;
					memset(
						vfHeader1.szNameOfResearchPoint,
						0,
						sizeof(vfHeader1.szNameOfResearchPoint));
					strcpy(vfHeader1.szNameOfResearchPoint,
						"Artyukhovka\0");
					vfHeader1.LatitudeOfResearchPoint		= 49.;
					vfHeader1.LognitudeOfResearchPoint		= 38.;
					memset(
						vfHeader1.Reserved,
						0, sizeof(vfHeader1.Reserved));
//
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					for(int i = 0; i< vDoc[0].m_t.Length();i++)
					{

						// зашифровываем x,y,z в строку outstring
						// encrypt(x,y,z,n, outstring);
						encrypt((int)vDoc[0].m_T[i], (int)vDoc[1].m_T[i], (int)vDoc[2].m_T[i],n, outstring);			// буфер для сжатой строки
						// сжимаем зашифрованную строку,
						// предварительно проверив контрольную сумму
						BYTE compressed_string[9];
						bCorrectCRC16 = test_and_compress_encrypted(outstring,compressed_string, n, bCorrectParity);


						// КОДИРУЕМ ВРЕМЯ СУТОК
						datevec(vDoc[0].m_t[i],tm);
						CodeTimeOfDay(tm, Record.time);

						for(int ibyte = 0; ibyte < 8; ibyte++)
							Record.data[ibyte] = compressed_string[ibyte];

						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						// записываем структуру данных в файл
						if(WriteRecord(hFile, &Record,
							sizeof(VARIATIONS_FILE_VERSION)+vfVersion.dwHeaderSize,
							sizeof(RECORD), vfHeader1.dwNumberOfWroteRecords, true ))
						{
							vfHeader1.dwNumberOfWroteRecords++;
							if (bCorrectCRC16 && bCorrectParity)
								vfHeader1.dwNumberOfWroteCorrectRecords++;
						}
					}
					// записываем структуру заголовка файла в файл
					WriteRecord(hFile, &vfHeader1,
						sizeof(VARIATIONS_FILE_VERSION),
						sizeof(VARIATIONS_FILE_HEADER_1),
						0, 
						true );
				}
			}
			CloseHandle(hFile);
		
		}
		break;
	case 1: // csv
		{
			FILE *stream2;
			if ((stream2 = fopen(lpSaveAsFileDlgData->szPath,"wt")) == NULL)
			{
				MessageBox(0, "Cannot open output file.\n", "Save As txt", 
					MB_OK | MB_ICONINFORMATION);
					return 0;
			}
			for(int i = 0; i< vDoc[0].m_t.Length();i++)
			{
				int y,mo,d,h,mi,s,milli;
				datevec(vDoc[0].m_t[i],y,mo,d,h,mi,s,milli);
				int yy = y - (y/100)*100;
				if(!(s == 59 && mi == 59 && h == 23))
				{
					milli = ((milli+5)/10)*10;
					if(milli == 1000)
					{
						milli = 0;
						s++;
						if(s == 60)
						{
							s = 0;
							mi++;
							if(mi == 60)
							{
								mi = 0;
								h++;
							}
						}
					}
				}

				fprintf(stream2,"%02d.%02d.%02d %d:%d:%d,%d,%d,%d,%d\n",
					d, mo, yy,h,mi,s,milli,
					(int)vDoc[0].m_T[i], (int)vDoc[1].m_T[i], (int)vDoc[2].m_T[i]);
			}
			fclose(stream2);
		}
		break;
	case 2: // txt
		{
			FILE *stream2;
			if ((stream2 = fopen(lpSaveAsFileDlgData->szPath,"wt")) == NULL)
			{
				MessageBox(0, "Cannot open output file.\n", "Save As txt", 
					MB_OK | MB_ICONINFORMATION);
					return 0;
			}
			for(int i = 0; i< vDoc[0].m_t.Length();i++)
			{
				fprintf(stream2,"%.8f\t%d\t%d\t%d\n", vDoc[0].m_t[i]-t0,
					(int)vDoc[0].m_T[i], (int)vDoc[1].m_T[i], (int)vDoc[2].m_T[i]);
			}
			fclose(stream2);
		}
		break;
	}

	MessageBox(0,lpSaveAsFileDlgData->szPath,"Экспорт завершён", 0);
	return 0;
}

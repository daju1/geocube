// ComPort.cpp: implementation of the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ComPort.h"
#include "raporto.h"
#include "../../tools/src/errorexit.h"

#include "GraphsDoc.h"
#include "GraphsView.h"
#include "XYZBuffer.h"


#ifdef COMMON_RAPORT
extern void WriteRaportoB(LPCTSTR s);
#else
extern void WriteRaportoA(LPCTSTR file, LPCTSTR s);
#endif
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
extern Vector<HWND> vhWndChild;
extern Vector<CGraphsDoc> vDoc;
extern Vector<CGraphsView> vView;
extern HWND hWndClient;
extern bool g_btoReverseCovariation;
extern bool g_bRealTimeCovariationMode;
extern bool g_bRealTimeWaveletMode;
extern bool g_bDisplayMode;
extern DWORD WINAPI AudioWarning(void * p);

extern void datevec(double dn, SYSTEMTIME& tm);

extern double datenum(SYSTEMTIME tm);


#if 0
CString printDCB(DCB& dcb)
{
	CString str, s;
	
	//    DWORD DCBlength;      /* sizeof(DCB)                     */

	s.Format("dcb.DCBlength = %lu\n",dcb.DCBlength);
//	  DWORD BaudRate;       /* Baudrate at which running       */
 	str+=s; 
	s.Format("dcb.BaudRate = %lu\n",dcb.BaudRate);
//    DWORD fBinary: 1;     /* Binary Mode (skip EOF check)    */
	str+=s; 
	s.Format("dcb.fBinary = %lu\n", dcb.fBinary);
//    DWORD fParity: 1;     /* Enable parity checking          */
	str+=s; 
	s.Format("dcb.fParity = %lu\n", dcb.fParity);
//    DWORD fOutxCtsFlow:1; /* CTS handshaking on output       */
	str+=s; 
	s.Format("dcb.fOutxCtsFlow = %lu\n", dcb.fOutxCtsFlow);
//    DWORD fOutxDsrFlow:1; /* DSR handshaking on output       */
	str+=s; 
	s.Format("dcb.fOutxDsrFlow = %lu\n", dcb.fOutxDsrFlow);
//    DWORD fDtrControl:2;  /* DTR Flow control                */
	str+=s; 
	s.Format("dcb.fDtrControl = %lu\n", dcb.fDtrControl);
//    DWORD fDsrSensitivity:1; /* DSR Sensitivity              */
	str+=s; 
	s.Format("dcb.fDsrSensitivity = %lu\n", dcb.fDsrSensitivity);
//    DWORD fTXContinueOnXoff: 1; /* Continue TX when Xoff sent */
	str+=s; 
	s.Format("dcb.fTXContinueOnXoff = %lu\n", dcb.fTXContinueOnXoff);
//    DWORD fOutX: 1;       /* Enable output X-ON/X-OFF        */
	str+=s; 
	s.Format("dcb.fOutX = %lu\n", dcb.fOutX);
//    DWORD fInX: 1;        /* Enable input X-ON/X-OFF         */
	str+=s; 
	s.Format("dcb.fInX = %lu\n", dcb.fInX);
//    DWORD fErrorChar: 1;  /* Enable Err Replacement          */
	str+=s; 
	s.Format("dcb.fErrorChar = %lu\n", dcb.fErrorChar);
//    DWORD fNull: 1;       /* Enable Null stripping           */
	str+=s; 
	s.Format("dcb.fNull = %lu\n", dcb.fNull);
//    DWORD fRtsControl:2;  /* Rts Flow control                */
	str+=s; 
	s.Format("dcb.fRtsControl = %lu\n", dcb.fRtsControl);
//    DWORD fAbortOnError:1; /* Abort all reads and writes on Error */
	str+=s; 
	s.Format("dcb.fAbortOnError = %lu\n", dcb.fAbortOnError);
//    DWORD fDummy2:17;     /* Reserved                        */
	str+=s; 
	s.Format("dcb.fDummy2 = %lu\n", dcb.fDummy2);
//    WORD wReserved;       /* Not currently used              */
	str+=s; 
	s.Format("dcb.wReserved = %hu\n", dcb.wReserved);
//    WORD XonLim;          /* Transmit X-ON threshold         */
	str+=s; 
	s.Format("dcb.XonLim = %hu\n", dcb.XonLim);
//    WORD XoffLim;         /* Transmit X-OFF threshold        */
	str+=s; 
	s.Format("dcb.XoffLim = %hu\n", dcb.XoffLim);
//    BYTE ByteSize;        /* Number of bits/byte, 4-8        */
	str+=s; 
	s.Format("dcb.ByteSize = %d\n",dcb.ByteSize);
//    BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
	str+=s; 
	s.Format("dcb.Parity = %d\n", dcb.Parity);
//    BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
	str+=s; 
	s.Format("dcb.StopBits = %d\n", dcb.StopBits);
//    char XonChar;         /* Tx and Rx X-ON character        */
	str+=s; 
	s.Format("dcb.XonChar = %c\n", dcb.XonChar);
//    char XoffChar;        /* Tx and Rx X-OFF character       */
	str+=s; 
	s.Format("dcb.XoffChar = %c\n", dcb.XoffChar);
//    char ErrorChar;       /* Error replacement char          */
	str+=s; 
	s.Format("dcb.ErrorChar = %c\n",dcb.ErrorChar);
//    char EofChar;         /* End of Input character          */
	str+=s; 
	s.Format("dcb.EofChar = %c\n",dcb.EofChar);
//    char EvtChar;         /* Received Event character        */
	str+=s; 
	s.Format("dcb.EvtChar = %c\n", dcb.EvtChar);
//    WORD wReserved1;      /* Fill for now.                   */
	str+=s; 
	s.Format("dcb.wReserved1 = %hu\n\n\n", dcb.wReserved1);
	str+=s;
	return str;
}
#endif

DWORD WINAPI Handling(void * p)
{
WriteRaporto("Handling\n");
	CComPort* pThis;
	if (p)
		pThis = reinterpret_cast<CComPort*>(p);
	else
	{
		pThis = NULL;
		return 1;
	}
	XYZ xyz;
	size_t sz = sizeof(XYZ);
	int posDoc;
	while(pThis && g_bDisplayMode)
	{
WriteRaporto("Handling while pThis\n");
		int iVal = 0;
		bool tocopy = true;
		while (pThis->m_queue.Copy(&xyz, sz))
		{
WriteRaporto("Handling while pThis->m_queue.Copy\n");
			iVal++;
			for (posDoc = 0; posDoc<3; posDoc++)
			{
				switch (posDoc)
				{
				case 0:
					{
						vDoc[posDoc].OnTick(xyz.time, xyz.x);
					}
					break;
				case 1:
					{
						vDoc[posDoc].OnTick(xyz.time, xyz.y);
					}
					break;
				case 2:
					{
						vDoc[posDoc].OnTick(xyz.time, xyz.z);
					}
					break;
				}
			}
		}
		if (g_bRealTimeWaveletMode && (iVal == 1 || iVal == 2) )
		{
			for (posDoc = 0; posDoc<3; posDoc++)
			{
				vDoc[posDoc].WaveletEpsilonApply();
			}
		}
		if ((iVal == 1 || iVal == 2))
		{
			for (posDoc = 0; posDoc<3; posDoc++)
			{
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[posDoc].DrawWithMemToWindow(vhWndChild[posDoc]);
#else

				RECT rect;
				GetClientRect(vhWndChild[posDoc],&rect);
				InvalidateRect(vhWndChild[posDoc],&rect, true);
#endif
				//SendMessage(vhWndChild[posDoc],
				//	WM_ERASEBKGND,0,0);
			}
		}
		if (g_bRealTimeCovariationMode && (iVal == 1 || iVal == 2))
		{
			for (int i = 0; i < 3; i++)
			{
				int j = i+1;
				if(j > 2)
					j = 0;
				vDoc[i+3].Covariation(&vDoc[i], &vDoc[j], g_btoReverseCovariation);
				RECT rect;
				GetClientRect(vhWndChild[i+3],&rect);
				InvalidateRect(vhWndChild[i+3],&rect, true);
			}
			for (int i = 0; i < 3; i++)
			{
				vDoc[i+6].Covariation(&vDoc[i], &vDoc[i], g_btoReverseCovariation);
				RECT rect;
				GetClientRect(vhWndChild[i+6],&rect);
				InvalidateRect(vhWndChild[i+6],&rect, true);
			}
		}
	}
	pThis->m_bTerminatedHandlingThread = true;
WriteRaporto("Handling end\n");
	return 0;
}
DWORD WINAPI ReadingFromXYZBuffer(void * p)
{
WriteRaporto("ReadingFromXYZBuffer\n");
	CComPort* pThis;
	if (p)
		pThis = reinterpret_cast<CComPort*>(p);
	else
	{
		pThis = NULL;
		return 1;
	}
	XYZ xyz;
	size_t sz = sizeof(XYZ);
	bool toSolve;
	int prevCount = 0;
	FILE *stream;
	FILE *stream2;
	char filename[128];
	char filename2[128];
	unsigned short iStr = 0;

	while(pThis && !pThis->m_bTerminatedXYZBufferThread)
	{
WriteRaporto("ReadingFromXYZBuffer while\n");
		if (pThis)
			pThis->m_XYZBuffer.Read(&xyz.time, xyz.x, xyz.y, xyz.z, toSolve);
		else
			return 1;
WriteRaporto("ReadingFromXYZBuffer Read\n");
		WORD yy = xyz.time.wYear - (xyz.time.wYear/100)*100,
			d = xyz.time.wDay,
			mo = xyz.time.wMonth;

			wsprintf(filename, "C:\\Variation/var%d%d_%d%d_%d.csv\0",
					d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, xyz.time.wYear);
			wsprintf(filename2, "C:\\Variation/%d%d_%d%d_%d.txt\0",
					d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, xyz.time.wYear);

			if ((stream = fopen(
				filename,
				"at")) == NULL)
			{
				MessageBox(NULL, "Cannot open file.\n", "ReadingFromXYZBuffer", MB_OK);
				return 0;
			}
			if ((stream2 = fopen(
				filename2,
				"at")) == NULL)
			{
				MessageBox(NULL, "Cannot open file.\n", "ReadingFromXYZBuffer", MB_OK);
				return 0;
			}

		char s[124];
#if 0
		wsprintf(s,"%d:%d:%d,%d:%d:%d,%d,%u,%u,%u\n",
			xyz.time.wDay, xyz.time.wMonth, xyz.time.wYear,
			xyz.time.wHour, xyz.time.wMinute, xyz.time.wSecond,
			xyz.time.wMilliseconds,
			xyz.x, xyz.y, xyz.z);
#else

		wsprintf(s,"%d%d.%d%d.%d%d %d:%d:%d,%d,%u,%u,%u\n", 
			d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, yy/10, yy-(yy/10)*10, 
			xyz.time.wHour, xyz.time.wMinute, xyz.time.wSecond,
			xyz.time.wMilliseconds,
			xyz.x, xyz.y, xyz.z);
#endif
		fprintf(stream,s);
		fclose(stream);

		double secs;
		secs = double(xyz.time.wHour*3600+xyz.time.wMinute*60+xyz.time.wSecond)
			+ double(xyz.time.wMilliseconds)/1000.0;
		///////////////////////////////////////////////////
		fprintf(stream2,"%.1f %u %u %u\n", 
			secs,xyz.x, xyz.y, xyz.z);

		fclose(stream2);

WriteRaporto("ReadingFromXYZBuffer file\n");
		if(g_bDisplayMode)
			pThis->m_queue.AddMsg(&xyz, sz);
WriteRaporto("ReadingFromXYZBuffer AddMsg\n");
	}
WriteRaporto("ReadingFromXYZBuffer end\n");
	return 0;
}
DWORD WINAPI ReadingFromCOM3(void * p)
{
	CComPort* pThis;
	if (p)
		pThis = reinterpret_cast<CComPort*>(p);
	else
	{
		pThis = NULL;
		return 1;
	}

	OVERLAPPED ReadOL;
	DWORD dwMask;
	DWORD dwBytesTrans;
	DWORD dwCodeError;
	COMSTAT portStat;
	DWORD dwModemStat;
	DWORD AvaibleBytes;
	char  szBuf[32];
	DWORD dwRealRead;
	SYSTEMTIME char_time, new_time, pre_time, old_time, line_time;

	bool toGetLine = false;
#ifdef DO_RAPORT
char sss[100];
#endif
	if (pThis)
	{
		if (!
		PurgeComm(pThis->m_hCommHandle, 
		/*PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | */
		PURGE_RXCLEAR))
			ErrorExit("PurgeComm");
	}
	else
		ErrorExit("pThis PurgeComm");

    // создание события для асинхронного чтения
	ReadOL.Internal = 0;
	ReadOL.InternalHigh = 0;
	ReadOL.Offset =0;
	ReadOL.OffsetHigh = 0;
	ReadOL.hEvent = CreateEvent(NULL, true, true, NULL);
//	ReadOL.hEvent = CreateEvent(NULL, true, FALSE, NULL);

	// Маска событий, которые будет отслеживать читающий поток
	// Пока это только получение символа
//	SetCommMask(pThis->m_hCommHandle, 
//		EV_RXCHAR | EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD | EV_RXFLAG | EV_TXEMPTY);
	SetCommMask(pThis->m_hCommHandle, 
		EV_RXCHAR);
	int q = 0;

	unsigned long x,y,z;

	bool toRead = true;
	bool bSuccessRead;
	bool toSolve;
	DWORD dwBytesToRead = 1;
	bool bStart = true;
	bool bLine  = false;

	GetTime(&old_time);
	GetTime(&pre_time);
	double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

	while (pThis && pThis->m_bIsConnected && !pThis->m_bTerminatedCOMThread)//пока порт открыт
	{
WriteRaporto("ComPortThread while\n");
		// Ждем одного из событий
		if (pThis)
			WaitCommEvent(pThis->m_hCommHandle, &dwMask, &ReadOL);
		else
			ErrorExit("ReadingFromCOM");
WriteRaporto("ComPortThread WaitCommEvent\n");

		if(!pThis)
		{
WriteRaporto("ComPortThread !pThis\n");
			ErrorExit("ReadingFromCOM");
		}
//		DWORD wt = INFINITE;
		DWORD wt = 10000;
		DWORD res = WaitForSingleObject(ReadOL.hEvent,wt);
WriteRaporto("ComPortThread WaitForSingleObject 0\n");

		if (res	!= WAIT_OBJECT_0)
		{
WriteRaporto("ComPortThread WaitForSingleObject != WAIT_OBJECT_0\n");
			DWORD dwChildID;
			HANDLE hAudioWarningThread;
			hAudioWarningThread = ::CreateThread(NULL, 0, 
				AudioWarning, 
				reinterpret_cast<LPVOID>(NULL), 
				0,
				&dwChildID );
			MessageBox(
				NULL,
				"Прибор не пишет показания\nВы уверены, что хотите прервать работу программы?\nНажмите \"Оk\", чтобы продолжить работу", 
				"Сбой в работе прибора",
				MB_OK);
			TerminateThread(hAudioWarningThread, 0);
			// Получаем состояние порта (линий и модема)
			if (pThis)
				ClearCommError(pThis->m_hCommHandle, &dwCodeError, &portStat);
			else
				ErrorExit("ClearCommError");
		}
		else
		{
WriteRaporto("ComPortThread WaitForSingleObject\n");
			GetTime(&new_time);
			if (pThis && GetOverlappedResult(
				pThis->m_hCommHandle, 
				&ReadOL, 
				&dwBytesTrans, 
				false))
			{
WriteRaporto("ComPortThread GetOverlappedResult\n");
				// после GetOverlappedResult в переменной mask, которая передавалась
				// в WaitCommEvent, появятся флаги произошедших событий, либо 0 в
				// случае ошибки.
				if ((dwMask & EV_RXCHAR) != 0)
				{
WriteRaporto("ComPortThread dwMask & EV_RXCHAR\n");
					// Получаем состояние порта (линий и модема)
					if (pThis)
						ClearCommError(pThis->m_hCommHandle, 
						&dwCodeError, 
						&portStat);
					else
						ErrorExit("ReadingFromCOM");

WriteRaporto("ComPortThread ClearCommError\n");

					/*if (dwCodeError == CE_FRAME)
					{
						printf("ClearCommError dwCodeError = Kadr error\n", dwCodeError);
					}*/
					if (pThis)
						GetCommModemStatus(pThis->m_hCommHandle,
						&dwModemStat);
					else
						ErrorExit("ReadingFromCOM");

WriteRaporto("ComPortThread GetCommModemStatus\n");

					// Число полученных, но еще не прочитанных байт
					AvaibleBytes = portStat.cbInQue;
#ifdef DO_RAPORT
char	str[100];
sprintf(str, "Avaible Bytes = %d\n", AvaibleBytes);
WriteRaporto(str);
#endif

					if (bStart)
					{
						toRead = AvaibleBytes > 0;
						toSolve = false;
					}
					else
					{
						toRead = AvaibleBytes >= dwBytesToRead;
						toSolve = AvaibleBytes == dwBytesToRead;
					}

					if (AvaibleBytes >= 24 && bLine)
					{
						/*if (AvaibleBytes > 24)
							line_time = old_time;
						else
							line_time = new_time;*/

						toGetLine = true;
						dwBytesToRead = 24;
						toRead = true;
					}
					else
						toGetLine = false;


					if (AvaibleBytes >= 4096)
					{
						// Буфер переполнен
						MessageBox(NULL, "Буфер COM порта переполнен\nПриложение завершает свою работу\nПозаботьтесь об увеличении быстродействия компьютера", "Fatal Error", MB_OK); 
						ExitProcess(0);
					}
					// Проверка числа доступный байт
					if (toRead)
					{
						if (pThis && 
							ReadFile(pThis->m_hCommHandle, 
							szBuf, 
							dwBytesToRead, &dwRealRead, &ReadOL))
						{
							
#ifdef DO_RAPORT
wsprintf(sss, "dwBytesToRead = %d dwRealRead = %d remainedBytes = %d\n", int(dwBytesToRead),int(dwRealRead),  int(AvaibleBytes - dwRealRead));
WriteRaporto(sss);
//szBuf[dwBytesToRead] = '\0';
wsprintf(sss, "ComPortThread ReadFile              %s\n", szBuf);
WriteRaporto(sss);		
#endif	

							bSuccessRead = true;
							if(!bStart)
							{
								if (szBuf[dwBytesToRead-1] == '$')
								{
									szBuf[dwBytesToRead-1] = '\0';
								}
								else
								{
									// Неизвестный протокол обмена - пропускаем строку и ждём символа начала строки
									toSolve = false;
									bStart = true;
									bLine = false;
									dwBytesToRead = 1;
									bSuccessRead = false;
								}
							}
							if(bSuccessRead){
								if(toGetLine)
								{
WriteRaporto("toGetLine\n");
									toSolve = false;
									bStart = true;
									bLine = true;
									dwBytesToRead = 1;

									x = atoi(szBuf+1);
									y = atoi(szBuf+8);
									z = atoi(szBuf+15);

									// Ко времени регистрации незадержанного импульса char_time
									// прибавляем межимпульсный интервал и получаем оценку времени генерации строки line_time 
									datevec(datenum(char_time) + delta_impuls_time, line_time);
									// обновляем время char_time
									char_time = line_time;
									if (pThis)
										pThis->m_XYZBuffer.Write(&line_time, x,y,z, toSolve);
								}
								else
								{
									if (bStart)
									{
										//Sleep(1200);// имитация долгого чтения
										if (szBuf[0] == '^')
										{
											// Начало последовательности
											bStart = false;
											bLine  = false;
											dwBytesToRead = 23;
											char_time = new_time;	

											// сравниваем время текущего тика new_time и время предыдущего тика pre_time
											double dn_new_time = datenum(new_time);
											double dn_pre_time = datenum(pre_time);
											double delta_time = dn_new_time-dn_pre_time;
											if (delta_time > 85./86400000.)// если разница больше 85 миллисекунд
											{
												old_time = pre_time; // пришедший символ уже из серии нового импульса
												//корректируем межимпульсный интервал
												delta_impuls_time = delta_time < delta_impuls_time ? delta_time : delta_impuls_time;
											}
											pre_time = new_time;
										}
									}
									else
									{
										x = atoi(szBuf);
										y = atoi(szBuf+7);
										z = atoi(szBuf+14);

										bStart = true;
										bLine  = true;
										dwBytesToRead = 1;
										if (pThis)
											pThis->m_XYZBuffer.Write(&char_time, x,y,z, toSolve);
									}
								}
							}
						}
						else
						{
WriteRaporto("ComPortThread ! ReadFile WriteErrorString\n");
							// Пропускаем прочитанное с ошибкой
							LPVOID lpMsgBuf;
							DWORD dw = GetLastError(); 

							FormatMessage(
								FORMAT_MESSAGE_ALLOCATE_BUFFER | 
								FORMAT_MESSAGE_FROM_SYSTEM,
								NULL,
								dw,
								MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
								(LPTSTR) &lpMsgBuf,
								0, NULL );

#ifdef DO_RAPORT
							char err_str[256]; 
							wsprintf(err_str, "ReadFile failed with error %d: %s", 
							dw, lpMsgBuf);
WriteRaporto(err_str);
WriteRaporto("\n");

WriteRaporto((char *)lpMsgBuf);
WriteRaporto("\n");
#endif
						
							
							// Неудачная попытка чтения
							toSolve = false;
							bStart = true;
							bLine = false;
							dwBytesToRead = 1;
#if 0
							if (pThis)
								PurgeComm(pThis->m_hCommHandle,
								PURGE_TXABORT /*| PURGE_RXABORT*/);
							else
								ErrorExit("PurgeComm");
#endif

							// Получаем состояние порта (линий и модема)
							if (pThis)
								ClearCommError(pThis->m_hCommHandle, &dwCodeError, &portStat);
							else
								ErrorExit("ClearCommError");

						}
					}
				}
			}
			// сравниваем время текущего тика new_time и время предыдущего тика pre_time
#if 0
			unsigned short dwDeltaMilliseconds = 
				new_time.wMilliseconds >= pre_time.wMilliseconds ?
				new_time.wMilliseconds - pre_time.wMilliseconds : 
			(1000 + new_time.wMilliseconds) - pre_time.wMilliseconds;

			int DeltaSeconds = 
				(60*(60*new_time.wHour + new_time.wMinute) + new_time.wSecond) -
				(60*(60*pre_time.wHour + pre_time.wMinute) + pre_time.wSecond);
			if (DeltaSeconds < 0)
				DeltaSeconds += 3600*24;
			if (DeltaSeconds > 1 || DeltaSeconds <= 1 && dwDeltaMilliseconds > 10)// если разница больше 10 миллисекунд
				old_time = pre_time; // пришедший символ уже из серии нового импульса
			pre_time = new_time;
#else
#endif

		}
	}
	// закрытие дескриптора сигнального объекта} 
	CloseHandle(ReadOL.hEvent);
	// Сброс события и маски ожидания}
	if (pThis)
		SetCommMask(pThis->m_hCommHandle, 0);
	else
		ErrorExit("ReadingFromCOM");

	if (pThis)
	{
		if (CloseHandle(pThis->m_hCommHandle))
			MessageBox(NULL, "The port is closed", "ReadingFromCOM", MB_OK );
		else
			ErrorExit("CloseHandle");

		pThis->m_bIsConnected = false;
	}
	else
		ErrorExit("ReadingFromCOM");


	return 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComPort::CComPort()
{
	m_hEventFrameReady = CreateEvent( NULL, TRUE, TRUE, "FrameReadyEvent" );
	m_hHandlingThread				= NULL;
	m_hReadingFromXYZBufferThread	= NULL;
	m_hReadingFromCOMThread			= NULL;
	m_nPortNumber = 1;
	m_bTerminatedHandlingThread = true;
	m_bTerminatedCOMThread = true;
	m_bTerminatedXYZBufferThread = true;
	m_bIsConnected = false;

}
CComPort::CComPort(int nPortNumber)
{
	m_hHandlingThread				= NULL;
	m_hReadingFromXYZBufferThread	= NULL;
	m_hReadingFromCOMThread			= NULL;
	m_nPortNumber = nPortNumber;
	m_bTerminatedHandlingThread = true;
	m_bTerminatedCOMThread = true;
	m_bTerminatedXYZBufferThread = true;
	m_bIsConnected = false;
}

CComPort::~CComPort()
{
	CloseHandle(m_hEventFrameReady);
}

int CComPort::DoConnect(int _nPortNumber)
{
	if (m_bIsConnected)
	{
		char str[32];
		wsprintf(str, "Порт COM%d и так уже открыт\n", this->m_nPortNumber);
		MessageBox(NULL, str, "Connect", MB_OK);
		return 0;
	}
	m_nPortNumber = _nPortNumber;

	char  szPort[16];

	wsprintf(szPort,"\\\\.\\COM%-d", m_nPortNumber); 
	if ((m_hCommHandle = CreateFile(szPort,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL)) == INVALID_HANDLE_VALUE)
	{
		ErrorExit("CreateFile");
		return 0;
	}
	else
	{
		m_bIsConnected = true;
		char str[32];
		wsprintf(str, "Порт COM%d открыт\n", this->m_nPortNumber);
		//MessageBox(NULL, str, "Connect", MB_OK);
	}

	COMSTAT stat;
	DWORD dwError;
	if(ClearCommError(m_hCommHandle, &dwError, &stat))
	{
		//MessageBox(NULL, "Ошибка порта успешно сброшена\n","", MB_OK);
	}
	else
	{
		ErrorExit("ClearCommError");
	}


	DCB dcb;

	if(GetCommState(m_hCommHandle, &dcb))
	{
		//MessageBox(NULL, "Новые настройки порта\n успешно считаны:\n\n","", MB_OK);
	}
	else
	{
		ErrorExit("GetCommState");
	}

	// Поле DCBLength должно содержать размер структуры
	dcb.DCBlength = sizeof(dcb);
	// Скорость обмена (бод) 
	dcb.BaudRate = CBR_9600;
	// Windows не поддерживает не бинарный режим работы последовательных портов
	dcb.fBinary = true;
	// Число бит в байте
	dcb.ByteSize = 8;
	// Контроль четности
	dcb.Parity  = NOPARITY;
	//Число стоп бит
	dcb.StopBits = 0;
	dcb.fDsrSensitivity = 0;
	//dcb.fDtrControl = 1;//DTR_CONTROL_ENABLE;// use EscapeCommFunction
	dcb.fDtrControl = DTR_CONTROL_ENABLE;// use EscapeCommFunction
	dcb.fRtsControl = RTS_CONTROL_ENABLE;// use EscapeCommFunction
	dcb.fOutxCtsFlow = 0;

	dcb.fOutxDsrFlow = 0;
	dcb.fTXContinueOnXoff = 1;

//	dcb.fAbortOnError = 0;// не прекращаем операцию ятения при возникновении ошибок
	dcb.fAbortOnError = 1;// не прекращаем операцию ятения при возникновении ошибок
	dcb.wReserved = 0; // должно быть 0
	dcb.wReserved1 = 0; // 
	dcb.fDummy2 = 0; // 
	dcb.XoffChar = 0x0013; // символ который должен подавать драйвер для приостановления потока принимаемых данных
	dcb.XonChar = 0x0011; // символ который должен подавать драйвер для возобновления потока принимаемых данных
//	dcb.ErrorChar = '&'; // символ, заменяющий ошибочно переданный символ
//	dcb.EofChar = '$'; // Символ конца данных
	dcb.ErrorChar = 0x0010; // символ, заменяющий ошибочно переданный символ
	dcb.EofChar = 0x0009; // Символ конца данных
//	dcb.EvtChar = '!'; // символ для вызова события
	dcb.EvtChar = 0x0008; // символ для вызова события
	dcb.XoffLim = 512;
	dcb.XonLim = 2048;


/*	if (PurgeComm(m_hCommHandle, 
		PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | 
		PURGE_RXCLEAR))
		MessageBox(NULL, "Порт очищен\n\n",
		"", MB_OK);
	else
			ErrorExit("PurgeComm");*/


	// Установить новые настройки порта 
	if(SetCommState(m_hCommHandle, &dcb))
	{
		//MessageBox(NULL, "Новые настройки порта\n успешно установлены:\n\n","", MB_OK);
	}
	else
	{
		ErrorExit("SetCommState");
	}

#if 0
	__asm
	{
		mov  ah,0                   ;функция инициaлизaции пopтa
		mov  dx,1                   ;выбиpaeм COM1
		mov  al, 227
		INT  14H                    ;инициaлизиpуeм пopт
	}
	__asm
	{
		;---пoлучaeм бaзoвый aдpec COM1
		;mov  ax,40H          ;ES укaзывaeт нa oблacть дaнныx BIOS
		;mov  es,ax           ;
		;mov  dx,es:[0]       ;пoлучaeм бaзoвый aдpec COM1


		add dx, 4               ;укaзывaeм нa peгиcтp кoнтpoля мoдeмa
		mov al, 1               ;уcтaнaвливaeм бит 1
		out dx, al              ;пocылaeм в пopт

		;---уcтaнaвливaeм бит RTS
		mov al, 1               ;clear cигнaл RTS
		out dx, al              ;пocылaeм в пopт
	}
#endif

//	char sss[100];
//	wsprintf(sss,"%d",base_addr_COM1);
//	MessageBox(0, sss, "", 0);

	// Передаём комманды драйверу напрямую об установлнии сигналов DTR и RTS
	// готовность терминала
#if 1
#define COM_GALVANI_INVERT_POLARNOST
#ifdef COM_GALVANI_INVERT_POLARNOST
	if(EscapeCommFunction(m_hCommHandle, SETDTR))
	{
		//MessageBox(NULL, "Сигнал DTR установлен\n ON false -5 -12",		"", MB_OK);
	}
	else
	{
		ErrorExit("EscapeCommFunction SETDTR");
	}
	// Запрос передачи
	if(EscapeCommFunction(m_hCommHandle, CLRRTS))
	{
		//MessageBox(NULL, "Сигнал RTS сброшен\n OFF true +5 +12","", MB_OK);
	}
	else
	{
		ErrorExit("EscapeCommFunction CLRRTS");
	}
#else
	if(EscapeCommFunction(m_hCommHandle, CLRDTR))
	{
		//MessageBox(NULL, "Сигнал DTR сброшен\n OFF true +5 +12","", MB_OK);
	}
	else
	{
		ErrorExit("EscapeCommFunction CLRDTR");
		return 0;
	}

	if(EscapeCommFunction(m_hCommHandle, SETRTS))
	{
		//MessageBox(NULL, "Сигнал RTS установлен\n ON false -5 -12","", MB_OK);
	}
	else
	{
		ErrorExit("EscapeCommFunction SETRTS");
		return 0;
	}
#endif
#endif

/*	int i;
	char c;
	for (c = 0x0000, i = 0; i < 1000; c++, i++)
		fprintf(stream, "%x      %c\n", c, c);
		
	fclose(stream);
*/
	return 1;
}

int CComPort::CloseConnection()
{
	DWORD dwExitCode = 1;
	if (!this->m_bTerminatedHandlingThread)
	{

		if (!TerminateThread(m_hHandlingThread, dwExitCode))
			ErrorExit("TerminateThread HandlingThread");
		else{
			m_bTerminatedHandlingThread = true;
			//MessageBox(NULL, "The Thread COMThread is Terminated\n",
			//	"ComPort", MB_OK);
		}
	}
	if (!this->m_bTerminatedCOMThread)
	{

		if (!TerminateThread(m_hReadingFromCOMThread, dwExitCode))
			ErrorExit("TerminateThread COMThread");
		else{
			m_bTerminatedCOMThread = true;
			//MessageBox(NULL, "The Thread COMThread is Terminated\n",
			//	"ComPort", MB_OK);
		}
	}
	if (!this->m_bTerminatedXYZBufferThread)
	{
		if (!TerminateThread(m_hReadingFromXYZBufferThread, dwExitCode))
			ErrorExit("TerminateThread XYZBufferThread");
		else{
			//MessageBox(NULL, "The Thread XYZBufferThread is Terminated\n",
			//	"ComPort", MB_OK);
			m_bTerminatedXYZBufferThread = true;
		}
	}
	if (m_bIsConnected)
	{
		char str[32];
		wsprintf(str, "Порт COM%d закрыт\n", this->m_nPortNumber);
		if(CloseHandle(m_hCommHandle)){
			MessageBox(NULL, 
				str,
				"ComPort", MB_OK);
			m_bIsConnected = false;
		}
		else
			ErrorExit("CloseHandle");
	}
	return 0;
}

void CComPort::ReadFromCOM()
{
	if (!m_bTerminatedCOMThread)
	{
		char str[100];
		wsprintf(str, "Процесс чтения из COM%d порта и так уже запущен\n", this->m_nPortNumber);
		MessageBox(NULL, str, "ReadFromCOM", MB_OK);
		return;
	}
	if (!m_bIsConnected)
	{
		MessageBox(NULL, "СОМ порт не открыт !!!\n",
			"", MB_OK);
		return;
	}

	DWORD dwChildID;

	if(g_bDisplayMode)
		StartHandling();

	m_hReadingFromXYZBufferThread = ::CreateThread(NULL, 0, 
		ReadingFromXYZBuffer, 
		reinterpret_cast<LPVOID>(this), 
		0,
		&dwChildID );

	if (m_hReadingFromXYZBufferThread)
	{
		m_bTerminatedXYZBufferThread = false;
		if (!SetThreadPriority(m_hReadingFromXYZBufferThread,
			THREAD_PRIORITY_HIGHEST))
			ErrorExit("SetThreadPriority m_hReadingFromXYZBufferThread");
	}
	else
		ErrorExit("CreateThread XYZBufferThread");

	m_hReadingFromCOMThread = ::CreateThread(NULL, 0, 
		ReadingFromCOM3, 
		reinterpret_cast<LPVOID>(this),  
		0,
		&dwChildID );



	if (m_hReadingFromCOMThread)
	{
		m_bTerminatedCOMThread = false;
		if(!SetThreadPriority(m_hReadingFromCOMThread,
			THREAD_PRIORITY_HIGHEST))
			ErrorExit("SetThreadPriority m_hReadingFromCOMThread");
	}
	else
		ErrorExit("CreateThread");


}
/*
int CComPort::SetWindowOwner(CMainFrame* pMainFrame, HWND hWnd)
{
	m_pMainFrame  = pMainFrame;
	if(::IsWindow(hWnd))
	{
		m_hWndOwner = hWnd;
		return 1;
	}
	else
		return 0;
}

int CComPort::ManualConnect()
{
	COMMCONFIG CommConfig;
	char  szPort[16];
	CommConfig.dwSize = sizeof(CommConfig);
	wsprintf(szPort,"COM%-d", m_nPortNumber); 
	if (!CommConfigDialog(szPort,NULL,&CommConfig))
	{
		ErrorExit("CommConfigDialog");
		return 0;
	}

	DWORD dwSize = sizeof(CommConfig);
	if(SetCommConfig(m_hCommHandle, &CommConfig, dwSize)){
		AfxMessageBox("новые настройки порта\n");
		return 1;
	}
	else
	{
		ErrorExit("SetCommConfig");
		return 0;
	}
}
*/


int CComPort::StartHandling()
{
	if (m_bTerminatedHandlingThread)
	{
		DWORD dwChildID;

		m_hHandlingThread = ::CreateThread(NULL, 0, 
			Handling, 
			reinterpret_cast<LPVOID>(this), 
			0,
			&dwChildID );


		if (m_hHandlingThread)
		{
			m_bTerminatedHandlingThread = false;
			if (!SetThreadPriority(m_hHandlingThread,
				THREAD_PRIORITY_NORMAL))
				ErrorExit("SetThreadPriority m_hHandlingThread");

		}
		else
			ErrorExit("CreateThread HandlingThread");

		return 1;
	}
	else
		return 0;

}

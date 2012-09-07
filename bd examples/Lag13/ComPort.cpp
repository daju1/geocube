// ComPort.cpp: implementation of the CComPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphs.h"
#include "GraphsDoc.h"
#include "ComPort.h"
#include "MainFrm.h"	
extern UINT g_comPortMessage, g_comPortErrorMessage;
extern void WriteRaporto(LPCTSTR s);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
void ErrorExit(LPTSTR lpszFunction) 
{ 
    TCHAR szBuf[80]; 
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

    wsprintf(szBuf, 
        "%s failed with error %d: %s", 
        lpszFunction, dw, lpMsgBuf); 
 
    MessageBox(NULL, szBuf, "Error", MB_OK); 

    LocalFree(lpMsgBuf);
//	ExitProcess(dw); 
}
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
//	str+=s; 
//	s.Format("dcb.wReserved = %hu\n", dcb.wReserved);
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
	POSITION posDoc;
	CGraphsDoc* pDoc;
	int iDoc;
	while(pThis)
	{
WriteRaporto("Handling while pThis\n");
		int iVal = 0;
		bool tocopy = true;
		while (pThis->m_queue.Copy(&xyz, sz))
		{
WriteRaporto("Handling while pThis->m_queue.Copy\n");
			iVal++;
			iDoc = 0;
			posDoc = ((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetFirstDocPosition();
			while (posDoc !=NULL)
			{
				iDoc++;
				pDoc = (CGraphsDoc*)((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetNextDoc(posDoc);
				switch (iDoc)
				{
				case 1:
					{
						pDoc->OnTick(xyz.x);
						pDoc->WaveletEpsilonApply();
					}
					break;
				case 2:
					{
						pDoc->OnTick(xyz.y);
						pDoc->WaveletEpsilonApply();
					}
					break;
				case 3:
					{
						pDoc->OnTick(xyz.z);
						pDoc->WaveletEpsilonApply();
					}
					break;
				}
			}
		}
		if (true || iVal==1)
		{
WriteRaporto("Handling if (iVal==1)\n");
//		Sleep(1000);// имитация долгой обработки

			iDoc = 0;
			posDoc = ((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetFirstDocPosition();
			while (posDoc !=NULL)
			{
				iDoc++;
				pDoc = (CGraphsDoc*)((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetNextDoc(posDoc);
				switch (iDoc)
				{
				case 1:
					{
						//pDoc->WaveletApply();
						pDoc->WaveletEpsilonApply();
					}
					break;
				case 2:
					{
						//pDoc->WaveletApply();
						pDoc->WaveletEpsilonApply();
					}
					break;
				case 3:
					{
						//pDoc->WaveletApply();
						pDoc->WaveletEpsilonApply();
					}
					break;
				}
			}
		}	
	}
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
	CString time_str;
	XYZ xyz;
	size_t sz = sizeof(XYZ);
	bool toSolve;
	int prevCount = 0;

	while(pThis && !pThis->m_bTerminatedXYZBufferThread)
	{
WriteRaporto("ReadingFromXYZBuffer while\n");
		if (pThis)
			pThis->m_XYZBuffer.Read(time_str, xyz.x, xyz.y, xyz.z, toSolve);
		else
			return 1;
WriteRaporto("ReadingFromXYZBuffer Read\n");
		if (pThis->m_pMainFrame->m_bToWriteTextFile)
		{
			FILE *stream;
			if ((stream = fopen(pThis->m_pMainFrame->m_sTextFilePath,"at")) == NULL)
			{
				AfxMessageBox("Cannot open file.\n");
				return 0;
			}
			CString s;
			s.Format("%s,%d,%d,%d\n",time_str, xyz.x, xyz.y, xyz.z);
			fprintf(stream,s);
			fclose(stream);
		}
WriteRaporto("ReadingFromXYZBuffer file\n");
		int count = pThis->m_queue.AddMsg(&xyz, sz);
WriteRaporto("ReadingFromXYZBuffer AddMsg\n");
	}
WriteRaporto("ReadingFromXYZBuffer end\n");
	return 0;
}
DWORD WINAPI ReadingFromCOM(void * p)
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
	char  szBuf[8];
	DWORD dwRealRead;
	CString time_str;

	if (pThis)
		PurgeComm(pThis->m_hCommHandle, 
		/*PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | */
		PURGE_RXCLEAR);
	else
		ErrorExit("PurgeComm");

/*
	COMMTIMEOUTS CommTimeOuts;


	GetCommTimeouts(pThis->m_hCommHandle, &CommTimeOuts);
	printf("%x\n", CommTimeOuts.ReadIntervalTimeout);
	printf("%x\n", CommTimeOuts.ReadTotalTimeoutConstant);
	printf("%x\n", CommTimeOuts.ReadTotalTimeoutMultiplier);
	printf("%x\n", CommTimeOuts.WriteTotalTimeoutConstant);
	printf("%x\n", CommTimeOuts.WriteTotalTimeoutMultiplier);

	CommTimeOuts.ReadIntervalTimeout = 10000;
	CommTimeOuts.ReadTotalTimeoutConstant = 10000;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 10000;
	if(	!SetCommTimeouts(pThis->m_hCommHandle, &CommTimeOuts))
		ErrorExit("SetCommTimeouts");



	GetCommTimeouts(pThis->m_hCommHandle, &CommTimeOuts);
	printf("%x\n", CommTimeOuts.ReadIntervalTimeout);
	printf("%x\n", CommTimeOuts.ReadTotalTimeoutConstant);
	printf("%x\n", CommTimeOuts.ReadTotalTimeoutMultiplier);
	printf("%x\n", CommTimeOuts.WriteTotalTimeoutConstant);
	printf("%x\n", CommTimeOuts.WriteTotalTimeoutMultiplier);
*/
    // создание события для асинхронного чтения
	ReadOL.Internal = 0;
	ReadOL.InternalHigh = 0;
	ReadOL.Offset =0;
	ReadOL.OffsetHigh = 0;
	ReadOL.hEvent = CreateEvent(NULL, true, true, NULL);

	// Маска событий, которые будет отслеживать читающий поток
	// Пока это только получение символа
	SetCommMask(pThis->m_hCommHandle, 
		EV_RXCHAR | EV_BREAK | EV_CTS | EV_DSR | EV_ERR | EV_RING | EV_RLSD | EV_RXFLAG | EV_TXEMPTY);
	int q = 0;

	DWORD dwPart;

	int x,y,z;

	bool toRead = true;
	bool toSolve;
	DWORD dwBytesToRead = 1;
	bool bStart = true;
	/*
	CString ss;
	ss.Format("pThis->m_bIsConnected = %d, pThis->m_bTerminated = %d",
		pThis->m_bIsConnected, pThis->m_bTerminated);
	AfxMessageBox(ss);*/


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
			ErrorExit("ReadingFromCOM");
//		DWORD wt = INFINITE;
		DWORD wt = 30000;

		if (WaitForSingleObject(ReadOL.hEvent,wt)
			!= WAIT_OBJECT_0)
		{
			// Получаем состояние порта (линий и модема)
			if (pThis)
				ClearCommError(pThis->m_hCommHandle, &dwCodeError, &portStat);
			else
				ErrorExit("ClearCommError");
		}
		else
		{
WriteRaporto("ComPortThread WaitForSingleObject\n");
			if (pThis && GetOverlappedResult(pThis->m_hCommHandle, &ReadOL, &dwBytesTrans, false))
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
						ClearCommError(pThis->m_hCommHandle, &dwCodeError, &portStat);
					else
						ErrorExit("ReadingFromCOM");
WriteRaporto("ComPortThread ClearCommError\n");

					/*if (dwCodeError == CE_FRAME)
					{
						printf("ClearCommError dwCodeError = Kadr error\n", dwCodeError);
					}*/
					if (pThis)
						GetCommModemStatus(pThis->m_hCommHandle, &dwModemStat);
					else
						ErrorExit("ReadingFromCOM");
WriteRaporto("ComPortThread GetCommModemStatus\n");

					// Число полученных, но еще не прочитанных байт
					AvaibleBytes = portStat.cbInQue;
char	str[100];
sprintf(str, "Avaible Bytes = %d\n", AvaibleBytes);
WriteRaporto(str);

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
					if (AvaibleBytes >= 4096)
					{
						// Буфер переполнен
						MessageBox(NULL, "Буфер COM порта переполнен\nПриложение завершает свою работу\nПозаботьтесь об увеличении быстродействия компьютера", "Fatal Error", MB_OK); 
						ExitProcess(0);
					}
#if 0
					while (false && AvaibleBytes > 48)
					{
						if (pThis)
							PurgeComm(pThis->m_hCommHandle, 
								/*PURGE_TXCLEAR |*/ PURGE_RXCLEAR);
						else
							ErrorExit("PurgeComm");
WriteRaporto("ComPortThread while (AvaibleBytes > 48) PurgeComm\n");
						
						// Получаем состояние порта (линий и модема)
						if (pThis)
							ClearCommError(pThis->m_hCommHandle, &dwCodeError, &portStat);
						else
							ErrorExit("ReadingFromCOM");
WriteRaporto("ComPortThread while (AvaibleBytes > 48) ClearCommError\n");

						if (pThis)
							GetCommModemStatus(pThis->m_hCommHandle, &dwModemStat);
						else
							ErrorExit("ReadingFromCOM");

WriteRaporto("ComPortThread while (AvaibleBytes > 48) GetCommModemStatus\n");

						// Число полученных, но еще не прочитанных байт
						AvaibleBytes = portStat.cbInQue;


						toRead = false;
						bStart = true;
						dwBytesToRead = 1;

						CString err_str; 
						err_str.Format("AvaibleBytes(%d) > 48 \n", 
						AvaibleBytes);

						pThis->m_XYZBuffer.WriteErrorString(err_str);

						pThis->m_pMainFrame->PostMessage(g_comPortErrorMessage);
					}
#endif
if (toRead)
{
WriteRaporto("ComPortThread toRead == true\n");
}
else
{
WriteRaporto("ComPortThread toRead == false\n");
}
					// Проверка числа доступный байт
					if (toRead)
					{
						if (pThis && ReadFile(pThis->m_hCommHandle, szBuf, dwBytesToRead, &dwRealRead, &ReadOL))
						{
WriteRaporto("ComPortThread ReadFile             ");
szBuf[dwBytesToRead] = '\0';
WriteRaporto(szBuf);
WriteRaporto("\n");

							if (bStart)
							{
								//Sleep(25);// имитация долгого чтения
								if (szBuf[0] == '^')
								{
									// Начало последовательности
									bStart = false;
									dwPart = 1;
									dwBytesToRead = 7;
									time_str =  CTime::GetCurrentTime().Format("%d:%m:%Y,%H:%M:%S");

								}
							}
							else
							{
								if (szBuf[dwBytesToRead-1] == ',' || szBuf[dwBytesToRead-1] == '$'){
									szBuf[dwBytesToRead-1] = '\0';
								}
								else
								{
									// Неизвестный протокол обмена
									MessageBox(NULL, "Неизвестный протокол обмена\nПриложение завершает свою работу", szBuf/*"Fatal Error"*/, MB_OK); 
									ExitProcess(0);

								}
								switch (dwPart)
								{
								case 1:
									{
										x = atoi(szBuf);
										dwBytesToRead = 7;
									}
									break;
								case 2:
									{
										y = atoi(szBuf);
										dwBytesToRead = 7;
									}
									break;
								case 3:
									{
										z = atoi(szBuf);
										dwBytesToRead = 2;
									}
									break;
								case 4:
									{
										//f = atoi(szBuf);
										bStart = true;
										dwBytesToRead = 1;
										//printf("Flag =  %d ", f);
										if (pThis){
											pThis->m_XYZBuffer.Write(time_str, x,y,z, toSolve);
//											pThis->m_pMainFrame->PostMessage(g_comPortMessage);
//											pThis->m_pMainFrame->OnComPortMessage(x,y,z);
										}
										// Вызываем событие OnReadByte. Для синхронизации с VCL
										// надо вызвать метод Synchronize                      
										//Synchronize(DoReadByte);
									}
								}
								dwPart++;
								if (dwPart > 4)
								{
									dwPart = 0;
									//printf("\n");
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

							CString err_str; 
							err_str.Format("ReadFile failed with error %d: %s", 
							dw, lpMsgBuf);
WriteRaporto(err_str);
WriteRaporto("\n");

WriteRaporto((char *)lpMsgBuf);
WriteRaporto("\n");

							pThis->m_XYZBuffer.WriteErrorString(time_str+err_str);

							pThis->m_pMainFrame->PostMessage(g_comPortErrorMessage);

							
							
							bStart = true;
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
			AfxMessageBox("ReadingFromCOM The port is closed");
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

int CComPort::DoConnect()
{
	if (m_bIsConnected)
		return 0;
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
		AfxMessageBox("The port is opened\n");
	}

/*	FILE* stream;
	stream = fopen("dcb.log","at");
*/

	DCB dcb;

	GetCommState(m_hCommHandle, &dcb);
//	fprintf(stream, "Настройки Порта перед устанвкой: \n");
//	fprintf(stream, printDCB(dcb));




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
	dcb.fDtrControl = 1;
	dcb.fOutxCtsFlow = 0;

	dcb.fOutxDsrFlow = 0;
	dcb.fTXContinueOnXoff = 1;

	dcb.fAbortOnError = 0;// не прекращаем операцию ятения при возникновении ошибок
//	dcb.wReserved = 0; // должно быть 0
	dcb.wReserved1 = 0; // 
	dcb.fDummy2 = 0; // 
	dcb.XoffChar = 0x0013; // символ который должен подавать драйвер для приостановления потока принимаемых данных
	dcb.XonChar = 0x0011; // символ который должен подавать драйвер для возобновления потока принимаемых данных
	dcb.ErrorChar = '&'; // символ, заменяющий ошибочно переданный символ
	dcb.EofChar = '$'; // Символ конца данных
	dcb.EvtChar = '!'; // символ для вызова события
	dcb.XoffLim = 512;
	dcb.XonLim = 2048;



	// Установить новые настройки порта }
	if(SetCommState(m_hCommHandle, &dcb))
		AfxMessageBox("Новые настройки порта\n успешно установлены:\n\n" + printDCB(dcb));
	else
	{
		ErrorExit("SetCommState");
		return 0;
	}

//	fprintf(stream, " новые Настройки Порта: \n");
//	fprintf(stream, printDCB(dcb));
//	fprintf(stream, printDCB(dcb));
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
//			AfxMessageBox("The Thread COMThread is Terminated\n");
		}
	}
	if (!this->m_bTerminatedCOMThread)
	{

		if (!TerminateThread(m_hReadingFromCOMThread, dwExitCode))
			ErrorExit("TerminateThread COMThread");
		else{
			m_bTerminatedCOMThread = true;
//			AfxMessageBox("The Thread COMThread is Terminated\n");
		}
	}
	if (!this->m_bTerminatedXYZBufferThread)
	{
		if (!TerminateThread(m_hReadingFromXYZBufferThread, dwExitCode))
			ErrorExit("TerminateThread XYZBufferThread");
		else{
//			AfxMessageBox("The Thread XYZBufferThread is Terminated\n");
			m_bTerminatedXYZBufferThread = true;
		}
	}
	if (m_bIsConnected)
	{
		if(CloseHandle(m_hCommHandle)){
//			AfxMessageBox("The port is closed\n");
			m_bIsConnected = false;
		}
		else
			ErrorExit("CloseHandle");
	}
	return 0;
}
void CComPort::ReadFromCOM()
{
	if (!m_bIsConnected)
	{
		AfxMessageBox("The port is not opened !!!\n");
		return;
	}

	DWORD dwChildID;

	m_hHandlingThread = ::CreateThread(NULL, 0, 
		Handling, 
		reinterpret_cast<LPVOID>(this), 
		0,
		&dwChildID );


	if (m_hHandlingThread)
	{
		m_bTerminatedHandlingThread = false;
		SetThreadPriority(m_hHandlingThread,
			THREAD_PRIORITY_NORMAL);
	}
	else
		ErrorExit("CreateThread HandlingThread");

	m_hReadingFromXYZBufferThread = ::CreateThread(NULL, 0, 
		ReadingFromXYZBuffer, 
		reinterpret_cast<LPVOID>(this), 
		0,
		&dwChildID );


	if (m_hReadingFromXYZBufferThread)
	{
		m_bTerminatedXYZBufferThread = false;
		SetThreadPriority(m_hReadingFromXYZBufferThread,
			THREAD_PRIORITY_TIME_CRITICAL);
	}
	else
		ErrorExit("CreateThread XYZBufferThread");

	m_hReadingFromCOMThread = ::CreateThread(NULL, 0, 
		ReadingFromCOM, 
		reinterpret_cast<LPVOID>(this),  
		0,
		&dwChildID );



	if (m_hReadingFromCOMThread)
	{
		m_bTerminatedCOMThread = false;
		SetThreadPriority(m_hReadingFromCOMThread,
			THREAD_PRIORITY_TIME_CRITICAL);
	}
	else
		ErrorExit("CreateThread");


}

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
	char  szPort[8];
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

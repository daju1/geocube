/*
Module : SMTP.CPP
Purpose: Implementation for a MFC class encapsulation of the SMTP protocol
Created: PJN / 22-05-1998
History: PJN / 15-06-1998 1) Fixed the case where a single dot occurs on its own
                          in the body of a message
													2) Class now supports Reply-To Header Field
                          3) Class now supports file attachments

				 PJN / 18-06-1998 1) Fixed a memory overwrite problem which was occurring 
				                  with the buffer used for encoding base64 attachments

         PJN / 27-06-1998 1) The case where a line begins with a "." but contains
                          other text is now also catered for. See RFC821, Section 4.5.2
                          for further details.
                          2) m_sBody in CSMTPMessage has now been made protected.
                          Client applications now should call AddBody instead. This
                          ensures that FixSingleDot is only called once even if the 
                          same message is sent a number of times.
                          3) Fixed a number of problems with how the MIME boundaries
                          were defined and sent.
                          4) Got rid of an unreferenced formal parameter 
                          compiler warning when doing a release build


Copyright (c) 1998 by PJ Naughter.  
All rights reserved.

*/

//////////////// Includes ////////////////////////////////////////////
#include "stdafx.h"
#include "smtp.h"
#include "Base64Coder.h"


//////////////// Macros / Locals /////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char CSMTPAttachment::m_base64tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                      "abcdefghijklmnopqrstuvwxyz0123456789+/";
#define BASE64_MAXLINE  76
#define EOL  "\r\n"



//////////////// Implementation //////////////////////////////////////
CSMTPSocket::CSMTPSocket()
{
  m_hSocket = INVALID_SOCKET; //default to an invalid scoket descriptor
}

CSMTPSocket::~CSMTPSocket()
{
  Close();
}

BOOL CSMTPSocket::Create()
{
  m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
  return (m_hSocket != INVALID_SOCKET);
}

BOOL CSMTPSocket::Connect(LPCTSTR pszHostAddress, int nPort)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

  //must have been created first
  ASSERT(m_hSocket != INVALID_SOCKET);
  
	LPSTR lpszAscii = T2A((LPTSTR)pszHostAddress);

	//Determine if the address is in dotted notation
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons((u_short)nPort);
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);

	//If the address is not dotted notation, then do a DNS 
	//lookup of it.
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL); 
			return FALSE;
		}
	}

	//Call the protected version which takes an address 
	//in the form of a standard C style struct.
	return Connect((SOCKADDR*)&sockAddr, sizeof(sockAddr));
}

BOOL CSMTPSocket::Connect(const SOCKADDR* lpSockAddr, int nSockAddrLen)
{
	return (connect(m_hSocket, lpSockAddr, nSockAddrLen) != SOCKET_ERROR);
}

BOOL CSMTPSocket::Send(LPCSTR pszBuf, int nBuf)
{
  //must have been created first
  ASSERT(m_hSocket != INVALID_SOCKET);

  return (send(m_hSocket, pszBuf, nBuf, 0) != SOCKET_ERROR);
}

int CSMTPSocket::Receive(LPSTR pszBuf, int nBuf)
{
  //must have been created first
  ASSERT(m_hSocket != INVALID_SOCKET);

  return recv(m_hSocket, pszBuf, nBuf, 0); 
}

void CSMTPSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		VERIFY(SOCKET_ERROR != closesocket(m_hSocket));
		m_hSocket = INVALID_SOCKET;
	}
}

BOOL CSMTPSocket::IsReadible(BOOL& bReadible)
{
  timeval timeout = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(m_hSocket, &fds);
  int nStatus = select(0, &fds, NULL, NULL, &timeout);
  if (nStatus == SOCKET_ERROR)
  {
    return FALSE;
  }
  else
  {
    bReadible = !(nStatus == 0);
    return TRUE;
  }
}





CSMTPAddress::CSMTPAddress(const CString& sAddress) : m_sEmailAddress(sAddress) 
{
}

CSMTPAddress::CSMTPAddress(const CString& sFriendly, const CString& sAddress) : 
              m_sFriendlyName(sFriendly), m_sEmailAddress(sAddress) 
{
}

CSMTPAddress& CSMTPAddress::operator=(const CSMTPAddress& r) 
{ 
  m_sFriendlyName = r.m_sFriendlyName; 
	m_sEmailAddress = r.m_sEmailAddress; 
	return *this;
}

CString CSMTPAddress::GetRegularFormat() const
{
  ASSERT(!m_sEmailAddress.IsEmpty()); //Email Address must be valid

  CString sAddress;
  if (m_sFriendlyName.IsEmpty())
    sAddress = m_sEmailAddress;  //Just transfer the address across directly
  else
    sAddress.Format(_T("%s <%s>"), m_sFriendlyName, m_sEmailAddress);

  return sAddress;
}





CSMTPAttachment::CSMTPAttachment()
{
  m_pszEncoded = NULL;
  m_nEncodedSize = 0;
}

CSMTPAttachment::~CSMTPAttachment()
{
  //free up any memory we allocated
  if (m_pszEncoded)
	{
    delete [] m_pszEncoded;
		m_pszEncoded = NULL;
	}
}

BOOL CSMTPAttachment::Attach(const CString& sFilename)
{
WriteRaporto("CSMTPAttachment::Attach(const CString& sFilename)\n");
WriteRaporto(sFilename);
 ASSERT(sFilename.GetLength());  //Empty Filename !

  //free up any memory we previously allocated
  if (m_pszEncoded)
  {
    delete [] m_pszEncoded;
    m_pszEncoded = NULL;
  }

  //determine the file size
  CFileStatus fs;
  if (!CFile::GetStatus(sFilename, fs))
    return FALSE;

  //open up the file for reading in
  CFile infile;
  if (!infile.Open(sFilename, CFile::modeRead | CFile::shareDenyWrite))
    return FALSE;

  //read in the contents of the input file
  char* pszIn = new char[fs.m_size];
  infile.Read(pszIn, fs.m_size);

  //allocate the encoded buffer
  int nOutSize = Base64BufferSize(fs.m_size);
  m_pszEncoded = new char[nOutSize];

  //Do the encoding
  EncodeBase64(pszIn, fs.m_size, m_pszEncoded, nOutSize, &m_nEncodedSize);

  //delete the input buffer
  delete [] pszIn;

  //Close the input file
  infile.Close();

	//Hive away the filename
  TCHAR sPath[_MAX_PATH];
  TCHAR sFname[_MAX_FNAME];
  TCHAR sExt[_MAX_EXT];
  _tsplitpath(sFilename, NULL, NULL, sFname, sExt);
  _tmakepath(sPath, NULL, NULL, sFname, sExt);
	m_sFilename = sPath;
WriteRaporto("CSMTPAttachment::Attach(const CString& sFilename) end\n");

  return TRUE;
}

int CSMTPAttachment::Base64BufferSize(int nInputSize)
{
  int nOutSize = (nInputSize+2)/3*4;                    // 3:4 conversion ratio
  nOutSize += strlen(EOL)*nOutSize/BASE64_MAXLINE + 3;  // Space for newlines and NUL
  return nOutSize;
}

BOOL CSMTPAttachment::EncodeBase64(const char* pszIn, int nInLen, char* pszOut, int nOutSize, int* nOutLen)
{
  //Input Parameter validation
  ASSERT(pszIn);
  ASSERT(pszOut);
  ASSERT(nOutSize);
  ASSERT(nOutSize >= Base64BufferSize(nInLen));

#ifndef _DEBUG
  //justs get rid of "unreferenced formal parameter"
  //compiler warning when doing a release build
  nOutSize;
#endif

  //Set up the parameters prior to the main encoding loop
  int nInPos  = 0;
  int nOutPos = 0;
  int nLineLen = 0;

  // Get three characters at a time from the input buffer and encode them
  for (int i=0; i<nInLen/3; ++i) 
  {
    //Get the next 2 characters
    int c1 = pszIn[nInPos++] & 0xFF;
    int c2 = pszIn[nInPos++] & 0xFF;
    int c3 = pszIn[nInPos++] & 0xFF;

    //Encode into the 4 6 bit characters
    pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
    pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4)];
    pszOut[nOutPos++] = m_base64tab[((c2 & 0x0F) << 2) | ((c3 & 0xC0) >> 6)];
    pszOut[nOutPos++] = m_base64tab[c3 & 0x3F];
    nLineLen += 4;

    //Handle the case where we have gone over the max line boundary
    if (nLineLen >= BASE64_MAXLINE-3) 
    {
      char* cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      nLineLen = 0;
    }
  }

  // Encode the remaining one or two characters in the input buffer
  char* cp;
  switch (nInLen % 3) 
  {
    case 0:
    {
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    case 1:
    {
      int c1 = pszIn[nInPos] & 0xFF;
      pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
      pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4)];
      pszOut[nOutPos++] = '=';
      pszOut[nOutPos++] = '=';
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    case 2:
    {
      int c1 = pszIn[nInPos++] & 0xFF;
      int c2 = pszIn[nInPos] & 0xFF;
      pszOut[nOutPos++] = m_base64tab[(c1 & 0xFC) >> 2];
      pszOut[nOutPos++] = m_base64tab[((c1 & 0x03) << 4) | ((c2 & 0xF0) >> 4)];
      pszOut[nOutPos++] = m_base64tab[((c2 & 0x0F) << 2)];
      pszOut[nOutPos++] = '=';
      cp = EOL;
      pszOut[nOutPos++] = *cp++;
      if (*cp) 
        pszOut[nOutPos++] = *cp;
      break;
    }
    default: 
    {
      ASSERT(FALSE); 
      break;
    }
  }
  pszOut[nOutPos] = 0;
  *nOutLen = nOutPos;
  return TRUE;
}





CSMTPMessage::CSMTPMessage() : m_sXMailer(_T("CSMTPConnection v1.12"))
{
}

CSMTPMessage::~CSMTPMessage()
{
}

void CSMTPMessage::SetRecipient(CSMTPAddress& recipient)
{
	m_Recipients.RemoveAll();
	m_Recipients.Add(recipient);
}
int CSMTPMessage::AddRecipient(CSMTPAddress& recipient)
{
  return m_Recipients.Add(recipient);
}

void CSMTPMessage::RemoveRecipient(int nIndex)
{
	m_Recipients.RemoveAt(nIndex);
}

CSMTPAddress CSMTPMessage::GetRecipient(int nIndex) const
{
  return m_Recipients.GetAt(nIndex);
}

int CSMTPMessage::GetNumberOfRecipients() const
{
	return m_Recipients.GetSize();
}

int CSMTPMessage::AddAttachment(CSMTPAttachment* pAttachment)
{
WriteRaporto("CSMTPMessage::AddAttachment(CSMTPAttachment* pAttachment)\n");
  ASSERT(pAttachment->GetFilename().GetLength()); //an empty filename !
	return m_Attachments.Add(pAttachment);
WriteRaporto("CSMTPMessage::AddAttachment(CSMTPAttachment* pAttachment) end\n");
}

void CSMTPMessage::RemoveAttachment(int nIndex)
{
	m_Attachments.RemoveAt(nIndex);
}

CSMTPAttachment* CSMTPMessage::GetAttachment(int nIndex) const
{
	return m_Attachments.GetAt(nIndex);
}

int CSMTPMessage::GetNumberOfAttachments() const
{
	return m_Attachments.GetSize();
}

CString CSMTPMessage::GetHeader() const
{
  //Create the "Date:" part of the header
  CTime now(CTime::GetCurrentTime());
  CString sDate(now.Format(_T("%a, %d %b %Y %H:%M:%S %Z")));

  //Create the "To:" part of the header
  CString sTo;
  for (int i=0; i<GetNumberOfRecipients(); i++)
  {
    CSMTPAddress recipient = GetRecipient(i);
    if (i)
 		  sTo += _T(",");
    sTo += recipient.GetRegularFormat();
  }

	//Stick everything together
	CString sBuf;
	sBuf.Format(_T("From: %s\r\n")\
              _T("To: %s\r\n")\
							_T("Subject: %s\r\n")\
							_T("Date: %s\r\n")\
							_T("X-Mailer: %s\r\n"), 
							m_From.GetRegularFormat(),
              sTo, 
							m_sSubject,
							sDate,
							m_sXMailer);


	//Add the optional Reply-To Field
	if (m_ReplyTo.m_sEmailAddress.GetLength())
	{
		CString sReply;
		sReply.Format(_T("Reply-To: %s\r\n"), m_ReplyTo.GetRegularFormat());
		sBuf += sReply;
	}

	//Add the optional fields if attachments are included
	if (m_Attachments.GetSize())
		sBuf += _T("MIME-Version: 1.0\r\nContent-type: multipart/mixed; boundary=\"#BOUNDARY#\"\r\n");

	sBuf += _T("\r\n");

	//Return the result
	return sBuf;
}

void CSMTPMessage::FixSingleDot(CString& sBody)
{
  int nFind = sBody.Find(_T("\n."));
  if (nFind != -1)
  {
	  CString sLeft(sBody.Left(nFind+1));
	  CString sRight(sBody.Right(sBody.GetLength()-(nFind+1)));
	  FixSingleDot(sRight);
	  sBody = sLeft + _T(".") + sRight;
  }
}

void CSMTPMessage::AddBody(const CString& sBody)
{
  m_sBody = sBody;

  //Fix the case of a single dot on a line in the message body
  FixSingleDot(m_sBody);
}





CSMTPConnection::CSMTPConnection()
{
  m_bConnected = FALSE;
#ifdef _DEBUG
  m_dwTimeout = 20000; //default timeout of 20 seconds when debugging
#else
  m_dwTimeout = 2000;  //default timeout of 2 seconds for normal release code
#endif
}

CSMTPConnection::~CSMTPConnection()
{
  if (m_bConnected)
    Disconnect();
}

BOOL CSMTPConnection::Connect(LPCTSTR pszHostName, int nPort, bool say_ehlo)
{
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

	//paramater validity checking
	ASSERT(pszHostName);
	
	//Create the socket
	if (!m_SMTP.Create())
	{
		TRACE(_T("Failed to create client socket\n"));
		return FALSE;
	}
	
	//Connect to the SMTP Host
	if (!m_SMTP.Connect(pszHostName, nPort))
	{
		CString err; err.Format(_T("Could not connect to the SMTP server %s on port %d\n"), pszHostName, nPort);
		AfxMessageBox(err);
		return FALSE;
	}
	else
	{
		//We're now connected !!
		m_bConnected = TRUE;
        
		//check the response to the login
		if (!ReadCommandResponse(220))
		{
			Disconnect();
			return FALSE;
		}

#if 0
		//retreive the localhost name
		char sHostName[100];
		gethostname(sHostName, sizeof(sHostName));
		TCHAR* pszHostName = A2T(sHostName);
#endif
		//Send the HELO command
		CString sBuf;
		if (say_ehlo)
			sBuf.Format(_T("EHLO %s\r\n"), pszHostName);
		else
			sBuf.Format(_T("HELO %s\r\n"), pszHostName);

		LPCSTR pszData = T2A((LPTSTR) (LPCTSTR) sBuf);
		int nCmdLength = strlen(pszData);
		
		if (!m_SMTP.Send(pszData, nCmdLength))
		{
			Disconnect();			
			return FALSE;
		}

		//check the response to the HELO command
		if (!ReadCommandResponse(250))
		{
			Disconnect();
			return FALSE;
		} 
		return TRUE;
	}
}

BOOL CSMTPConnection::Disconnect()
{
	BOOL bSuccess = FALSE;   
	
	//disconnect from the SMTP server if connected 
	if (m_bConnected)
	{
		char sBuf[10];
		strcpy(sBuf, "QUIT\r\n");
		int nCmdLength = strlen(sBuf);
		if (!m_SMTP.Send(sBuf, nCmdLength))
			TRACE(_T("Failed in call to send QUIT command\n"));
		
		//Check the reponse
		bSuccess = ReadCommandResponse(221);
		if (!bSuccess)
			SetLastError(ERROR_BAD_COMMAND);
		
		//Reset all the state variables
		m_bConnected = FALSE;
	}
	else
		TRACE(_T("Already disconnected\n"));
    
	//free up our socket
	m_SMTP.Close();
	
	return bSuccess;
}

BOOL CSMTPConnection::Autorization(
								   LPCTSTR szUser, 
								   LPCTSTR szPas)
{
	// General purpose strings
	CString strCommand;
	CString strResponse;

	//Alex beb
	if(strlen(szUser)>0)
	{
		strCommand = "AUTH LOGIN";
				
		strCommand += "\r\n";
#if 0
		theSocket.Send(strCommand);
		
		// and check the response
		if (theSocket.Receive(strResponse, uTimeOut) == SOCKET_ERROR)
		{
			ReportSocketError(theSocket.GetLastError());
			return FALSE;
		}
		if (strResponse.Left(3) != _T("334"))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			theSocket.Send("QUIT\r\n");
			return FALSE;
		}
#else
		LPCSTR pszData = T2A((LPTSTR) (LPCTSTR) strCommand);
		int nCmdLength = strlen(pszData);
		
		if (!m_SMTP.Send(pszData, nCmdLength))
		{
			Disconnect();			
			return FALSE;
		}

		//check the response to the HELO command
		if (!ReadCommandResponse(334))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			Disconnect();
			return FALSE;
		} 

#endif

		Base64Coder		Coder;
		Coder.Encode(szUser);
		strCommand = Coder.EncodedMessage();
	 

		
		strCommand += "\r\n";
#if 0
		theSocket.Send(strCommand);
		
		// and check the response
		if (theSocket.Receive(strResponse, uTimeOut) == SOCKET_ERROR)
		{
			ReportSocketError(theSocket.GetLastError());
			return FALSE;
		}
		if (strResponse.Left(3) != _T("334"))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			theSocket.Send("QUIT\r\n");
			return FALSE;
		}
#else
		pszData = T2A((LPTSTR) (LPCTSTR) strCommand);
		nCmdLength = strlen(pszData);
		
		if (!m_SMTP.Send(pszData, nCmdLength))
		{
			Disconnect();			
			return FALSE;
		}

		//check the response to the HELO command
		if (!ReadCommandResponse(334))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			Disconnect();
			return FALSE;
		} 
#endif
		
		Coder.Encode(szPas);
		strCommand = Coder.EncodedMessage();	 

		
		strCommand += "\r\n";
#if 0
		theSocket.Send(strCommand);
		
		// and check the response
		if (theSocket.Receive(strResponse, uTimeOut) == SOCKET_ERROR)
		{
			ReportSocketError(theSocket.GetLastError());
			return FALSE;
		}
		if (strResponse.Left(3) != _T("235"))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			theSocket.Send("QUIT\r\n");
			return FALSE;
		}
#else
		pszData = T2A((LPTSTR) (LPCTSTR) strCommand);
		nCmdLength = strlen(pszData);
		
		if (!m_SMTP.Send(pszData, nCmdLength))
		{
			Disconnect();			
			return FALSE;
		}

		//check the response to the HELO command
		if (!ReadCommandResponse(235))
		{
			CString strError = "ERROR: Sender rejected\r\n";
			strError += strResponse;
			AfxMessageBox(strError);

			Disconnect();
			return FALSE;
		} 
#endif
		return TRUE;
	}
	//Alex end
	//helo
}

BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message)
{
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 1\n");
	//For correct operation of the T2A macro, see MFC Tech Note 59
	USES_CONVERSION;

	//paramater validity checking
	ASSERT(m_bConnected); //Must be connected to send a message
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 2\n");

	//Send the MAIL command
	ASSERT(Message.m_From.m_sEmailAddress.GetLength());
	CString sBuf;
	sBuf.Format(_T("MAIL FROM:<%s>\r\n"), Message.m_From.m_sEmailAddress);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 3\n");
WriteRaporto("sBuf = ");
WriteRaporto(sBuf);
WriteRaporto("\n");
	LPCSTR pszMailFrom = T2A((LPTSTR) (LPCTSTR) sBuf);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 4\n");
WriteRaporto("pszMailFrom = ");
WriteRaporto(pszMailFrom);
WriteRaporto("\n");

	int nCmdLength = strlen(pszMailFrom);
	if (!m_SMTP.Send(pszMailFrom, nCmdLength))
	{
		TRACE(_T("Failed in call to send MAIL command\n"));
		return FALSE;
	}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 5\n");

	//check the response to the MAIL command
	if (!ReadCommandResponse(250))
	{
		SetLastError(ERROR_BAD_COMMAND);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) SetLastError(ERROR_BAD_COMMAND);\n");
		return FALSE;
	} 
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 6\n");
	
	//Send the RCPT command, one for each recipient
	ASSERT(Message.GetNumberOfRecipients()); //Must have at least one recipient for the message
	for (int i=0; i<Message.GetNumberOfRecipients(); i++)
	{
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 7\n");
		CSMTPAddress recipient = Message.GetRecipient(i);
		ASSERT(recipient.m_sEmailAddress.GetLength()); //must have an email address for this recipient
		sBuf.Format(_T("RCPT TO:<%s>\r\n"), recipient.m_sEmailAddress);
WriteRaporto("sBuf = ");
WriteRaporto(sBuf);
WriteRaporto("\n");
		LPTSTR pszRCPT = T2A((LPTSTR) (LPCTSTR) sBuf);
WriteRaporto("pszRCPT = ");
WriteRaporto(pszRCPT);
WriteRaporto("\n");

WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 8\n");
		int nCmdLength = strlen(pszRCPT);
		if (!m_SMTP.Send(pszRCPT, nCmdLength))
		{
			TRACE(_T("Failed in call to send MAIL command\n"));
WriteRaporto("Message Was not sent to recepient \n");
WriteRaporto(recipient.m_sEmailAddress);
WriteRaporto("\n");
			return FALSE;
		}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 9\n");
		
		//check the response to each RCPT command
		if (!ReadCommandResponse(250))
		{
			SetLastError(ERROR_BAD_COMMAND);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) SetLastError(ERROR_BAD_COMMAND);\n");
WriteRaporto("Message Was not sent to recepient \n");
WriteRaporto(recipient.m_sEmailAddress);
WriteRaporto("\n");
			return FALSE;
		} 
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 10\n");
	}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 11\n");
	
	//Send the DATA command
	char* pszDataCommand = "DATA\r\n";
	nCmdLength = strlen(pszDataCommand);
	if (!m_SMTP.Send(pszDataCommand, nCmdLength))
	{
		TRACE(_T("Failed in call to send MAIL command\n"));
		return FALSE;
	}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 12\n");
	
	//check the response to the DATA command
	if (!ReadCommandResponse(354))
	{
		SetLastError(ERROR_BAD_COMMAND);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) SetLastError(ERROR_BAD_COMMAND);\n");
		return FALSE;
	} 
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 13\n");

  //Send the Header
  CString sHeader = Message.GetHeader();
  char* pszHeader = T2A((LPTSTR) (LPCTSTR) sHeader);
  nCmdLength = strlen(pszHeader);
WriteRaporto("pszHeader = ");
WriteRaporto(pszHeader);
WriteRaporto("\n");
  if (!m_SMTP.Send(pszHeader, nCmdLength))
  {
    TRACE(_T("Failed in call to send the header\n"));
    return FALSE;
  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 14\n");

	//Send the Mime Header for the body
  if (Message.m_Attachments.GetSize())
  {
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 15\n");
	  char* psBodyHeader = (_T("\r\n--#BOUNDARY#\r\n")\
		                      _T("Content-Type: text/plain; charset=us-ascii\r\n")\
									        _T("Content-Transfer-Encoding: quoted-printable\r\n\r\n"));
    nCmdLength = strlen(psBodyHeader);
WriteRaporto("psBodyHeader = ");
WriteRaporto(psBodyHeader);
WriteRaporto("\n");
    if (!m_SMTP.Send(psBodyHeader, nCmdLength))
    {
      TRACE(_T("Failed in call to send the body header\n"));
      return FALSE;
    }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 16\n");
  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 17\n");

  //Send the body
  char* pszBody = T2A((LPTSTR) (LPCTSTR) Message.m_sBody);
  nCmdLength = strlen(pszBody);
WriteRaporto("pszBody = ");
WriteRaporto(pszBody);
WriteRaporto("\n");
 if (!m_SMTP.Send(pszBody, nCmdLength))
  {
    TRACE(_T("Failed in call to send the header\n"));
    return FALSE;
  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 18\n");

  //Send all the attachments
  for (i=0; i<Message.m_Attachments.GetSize(); i++)
  {
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 19\n");
    CSMTPAttachment* pAttachment = Message.m_Attachments.GetAt(i);

	if (pAttachment)
	{
		//First send the Mime header for each attachment
		CString sContent;
		sContent.Format(_T("\r\n\r\n--#BOUNDARY#\r\n")\
		                _T("Content-Type: application/octet-stream; name=%s\r\n")\
										_T("Content-Transfer-Encoding: base64\r\n")\
										_T("Content-Disposition: attachment; filename=%s\r\n\r\n"), pAttachment->GetFilename(), pAttachment->GetFilename());

		char* pszContent = T2A((LPTSTR) (LPCTSTR) sContent);
WriteRaporto("pszContent = ");
WriteRaporto(pszContent);
WriteRaporto("\n");
		nCmdLength = strlen(pszContent);
		if (!m_SMTP.Send(pszContent, nCmdLength))
		{
			TRACE(_T("Failed in call to send Mime attachment header\n"));
			return FALSE;
		}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 20\n");

WriteRaporto("pAttachment->GetEncodedBuffer() = ");
WriteRaporto(pAttachment->GetEncodedBuffer());
WriteRaporto("\n");
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 21\n");
		//Then send the encoded attachment
		if (!m_SMTP.Send(pAttachment->GetEncodedBuffer(), pAttachment->GetEncodedSize()))
		{
		TRACE(_T("Failed in call to send the attachment\n"));
		return FALSE;
		}
	}
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 22\n");
  }

	//Send the final mime boundary
  if (Message.m_Attachments.GetSize())
  {
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 23\n");
	  char* pszFinalBoundary = "\r\n--#BOUNDARY#--";
	  nCmdLength = strlen(pszFinalBoundary);
WriteRaporto("pszFinalBoundary = ");
WriteRaporto(pszFinalBoundary);
WriteRaporto("\n");
	  if (!m_SMTP.Send(pszFinalBoundary, nCmdLength))
	  {
		  TRACE(_T("Failed in call to send Mime attachment header\n"));
		  return FALSE;
	  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 24\n");
  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 25\n");

  //Send the end of message indicator
  char* pszEOM = "\r\n.\r\n";
	nCmdLength = strlen(pszEOM);
  if (!m_SMTP.Send(pszEOM, nCmdLength))
  {
    TRACE(_T("Failed in call to send end of message indicator\n"));
    return FALSE;
  }
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 26\n");

  //check the response to the End of Message command
  if (!ReadCommandResponse(250))
  {
    SetLastError(ERROR_BAD_COMMAND);
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) SetLastError(ERROR_BAD_COMMAND);;\n");
    return FALSE;
  } 
WriteRaporto("BOOL CSMTPConnection::SendMessage(CSMTPMessage& Message) 27 return TRUE;\n");

	return TRUE;
}

BOOL CSMTPConnection::ReadCommandResponse(int nExpectedCode)
{
	char sBuf[1000];
	return ReadResponse(sBuf, sizeof(sBuf), "\r\n", nExpectedCode);
}

BOOL CSMTPConnection::ReadResponse(LPSTR pszBuffer, int nBuf, LPSTR pszTerminator, int nExpectedCode)
{
	//paramater validity checking
	ASSERT(pszBuffer);
	ASSERT(nBuf);

  //must have been created first
  ASSERT(m_bConnected);

  //retrieve the reponse using until we
	//get the terminator or a timeout occurs
	BOOL bFoundTerminator = FALSE;
	int nReceived = 0;
	DWORD dwStartTicks = ::GetTickCount();
	while (!bFoundTerminator)
	{
		//timeout has occured
		if ((::GetTickCount() - dwStartTicks) >	m_dwTimeout)
		{
		  pszBuffer[nReceived] = '\0';
			SetLastError(WSAETIMEDOUT);
      m_sLastCommandResponse = pszBuffer; //Hive away the last command reponse
			return FALSE;
		}

    //check the socket for readability
    BOOL bReadible;
    if (!m_SMTP.IsReadible(bReadible))
    {
	    pszBuffer[nReceived] = '\0';
			m_sLastCommandResponse = pszBuffer; //Hive away the last command reponse
			return FALSE;
    }
    else if (!bReadible) //no data to receive, just loop around
    {
      Sleep(100); //Wait for 100 ms prior to looping around, 
                  //helps to improve performance of system
      continue;
    }

		//receive the data from the socket
	  int nData = m_SMTP.Receive(pszBuffer+nReceived, nBuf-nReceived);
		if (nData == SOCKET_ERROR)
		{
		  pszBuffer[nReceived] = '\0';
      m_sLastCommandResponse = pszBuffer; //Hive away the last command reponse
		  return FALSE; 
		}
		else
		{
      if (nData)
			  dwStartTicks = ::GetTickCount(); //Reset the idle timeout
		  nReceived += nData;							   //Increment the count of data received
		}

		pszBuffer[nReceived] = '\0';	//temporarily NULL terminate the string
																	//so that strstr works
		bFoundTerminator = (strstr(pszBuffer, pszTerminator) != NULL);
	}

	//Remove the terminator from the response data
  pszBuffer[nReceived - strlen(pszTerminator)] = '\0';

  //determine if the response is an error
	char sCode[4];
	strncpy(sCode, pszBuffer, 3);
	sCode[3] = '\0';
	sscanf(sCode, "%d", &m_nLastCommandResponseCode);
	BOOL bSuccess = (m_nLastCommandResponseCode == nExpectedCode);

  if (!bSuccess)
  {
    SetLastError(WSAEPROTONOSUPPORT);
    m_sLastCommandResponse = pszBuffer; //Hive away the last command reponse
  }

  return bSuccess;
}


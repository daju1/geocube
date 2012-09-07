#include "stdafx.h"
#include ".\commandlineparser.h"


#define RAPORT
#undef RAPORT

const char * GetNameFromCommandLine(const char *in, char *out)
{
#ifdef RAPORT
#define RAPORT_STR_LEN 256
	printf( "GetNameFromCommandLine in = %s\n", in);
#endif
	const char *p, *p1, *p2;
	p  = NULL;
	p1 = NULL;
	p2 = NULL;

	// ���� ����������� � ����������� ������� 
	// � ����� �� ���������� ������
	p1 = strchr(in,'\"');
	if(p1)
		p2 = strchr(p1+1,'\"');

	if (p1 && p2)
	{
#ifdef RAPORT
		printf( "GetNameFromCommandLine p1 = %s p2 = %s\n", p1, p2);
#endif
		// ������ ���� ���������, � ����� ��� ����� 
		// ������� ��� ������� � ��������� ������ ��� ������� ��������� � ����
		// ��� ���������� �����
		int n = sscanf(in, "%s", out);
#ifdef RAPORT
		printf( "GetNameFromCommandLine n = %d out = %s\n", n, out);
#endif
		
		if (n==1 && out[0] == '\"')
		{
			// ���� ������ ����� 
			// ���������� � �������, �� �� ��������� -
			// � ��������� ������� �������� ������ 1-�� ����
			// �� �� ���������� ���

			// �������� �� ���������� ������ ���� � �����
			int len = min(FILE_NAME_LEN-1, p2-p1-1);
			strncpy(out, p1+1, len);
			out[len] = '\0';
#ifdef RAPORT
			printf( "GetNameFromCommandLine len = %d out = %s\n", len, out);
#endif

			// ����������� ����� ������ �� ������ in �� ������ �������
			len = p2-in+1;

#ifdef RAPORT
			printf( "GetNameFromCommandLine len = %d strlen(in) = %d\n", len, strlen(in));
#endif

			if (strlen(in) > len + 1 )
			{
#ifdef RAPORT
				printf( "GetNameFromCommandLine (strlen(in) > len + 1 )\n");
#endif
				p = p2+1;
			}

#ifdef RAPORT
			printf( "GetNameFromCommandLine p = %s\n", p);
#endif

			// ���������� ��������� ��� ������ ������
			return p;

		}
		else
		{
			// �����
			// ���� ������ ����� 
			// �� ���������� � �������, �� ��� ������ -
			// � ��������� ������� �������� ���� �� ��������� ������
			// � ������ ��� ���� �� ��� �������� � ������� sscanf

#ifdef RAPORT
			printf( "GetNameFromCommandLine ������ ��� ���� �� ��� �������� � ������� sscanf n = %d out = %s\n", n, out);
#endif
			if (n != 1)
			{
				p = NULL;
				return p;
			}
		}
	}
	else
	{
		// ���� ������� ��� 
		// ������ ����� ������ 
		// ������� ��� ������� � ������ �� ��� ���������� 
		// ���� ����� ������� ��������� ������� sscanf
		int n = sscanf(in, "%s", out);
#ifdef RAPORT
		printf( "GetNameFromCommandLine ���� ������� ��� n = %d out = %s\n", n, out);
#endif
		if (n != 1)
		{
			p = NULL;
			return p;
		}
	}

	// ����� ��������� ��������� ��������� � �������� ������
	const char * p0 = strstr(in, out);
	if (p0 == NULL)
		return p0;
	// ����� ������ out
	int len = strlen(out);
#ifdef RAPORT
	printf( "GetNameFromCommandLine len = %d strlen(p0) = %d\n", len, strlen(p0));
#endif

	if (strlen(p0) > len + 1 )
	{
#ifdef RAPORT
		printf( "GetNameFromCommandLine (strlen(p0) > len + 1 ) 2\n");
#endif
		p = p0 + len + 1;
	}
#ifdef RAPORT
	printf( "GetNameFromCommandLine p 2 = %s\n", p);
#endif


	// ���������� ��������� ��� ������ ������
	return p;
}

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

CommandLineParser::CommandLineParser(void)
{
	open_file[0] =  '\0';
}

CommandLineParser::~CommandLineParser(void)
{
}
void CommandLineParser::DoParsing()
{
#ifdef RAPORT
	printf( "CServiceModule::ParseCommandLine()\n");
#endif

	// ������ ���������� ������ � �������
	LPSTR command_line = GetCommandLine();
#ifdef RAPORT
	printf( "command_line = %s\n", command_line);
#endif
				
	const char * p;
	if (command_line)
		p = GetNameFromCommandLine(command_line, module);

#if 1
    TCHAR szTokens[] = _T("-&/");

    LPCTSTR lpszToken = FindOneOf(command_line, szTokens);
    while (lpszToken != NULL)
    {
		//	printf("lpszToken = %s\n", lpszToken);
        //if (lstrcmpi(lpszToken, _T("open"))==0)
        if (strspn(lpszToken, _T("open"))==lstrlen(_T("open")))
		{
			int index = lstrlen(_T("open"));
			if(lstrlen(lpszToken) > index)
			{
				p = GetNameFromCommandLine(&lpszToken[index], open_file);
			}
		}

        lpszToken = FindOneOf(lpszToken, szTokens);
    }
#ifdef RAPORT
	printf("p = %s\n", p);
#endif
#else
	if (p) 	p = GetNameFromCommandLine(command_line, open_file);
#endif



/*	if (p)
		p = GetNameFromCommandLine(p, config);
	if (p)
		p = GetNameFromCommandLine(p, login);*/

	if(module)
	{
		// ������ �������� �����, ��� ����� ����������� ����
		char *p, *p1, *p2;
		p  = NULL;
		p1 = NULL;
		p2 = NULL;

		size_t pos_of_flash = 0;
		strcpy(path, module);

		p1 = strrchr(path,'\\');
		p2 = strrchr(path,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = NULL;

		if (p)
			pos_of_flash = int(p - path) / sizeof(char);
		path[pos_of_flash] = '\0';
	}



#ifdef RAPORT
	printf("\n");
	printf( "command_line = %s\n",  command_line);
//#endif
//#ifdef RAPORT
	printf( "module = %s\n",  module);
//#endif
//#ifdef RAPORT
	printf( "path = %s\n",  path);
//#endif
//#ifdef RAPORT
	printf( "open_file = %s\n",  open_file);
#endif

}

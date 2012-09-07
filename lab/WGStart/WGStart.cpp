// WGStart.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false) ;
void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess = false);
void ErrorPrint(LPTSTR lpszFunction);

int main(int argc, char* argv[])
{
	printf("Starting WenGeo!\n");
#if 0
	if (ERROR_SUCCESS != RegDeleteKey( HKEY_CURRENT_USER,
		"Software\\Mathematical Center\\WenGeo\\Option"))
	{
		ErrorExit("RegDeleteKey");

	}
#else
    HKEY hKey;
    if (ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER,
		"Software\\Mathematical Center\\WenGeo\\Option",
		0, KEY_SET_VALUE, &hKey ))
	{			
		if (ERROR_SUCCESS != RegDeleteValue( hKey,
			"WDSHURFW"))
		{
			ErrorExit("RegDeleteValue");

		}
	}
#endif

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process. 
    if( !CreateProcess( "C:\\Program Files\\Mathematical Center\\WenGeo\\WenGeo.exe", // No module name (use command line). 
        "WenGeo", // Command line. 
        NULL,             // Process handle not inheritable. 
        NULL,             // Thread handle not inheritable. 
        FALSE,            // Set handle inheritance to FALSE. 
        0,                // No creation flags. 
        NULL,             // Use parent's environment block. 
        NULL,             // Use parent's starting directory. 
        &si,              // Pointer to STARTUPINFO structure.
        &pi )             // Pointer to PROCESS_INFORMATION structure.
    ) 
    {
        ErrorExit( "CreateProcess failed." );
    }

    // Wait until child process exits.
#if 0
    WaitForSingleObject( pi.hProcess, INFINITE );
#endif
    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	return 0;
}


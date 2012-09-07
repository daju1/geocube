// TezeyCon2003.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "generic.h"

HINSTANCE hInst;								// current instance

int main(int argc, _TCHAR* argv[])
{
	hInst = GetModuleHandle(NULL);
	//printf("main hInst = %x\n", hInst);
	WinMain( hInst, NULL,
		::GetCommandLine(), /*int nCmdShow */1);
	return 0;
}


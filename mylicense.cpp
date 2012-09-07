#include "StdAfx.h"
#include "mylicense.h"
#include "math.h"
#include <stdio.h>

#define USE_GRINVICH_TIME


#ifdef USE_GRINVICH_TIME
#define GetTime GetSystemTime
#else
#define GetTime GetLocalTime
#endif

BOOL /*__fastcall*/ CheckMyLicense()
{
	return true;

	int cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;



	//MessageBox(0, lpCmdLine, GetCommandLine(),0);

	int days, compiled;

	SYSTEMTIME time;
	GetTime(&time);

	int d = time.wDay;
	int mo = time.wMonth;
	int y = time.wYear;
	
	//printf("days = [%d %d %d]\n", y, mo, d);

	days = 365*y +                   // Convert year, month, day to date number
	  (int)ceil((double)y/4.0)-(int)ceil((double)y/100.0)+(int)ceil((double)y/400.0) + cumdpm[mo-1] + 
		((mo > 2) && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) + d;

	//printf("days = %d\n", days);

/*	DWORD lpdwDaysSet[1];
	DWORD lpdwDaysGet[1];
	lpdwDaysSet[0] = DWORD(days);*/

//	FILETIME  ftLastWriteTime;
	// Выбрать время последнего видоизменения ключа или любого его из значений
	//...........................................
//	RegQueryInfoKey( HKEY_CLASSES_ROOT, NULL, NULL, NULL, NULL, NULL, NULL,
//		NULL, NULL, NULL, NULL, &ftLastWriteTime);
#if 1

	LONG  lResult;
	HKEY  hKeyResult = 0;
	DWORD dwDisposition = 0;

	bool toRegSetValue;

	// Создать или открыть ключ
	//................................
	lResult = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
      		"SOFTWARE\\ravyezetty\\Last\\Time", 0, "",
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			NULL, &hKeyResult, &dwDisposition );

	switch(dwDisposition)
	{
	case REG_CREATED_NEW_KEY:
		toRegSetValue = true;
		break;
	case REG_OPENED_EXISTING_KEY:
		toRegSetValue = false;
		break;
	}

		
	//printf("toRegSetValue = %d\n", toRegSetValue);

	DWORD DaysSet = days;
	DWORD DaysGet;

	//printf("DaysSet = %d\n", DaysSet);

	if(toRegSetValue)
	{
		// Присвоить значение
		//..................................
		if ( lResult == ERROR_SUCCESS )
		{
			lResult = RegSetValueEx( hKeyResult, "ravyezetty", 0, REG_DWORD,
				(unsigned char *)&DaysSet, sizeof(DWORD));
			RegCloseKey( hKeyResult );
		}
	}
	else
	{
		if ( lResult == ERROR_SUCCESS )
		{
                  DWORD dwType;
                  DWORD dwBytes = sizeof(DWORD);			

                  // Выбрать значение
                  //........................
                  RegQueryValueEx( hKeyResult, "ravyezetty", 0, &dwType,
                                   (unsigned char *)&DaysGet, &dwBytes );
//printf("DaysGet = %d\n", DaysGet);
			
			if(DaysGet>DaysSet+1)
			{
				RegCloseKey( hKeyResult );
				char str[200];
				wsprintf(str, "Системное время компьютера нарушено\n");
				MessageBox(0, str, "Временные вариации показаний прибора \"Tезей\"", 0);
				return FALSE;
			}
			else
			{
				// Присвоить значение
				//..................................
				lResult = RegSetValueEx( hKeyResult, "ravyezetty", 0, REG_DWORD,
					(unsigned char *)&DaysSet, sizeof(DWORD));
			}
			RegCloseKey( hKeyResult );
		}
	}	
#endif

	//compilation time
	char date[255];
	sprintf(date,"%s", __DATE__);
	char mon[32];
	sscanf(date, "%s %d %d", mon, &d, &y);

	if (strcmp(mon,"Jan") == 0)
		mo = 1;
	if (strcmp(mon,"Feb") == 0)
		mo = 2;
	if (strcmp(mon,"Mar") == 0)
		mo = 3;
	if (strcmp(mon,"Apr") == 0)
		mo = 4;
	if (strcmp(mon,"May") == 0)
		mo = 5;
	if (strcmp(mon,"Jun") == 0)
		mo = 6;
	if (strcmp(mon,"Jul") == 0)
		mo = 7;
	if (strcmp(mon,"Aug") == 0)
		mo = 8;
	if (strcmp(mon,"Sep") == 0)
		mo = 9;
	if (strcmp(mon,"Oct") == 0)
		mo = 10;
	if (strcmp(mon,"Nov") == 0)
		mo = 11;
	if (strcmp(mon,"Dec") == 0)
		mo = 12;

	//printf("compiled = %s %s %d %d mo = %d\n", __DATE__, mon, d, y, mo);
	//printf("compiled = [%d %d %d]\n", y, mo, d);

	compiled = 365*y +                   // Convert year, month, day to date number
	  (int)ceil((double)y/4.0)-(int)ceil((double)y/100.0)+(int)ceil((double)y/400.0) + cumdpm[mo-1] + 
		((mo > 2) && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) + d;
	
	//printf("compiled = %d\n", compiled);

	int used_days = days - compiled;
	//printf("used_days = %d\n", used_days);
	//int remaine_days = (1.2 * 365) / 12 - used_days;
	int remaine_days = 20 - used_days;
	if (false && remaine_days < 30 && remaine_days >=0)
	{
		//char str[200];
		char str[200];
		sprintf(str, "trial soon will be off!!!\n remaine_days = %d\n", remaine_days);
		//printf(str);
		//wsprintf(str, "Срок использования программы\n"
		//	"истекает через %i дней", remaine_days);
		//MessageBox(0, str, "Временные вариации показаний прибора \"Tезей\"", 0);
	}
	if (remaine_days < 0)
	{
		char str[200];
		sprintf(str, "trial off!!! days ago = %d\n", - remaine_days);
		//printf(str);
		//wsprintf(str, "Срок использования программы\n"
		//	"\tистёк");
		//MessageBox(0, str, "Временные вариации показаний прибора \"Tезей\"", 0);
		return FALSE;
	}
	return TRUE;
}

/*
VOID EnumerateRegistry( HKEY hKey, HTREEITEM hParent )
{
   static TV_INSERTSTRUCT tvi;
   static DWORD           dwNameLen;
   static DWORD           dwClassLen;
   static FILETIME        ftime;

   HTREEITEM hNewItem;
   HKEY      hNewKey;
   LPTSTR    lpszName;
   LPTSTR    lpszClass;
   LPTSTR    lpszValueName;
   DWORD     dwMaxNameLen;
   DWORD     dwMaxClassLen;
   DWORD     dwMaxValueNameLen;
   LONG      lReturn;
   DWORD     dwIndex = 0;
   FILETIME  ftLastWriteTime;

   // Выбрать максимальную длину имени ключа, имени класса и 
   // имени значения с данными о ключе.
   //...........................................
   RegQueryInfoKey( hKey, NULL, NULL, NULL, NULL, &dwMaxNameLen, &dwMaxClassLen,
 			  NULL, &dwMaxValueNameLen, NULL, NULL, &ftLastWriteTime);
   // Выполнить приращение на 1, поскольку в данном случае требуется место 
   // для символа, завершающего строку.
   //...............................
   dwMaxNameLen++;
   dwMaxClassLen++;
   dwMaxValueNameLen++;

   // Распределить память под выборку информации.
   //..............................................
   lpszName      	= (LPTSTR)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                           		   dwMaxNameLen );
   lpszClass     	= (LPTSTR)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                                	   dwMaxClassLen );
   lpszValueName 	= (LPTSTR)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
                                	   dwMaxValueNameLen );

   tvi.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
   tvi.hInsertAfter = TVI_LAST;

   // Перечислить все подключи для текущего ключа.
   //...............................................
   do
   {
      dwNameLen = dwMaxNameLen;
      dwClassLen = dwMaxClassLen;

      lReturn = RegEnumKeyEx( hKey, dwIndex, lpszName, &dwNameLen,
                              NULL, lpszClass, &dwClassLen, &ftime );

      if ( lReturn != ERROR_NO_MORE_ITEMS )
      {
         tvi.item.iImage  = 0;
         tvi.item.iSelectedImage = 1;
         tvi.item.pszText = lpszName;
         tvi.hParent = hParent;

         hNewItem = TreeView_InsertItem( hTree, &tvi );

         if ( RegOpenKeyEx( hKey, lpszName, 0, KEY_ALL_ACCESS,
                         	    &hNewKey ) == ERROR_SUCCESS )
         {
            EnumerateRegistry( hNewKey, hNewItem );
            RegCloseKey( hNewKey );
         }
      }
      dwIndex++;
   }
   while( lReturn != ERROR_NO_MORE_ITEMS );

   tvi.item.iImage  = 2;
   tvi.item.iSelectedImage = 2;
   dwIndex = 0;

   // Перечислить все значения для текущего ключа.
   //..............................................
   do
   {
      dwNameLen = dwMaxValueNameLen;

      lReturn = RegEnumValue( hKey, dwIndex, lpszValueName,
                              &dwNameLen, 0, NULL, NULL, NULL );

      if ( lReturn != ERROR_NO_MORE_ITEMS )
      {
         tvi.item.pszText = lpszValueName;
         tvi.hParent = hParent;

         TreeView_InsertItem( hTree, &tvi );
      }

      dwIndex++;
   }
   while( lReturn != ERROR_NO_MORE_ITEMS );

   // Очистить ранее распределенную память.
   //..................................
   if ( lpszName  )     HeapFree( GetProcessHeap(), 0, lpszName );
   if ( lpszClass )     HeapFree( GetProcessHeap(), 0, lpszClass );
   if ( lpszValueName ) HeapFree( GetProcessHeap(), 0, lpszValueName );
}*/
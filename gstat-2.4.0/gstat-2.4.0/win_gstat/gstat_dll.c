// gstat_dll.cpp : Defines the entry point for the DLL application.
//

#include "windows.h"
#include "gstat_dll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
    case DLL_PROCESS_ATTACH:  // Подключение DLL
      // Выполняем все необходимые
      // действия по инициализации

      // если инициализация прошла
      // успешно возвращаем TRUE
      // в противном случае – FALSE
      return 1; 

    case DLL_PROCESS_DETACH: // Отключение DLL
      // Выполняем все действия
      // по деинициализации
      break;

    case DLL_THREAD_ATTACH: // Создание нового потока
      // Переходим на многопоточную версию,
      // если необходимо
      break;

    case DLL_THREAD_DETACH: // Завершение потока
      // Освобождаем переменные, связанные с потоком
      break;
    }
    return TRUE;// Возвращаем что-нибудь (все равно
        // код возврата игнорируется)
}
//int __declspec(dllexport) gstat_main(int argc, char *argv[]);
/*
// This is an example of an exported variable
GSTAT_DLL_API int nGstat_dll=0;

// This is an example of an exported function.
GSTAT_DLL_API int fnGstat_dll(void)
{
	return 42;
}
*/

// This is the constructor of a class that has been exported.
// see gstat_dll.h for the class definition
//CGstat_dll::CGstat_dll()
//{ 
//	return; 
//}


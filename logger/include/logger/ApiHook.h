#pragma once


namespace Logger
{


class ApiHook
{
public:
   // Hook a function in all modules
   ApiHook(PSTR  pszCalleeModName,
           PSTR  pszFuncName,
           PROC  pfnHook,
           PROC* pfnOrig = 0);

   // Unhook a function from all modules
   ~ApiHook();

   // Returns the original address of the hooked function
   operator PROC()
   {
      return(m_pfnOrig);
   }

   // Hook module w/CAPIHook implementation?
   // I have to make it static because I need to use it 
   // in ReplaceIATEntryInAllMods
   static BOOL ExcludeAPIHookMod;

public:
   // Calls the real GetProcAddress 
   static FARPROC WINAPI GetProcAddressRaw(HMODULE hmod,
                                           PCSTR   pszProcName);

private:
   static PVOID       sm_pvMaxAppAddr;      // Maximum private memory address
   static ApiHook*    sm_pHead;             // Address of first object
   ApiHook*           m_pNext;              // Address of next  object

   PCSTR              m_pszCalleeModName;   // Module containing the function (ANSI)
   PCSTR              m_pszFuncName;        // Function name in callee (ANSI)
   PROC               m_pfnOrig;            // Original function address in callee
   PROC               m_pfnHook;            // Hook function address

private:
   // Replaces a symbol's address in a module's import section
   static void WINAPI ReplaceIATEntryInAllMods(PCSTR    pszCalleeModName, 
                                               PROC     pfnOrig,
                                               PROC     pfnHook);

   // Replaces a symbol's address in all modules' import sections
   static void WINAPI ReplaceIATEntryInOneMod( PCSTR    pszCalleeModName, 
                                               PROC     pfnOrig,
                                               PROC     pfnHook,
                                               HMODULE  hmodCaller);

   // Replaces a symbol's address in a module's export sections
   static void ReplaceEATEntryInOneMod       ( HMODULE  hmod,
                                               PCSTR    pszFunctionName,
                                               PROC     pfnNew);

private:
   // Used when a DLL is newly loaded after hooking a function
   static void WINAPI FixupNewlyLoadedModule(HMODULE hmod,
                                             DWORD   dwFlags);

   // Used to trap when DLLs are newly loaded
   static HMODULE WINAPI LoadLibraryA  (PCSTR  pszModulePath);

   static HMODULE WINAPI LoadLibraryW  (PCWSTR pszModulePath);

   static HMODULE WINAPI LoadLibraryExA(PCSTR  pszModulePath,
                                        HANDLE hFile,
                                        DWORD  dwFlags);

   static HMODULE WINAPI LoadLibraryExW(PCWSTR pszModulePath,
                                        HANDLE hFile,
                                        DWORD  dwFlags);

   // Returns address of replacement function if hooked function is requested
   static FARPROC WINAPI GetProcAddress(HMODULE hmod,
                                        PCSTR   pszProcName);

   typedef HMODULE (WINAPI *ProcLoadLibraryA)  (PCSTR  pszModulePath);

   typedef HMODULE (WINAPI *ProcLoadLibraryW)  (PCWSTR pszModulePath);

   typedef HMODULE (WINAPI *ProcLoadLibraryExA)(PCSTR  pszModulePath,
                                                HANDLE hFile,
                                                DWORD  dwFlags);

   typedef HMODULE (WINAPI *ProcLoadLibraryExW)(PCWSTR pszModulePath,
                                                HANDLE hFile,
                                                DWORD  dwFlags);

   typedef FARPROC (WINAPI *ProcGetProcAddress)(HMODULE hmod,
                                                PCSTR   pszProcName);

private:
   // Instantiates hooks on these functions
   static PROC      sm_ProcLoadLibraryA;
   static PROC      sm_ProcLoadLibraryW;
   static PROC      sm_ProcLoadLibraryExA;
   static PROC      sm_ProcLoadLibraryExW;
   static PROC      sm_ProcGetProcAddress;

   static ApiHook   sm_LoadLibraryA;
   static ApiHook   sm_LoadLibraryW;
   static ApiHook   sm_LoadLibraryExA;
   static ApiHook   sm_LoadLibraryExW;
   static ApiHook   sm_GetProcAddress;
};


} // namespace Logger

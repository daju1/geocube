#include "logger/CrashDumper.h"
#include "logger/ApiHook.h"
#include <dbghelp.h>
#include <shlwapi.h>
#include <tchar.h>
#include <strstream>



namespace Logger
{


typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE                            a_process_handle,
                                         DWORD                             a_process_id,
                                         HANDLE                            a_file_handle,
                                         MINIDUMP_TYPE                     a_dump_type,
                                         PMINIDUMP_EXCEPTION_INFORMATION   a_exception_param,
                                         PMINIDUMP_USER_STREAM_INFORMATION a_user_stream_param,
                                         PMINIDUMP_CALLBACK_INFORMATION    a_callback_param);



unsigned int CrashDumper::m_svn_revision           = 0;
bool         CrashDumper::m_is_local_modification  = false;
bool         CrashDumper::m_is_svn_supported       = false;
bool         CrashDumper::m_is_exit_enabled        = true;
PROC         CrashDumper::m_exit_process_proc      = 0;
PROC         CrashDumper::m_terminate_process_proc = 0;
MiniDumpType CrashDumper::m_dump_type              = MINI_DUMP_NORMAL;



CrashDumper::CrashDumper()
{
   set_exception_filters();
}



CrashDumper::CrashDumper(const MiniDumpType& a_dump_type)
{
   m_dump_type = a_dump_type;
   set_exception_filters();
}



CrashDumper::CrashDumper(const MiniDumpType& a_dump_type,
                         unsigned int        a_svn_revision,
                         bool                a_is_local_modification)
{
   m_dump_type             = a_dump_type;
   m_is_svn_supported      = true;
   m_svn_revision          = a_svn_revision;
   m_is_local_modification = a_is_local_modification;

   set_exception_filters();
}



CrashDumper::~CrashDumper()
{
   m_is_exit_enabled = true;
}



void CrashDumper::set_dump_type(const MiniDumpType& a_dump_type)
{
   m_dump_type = a_dump_type;
}



void CrashDumper::set_exception_filters()
{
   ::SetUnhandledExceptionFilter(top_level_filter);
   set_terminate (force_crash);
   set_unexpected(force_crash);

   static ApiHook unhandled_hook("Kernel32.dll", "SetUnhandledExceptionFilter", (PROC)set_unhandled_exception_hook);
   static ApiHook exit_hook     ("Kernel32.dll", "ExitProcess",                 (PROC)exit_process_hook,      &m_exit_process_proc);
   static ApiHook terminate_hook("Kernel32.dll", "TerminateProcess",            (PROC)terminate_process_hook, &m_terminate_process_proc);

   m_is_exit_enabled = false;
}



void CrashDumper::force_crash()
{
   m_is_exit_enabled = true;

   __try
   {
      raise_access_violation();
   }
   __except(top_level_filter(GetExceptionInformation()))
   {
   }

   ::TerminateProcess(::GetCurrentProcess(), 0);
}



void CrashDumper::force_terminate()
{
   ::TerminateProcess(::GetCurrentProcess(), TERMINATE_MAGIC_CODE);
}



void CrashDumper::raise_access_violation()
{
   int* addr = 0;
   *addr     = 0;
}



void WINAPI CrashDumper::exit_process_hook(UINT a_exit_code)
{
   if (!m_is_exit_enabled)
      force_crash();

   ProcExitProcess proc = (ProcExitProcess)m_exit_process_proc;

   return proc(a_exit_code);
}



BOOL WINAPI CrashDumper::terminate_process_hook(HANDLE a_process,
                                                UINT   a_exit_code)
{
   if (!m_is_exit_enabled)
   {
      if (::GetCurrentProcess() == a_process)
      {
         if (a_exit_code != TERMINATE_MAGIC_CODE)
            force_crash();
      }
   }

   ProcTerminateProcess proc = (ProcTerminateProcess)m_terminate_process_proc;

   return proc(a_process, a_exit_code);
}



LPTOP_LEVEL_EXCEPTION_FILTER WINAPI CrashDumper::set_unhandled_exception_hook(LPTOP_LEVEL_EXCEPTION_FILTER a_exception_filter)
{
   return a_exception_filter;
}



LONG WINAPI CrashDumper::top_level_filter(struct _EXCEPTION_POINTERS* a_exception_info)
{
   HMODULE dll = load_dbg_help_dll();

   if (!dll)
      return EXCEPTION_CONTINUE_SEARCH;

   MINIDUMPWRITEDUMP dump_proc = (MINIDUMPWRITEDUMP)::GetProcAddress(dll, "MiniDumpWriteDump");

   if (!dump_proc)
      return EXCEPTION_CONTINUE_SEARCH;

   HANDLE file = create_dump_file();

   if (INVALID_HANDLE_VALUE == file)
      return EXCEPTION_CONTINUE_SEARCH;

   _MINIDUMP_EXCEPTION_INFORMATION info;
   {
      info.ThreadId          = ::GetCurrentThreadId();
      info.ExceptionPointers = a_exception_info;
      info.ClientPointers    = NULL;
   }

   MINIDUMP_TYPE  dump_type = (MINI_DUMP_FULL == m_dump_type)
                            ? (MiniDumpWithFullMemory)
                            : (MiniDumpNormal);

   LONG rc = EXCEPTION_CONTINUE_SEARCH;

   if (dump_proc(::GetCurrentProcess(),
                 ::GetCurrentProcessId(),
                 file,
                 (MINIDUMP_TYPE)(   dump_type
                                  | MiniDumpWithFullMemoryInfo
                                  | MiniDumpWithHandleData
                                  | MiniDumpWithThreadInfo
                                  | MiniDumpWithUnloadedModules
                                  | MiniDumpWithProcessThreadData),
                  &info,
                  0,
                  0))
   {
      if (m_is_svn_supported)
      {
         std::strstream revision;
         revision << "\r\nSvn revision: " << m_svn_revision;

         if (m_is_local_modification)
            revision << ", with local modifications";
         else
            revision << ")";

         DWORD bytes_written = 0;
         ::SetFilePointer(file, 0, 0, FILE_END);
         ::WriteFile(file, revision.str(), (DWORD)revision.pcount(), &bytes_written, 0);
      }

      rc = EXCEPTION_EXECUTE_HANDLER;
   }

   ::FlushFileBuffers(file);
   ::CloseHandle     (file);

   m_is_exit_enabled = true;

   if (EXCEPTION_EXECUTE_HANDLER == rc)
      TerminateProcess(::GetCurrentProcess(), rc);

   return rc;
}



HMODULE CrashDumper::load_dbg_help_dll()
{
   HMODULE rc                     = 0;
   TCHAR   module_path[_MAX_PATH] = {};

   if (::GetModuleFileName(0, module_path, _MAX_PATH))
   {
      ::PathRemoveFileSpec(module_path);
      ::PathAddBackslash  (module_path);

      TCHAR dbg_help_path[_MAX_PATH] = {};
      {
         ::PathAppend(dbg_help_path, module_path);
         ::PathAppend(dbg_help_path, _T("DBGHELP.DLL"));

         rc = ::LoadLibrary(dbg_help_path);
      }

      if (!rc)
         rc = ::LoadLibrary(_T("DBGHELP.DLL"));
   }

   return rc;
}



HANDLE CrashDumper::create_dump_file()
{
   TCHAR module_path[_MAX_PATH] = {};

   if (!::GetModuleFileName(NULL, module_path, _MAX_PATH ))
      return INVALID_HANDLE_VALUE;

   ::PathRemoveFileSpec(module_path);
   ::PathAddBackslash  (module_path);

   SYSTEMTIME st = {};
   ::GetLocalTime(&st);

   ::PathAppend(module_path, _T("crash_dump"));

   if(!::PathFileExists(module_path))
      ::CreateDirectory(module_path, NULL);

   ::PathAddBackslash(module_path);

   TCHAR dump_path[_MAX_PATH] = {};
   _sntprintf(dump_path, (size_t)_MAX_PATH, (LPCTSTR)_T("%scrash_dump_%04u-%02u-%02u_%02u.%02u.%02u.dmp"),
              module_path, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

   return ::CreateFile(dump_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}


} // namespace Logger

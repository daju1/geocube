#ifndef __LOGGER_CRASH_DUMPER_H__
#define __LOGGER_CRASH_DUMPER_H__


#include <windows.h>
#include <boost/noncopyable.hpp>



namespace Logger
{


enum MiniDumpType
{
   MINI_DUMP_NORMAL,
   MINI_DUMP_FULL
};



class CrashDumper
   : private boost::noncopyable
{
public:
   CrashDumper();

   CrashDumper(const MiniDumpType& a_dump_type);

   CrashDumper(const MiniDumpType& a_dump_type,
               unsigned int        a_svn_revision,
               bool                a_is_local_modification);

   ~CrashDumper();

   void set_dump_type(const MiniDumpType& a_dump_type);

   static void force_crash();

   static void force_terminate();

private:
   enum
   {
      TERMINATE_MAGIC_CODE = 0xAA55AA55
   };

   /// ������ ����������
   static LONG WINAPI top_level_filter(struct _EXCEPTION_POINTERS* a_exception_info);

   /// ��������� ���������� DBGHELP.DLL
   static HMODULE load_dbg_help_dll();

   /// ������ ���� ��� ������ CrashDump
   static HANDLE  create_dump_file();

   /// ���������� ���������� Access Violation
   static void raise_access_violation();

   /// ������������� ������� ���������� �������� ������
   static void set_exception_filters();

   /// Hook ����� ��� ������� ExitProcess
   static void WINAPI exit_process_hook(UINT a_exit_code);

   /// Hook ����� ��� ������� TerminateProcess
   static BOOL WINAPI terminate_process_hook(HANDLE a_process,
                                             UINT   a_exit_code);

      /// Hook ����� ��� ������� SetUnhandledExceptionFilter
   static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI set_unhandled_exception_hook(LPTOP_LEVEL_EXCEPTION_FILTER a_exception_filter);

   /// ��� ��������� �� ������� ExitProcess
   typedef void (WINAPI *ProcExitProcess)(UINT a_exit_code);

   /// ��� ��������� �� ������� TerminateProcess
   typedef BOOL (WINAPI *ProcTerminateProcess)(HANDLE a_process,
                                               UINT   a_exit_code);

   /// ��� �����
   static MiniDumpType m_dump_type;

   /// SVN �������
   static unsigned int m_svn_revision;

   /// � ���������� �����������?
   static bool         m_is_local_modification;

   /// �������� �� ��������� SVN
   static bool         m_is_svn_supported;

   /// �������� �� ����� ExitProcess
   static bool         m_is_exit_enabled;

   /// ��������� �� ������������ ������� ExitProcess
   static PROC         m_exit_process_proc;

   /// ��������� �� ������������ ������� TerminateProcess
   static PROC         m_terminate_process_proc;
};


} // namespace Logger


#endif // __LOGGER_CRASH_DUMPER_H__

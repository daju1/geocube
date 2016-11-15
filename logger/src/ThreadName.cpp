#include "logger/ThreadName.h"
#include <windows.h>



namespace Logger
{


class ThreadTlsHolder
   : private boost::noncopyable
{
private:
   DWORD    m_index;

public:
   ThreadTlsHolder()
   {
      m_index = ::TlsAlloc();
   };

   ~ThreadTlsHolder()
   {
      if (m_index != TLS_OUT_OF_INDEXES)
         ::TlsFree(m_index);
   };

   DWORD get_index()
   {
      return m_index;
   }
};


/// Хранитель TLS индекса для класса ThreadName
ThreadTlsHolder   tls_holder;



ThreadName::ThreadName(const std::string& a_name)
{
   set_debuger_name(a_name);
   set_tls_name    (a_name);
}



ThreadName::~ThreadName()
{
}



void ThreadName::set_debuger_name(const std::string& a_name)
{
   const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)
   typedef struct tagTHREADNAME_INFO
   {
      DWORD  dwType;      // Must be 0x1000.
      LPCSTR szName;      // Pointer to name (in user addr space).
      DWORD  dwThreadID;  // Thread ID (-1 = caller thread).
      DWORD  dwFlags;     // Reserved for future use, must be zero.
   } THREADNAME_INFO;
#pragma pack(pop)

   THREADNAME_INFO info = {0x1000, a_name.c_str(), -1, 0};

   __try
   {
      ::RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
   }
   __except(EXCEPTION_EXECUTE_HANDLER)
   {
   }
}



void ThreadName::set_tls_name(const std::string& a_name)
{
   m_name = a_name;
   ::TlsSetValue(tls_holder.get_index(), (LPVOID)m_name.c_str());
}



std::string ThreadName::get_name()
{
   const char* name = (const char*)::TlsGetValue(tls_holder.get_index());
   return   (name && *name)
          ? boost::str(boost::format("%u-%s") % ::GetCurrentThreadId() % name)
          : boost::str(boost::format("%u") % ::GetCurrentThreadId());
}


} // namespace Logger

#include "logger/Journal.h"
#include "logger/ThreadName.h"
#include <windows.h>



namespace Logger
{

Journal* Journal::s_instance = NULL;


Journal::Journal()
   : m_log_level(LL_DEBUG)
{
}



Journal::~Journal()
{
}



Journal& Journal::instance()
{
#if 0
   static Journal journal;
   return journal;
#else

   if (NULL == s_instance) {
      s_instance = new Journal();
   }

   return *s_instance;
#endif
}



void Journal::register_dispatcher(DispatcherPtr a_dispatcher)
{
   Guard guard(m_dispatch_mutex);
   m_dispatchers.insert(a_dispatcher);
}



void Journal::unregister_dispatcher(DispatcherPtr a_dispatcher)
{
   Guard guard(m_dispatch_mutex);
   m_dispatchers.erase(a_dispatcher);
}



void Journal::thread_proc()
{
   ThreadName threadName("Logger");

   while(!m_is_terminate)
   {
      Lock lock(m_condition_mutex);
      m_condition.timed_wait(lock, boost::posix_time::time_duration(0 ,0 , FLUSH_TIMEOUT, 0));

      process_queue();
   }

   process_queue();
}



void Journal::process_queue()
{
   LogMessageQueue queue;
   swap_queue(queue);

   if (!queue.empty())
      dispatch(queue);
}



void Journal::swap_queue(LogMessageQueue& r_queue)
{
   Guard guard(m_queue_mutex);
   m_queue.swap(r_queue);
}



bool Journal::start()
{
   stop();
   m_is_terminate = false;
   m_thread.swap(boost::thread(boost::bind(&Journal::thread_proc, this)));
   return true;
}



void Journal::stop()
{
   m_is_terminate = true;
   m_condition.notify_one();
   m_thread.join();
}



void Journal::set_log_level(LogLevel a_log_level)
{
   Guard guard(m_queue_mutex);
   m_log_level = a_log_level;
}



LogLevel Journal::get_log_level() const
{
   Guard guard(m_queue_mutex);
   return m_log_level;
}



void Journal::message(const LogLevel&    a_log_level,
                      const std::string& a_source,
                      const std::string& a_info,
                      const std::string& a_thread_name)
{
   Guard guard(m_queue_mutex);

   if (m_is_terminate)
      return;

   if (a_log_level > m_log_level)
      return;

   LogMessagePtr message(new LogMessage(a_log_level, a_source, a_info, a_thread_name));

   m_queue.push_back(message);

    if (m_queue.size() > FLUSH_SIZE)
       m_condition.notify_one();
}



void Journal::debug_message(const std::string& a_source,
                            const std::string& a_info)
{
   message(LL_DEBUG, a_source, a_info, ThreadName::get_name());
}



void Journal::error_message(const std::string& a_source,
                            const std::string& a_info)
{
   message(LL_ERROR, a_source, a_info, ThreadName::get_name());
}



void Journal::info_message(const std::string& a_source,
                           const std::string& a_info)
{
   message(LL_INFO, a_source, a_info, ThreadName::get_name());
}



void Journal::warning_message(const std::string& a_source,
                              const std::string& a_info)
{
   message(LL_WARNING, a_source, a_info, ThreadName::get_name());
}



void Journal::dispatch(const LogMessageQueue& a_message_queue)
{
   Guard guard(m_dispatch_mutex);

   DispatcherSetIter it     = m_dispatchers.begin();
   DispatcherSetIter it_end = m_dispatchers.end();

   for(; it != it_end; ++it)
   {
      const DispatcherPtr& dispatcher = *it;
      dispatcher->dispatch(a_message_queue);
   }
}



void Journal::hex_dump(const LogLevel&    a_log_level,
                       const std::string& a_source,
                       const std::string& a_info,
                       const void*        a_data,
                       const size_t       a_data_size)
{
   hex_dump(a_log_level,
            a_source,
            a_info,
            ThreadName::get_name(),
            a_data,
            a_data_size);
}



void Journal::hex_dump(const LogLevel&    a_log_level,
                       const std::string& a_source,
                       const std::string& a_info,
                       const std::string& a_thread_name,
                       const void*        a_data,
                       const size_t       a_data_size)
{
   Guard guard(m_queue_mutex);

   message(a_log_level, a_source, a_info, a_thread_name);

   for(size_t i = 0; i < a_data_size; )
   {
      std::string s;
      std::string ss;

      for (int j = 0; j < 8; ++j)
      {
         if (i < a_data_size)
         {
            unsigned char c = ((unsigned char*)a_data)[i++];
            s .append(boost::str(boost::format("%02X ") % int(c)));
            ss.append(1, (c > 0x20) ? c : '.');
         }
         else
         {
            s  += "   ";
            ss += " ";
         }
      }

      message(a_log_level, a_source, s + " " + ss, a_thread_name);
   }
}



void Journal::last_error( const std::string& a_source )
{
   message(LL_DEBUG, a_source, get_error_text(GetLastError()), ThreadName::get_name());
}



std::string Journal::get_error_text(unsigned long a_error_code)
{
   std::string rc     = "";
   char*       buffer = 0;

   try
   {
      ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       ::GetModuleHandle(0),
                       a_error_code,
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPSTR)&buffer,
                       0,
                       0);

      if (buffer)
      {
         rc = std::string(buffer);
         ::LocalFree(buffer);
      }
   }
   catch (...)
   {
   }

   return rc;
}


} // namespace Logger

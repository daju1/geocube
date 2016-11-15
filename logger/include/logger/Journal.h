#ifndef __LOGGER_JOURNAL_H__
#define __LOGGER_JOURNAL_H__

#include <set>

#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>


#include "logger/Dispatcher.h"

namespace Logger
{


class Journal
   : private boost::noncopyable
{
public:
   static Journal& instance();

   bool start();
   void stop();

   void     set_log_level(LogLevel a_log_level);
   LogLevel get_log_level() const;

   void register_dispatcher  (DispatcherPtr a_dispatcher);
   void unregister_dispatcher(DispatcherPtr a_dispatcher);

   void debug_message  (const std::string& a_source,
                        const std::string& a_info);

   void error_message  (const std::string& a_source,
                        const std::string& a_info);

   void last_error     (const std::string& a_source);

   void info_message   (const std::string&  a_source,
                        const std::string&  a_info);

   void warning_message(const std::string& a_source,
                        const std::string& a_info);

   void message        (const LogLevel&    a_log_level,
                        const std::string& a_source,
                        const std::string& a_info,
                        const std::string& a_thread_name);

   void hex_dump       (const LogLevel&    a_log_level,
                        const std::string& a_source,
                        const std::string& a_info,
                        const std::string& a_thread_name,
                        const void*        a_data,
                        const size_t       a_data_size);

   void hex_dump       (const LogLevel&    a_log_level,
                        const std::string& a_source,
                        const std::string& a_info,
                        const void*        a_data,
                        const size_t       a_data_size);

private:
   Journal ();
   ~Journal();

   static Journal* s_instance;

   enum
   {
      FLUSH_TIMEOUT = 1,
      FLUSH_SIZE    = 10
   };

   typedef  std::set<DispatcherPtr>    DispatcherSet;
   typedef  DispatcherSet::iterator    DispatcherSetIter;

   typedef boost::recursive_mutex      RecursiveMutex;
   typedef boost::mutex                Mutex;
   typedef RecursiveMutex::scoped_lock Guard;

   typedef boost::unique_lock<Mutex>   Lock;
   typedef boost::condition_variable   Condition;
   typedef boost::thread               Thread;

   /// ������������������ ����������
   DispatcherSet   m_dispatchers;

   /// ������ ������� ���������
   mutable RecursiveMutex  m_queue_mutex;

   /// ������ �����������
   mutable RecursiveMutex  m_dispatch_mutex;

   /// ������ ��� Condition Variable
   mutable Mutex           m_condition_mutex;

   /// ������� ��� ���������
   LogMessageQueue m_queue;

   /// ������� �����������
   LogLevel        m_log_level;

   /// ����� ������
   Thread          m_thread;

   /// Condition Variable ������� ���������������
   Condition       m_condition;

   /// ���� ���������� ������
   volatile bool   m_is_terminate;

   /// ��������� �������
   void thread_proc();

   /// ������������ ������� ������� ���������
   void process_queue();

   /// ��������� swap ��� ������� ���������
   void swap_queue(LogMessageQueue& r_queue);

   /// ��������� �������� ������� ��������� �����������
   void dispatch(const LogMessageQueue& a_message_queue);

   /// �������������� ���� ������ � ��������� �������������
   static std::string get_error_text(unsigned long a_error_code);
};


} // namespace Logger


#endif // __LOGGER_JOURNAL_H__

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

   /// Зарегистрированные диспетчеры
   DispatcherSet   m_dispatchers;

   /// Защита очереди сообщений
   mutable RecursiveMutex  m_queue_mutex;

   /// Защита диспетчеров
   mutable RecursiveMutex  m_dispatch_mutex;

   /// Защита для Condition Variable
   mutable Mutex           m_condition_mutex;

   /// Очередь лог сообщений
   LogMessageQueue m_queue;

   /// Уровень логирования
   LogLevel        m_log_level;

   /// Поток логера
   Thread          m_thread;

   /// Condition Variable запуска диспетчеризации
   Condition       m_condition;

   /// Флаг завершения потока
   volatile bool   m_is_terminate;

   /// Потоковая функция
   void thread_proc();

   /// Обрабытывает текущую очередь сообщений
   void process_queue();

   /// Выполняет swap для очереди сообщений
   void swap_queue(LogMessageQueue& r_queue);

   /// Выполняет доставку очереди сообщений диспетчерам
   void dispatch(const LogMessageQueue& a_message_queue);

   /// Преобразование кода ошибки в текстовое представление
   static std::string get_error_text(unsigned long a_error_code);
};


} // namespace Logger


#endif // __LOGGER_JOURNAL_H__

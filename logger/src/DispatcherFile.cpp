#include "logger/DispatcherFile.h"
#include <boost/format.hpp>



namespace Logger
{


   DispatcherFile::DispatcherFile(const std::string& a_file_name)
      : m_file_name(a_file_name)
   {
   }



   DispatcherFile::~DispatcherFile()
   {
      flush();
   }



   void DispatcherFile::dispatch(const LogMessagePtr& a_message)
   {
      check_date(a_message);

      if (m_device)
      {
         char error_symbol[] = "E!i.";

         std::string info(boost::str(boost::format(
               "%02.2u:%02.2u:%02.2u.%06u|%c|%-25.25s|%-40.40s|%s\n")
               % a_message->time_stamp.hours()
               % a_message->time_stamp.minutes()
               % a_message->time_stamp.seconds()
               % a_message->time_stamp.microseconds()
               % error_symbol[a_message->log_level]
               % a_message->thread_name
               % a_message->source
               % a_message->info
               ));

         (*m_device) << info;
      }
   }



   void DispatcherFile::flush()
   {
      if (m_device)
         m_device->flush();
   }



   void DispatcherFile::check_date(const LogMessagePtr& a_message)
   {
      bool is_need_create = (!m_device) || (!check_time_stamp(a_message->time_stamp));

      if (is_need_create)
         switch_log_file();
   }



   bool DispatcherFile::check_time_stamp(const TimeStamp& a_time_stamp)
   {
      return (    a_time_stamp.day  () == m_time_stamp.day  ()
               && a_time_stamp.month() == m_time_stamp.month()
               && a_time_stamp.year () == m_time_stamp.year ());
   }



   void DispatcherFile::switch_log_file()
   {
      flush();

      m_time_stamp = TimeStamp();

      std::string file_name(boost::str(boost::format
            ("%s_%04d_%02d_%02d.log")
            % m_file_name
            % m_time_stamp.year ()
            % m_time_stamp.month()
            % m_time_stamp.day  ()
            ));

      m_device.reset(new LoggerDevice(file_name.c_str(), std::ios::out | std::ios::app));
   }

} // namespace Logger

#ifndef __LOGGER_LOG_MESSAGE_H__
#define __LOGGER_LOG_MESSAGE_H__

#include "logger/LogLevel.h"
#include "logger/TimeStamp.h"



namespace Logger
{

   struct LogMessage
   {
      TimeStamp    time_stamp;
      LogLevel     log_level;
      std::string  thread_name;
      std::string  source;
      std::string  info;

      LogMessage(const LogLevel&    a_log_level,
                 const std::string& a_source,
                 const std::string& a_info,
                 const std::string& a_thread_name);
   };


   typedef boost::shared_ptr<LogMessage> LogMessagePtr;


} // namespace Logger


#endif // __LOGGER_LOG_MESSAGE_H__

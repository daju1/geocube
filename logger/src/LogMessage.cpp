#include "logger/LogMessage.h"
#include <windows.h>



namespace Logger
{

   LogMessage::LogMessage(const LogLevel&    a_log_level,
                          const std::string& a_source,
                          const std::string& a_info,
                          const std::string& a_thread_name)
      : log_level  (a_log_level)
      , source     (a_source)
      , info       (a_info)
      , thread_name(a_thread_name)
   {
   }

} // namespace Logger

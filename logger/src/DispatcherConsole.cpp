#include "logger/DispatcherConsole.h"
#include "logger/LogMessageQueue.h"
#include <boost/format.hpp>
#include <iostream>
#include <windows.h>



namespace Logger
{


struct color
{
   color(unsigned int attribute) : m_color(attribute) {};
   unsigned int m_color;
};



template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>& operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c)
{
   HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
   ::SetConsoleTextAttribute(handle, c.m_color);
   return i;
}



DispatcherConsole::DispatcherConsole()
{
   ::SetConsoleCP(1251);
   ::SetConsoleOutputCP(1251);
}



DispatcherConsole::~DispatcherConsole()
{
}



void DispatcherConsole::dispatch(const LogMessagePtr& a_message)
{
   char error_symbol[] = "E!i.";

   std::string info(boost::str(boost::format
         ("%02.2u:%02.2u:%02.2u.%06u|%c|%-25.25s|%-40.40s|%s\n")
         % a_message->time_stamp.hours()
         % a_message->time_stamp.minutes()
         % a_message->time_stamp.seconds()
         % a_message->time_stamp.microseconds()
         % error_symbol[a_message->log_level]
         % a_message->thread_name
         % a_message->source
         % a_message->info
         ));

   static int record_number = 0;

   unsigned int cl = (record_number++ % 2)
                   ? (FOREGROUND_GREEN | FOREGROUND_RED)
                   : (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

   switch (a_message->log_level)
   {
   case LL_ERROR:
      cl = FOREGROUND_RED | FOREGROUND_INTENSITY;
      break;

   case LL_WARNING:
      cl = FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_INTENSITY;
      break;

   case LL_INFO:
      cl = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;

   case LL_DEBUG:
      // NOOP
      break;

   default:
      _ASSERT(0);
   }

   std::cout << color(cl) << info;
}



void DispatcherConsole::flush()
{
   // NOOP
}


} // namespace Logger

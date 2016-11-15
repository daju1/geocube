#ifndef __LOGGER_DISPATCHER_CONSOLE_H__
#define __LOGGER_DISPATCHER_CONSOLE_H__

#include "logger/Dispatcher.h"



namespace Logger
{


class DispatcherConsole
   : public Dispatcher
{
public:
   DispatcherConsole();
   virtual ~DispatcherConsole();

protected:
   virtual void dispatch(const LogMessagePtr& a_message);
   virtual void flush();
};


} // namespace Logger


#endif // __LOGGER_DISPATCHER_CONSOLE_H__

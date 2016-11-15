#ifndef __LOGGER_DISPATCHER_H__
#define __LOGGER_DISPATCHER_H__

#include "logger/LogMessageQueue.h"
#include <boost/noncopyable.hpp>



namespace Logger
{


class Dispatcher
   : private boost::noncopyable
{
public:
   Dispatcher();
   virtual ~Dispatcher();

   void dispatch(const LogMessageQueue& a_message_queue);

protected:
   virtual void dispatch(const LogMessagePtr& a_message) = 0;
   virtual void flush() = 0;
};


typedef boost::shared_ptr<Dispatcher>  DispatcherPtr;


} // namespace Logger


#endif // __LOGGER_DISPATCHER_H__

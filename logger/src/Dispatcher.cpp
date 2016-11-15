#include "logger/Dispatcher.h"



namespace Logger
{


Dispatcher::Dispatcher()
{
}



Dispatcher::~Dispatcher()
{
}



void Dispatcher::dispatch(const LogMessageQueue& a_message_queue)
{
   LogMessageQueue::const_iterator it     = a_message_queue.begin();
   LogMessageQueue::const_iterator it_end = a_message_queue.end();

   for(; it != it_end; ++it)
   {
      const LogMessagePtr& message = *it;
      dispatch(message);
   }

   flush();
}


} // namespace Logger

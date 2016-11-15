#ifndef __LOGGER_LOG_MESSAGE_QUEUE_H__
#define __LOGGER_LOG_MESSAGE_QUEUE_H__

#include "logger/LogMessage.h"
#include <deque>



namespace Logger
{

   typedef std::deque<LogMessagePtr> LogMessageQueue;

} // namespace Logger


#endif // __LOGGER_LOG_MESSAGE_QUEUE_H__

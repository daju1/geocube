#ifndef __LOGGER_MACRO_H__
#define __LOGGER_MACRO_H__

#include "logger/Journal.h"
#include <boost/format.hpp>


#define DBG(args)  Logger::Journal::instance().debug_message  (__FUNCTION__, args )
#define ERR(args)  Logger::Journal::instance().error_message  (__FUNCTION__, args )
#define WARN(args) Logger::Journal::instance().warning_message(__FUNCTION__, args )
#define INFO(args) Logger::Journal::instance().info_message   (__FUNCTION__, args )
#define LAST()     Logger::Journal::instance().last_error     (__FUNCTION__)

#define DBGFMT(args, vals)  Logger::Journal::instance().debug_message  (__FUNCTION__, boost::str(boost::format(args) vals))
#define ERRFMT(args, vals)  Logger::Journal::instance().error_message  (__FUNCTION__, boost::str(boost::format(args) vals))
#define INFOFMT(args, vals) Logger::Journal::instance().info_message   (__FUNCTION__, boost::str(boost::format(args) vals))
#define WARNFMT(args, vals) Logger::Journal::instance().warning_message(__FUNCTION__, boost::str(boost::format(args) vals))
#define HEXDUMP(args, buffer, buffersize)           Logger::Journal::instance().hex_dump(Logger::LL_DEBUG, __FUNCTION__ , args, buffer, buffersize)
#define HEXDUMP_EX(level, args, buffer, buffersize) Logger::Journal::instance().hex_dump(level,            __FUNCTION__ , args, buffer, buffersize)

#endif // __LOGGER_MACRO_H__

#ifndef __LOGGER_THREAD_NAME_H__
#define __LOGGER_THREAD_NAME_H__

#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
#include <string>


namespace Logger
{


class ThreadName
   : private boost::noncopyable
{
public:
   ThreadName (const std::string& a_name);
   ~ThreadName();

   static std::string get_name();

private:
   /// Устанавливает имя потока на уровне TLS
   void set_tls_name           (const std::string& a_name);

   /// Устанавливает имя потока на уровне отладчика
   static void set_debuger_name(const std::string& a_name);

   /// Имя потока
   std::string    m_name;
};


} // namespace Logger


#endif // __LOGGER_THREAD_NAME_H__

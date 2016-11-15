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
   /// ������������� ��� ������ �� ������ TLS
   void set_tls_name           (const std::string& a_name);

   /// ������������� ��� ������ �� ������ ���������
   static void set_debuger_name(const std::string& a_name);

   /// ��� ������
   std::string    m_name;
};


} // namespace Logger


#endif // __LOGGER_THREAD_NAME_H__

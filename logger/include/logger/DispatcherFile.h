#ifndef __LOGGER_DISPATCHER_FILE_H__
#define __LOGGER_DISPATCHER_FILE_H__

#include "logger/Dispatcher.h"
#include <boost/filesystem/fstream.hpp>



namespace Logger
{


class DispatcherFile
   : public Dispatcher
{
public:
   DispatcherFile(const std::string& a_file_name);
   virtual ~DispatcherFile();

protected:
   virtual void dispatch(const LogMessagePtr& a_message);
   virtual void flush();

private:
   typedef std::ofstream                   LoggerDevice;
   typedef boost::shared_ptr<LoggerDevice> LoggerDevicePtr;

   void check_date      (const LogMessagePtr& a_message);

   bool check_time_stamp(const TimeStamp&     a_time_stamp);

   void switch_log_file();

   /// ���� ��� ������ ����
   LoggerDevicePtr   m_device;

   /// ��������� ����� ������ ������ � �����
   TimeStamp         m_time_stamp;

   /// ��� ��� �����
   std::string       m_file_name;
};


} // namespace Logger


#endif // __LOGGER_DISPATCHER_FILE_H__

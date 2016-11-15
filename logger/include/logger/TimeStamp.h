#ifndef __LOGGER_TIME_STAMP_H__
#define __LOGGER_TIME_STAMP_H__

#include <boost/date_time/posix_time/posix_time_types.hpp>


namespace Logger
{


   class TimeStamp
   {
   public:
      TimeStamp ();
      ~TimeStamp();

      /// ���
      unsigned int year() const;

      /// �����
      unsigned int month() const;

      /// ����
      unsigned int day() const;

      /// ����
      unsigned int hours() const;

      /// ������
      unsigned int minutes() const;

      /// �������
      unsigned int seconds() const;

      /// ������������
      unsigned int microseconds() const;

      /// ���������� ������� � �������������
      long long difference_milliseconds(const TimeStamp& a_other);

   private:
      boost::posix_time::ptime   m_time;
   };

} // namespace Logger


#endif // __LOGGER_TIME_STAMP_H__

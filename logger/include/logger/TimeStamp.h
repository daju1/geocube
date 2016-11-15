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

      /// год
      unsigned int year() const;

      /// месяц
      unsigned int month() const;

      /// день
      unsigned int day() const;

      /// часы
      unsigned int hours() const;

      /// минуты
      unsigned int minutes() const;

      /// секунды
      unsigned int seconds() const;

      /// миллисекунды
      unsigned int microseconds() const;

      /// Возвращает разницу в миллисекундах
      long long difference_milliseconds(const TimeStamp& a_other);

   private:
      boost::posix_time::ptime   m_time;
   };

} // namespace Logger


#endif // __LOGGER_TIME_STAMP_H__

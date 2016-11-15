#include "logger/TimeStamp.h"



namespace Logger
{


TimeStamp::TimeStamp()
   : m_time(boost::posix_time::microsec_clock::local_time())
{
}



TimeStamp::~TimeStamp()
{
}



unsigned int TimeStamp::year() const
{
   boost::gregorian::date::ymd_type ymd = m_time.date().year_month_day();
   return ymd.year;
}



unsigned int TimeStamp::month() const
{
   boost::gregorian::date::ymd_type ymd = m_time.date().year_month_day();
   return ymd.month;
}



unsigned int TimeStamp::day() const
{
   boost::gregorian::date::ymd_type ymd = m_time.date().year_month_day();
   return ymd.day;
}



unsigned int TimeStamp::hours() const
{
   boost::posix_time::time_duration td = m_time.time_of_day();
   return td.hours();
}



unsigned int TimeStamp::minutes() const
{
   boost::posix_time::time_duration td = m_time.time_of_day();
   return td.minutes();
}



unsigned int TimeStamp::seconds() const
{
   boost::posix_time::time_duration td = m_time.time_of_day();
   return td.seconds();
}



unsigned int TimeStamp::microseconds() const
{
   boost::posix_time::time_duration td = m_time.time_of_day();
   return (unsigned int)td.fractional_seconds();
}



long long TimeStamp::difference_milliseconds(const TimeStamp& a_other)
{
   boost::posix_time::time_duration td = m_time - a_other.m_time;
   long long rc = td.total_milliseconds();

   return (rc < 0) ? -rc : rc;
}


} // namespace Logger

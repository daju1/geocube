#pragma once

#include <boost/filesystem.hpp>

namespace sys
{

class LogManager
{
public:

   static LogManager& instance();

   boost::filesystem::path get_root_directory  () const;

   boost::filesystem::path get_log_directory   () const;
   boost::filesystem::path get_log_file_name   () const;


private:

   LogManager(void);
   ~LogManager(void);

   void init();

   boost::filesystem::path m_root_directory;
   boost::filesystem::path m_log_directory;
   boost::filesystem::path m_log_file_name;
};

} // namespace sys
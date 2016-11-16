#include "stdafx.h"
#include <windows.h>
#include "SysLogManager.h"

namespace sys
{

   namespace data
   {
      const std::string LOG_DIRECTORY           = "log";
      const std::string LOG_FILE_NAME           = "geo_cube_log";
   }


LogManager::LogManager( void )
   : m_root_directory         ( "")
   , m_log_directory          ( "")
   , m_log_file_name          ( "")
{
   init();
}



LogManager::~LogManager( void )
{}



LogManager& LogManager::instance()
{
   static LogManager inst;
   return inst;
}



void LogManager::init()
{
   const size_t FILE_NAME_SIZE = 1024;

   std::wstring module_name( L"");
   module_name.resize( FILE_NAME_SIZE);

   GetModuleFileNameW( NULL, &module_name[0], FILE_NAME_SIZE);

   _ASSERT(GetLastError() != ERROR_INSUFFICIENT_BUFFER);

   using namespace boost::filesystem;

   m_root_directory = path( module_name).remove_filename();

   // Log
   {
      m_log_directory = m_root_directory / data::LOG_DIRECTORY;
      if ( !exists( m_log_directory))
         create_directory( m_log_directory);

      m_log_file_name = m_log_directory / data::LOG_FILE_NAME;
   }

}



boost::filesystem::path LogManager::get_root_directory() const
{
   return m_root_directory;
}



boost::filesystem::path LogManager::get_log_directory() const
{
   return m_log_directory;
}



boost::filesystem::path LogManager::get_log_file_name() const
{
   return m_log_file_name;
}



} // namespace sys
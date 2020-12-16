// #38 一時ログファイル
#include <iostream>
#include <fstream>

// uuid.h:134:13: error: memcpy was not declared in this scope
// 著者ライブラリーの不具合をここで解消する
#include <cstring>
// apt install uuid-dev
#include "uuid.h"

#ifdef USE_BOOST_FILESYSTEM
#  include <boost/filesystem/path.hpp>
#  include <boost/filesystem/operations.hpp>
   namespace fs = boost::filesystem;
#else
#  include <filesystem>
#  ifdef FILESYSTEM_EXPERIMENTAL
   namespace fs = std::experimental::filesystem;
#  else
   namespace fs = std::filesystem;
#  endif
#endif

class logger
{
   fs::path       logpath;
   std::ofstream  logfile;
public:
   logger()
   {
      auto name = uuids::to_string(uuids::uuid_random_generator{}());
      logpath = fs::temp_directory_path() / (name + ".tmp");
      logfile.open(logpath.c_str(), std::ios::out|std::ios::trunc);
   }

   ~logger() noexcept
   {
      try {
         if(logfile.is_open())
            logfile.close();
         if (!logpath.empty())
            fs::remove(logpath);
      }
      catch (...) {
      }
   }

   void persist(fs::path const & path)
   {
      logfile.close();
      fs::rename(logpath, path);
      logpath.clear();
   }

   logger& operator<<(std::string_view message)
   {
      logfile << message.data() << '\n';
      return *this;
   }
};

int main()
{
   logger log;
   try
   {
      log << "this is a line" << "and this is another one";

      throw std::runtime_error("error");
   }
   catch (...)
   {
      log.persist(R"(lastlog.txt)");
   }
}

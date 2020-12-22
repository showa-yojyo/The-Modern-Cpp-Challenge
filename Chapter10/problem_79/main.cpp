// #79 Zip アーカイブにあるファイルを探し出す
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <regex>

// 今回は ZipLib を採用
#include "ZipFile.h"
#include "ZipArchive.h"

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

std::vector<std::string> find_in_archive(
   fs::path const & archivepath,
   std::string_view pattern)
{
   std::vector<std::string> results;

   if (fs::exists(archivepath)) // このテストは本質的には不要
   {
      try
      {
         // Zip ファイルを「開く」
         auto archive = ZipFile::Open(archivepath.string());

         // ZipLib のインターフェイスがダサい
         for (size_t i = 0; i < archive->GetEntriesCount(); ++i)
         {
            if (auto entry = archive->GetEntry(i); !entry->IsDirectory())
            {
               auto name = entry->GetName();
               if (std::regex_match(name, std::regex{ pattern.data() }))
               {
                  results.push_back(entry->GetFullName());
               }
            }
         }
      }
      catch (std::exception const & ex) // ここをまともに書き直す
      {
         std::cout << ex.what() << std::endl;
      }
   }

   return results;
}

int main()
{
   std::string archivepath;
   std::cout << "Archive path:";
   std::cin >> archivepath;

   std::string pattern;
   std::cout << "Pattern:";
   std::cin >> pattern;

   std::cout << "Results:" << std::endl;

   for (auto const & name : find_in_archive(archivepath, pattern))
   {
      std::cout << name << std::endl;
   }
}

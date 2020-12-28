// #35 ディレクトリのサイズを計算する
#include <iostream>
#include <numeric>
#include <string>

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

std::uintmax_t get_directory_size(

   fs::path const & dir,
   bool follow_symlinks = false)
{
#ifdef USE_BOOST_FILESYSTEM
   auto iterator = fs::recursive_directory_iterator(
      dir,
      follow_symlinks ? fs::symlink_option::recurse : fs::symlink_option::none);
#else
   // ディレクトリーのすべてのファイルを再帰的に反復する
   auto iterator = fs::recursive_directory_iterator(
      dir,
      follow_symlinks ? fs::directory_options::follow_directory_symlink : fs::directory_options::none);
#endif

   // std::accumulate() にラムダ式で演算を与える。
   // いつものように uintmax_t などを採用することに注意。
   return std::accumulate(
      fs::cbegin(iterator), fs::cend(iterator),
      0ull,
      [](std::uintmax_t const total,
         fs::directory_entry const & entry) {
      return total + (fs::is_regular_file(entry) ?
         fs::file_size(entry.path()) : 0);
   });
}

int main()
{
   std::string path;
   std::cout << "Path: ";
   std::cin >> path;
   // バイト単位で出力するのでわかりづらければ改良するといい。
   std::cout << "Size: " << get_directory_size(path) << std::endl;
}

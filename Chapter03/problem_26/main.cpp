// #26 指定した区切り文字で文字列を連結する
#include <string>
#include <iterator>
#include <sstream>
#include <vector>
#include <array>
#include <list>
#include <cassert>

// シーケンスの範囲を引数に取る版
template <typename Iter>
std::string join_strings(Iter begin, Iter end, char const * const separator)
{
   std::ostringstream os;
   // この end - 1 は怖くないか？
   std::copy(begin, end-1, std::ostream_iterator<std::string>(os, separator));
   os << *(end-1);
   return os.str();
}

// シーケンスコンテナーを引数に取る版
template <typename C>
std::string join_strings(C const & c, char const * const separator)
{
   if (c.empty()) return std::string{};
   return join_strings(std::begin(c), std::end(c), separator);
}

int main()
{
   // 前項参照
   using namespace std::string_literals;

   std::vector<std::string> v1{ "this","is","an","example" };
   std::vector<std::string> v2{ "example" };
   std::vector<std::string> v3{ };

   assert(
      join_strings(v1, " ") == "this is an example"s);

   assert(
      join_strings(v2, " ") == "example"s);

   assert(
      join_strings(v3, " ") == ""s);

   std::array<std::string, 4> a1{ {"this","is","an","example"} };
   std::array<std::string, 1> a2{ {"example"} };
   std::array<std::string, 0> a3{};

   assert(
      join_strings(a1, " ") == "this is an example"s);

   assert(
      join_strings(a2, " ") == "example"s);

   assert(
      join_strings(a3, " ") == ""s);
}

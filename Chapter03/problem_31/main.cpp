// #31 文字列の日付を変換する
#include <string>
#include <string_view>
#include <regex>
#include <cassert>

std::string transform_date(std::string_view text)
{
   // キャプチャーグループに名前をつけたい
   std::regex rx{ R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))" };
   return std::regex_replace(text.data(), rx, R"($5-$3-$1)");
}

int main()
{
   using namespace std::string_literals;

   assert(
      transform_date("today is 01.12.2017!"s) ==
      "today is 2017-12-01!"s);
}

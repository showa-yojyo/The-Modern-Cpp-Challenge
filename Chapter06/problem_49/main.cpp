// #49 テキストヒストグラム
#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>
#include <string_view>

std::map<char, double> analyze_text(std::string_view text)
{
   // Python の collections.Counter のように取り扱う
   std::map<char, double> frequencies;
   for (char ch = 'a'; ch <= 'z'; ch++)
      frequencies[ch] = 0;

   // range-based for loop
   for (auto ch : text)
   {
      if (isalpha(ch))
         frequencies[tolower(ch)]++;
   }

   // accumulate() の func がラムダ式。引数リストに auto が使われている
   auto total = std::accumulate(
      std::cbegin(frequencies), std::cend(frequencies),
      0ull,
      [](auto const sum, auto const & kvp) {
         // 例によって long long を採用する
         return sum + static_cast<unsigned long long>(kvp.second);
   });

   std::for_each(
      std::begin(frequencies), std::end(frequencies),
      [total](auto & kvp) {
      kvp.second = (100.0 * kvp.second) / total;
   });

   return frequencies;
}

int main()
{
   // 生文字列
   auto result = analyze_text(R"(Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.)");

   // range-based for loop
   for (auto const & kvp : result)
   {
      // ヒストグラムを Ascii アートで表現するわけではない。
      // 浮動小数点数を絵にするのは至難だ……。
      std::cout
         << kvp.first << " : "
         << std::fixed
         << std::setw(5) << std::setfill(' ')
         << std::setprecision(2) << kvp.second << std::endl;
   }
}

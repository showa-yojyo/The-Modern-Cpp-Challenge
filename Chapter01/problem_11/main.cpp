// #11 ローマ数字に変換
// よくあるローマ数字変換の演習問題
#include <iostream>
#include <string>
#include <vector>

std::string to_roman(unsigned int value)
{
   // .second は std::string でいいと思う
   std::vector<std::pair<decltype(value), char const*>> roman
   {
      { 1000, "M" },{ 900, "CM" },
      { 500, "D" },{ 400, "CD" },
      { 100, "C" },{ 90, "XC" },
      { 50, "L" },{ 40, "XL" },
      { 10, "X" },{ 9, "IX" },
      { 5, "V" },{ 4, "IV" },
      { 1, "I" }
   };

   // 範囲 for ループの書き方の例になる
   std::string result;
   for (auto const & kvp : roman)
   {
      while (value >= kvp.first)
      {
         result += kvp.second;
         value -= kvp.first;
      }
   }

   return result;
}

int main()
{
   for(auto i = 1; i <= 100; ++i)
   {
      std::cout << i << "\t" << to_roman(i) << std::endl;
   }

   int number = 0;
   std::cout << "number:";
   std::cin >> number;

   std::cout << to_roman(number) << std::endl;
}

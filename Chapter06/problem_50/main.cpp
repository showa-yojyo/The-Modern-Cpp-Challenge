// #50 電話番号のリストをフィルタリング
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>

bool starts_with(std::string_view str, std::string_view prefix) noexcept
{
   return str.find(prefix) == 0;
}

// 区間版
template <typename InputIt>
std::vector<std::string> filter_numbers(
    InputIt begin, InputIt end,
    std::string const &countryCode)
{
   std::vector<std::string> result;

   // copy_if() の func がラムダ式。
   // キャプチャーリストに注意。
   std::copy_if(
       begin, end,
       std::back_inserter(result),
       [countryCode](auto const &number) {
          // 正規表現で書き換えてみよう
          return starts_with(number, countryCode) ||
                  starts_with(number, "+" + countryCode);
       });

   return result;
}

// コンテナ版
std::vector<std::string> filter_numbers(
    std::vector<std::string> const &numbers,
    std::string const &countryCode)
{
   return filter_numbers(
       std::cbegin(numbers), std::cend(numbers),
       countryCode);
}

int main()
{
   std::vector<std::string> numbers{
       "+40744909080",
       "44 7520 112233",
       "+44 7555 123456",
       "40 7200 123456",
       "7555 123456"};

   auto result = filter_numbers(numbers, "44");

   // range-based for loop
   for (auto const &number : result)
   {
      std::cout << number << std::endl;
   }
}

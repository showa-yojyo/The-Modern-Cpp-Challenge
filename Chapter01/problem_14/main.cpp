#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <cassert>

bool validate_isbn_10(std::string_view isbn)
{
   auto valid = false;

   // 10 文字がすべて数字かどうかをテスト
   if (isbn.size() == 10 &&
       std::count_if(std::begin(isbn), std::end(isbn), isdigit) == 10)
   {
      auto w = 10;
      // std::accumulate() に演算を指定する例になっている。
      // キャプチャーリストに注意。
      auto sum = std::accumulate(
         std::begin(isbn), std::end(isbn), 0,
         [&w](int const total, char const c) {
            return total + w-- * (c - '0'); });

      valid = !(sum % 11);
   }

   return valid;
}

int main()
{
   assert(validate_isbn_10("0306406152"));
   assert(!validate_isbn_10("0306406151"));

   std::string isbn;
   std::cout << "isbn:";
   std::cin >> isbn;

   std::cout << "valid: " << validate_isbn_10(isbn) << std::endl;
}

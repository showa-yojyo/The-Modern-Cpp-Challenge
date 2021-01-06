// #6 過剰数
// 真の約数の総和が元の数よりも大きいような数の意。
#include <iostream>
#include <cmath>

constexpr int sum_proper_divisors(int number) noexcept
{
   int result = 1;
   // これは書籍版のコードのほうがいいので書き換える。
   auto root = static_cast<int>(std::sqrt(number));
   for (auto i = 2; i <= root; i++)
   {
      if (number%i == 0)
      {
         result += (i == (number / i)) ? i : (i + number / i);
      }
   }

   return result;
}

void print_abundant(int limit)
{
   for (auto number = 10; number <= limit; ++number)
   {
      // いちばん基本的な auto の用例
      auto sum = sum_proper_divisors(number);
      if (sum > number)
      {
         std::cout
            << number
            << ", abundance=" << sum - number << std::endl;
      }
   }
}

int main()
{
   int limit = 0;
   std::cout << "Upper limit:";
   std::cin >> limit;

   print_abundant(limit);
}

// #7 友愛数
// 一方の数の真の約数の和がもう一方の数と等しくなり、
// 他方の数の真の約数の和がもう一方の数と等しくなる二つの数の対。
#include <iostream>
#include <set>
#include <cmath>

// 前項と同じものになる
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

void print_amicables(int limit)
{
   for (decltype(limit) number = 4; number < limit; ++number)
   {
      if (auto sum1 = sum_proper_divisors(number); sum1 < limit)
      {
         if (auto sum2 = sum_proper_divisors(sum1);
             sum2 == number && number != sum1)
         {
            std::cout << number << "," << sum1 << std::endl;
         }
      }
   }
}

// こちらは練習問題の解答例だろう
void print_amicables_once(int limit)
{
   std::set<int> printed;
   for (decltype(limit) number = 4; number < limit; ++number)
   {
      if (printed.find(number) != printed.end()) continue;

      if (auto sum1 = sum_proper_divisors(number); sum1 < limit)
      {
         if (auto sum2 = sum_proper_divisors(sum1);
             sum2 == number && number != sum1)
         {
            printed.insert(number);
            printed.insert(sum1);

            std::cout << number << "," << sum1 << std::endl;
         }
      }
   }
}

int main()
{
   print_amicables(1000000);
   print_amicables_once(1000000);
}

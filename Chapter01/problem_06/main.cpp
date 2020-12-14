#include <iostream>
#include <cmath>

int sum_proper_divisors(int const number)
{
   int result = 1;
   // これは書籍版のコードのほうがいいので書き換える。
   //for (int i = 2; i <= std::sqrt(number); i++)
   int root = static_cast<int>(std::sqrt(number));
   for (int i = 2; i <= root; i++)
   {
      if (number%i == 0)
      {
         result += (i == (number / i)) ? i : (i + number / i);
      }
   }

   return result;
}

void print_abundant(int const limit)
{
   for (int number = 10; number <= limit; ++number)
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

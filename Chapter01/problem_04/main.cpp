// #4 与えられた正の整数より小さい最大の素数
#include <iostream>

constexpr bool is_prime(int const num) noexcept
{
   if (num <= 3)
   {
      return num > 1;
   }
   else if (num % 2 == 0 || num % 3 == 0)
   {
      return false;
   }
   else
   {
      for (int i = 5; i * i <= num; i += 6)
      {
         if (num % i == 0 || num % (i + 2) == 0)
         {
            return false;
         }
      }

      return true;
   }
}

int main()
{
   int limit = 0;
   std::cout << "Upper limit:";
   std::cin >> limit;

   for (auto i = limit; i > 1; i--)
   {
      if (is_prime(i))
      {
         std::cout << "Largest prime:" << i << std::endl;
         return 0;
      }
   }
}

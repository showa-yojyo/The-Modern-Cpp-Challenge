// #12 最長コラッツ数列
#include <iostream>
#include <vector>

// いつものように long long に注意
auto longest_collatz_uncached(unsigned long long limit) -> std::pair<decltype(limit), long>
{
   long length = 0;
   decltype(limit) number = 0;

   for (decltype(limit) i = 2; i <= limit; i++)
   {
      auto n = i;
      long steps = 0;
      while (n != 1)
      {
         if ((n % 2) == 0)
            n = n / 2;
         else
            n = n * 3 + 1;
         steps++;
      }

      if (steps > length)
      {
         length = steps;
         number = i;
      }
   }

   return std::make_pair(number, length);
}

auto longest_collatz(unsigned long long limit) -> std::pair<decltype(limit), long>
{
   long length = 0;
   decltype(limit) number = 0;

   std::vector<int> cache(limit + 1, 0);

   for (decltype(limit) i = 2; i <= limit; i++)
   {
      auto n = i;
      long steps = 0;
      while (n != 1 && n >= i)
      {
         if ((n % 2) == 0)
            n = n / 2;
         else
            n = n * 3 + 1;
         steps++;
      }
      cache[i] = steps + cache[n];

      if (cache[i] > length)
      {
         length = cache[i];
         number = i;
      }
   }

   return std::make_pair(number, length);
}

int main()
{
   struct test_data
   {
      unsigned long long limit;
      unsigned long long start;
      long steps;
   };

   // unsigned long long の suffix は珍しい
   std::vector<test_data> data
   {
      { 10ULL, 9ULL, 19 },
      { 100ULL, 97ULL, 118 },
      { 1000ULL, 871ULL, 178 },
      { 10000ULL, 6171ULL, 263 },
      { 100000ULL, 77031ULL, 350 },
      { 1000000ULL, 837799ULL, 524 },
      { 10000000ULL, 8400511ULL, 685 },
      { 100000000ULL, 63728127ULL, 949 }
   };

   // 範囲 for 文
   for (auto const & d : data)
   {
      auto result = longest_collatz(d.limit);

      if (result.first != d.start || result.second != d.steps)
         std::cout << "error on limit " << d.limit << std::endl;
      else
         std::cout
            << "less than      : " << d.limit << std::endl
            << "starting number: " << result.first << std::endl
            << "sequence length: " << result.second << std::endl;
   }
}

// #9 素因数分解
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <algorithm>

// 素因数分解のロジックは他でもよく見られるものだろう。
// 例によって long long に注意。
auto prime_factors(unsigned long long n) -> std::vector<decltype(n)>
{
   std::vector<decltype(n)> factors;
   // print the number of 2s that divide n
   while (n % 2 == 0)
   {
      factors.push_back(2);
      n = n / 2;
   }

   // 本書のように、この sqrt はループの外に出すのが普通だ。
   auto root = static_cast<decltype(n)>(std::sqrt(n));
   for (decltype(n) i = 3; i <= root; i += 2)
   {
      // while i divides n, print i and divide n
      while (n%i == 0)
      {
         factors.push_back(i);
         n = n / i;
      }
   }

   // n is a prime number greater than 2
   if (n > 2)
      factors.push_back(n);

   // 現代的な C++ では std::vector をそのまま戻して大丈夫
   return factors;
}

int main()
{
   unsigned long long number = 0;
   std::cout << "number:";
   std::cin >> number;

   auto factors = prime_factors(number);

   std::copy(
      std::cbegin(factors), std::cend(factors),
      std::ostream_iterator<unsigned long long>(std::cout, " "));
}

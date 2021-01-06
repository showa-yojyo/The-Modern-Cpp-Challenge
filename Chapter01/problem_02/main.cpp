// #2 最大公約数
#include <iostream>
#include <numeric>

constexpr unsigned int gcd(unsigned int a, unsigned int b) noexcept
{
   return b == 0 ? a : gcd(b, a % b);
}

constexpr unsigned int gcd2(unsigned int a, unsigned int b) noexcept
{
   while (b != 0)
   {
      unsigned int r = a % b;
      a = b;
      b = r;
   }

   return a;
}

int main()
{
   std::cout << "Input numbers:";

   unsigned int a, b;
   std::cin >> a >> b;

   std::cout
      << "rec gcd(" << a << ", " << b << ")="
      << gcd(a, b) << std::endl;

   std::cout
      << "    gcd(" << a << ", " << b << ")="
      << gcd2(a, b) << std::endl;

   // C++17 には <numeric> に std::gcd() がある (p. 4)
   std::cout
      << "    gcd(" << a << ", " << b << ")="
      << std::gcd(a, b) << std::endl;
}

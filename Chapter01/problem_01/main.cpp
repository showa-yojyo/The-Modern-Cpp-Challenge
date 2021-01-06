// #1 3 または 5 で割り切れる正の整数の総和
#include <iostream>

int main()
{
   unsigned int limit = 0;
   std::cout << "Upper limit:";
   std::cin >> limit;

   // 大きな上限まで加算するために long long を使う (p. 3)
   unsigned long long sum = 0;
   for (decltype(limit) i = 3; i < limit; ++i)
   {
      if (i % 3 == 0 || i % 5 == 0)
         sum += i;
   }

   std::cout << "sum=" << sum << std::endl;
}

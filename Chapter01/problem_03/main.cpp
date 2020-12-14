#include <iostream>
#include <numeric>
#include <vector>

// C++ 17 では <numeric> に std::lcm() がある (p. 5)
int lcm(int a, int b)
{
   // C++ 17 では <numeric> に std::gcd() がある (p. 4)
   int h = std::gcd(a, b);
   return h ? (a * (b / h)) : 0;
}

template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
   //return std::accumulate(first, last, 1, lcm);
   // C++ 17 では <numeric> に std::lcm() がある (p. 5) が、
   // 次のようにテンプレート引数を明示しないと g++ 9.3.0 はエラーを出す。
   using IntType = typename InputIt::value_type;
   return std::accumulate(first, last, 1, std::lcm<IntType, IntType>);
}

int main()
{
   unsigned int n = 0;
   std::cout << "Input count:";
   std::cin >> n;

   std::vector<int> numbers;
   for (unsigned int i = 0; i < n; ++i)
   {
      int v{ 0 };
      std::cin >> v;
      numbers.push_back(v);
   }

   std::cout
      << "lcm="
      << lcmr(std::begin(numbers), std::end(numbers))
      << std::endl;
}

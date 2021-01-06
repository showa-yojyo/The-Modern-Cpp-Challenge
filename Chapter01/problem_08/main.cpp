// #8 Armstrong Number
// ある数の桁数を n とする。その数の各桁の数の n 乗の和が元の数と等しいような数。
//
// 本書のコードよりも分量が多くなっている。
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <chrono>
#include <functional> // Use std::invoke()

// クラステンプレート
template <typename Time = std::chrono::microseconds,
   typename Clock = std::chrono::high_resolution_clock>
   struct perf_timer
{
   // Python なら decorator で実装するような機能
   template <typename F, typename... Args>
   static Time duration(F&& f, Args... args)
   {
      auto start = Clock::now();

      // std::invoke(f, args) については要調査
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
   }
};

// これが本書のコード
void print_narcissistics_1(bool printResults)
{
   // 3 ケタなので三重ループ
   for (auto a = 1; a <= 9; a++)
   {
      for (auto b = 0; b <= 9; b++)
      {
         for (auto c = 0; c <= 9; c++)
         {
            auto abc = a * 100 + b * 10 + c;
            auto arm = a * a * a + b * b * b + c * c * c;
            if (abc == arm)
            {
               if (printResults) std::cout << arm << std::endl;
            }
         }
      }
   }
}

void print_narcissistics_2(bool printResults)
{
   for (auto i = 100; i <= 1000; ++i)
   {
      int arm = 0;
      auto n = i;
      while (n > 0)
      {
         auto d = n % 10;
         n = n / 10;
         arm += d*d*d;
      }

      if (i == arm)
      {
         if (printResults) std::cout << arm << std::endl;
      }
   }
}

void print_narcissistics_3(int limit, bool printResults)
{
   for (decltype(limit) i = 1; i <= limit; ++i)
   {
      std::vector<int> digits;
      auto n = i;
      while (n > 0)
      {
         digits.push_back(n % 10);
         n = n / 10;
      }

      // ラムダの利用例
      // キャプチャーに注意
      int arm = std::accumulate(
         std::cbegin(digits), std::cend(digits),
         0,
         [s = digits.size()](int sum, int digit) {return sum + static_cast<int>(std::pow(digit, s)); });

      if (i == arm)
      {
         if (printResults) std::cout << arm << std::endl;
      }
   }
}

int main()
{
   print_narcissistics_1(true);
   print_narcissistics_2(true);
   print_narcissistics_3(1000, true);

   // これは面白い。
   // ラムダ式の実行時間を計測するのはこう書けるのか。
   auto t1 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_narcissistics_1(false); });
   std::cout << std::chrono::duration<double, std::milli>(t1).count() << "ms" << std::endl;

   auto t2 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_narcissistics_2(false); });
   std::cout << std::chrono::duration<double, std::milli>(t2).count() << "ms" << std::endl;

   auto t3 = perf_timer<>::duration([]() { for (int i = 0; i < 10000; ++i) print_narcissistics_3(1000, false); });
   std::cout << std::chrono::duration<double, std::milli>(t3).count() << "ms" << std::endl;
}

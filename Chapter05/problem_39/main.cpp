// #39 実行時間を測定する関数
#include <iostream>
#include <chrono>
#include <thread>
#include <functional> // std::invoke() のために include が必要

template <typename Time = std::chrono::microseconds,
   typename Clock = std::chrono::high_resolution_clock>
   struct perf_timer
{
   // 可変テンプレート引数
   template <typename F, typename... Args>
   static Time duration(F&& f, Args... args)
   {
      auto start = Clock::now();
      // 完全転送
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
   }
};

// 2s などのコードを有効にするのに必要な宣言
using namespace std::chrono_literals;

void f()
{
   // simulate work
   std::this_thread::sleep_for(2s);
   // std::this_thread に注意
}

void g(int a, int b)
{
   // simulate work
   std::this_thread::sleep_for(1s);
}

int main()
{
   auto t1 = perf_timer<std::chrono::microseconds>::duration(f);
   auto t2 = perf_timer<std::chrono::milliseconds>::duration(g, 1, 2);

   auto total = std::chrono::duration<double, std::nano>(t1 + t2).count();

   std::cout << total << std::endl;
}

// #65 コンソールへのスレッドセーフなロギング
// 〈標準出力ストリームに同期してアクセスするようにして出力の整合性を保証すること〉
// だそうだ。
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include <string_view>
#include <mutex>
#include <string>

class logger
{
   logger() = default;
public:
   static logger& instance()
   {
      static logger lg;
      return lg;
   }

   logger(logger const &) = delete;
   logger& operator=(logger const &) = delete;

   void log(std::string_view message)
   {
      // いつもの手法で複数スレッドからの出力を〈安全に実行する〉。
      std::lock_guard<std::mutex> lock(mt);
      // string_view をそのまま cout に渡せる。
      std::cout << "LOG: " << message << std::endl;
   }

private:
   std::mutex mt;
};

int main()
{
   std::vector<std::thread> modules;

   for(auto id = 1; id <= 5; ++id)
   {
      // タスクをラムダ式で与える
      modules.emplace_back([id](){
         std::random_device rd;
         std::mt19937 mt(rd());
         std::uniform_int_distribution<> ud(100, 1000);

         logger::instance().log("module " + std::to_string(id) + " started");

         std::this_thread::sleep_for(std::chrono::milliseconds(ud(mt)));

         logger::instance().log("module " + std::to_string(id) + " finished");
      });
   }

   for(auto & m : modules) m.join();
}

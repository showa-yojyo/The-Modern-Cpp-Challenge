// #47 ダブルバッファ
// 同時に読み書きできるバッファ
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread> // Use -pthread option in Linux
#include <chrono>
#include <mutex>
#include <iterator>

template <typename T>
class double_buffer
{
   typedef T         value_type;
   typedef T&        reference;
   typedef T const & const_reference;
   typedef T*        pointer;
public:
   explicit double_buffer(size_t size) :
      rdbuf(size), wrbuf(size)
   {}

   size_t size() const noexcept { return rdbuf.size(); }

   // 以下、すべての I/O 処理に同期処理を提供する。

   void write(T const * const ptr, size_t size)
   {
      std::unique_lock<std::mutex> lock(mt);
      auto length = std::min(size, wrbuf.size());
      std::copy(ptr, ptr + length, std::begin(wrbuf));
      wrbuf.swap(rdbuf); // このスワップがダブルバッファ処理の急所
   }

   template <class Output>
   void read(Output it) const
   {
      std::unique_lock<std::mutex> lock(mt);
      std::copy(std::cbegin(rdbuf), std::cend(rdbuf), it);
   }

   pointer data() const
   {
       std::unique_lock<std::mutex> lock(mt);
       return rdbuf.data();
   }

   reference operator[](size_t const pos)
   {
      std::unique_lock<std::mutex> lock(mt);
      return rdbuf[pos];
   }

   const_reference operator[](size_t const pos) const
   {
      std::unique_lock<std::mutex> lock(mt);
      return rdbuf[pos];
   }

   // #45 の技法を適用してみる
   void swap(double_buffer other) noexcept(noexcept(this->rdbuf.swap(other.rdbuf)))
   {
      std::swap(rdbuf, other.rdbuf);
      std::swap(wrbuf, other.wrbuf);
   }

private:
   // バッファが二つある。
   // コンテナの型はとりあえずは何でもいい。
   std::vector<T> rdbuf;
   std::vector<T> wrbuf;
   mutable std::mutex mt;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const double_buffer<T>& buf)
{
   buf.read(std::ostream_iterator<T>(os, " "));
   return os;
}

int main()
{
   // 単に ms を使いたいだけの using 文
   using namespace std::chrono_literals;

   double_buffer<int> buf(10);

   // スレッドの引数はラムダ式
   std::thread t([&buf]() {
      for (int i = 1; i < 1000; i += 10)
      {
         // iota を使って書き直してみよう
         int data[] = { i, i + 1, i + 2, i + 3, i + 4, i + 5, i + 6,i + 7,i + 8,i + 9 };
         buf.write(data, 10);
         std::this_thread::sleep_for(100ms);
      }
   });

   auto start = std::chrono::system_clock::now();
   do
   {
      std::cout << buf << std::endl;
      std::this_thread::sleep_for(150ms);
   } while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 12);

   t.join();
}

// #57 ソートアルゴリズム
// 何のことはない quick sort だ。
#include <algorithm> // std::generate() 系
#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <numeric>
#include <random>
#include <stack>
#include <chrono>
#include <cassert>

// ランダム反復子でなければならない
template <class RandomIt>
RandomIt partition(RandomIt first, RandomIt last)
{
   auto pivot = *first;
   auto i = first + 1;
   auto j = last - 1;
   while (i <= j)
   {
      while (i <= j && *i <= pivot) i++;
      while (i <= j && *j > pivot) j--;
      // swap() ではなく iter_swap() を使うこだわり
      if (i < j) std::iter_swap(i, j);
   }

   std::iter_swap(i - 1, first);

   return i - 1;
}

// 意味は上と同じ
template <class RandomIt, class Compare>
RandomIt partitionc(RandomIt first, RandomIt last, Compare comp)
{
   auto pivot = *first;
   auto i = first + 1;
   auto j = last - 1;
   while (i <= j)
   {
      while (i <= j && comp(*i, pivot)) i++;
      while (i <= j && !comp(*j, pivot)) j--;
      if (i < j) std::iter_swap(i, j);
   }

   std::iter_swap(i - 1, first);

   return i - 1;
}

// 一時的な記憶域を要するバージョン。本書では反復版と称している。
template <class RandomIt>
void quicksorti(RandomIt first, RandomIt last)
{
   // スタックの利用が再帰アルゴリズムを示唆するようではないか。
   std::stack<std::pair<RandomIt, RandomIt>> st;
   st.push(std::make_pair(first, last));
   while (!st.empty())
   {
      auto iters = st.top();
      st.pop();

      if (iters.second - iters.first < 2) continue;

      auto p = partition(iters.first, iters.second);

      st.push(std::make_pair(iters.first, p));
      st.push(std::make_pair(p+1, iters.second));
   }
}

// ふつうの quick sort
// 再帰アルゴリズム
template <class RandomIt>
void quicksort(RandomIt first, RandomIt last)
{
   if (first < last)
   {
      auto p = partition(first, last);
      quicksort(first, p);
      quicksort(p + 1, last);
   }
}

// 意味は上と同じ
template <class RandomIt, class Compare>
void quicksort(RandomIt first, RandomIt last, Compare comp)
{
   if (first < last)
   {
      auto p = partitionc(first, last, comp);
      quicksort(first, p, comp);
      quicksort(p + 1, last, comp);
   }
}

template <class RandomIt>
void print(RandomIt first, RandomIt last)
{
   for (auto it = first; it < last; ++it)
   {
      std::cout << *it << ' ';
   }
   std::cout << std::endl;
}

int main()
{
   {
      std::vector<int> v{ 1,5,3,8,6,2,9,7,4 };

      quicksort(std::begin(v), std::end(v));

      print(std::cbegin(v), std::cend(v));
   }

   {
      std::array<int, 9> a{ 1,2,3,4,5,6,7,8,9 };

      quicksort(std::begin(a), std::end(a));

      print(std::cbegin(a), std::cend(a));
   }


   {
      int a[]{ 9,8,7,6,5,4,3,2,1 };

      quicksort(std::begin(a), std::end(a));

      print(std::cbegin(a), std::cend(a));
   }

   {
      std::vector<int> v{ 1,5,3,8,6,2,9,7,4 };

      quicksort(std::begin(v), std::end(v), std::greater_equal<>());

      print(std::cbegin(v), std::cend(v));
   }

   {
      std::array<int, 9> a{ 1,2,3,4,5,6,7,8,9 };

      quicksort(std::begin(a), std::end(a), std::greater_equal<>());

      print(std::cbegin(a), std::cend(a));
   }


   {
      int a[]{ 9,8,7,6,5,4,3,2,1 };

      quicksort(std::begin(a), std::end(a), std::greater_equal<>());

      print(std::cbegin(a), std::cend(a));
   }

    {
        std::vector<int> v{ 1, 5,3,8,6,2,9,7,4 };

        quicksorti(std::begin(v), std::end(v));

        print(std::cbegin(v), std::cend(v));
    }

   {
      const size_t count = 1000000;
      std::vector<int> data(count);

      // 乱数
      std::random_device rd;
      std::mt19937 mt;
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
      mt.seed(seq);
      std::uniform_int_distribution<> ud(1, 1000);

      // とにかく長い数列
      std::cout << "generating..." << std::endl;
      std::generate_n(std::begin(data), count, [&mt, &ud]() {return ud(mt); });

      auto d1 = data;
      auto d2 = data;

      std::cout << "sorting..." << std::endl;
      auto start1 = std::chrono::system_clock::now();
      quicksort(std::begin(d1), std::end(d1));
      auto end1 = std::chrono::system_clock::now();
      auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

      // 実行すると秒単位の処理時間であった。
      std::cout << "time: " << t1.count() << "ms" << std::endl;

      std::cout << "sorting..." << std::endl;
      auto start2 = std::chrono::system_clock::now();
      quicksorti(std::begin(d2), std::end(d2));
      auto end2 = std::chrono::system_clock::now();
      auto t2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

      // これも。
      std::cout << "time: " << t2.count() << "ms" << std::endl;

      assert(d1 == d2);
   }

}

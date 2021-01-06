// #45 優先度付きキュー
// 要件：
// top() のコストが O(N)
// pusu(), pop() のコストが O(logN)
// size(), empty() を提供する
// 比較演算を指定可能にする
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// std::vector のアダプターとする priority_queue は珍しいような？
template <class T,
   class Compare = std::less<typename std::vector<T>::value_type>>
   class priority_queue
{
   typedef typename std::vector<T>::value_type      value_type;
   typedef typename std::vector<T>::size_type       size_type;
   typedef typename std::vector<T>::reference       reference;
   typedef typename std::vector<T>::const_reference const_reference;
public:
   // noexcept に注意
   bool empty() const noexcept { return data.empty(); }
   size_type size() const noexcept { return data.size(); }

   // ヒープが優先度付きキューを実装するのに最適だとのこと。
   void push(value_type const & value)
   {
      data.push_back(value);
      std::push_heap(std::begin(data), std::end(data), comparer);
   }

   void pop()
   {
      std::pop_heap(std::begin(data), std::end(data), comparer);
      data.pop_back();
   }

   const_reference top() const noexcept{ return data.front(); }

   void swap(priority_queue& other) noexcept
   {
      swap(data, other.data);
      swap(comparer, other.comparer);
   }

private:
   std::vector<T> data;
   Compare comparer;
};

// noexcept かどうかわからないので lhs.swap(rhs) の noexcept 値を採用する
template< class T, class Compare>
void swap(
   priority_queue<T, Compare>& lhs,
   priority_queue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
   lhs.swap(rhs);
}

int main()
{
   priority_queue<int> q;
   for (int i : {1, 5, 3, 1, 13, 21, 8})
   {
      q.push(i);
   }

   assert(!q.empty());
   assert(q.size() == 7);

   while (!q.empty())
   {
      std::cout << q.top() << ' ';
      q.pop();
   }
   std::cout << std::endl;
}

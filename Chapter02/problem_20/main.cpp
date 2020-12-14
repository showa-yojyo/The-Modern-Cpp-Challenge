// コンテナの any, all, none
#include <algorithm>
#include <vector>
#include <array>
#include <list>
#include <cassert>

// これはふつう
template<class C, class T>
bool contains(C const & c, T const & value)
{
   // 本書では cbegin/cend を採用。
   return std::cend(c) != std::find(std::cbegin(c), std::cend(c), value);
}

// ここがモダン
template<class C, class... T>
bool contains_any(C const & c, T &&... value)
{
   // 畳み込み
   // 左部分が true なら右部分の contains() が呼び出されないとのこと。
   // このような short circuit は以下同様。
   return (... || contains(c, value));
}

template<class C, class... T>
bool contains_all(C const & c, T &&... value)
{
   // 畳み込み
   return (... && contains(c, value));
}

// 論理的には none() は !any() でなければならないので：
template<class C, class... T>
bool contains_none(C const & c, T &&... value)
{
   return !contains_any(c, std::forward<T>(value)...);
}

int main()
{
   std::vector<int> v{ 1,2,3,4,5,6 };
   std::array<int, 6> a{ { 1,2,3,4,5,6 } };
   std::list<int> l{ 1,2,3,4,5,6 };

   assert(contains(v, 3));
   assert(contains(a, 3));
   assert(contains(l, 3));

   assert(!contains(v, 30));
   assert(!contains(v, 30));
   assert(!contains(v, 30));

   assert(contains_any(v, 0, 3, 30));
   assert(contains_any(a, 0, 3, 30));
   assert(contains_any(l, 0, 3, 30));

   assert(!contains_any(v, 0, 30));
   assert(!contains_any(a, 0, 30));
   assert(!contains_any(l, 0, 30));

   assert(contains_all(v, 1, 3, 6));
   assert(contains_all(a, 1, 3, 6));
   assert(contains_all(l, 1, 3, 6));

   assert(!contains_all(v, 0, 1));
   assert(!contains_all(a, 0, 1));
   assert(!contains_all(l, 0, 1));

   assert(contains_none(v, 0, 7));
   assert(contains_none(a, 0, 7));
   assert(contains_none(l, 0, 7));

   assert(!contains_none(v, 0, 6, 7));
   assert(!contains_none(a, 0, 6, 7));
   assert(!contains_none(l, 0, 6, 7));
}

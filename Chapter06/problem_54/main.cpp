// #54 ペア作成アルゴリズム
// この問題は実用上よく出くわすので覚えて損はない。
#include <iostream>
#include <vector>

// 区間バージョン
template <typename Input, typename Output>
void pairwise(Input begin, Input end, Output result)
{
   auto it = begin;
   while (it != end) // ふつうは for ループで書くものだが
   {
      // ここで auto を書けるのはありがたい。
      auto v1 = *it++; if (it == end) break; // 奇数個のシーケンスの末尾要素を無視する
      auto v2 = *it++;
      result++ = std::make_pair(v1, v2);
   }
}

// コンテナバージョン
template <typename T>
std::vector<std::pair<T, T>> pairwise(std::vector<T> const & range)
{
   std::vector<std::pair<T, T>> result;
   pairwise(std::cbegin(range), std::cend(range),
      std::back_inserter(result));

   return result;
}

int main()
{
   std::vector<int> v{ 1, 1, 3, 5, 8, 13, 21 };

   auto result = pairwise(v);

   for (auto const & p : result)
   {
      std::cout << '{' << p.first << ',' << p.second << '}' << std::endl;
   }
}

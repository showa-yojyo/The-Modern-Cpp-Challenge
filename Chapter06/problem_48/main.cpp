// #48 要素列の最頻出要素
// Python の Counter.most_common() みたいなものか。
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
std::vector<std::pair<T, size_t>> find_most_frequent(std::vector<T> const & range)
{
   // Python の collections.Counter のようなもの
   std::map<T, size_t> counts;

   // std::map::operator[] は含まれていない要素を勝手に追加する
   for (auto const & e : range) counts[e]++;

   // 要素の個数の最大値を先に知る。
   // それに合致する要素をあとから検索する。
   auto maxelem = std::max_element(
      std::cbegin(counts), std::cend(counts),
      [](auto const & e1, auto const & e2) {
         return e1.second < e2.second;
      });

   std::vector<std::pair<T, size_t>> result;

   // コンストラクターに直接 [first, last) を指定してよいのでは？
   std::copy_if(
      std::begin(counts), std::end(counts),
      std::back_inserter(result),
      [maxelem](auto const & kvp) {
         return kvp.second == maxelem->second;
      });

   return result;
}

int main()
{
   auto range = std::vector<int>{1,1,3,5,8,13,3,5,8,8,5};
   auto result = find_most_frequent(range);

   for (auto const & e : result)
   {
      std::cout << e.first << " : " << e.second << std::endl;
   }
}

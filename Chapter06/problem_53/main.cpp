// #53 映画の平均評価
// ただし両側 5% * 2 を除外せよとある。
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

struct movie
{
   int id;
   std::string title;
   std::vector<int> ratings;
};

double truncated_mean(std::vector<int> values, double percentage)
{
   // 両側 10% を削るにはソートしておく……。
   // std::nth_element() を二回呼び出す方法が考えられる。
   std::sort(std::begin(values), std::end(values));

   // 5% に相当する個数を求める
   auto remove_count = static_cast<size_t>(values.size() * percentage + 0.5);

   values.erase(std::begin(values), std::begin(values) + remove_count);
   // rbegin() を使う方法もあるかもしれない。
   values.erase(std::end(values) - remove_count, std::end(values));

   // ここから算術平均を計算する

   // 和を求めるだけだから素の accumulate() で十分だろう。
   auto total = std::accumulate(
      std::cbegin(values), std::cend(values),
      0ull,
      [](auto const sum, auto const e) {
      return sum + e; });

   return static_cast<double>(total) / values.size();
}

void print_movie_ratings(std::vector<movie> const & movies)
{
   for (auto const & m : movies)
   {
      std::cout
         << m.title << " : "
         << std::fixed << std::setprecision(1)
         << truncated_mean(m.ratings, 0.05) << std::endl;
   }
}

int main()
{
   std::vector<movie> movies
   {
      { 101, "The Matrix",{ 10, 9, 10, 9, 9, 8, 7, 10, 5, 9, 9, 8 } },
      { 102, "Gladiator",{ 10, 5, 7, 8, 9, 8, 9, 10, 10, 5, 9, 8, 10 } },
      { 103, "Interstellar",{ 10, 10, 10, 9, 3, 8, 8, 9, 6, 4, 7, 10 } }
   };

   print_movie_ratings(movies);
}

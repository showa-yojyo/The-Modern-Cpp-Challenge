// #56 選択アルゴリズム
// 問題文には「射影」とあるので何をするのかはわかる。
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// ゴチャゴチャしたテンプレートに見える。
template <
   typename T, typename A, typename F,
   // ここは解説を要する。
   // - std::result_of() は <...> の結果の型をコンパイル時に得るのに必要。
   // - std::decay<> は？
   typename R = typename std::decay<typename std::result_of<typename std::decay<F>::type&(typename std::vector<T, A>::const_reference)>::type>::type>
   std::vector<R> select(std::vector<T, A> const & c, F&& f)
{
   std::vector<R> v;
   std::transform(
      std::cbegin(c), std::cend(c),
      std::back_inserter(v),
      // F&& 型の引数は std::forward<F>() するのが定石
      std::forward<F>(f));

   return v;
}

// 適当なデータ型
struct book
{
   int id;
   std::string title;
   std::string author;
};

int main()
{
   // 適当なデータのコンテナ
   std::vector<book> books{
      {101, "The C++ Programming Language", "Bjarne Stroustrup"},
      {203, "Effective Modern C++", "Scott Meyers"},
      {404, "The Modern C++ Programming Cookbook", "Marius Bancila"}};

   // .title を select する
   auto titles = select(books, [](book const & b) {return b.title; });

   for (auto const & title : titles)
   {
      std::cout << title << std::endl;
   }
}

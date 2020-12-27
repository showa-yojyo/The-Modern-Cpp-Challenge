// #19 任意個数の要素をコンテナに追加
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <list>

// 可変引数テンプレートの演習問題となる。
template<typename C, typename... Args>
void push_back(C& c, Args&&... args)
{
   // この記法を畳み込みという。これは右畳み込みか？
   (c.push_back(args), ...);
}

int main()
{
   std::vector<int> v;
   //push_back(v, 1, 2, 3, 4);
   v.insert(v.end(), {1, 2, 3, 4});
   std::copy(std::cbegin(v), std::cend(v),
             std::ostream_iterator<int>(std::cout, " "));

   std::list<int> l;
   //push_back(l, 1, 2, 3, 4);
   l.insert(l.end(), {1, 2, 3, 4});
   std::copy(std::cbegin(l), std::cend(l),
             std::ostream_iterator<int>(std::cout, " "));
}

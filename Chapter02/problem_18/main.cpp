// #18 任意個数の引数を取る最小値関数
// C++14 では std::min() がそれをサポートしている
#include <iostream>
#include <functional>
// 参考
#include <algorithm>

// std::min() でよさそうだ
// これが任意個数版の「終端条件」になる
template <typename T>
T minimum(T a, T b) { return a < b ? a : b; }

// これを実装しろというのが演習問題だ
template <typename T1, typename... T>
T1 minimum(T1 a, T... args)
{
   return minimum(a, minimum(args...));
}

// 以下 operator< をカスタム化する場合の最小値関数。
// 残念ながら？比較演算は第一引数にしかできない。
template <class Compare, typename T>
T minimumc(Compare comp, T const a, T const b) { return comp(a, b) ? a : b; }

template <class Compare, typename T1, typename... T>
T1 minimumc(Compare comp, T1 a, T... args)
{
   return minimumc(comp, a, minimumc(comp, args...));
}

int main()
{
   std::cout << minimum(5, 4, 2, 3) << std::endl;
   std::cout << minimumc(std::less<>(), 3, 2, 1, 0) << std::endl;

   // 参考
   std::cout << std::min({5, 4, 2, 3}) << std::endl;
   std::cout << std::min({3, 2, 1, 0}, std::less<>()) << std::endl;
}

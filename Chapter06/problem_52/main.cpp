// #52 文字列の文字の順列を生成
#include <iostream>
#include <string>
#include <algorithm>

// std::next_permutation() を使う非再帰アルゴリズムでいくというのは賛成だ。
void print_permutations(std::string str)
{
   std::sort(std::begin(str), std::end(str));

   // ループと next_permutation の使い方の手本のようだ
   do
   {
      std::cout << str << std::endl;
   } while (std::next_permutation(std::begin(str), std::end(str)));
}

// string は値渡し
void next_permutation(std::string str, std::string perm)
{
   if (str.empty()) std::cout << perm << std::endl;
   else
   {
      // この for loop は古い書き方しかできないか？
      for (size_t i = 0; i < str.size(); ++i)
      {
         next_permutation(str.substr(1), perm + str[0]);

         // rotate() は左なのか右なのか忘れる。
         std::rotate(std::begin(str), std::begin(str) + 1, std::end(str));
      }
   }
}

void print_permutations_recursive(std::string str)
{
   next_permutation(str, "");
}

int main()
{
   std::cout << "non-recursive version" << std::endl;
   print_permutations("main");

   std::cout << "recursive version" << std::endl;
   print_permutations_recursive("main");
}

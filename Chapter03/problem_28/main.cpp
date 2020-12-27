// #28 最長回文部分文字列
#include <string>
#include <string_view>
#include <vector>
#include <cassert>

std::string longest_palindrome(std::string_view str)
{
   auto len = str.size();
   decltype(len) longestBegin = 0;
   decltype(len) maxLen = 1;

   // 部分問題の結果を格納する
   std::vector<bool> table(len * len, false);

   for (decltype(len) i = 0; i < len; i++)
   {
      table[i * len + i] = true;
   }

   for (decltype(len) i = 0; i < len - 1; i++)
   {
      if (str[i] == str[i + 1])
      {
         table[i * len + i + 1] = true;
         if (maxLen < 2)
         {
            longestBegin = i;
            maxLen = 2;
         }
      }
   }

   for (decltype(len) k = 3; k <= len; k++)
   {
      for (decltype(len) i = 0; i < len - k + 1; i++)
      {
         auto j = i + k - 1;
         if (str[i] == str[j] && table[(i + 1) * len + j - 1])
         {
            table[i * len + j] = true;
            if (maxLen < k)
            {
               longestBegin = i;
               maxLen = k;
            }
         }
      }
   }

   // std::string のコンストラクターが必要な理由は str がビューだから。
   return std::string(str.substr(longestBegin, maxLen));
}

int main()
{
   assert(longest_palindrome("sahararahnide") == "hararah");
   assert(longest_palindrome("level") == "level");
   assert(longest_palindrome("s") == "s");
   assert(longest_palindrome("aabbcc") == "aa");
   assert(longest_palindrome("abab") == "aba");
}

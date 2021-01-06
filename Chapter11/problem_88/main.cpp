// #88 シーザー暗号
// 簡単のために大文字しか処理しない
//
// C++ 新機能の学習には不向き
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

std::string caesar_encrypt(std::string_view text, int shift)
{
   std::string str;
   str.reserve(text.length());
   for (auto const & c : text)
   {
      if (isalpha(c) && isupper(c))
         str += 'A' + (c - 'A' + shift) % 26;
      else
         str += c;
   }

   return str;
}

std::string caesar_decrypt(std::string_view text, int shift)
{
   std::string str;
   str.reserve(text.length());
   for (auto const & c : text)
   {
      if (isalpha(c) && isupper(c))
         str += 'A' + (26 + c - 'A' - shift) % 26;
      else
         str += c;
   }

   return str;
}

int main()
{
   std::string text("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   for (auto i: text)
   {
      auto enc = caesar_encrypt(text, i);
      auto dec = caesar_decrypt(enc, i);
      assert(text == dec);
   }
}

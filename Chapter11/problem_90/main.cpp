// #90 base64 encoding & decoding
//
// 珍しく標準ライブラリーしか利用しないコードだ。
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cassert>

class encoder
{
   // モダンな C++ ではメンバー変数の宣言時に値を代入することができる

   // このアルゴリズムでは次の 64 文字を用いる
   std::string const table_enc = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   char const padding_symbol = '=';

   // 復号用
   char const table_dec[256] =
   {
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
      52,53,54,55,56,57,58,59,60,61,-1,-1,-1,65,-1,-1,
      -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
      15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
      -1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
      41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
      -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
   };
   char const invalid_char = -1;
   char const padding_char = 65;

public:
   // バイトのベクトルを base64 符号化する
   std::string to_base64(std::vector<unsigned char> const & data)
   {
      std::string result(
         (data.size() / 3 + ((data.size() % 3 > 0) ? 1 : 0)) * 4, 0);
      auto result_ptr = &result[0];
      size_t i = 0;
      size_t j = 0;

      const auto bound = data.size() / 3;
      while (j++ < bound)
      {
         unsigned int value = (data[i] << 16) | (data[i+1] << 8) | data[i+2];
         i += 3;

         *result_ptr++ = table_enc[(value & 0x00fc0000) >> 18];
         *result_ptr++ = table_enc[(value & 0x0003f000) >> 12];
         *result_ptr++ = table_enc[(value & 0x00000fc0) >> 6];
         *result_ptr++ = table_enc[(value & 0x0000003f)];
      };

      if (auto rest = data.size() - i; rest == 1)
      {
         *result_ptr++ = table_enc[(data[i] & 0x000000fc) >> 2];
         *result_ptr++ = table_enc[(data[i] & 0x00000003) << 4];
         *result_ptr++ = padding_symbol;
         *result_ptr++ = padding_symbol;
      }
      else if (rest == 2)
      {
         unsigned int value = (data[i] << 8) | data[i + 1];

         *result_ptr++ = table_enc[(value & 0x0000fc00) >> 10];
         *result_ptr++ = table_enc[(value & 0x000003f0) >> 4];
         *result_ptr++ = table_enc[(value & 0x0000000f) << 2];
         *result_ptr++ = padding_symbol;
      }

      return result;
   }

   // 復号アルゴリズム
   std::vector<unsigned char> from_base64(std::string data)
   {
      auto padding = data.size() % 4;
      if (padding == 0)
      {
         if (data[data.size() - 1] == padding_symbol) padding++;
         if (data[data.size() - 2] == padding_symbol) padding++;
      }
      else
      {
         data.append(2, padding_symbol);
      }

      // これもコンストラクターでサイズを初期化する
      std::vector<unsigned char> result((data.length() / 4) * 3 - padding);
      auto result_ptr = &result[0];

      size_t i = 0;
      size_t j = 0;
      const auto bound = data.size() / 4;
      while (j++ < bound)
      {
         unsigned char c1 = table_dec[static_cast<int>(data[i++])];
         unsigned char c2 = table_dec[static_cast<int>(data[i++])];
         unsigned char c3 = table_dec[static_cast<int>(data[i++])];
         unsigned char c4 = table_dec[static_cast<int>(data[i++])];

         if (c1 == invalid_char || c2 == invalid_char ||
             c3 == invalid_char || c4 == invalid_char)
            throw std::runtime_error("invalid base64 encoding");

         if (c4 == padding_char && c3 == padding_char)
         {
            unsigned int value = (c1 << 6) | c2;
            *result_ptr++ = (value >> 4) & 0x000000ff;
         }
         else if (c4 == padding_char)
         {
            unsigned int value = (c1 << 12) | (c2 << 6) | c3;
            *result_ptr++ = (value >> 10) & 0x000000ff;
            *result_ptr++ = (value >> 2) & 0x000000ff;
         }
         else
         {
            unsigned int value = (c1 << 18) | (c2 << 12) | (c3 << 6) | c4;

            *result_ptr++ = (value >> 16) & 0x000000ff;
            *result_ptr++ = (value >> 8) & 0x000000ff;
            *result_ptr++ = value & 0x000000ff;
         }
      }

      return result;
   }
};

// 補助的な
namespace converter
{
   auto from_string(std::string_view data)
   {
      return std::vector<unsigned char>(std::cbegin(data), std::cend(data));
   }

   auto from_range(std::vector<unsigned char> const & data)
   {
      return std::string(std::cbegin(data), std::cend(data));
   }
};

int main()
{
   std::vector<std::vector<unsigned char>> data
   {
      { 's' },
      { 's','a' },
      { 's','a','m' },
      { 's','a','m','p' },
      { 's','a','m','p','l' },
      { 's','a','m','p','l','e' },
   };

   encoder enc;

   for (auto const & v : data)
   {
      auto encv = enc.to_base64(v);
      auto decv = enc.from_base64(encv);
      assert(v == decv);
   }

   auto text = "cppchallenge";
   auto textenc = enc.to_base64(converter::from_string(text));
   auto textdec = converter::from_range(enc.from_base64(textenc));
   assert(text == textdec);
}

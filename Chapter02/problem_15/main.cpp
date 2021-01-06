// #15 IPv4 データ型
#include <iostream>
#include <array>
#include <sstream>
#include <cassert>

// IPv4 アドレスを表すクラス
class ipv4
{
   // 固定長配列
   std::array<unsigned char, 4> data;

public:
   // コンストラクター群
   // 1. 可能な限り constexpr を付ける
   // 2. 可能な限り noexcept を付ける

   // デフォルトコンストラクター
   constexpr ipv4() : data{{0}} {}

   // メンバーすべてを明示的に入力するコンストラクター
   constexpr ipv4(unsigned char a, unsigned char b,
                  unsigned char c, unsigned char d) : data{{a, b, c, d}} {}

   // ある種の変換コンストラクター
   explicit constexpr ipv4(unsigned long a) : data{{static_cast<unsigned char>((a >> 24) & 0xFF),
                                                    static_cast<unsigned char>((a >> 16) & 0xFF),
                                                    static_cast<unsigned char>((a >> 8) & 0xFF),
                                                    static_cast<unsigned char>(a & 0xFF)}} {}

   // コピーコンストラクター
   ipv4(ipv4 const &other) noexcept : data(other.data) {}

   // コピー代入演算子
   ipv4 &operator=(ipv4 const &other) noexcept
   {
      data = other.data;
      return *this;
   }

   std::string to_string() const
   {
      std::stringstream sstr;
      // ここで暗黙の変換を期待している
      sstr << *this;
      return sstr.str();
   }

   constexpr unsigned long to_ulong() const noexcept
   {
      return (static_cast<unsigned long>(data[0]) << 24) |
             (static_cast<unsigned long>(data[1]) << 16) |
             (static_cast<unsigned long>(data[2]) << 8) |
             static_cast<unsigned long>(data[3]);
   }

   friend std::ostream &operator<<(std::ostream &os, const ipv4 &a)
   {
      os << static_cast<int>(a.data[0]) << '.'
         << static_cast<int>(a.data[1]) << '.'
         << static_cast<int>(a.data[2]) << '.'
         << static_cast<int>(a.data[3]);
      return os;
   }

   friend std::istream &operator>>(std::istream &is, ipv4 &a)
   {
      char d1, d2, d3;
      int b1, b2, b3, b4;
      is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
      if (d1 == '.' && d2 == '.' && d3 == '.')
         a = ipv4(b1, b2, b3, b4);
      else
         // setstate については C++ の教科書の入出力の章を参照
         is.setstate(std::ios_base::failbit);

      return is;
   }
};

int main()
{
   ipv4 a(168, 192, 0, 1);
   std::cout << a << std::endl;
   std::cout << a.to_string() << std::endl;

   ipv4 b = a;

   // 下 2 行は意図的にこう書いてある。
   ipv4 c;
   c = b;

   ipv4 ip;
   std::cout << ip << std::endl;
   std::cin >> ip;
   // istream の >> の呼び出し後は状態をテストするのがマナー
   if (!std::cin.fail())
   {
      // 上記実装で 333.333.333.333 と入力すると 77.77.77.77 が出力される。
      std::cout << ip << std::endl;
   }
}

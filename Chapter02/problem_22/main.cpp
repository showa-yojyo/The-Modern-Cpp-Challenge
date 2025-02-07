// #22 さまざまな温度単位のリテラル
#include <cmath>
#include <cassert>

// よくあるトレランス付き比較
constexpr bool are_equal(double d1, double d2, double epsilon = 0.001) noexcept
{
   return std::fabs(d1 - d2) < epsilon;
}

// 唐突な名前空間
namespace temperature
{
   // 新式 enum
   enum class scale
   {
      celsius,
      fahrenheit,
      kelvin
   };

   // クラステンプレート
   template <scale S>
   class quantity
   {
      const double amount; // const メンバー変数
   public:
      // この explicit は従来の C++ にもあるが、
      constexpr explicit quantity(double a) : amount(a) {}

      // 変換演算子にも explicit を付けられるようになった。
      constexpr explicit operator double() const noexcept { return amount; }
   };

   // 同じ単位同士の比較演算

   template <scale S>
   inline bool operator==(quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
   }

   template <scale S>
   inline bool operator!=(quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return !(lhs == rhs);
   }

   template <scale S>
   inline bool operator< (quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return static_cast<double>(lhs) < static_cast<double>(rhs);
   }

   template <scale S>
   inline bool operator> (quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return rhs < lhs;
   }

   template <scale S>
   inline bool operator<=(quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return !(lhs > rhs);
   }

   template <scale S>
   inline bool operator>=(quantity<S> const & lhs, quantity<S> const & rhs) noexcept
   {
      return !(lhs < rhs);
   }

   // 同じ単位同士の加減演算

   template <scale S>
   constexpr quantity<S> operator+(quantity<S> const &q1, quantity<S> const &q2) noexcept
   {
      return quantity<S>(static_cast<double>(q1) + static_cast<double>(q2));
   }

   template <scale S>
   constexpr quantity<S> operator-(quantity<S> const &q1, quantity<S> const &q2) noexcept
   {
      return quantity<S>(static_cast<double>(q1) - static_cast<double>(q2));
   }

   // 以下、テンプレート特殊化を応用した何かをする

   template <scale S, scale R>
   struct conversion_traits
   {
      // この = delete の利用法はおもしろい。
      // 特殊化それぞれで定義しなくてはならないということか。
      static double convert(double value) noexcept = delete;
   };

   // 以下、異なる単位同士の convert() を実装する。

   template <>
   struct conversion_traits<scale::celsius, scale::kelvin>
   {
      static double convert(double value) noexcept
      {
         return value + 273.15;
      }
   };

   template <>
   struct conversion_traits<scale::kelvin, scale::celsius>
   {
      static double convert(double value) noexcept
      {
         return value - 273.15;
      }
   };

   template <>
   struct conversion_traits<scale::celsius, scale::fahrenheit>
   {
      static double convert(double value) noexcept
      {
         return (value * 9) / 5 + 32;
      }
   };

   template <>
   struct conversion_traits<scale::fahrenheit, scale::celsius>
   {
      static double convert(double value) noexcept
      {
         return (value - 32) * 5 / 9;
      }
   };

   template <>
   struct conversion_traits<scale::fahrenheit, scale::kelvin>
   {
      static double convert(double value) noexcept
      {
         return (value + 459.67) * 5 / 9;
      }
   };

   template <>
   struct conversion_traits<scale::kelvin, scale::fahrenheit>
   {
      static double convert(double value) noexcept
      {
         return (value * 9) / 5 - 459.67;
      }
   };

   // 最後にキャストを提供する。

   template <scale R, scale S>
   constexpr quantity<R> temperature_cast(quantity<S> const q)
   {
      return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
   }

   // リテラル演算子を部分名前空間に定義する
   namespace temperature_scale_literals
   {
      constexpr quantity<scale::celsius> operator "" _deg(long double amount) noexcept
      {
         return quantity<scale::celsius> {static_cast<double>(amount)};
      }

      constexpr quantity<scale::fahrenheit> operator "" _f(long double amount) noexcept
      {
         return quantity<scale::fahrenheit> {static_cast<double>(amount)};
      }

      constexpr quantity<scale::kelvin> operator "" _k(long double amount) noexcept
      {
         return quantity<scale::kelvin> {static_cast<double>(amount)};
      }
   }
}

int main()
{
   using namespace temperature;
   using namespace temperature_scale_literals;

   // この auto の使い方もさりげなく重要
   auto t1{ 36.5_deg };
   auto t2{ 79.0_f };
   auto t3{ 100.0_k };

   {
      auto tf = temperature_cast<scale::fahrenheit>(t1);
      auto tc = temperature_cast<scale::celsius>(tf);
      assert(t1 == tc);
   }

   {
      auto tk = temperature_cast<scale::kelvin>(t1);
      auto tc = temperature_cast<scale::celsius>(tk);
      assert(t1 == tc);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tc);
      assert(t2 == tf);
   }

   {
      auto tk = temperature_cast<scale::kelvin>(t2);
      auto tf = temperature_cast<scale::fahrenheit>(tk);
      assert(t2 == tf);
   }

   {
      auto tc = temperature_cast<scale::celsius>(t3);
      auto tk = temperature_cast<scale::kelvin>(tc);
      assert(t3 == tk);
   }

   {
      auto tf = temperature_cast<scale::fahrenheit>(t3);
      auto tk = temperature_cast<scale::kelvin>(tf);
      assert(t3 == tk);
   }
}

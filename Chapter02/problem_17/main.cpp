// #17 基本演算を備えた二次元配列を作る
// - indexing
// - size()
// - iterators
// - filling
// - swap()
// - move 操作
//
// 先に main() を見るといい
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// クラステンプレート
template <class T, size_t R, size_t C>
class array2d
{
   // vector を使う
   // 本書では本クラスを vector のアダプターであると表現している。
   // 行と列の扱いについては p. 26 の説明が本質的なので読んでおくこと。
   std::vector<T> arr;

public:
   // 標準ライブラリー志向の typedef
   typedef T value_type;
   typedef value_type *iterator;
   typedef value_type const *const_iterator;

public:
   // デフォルトコンストラクター
   array2d() : arr(R * C) {}

   // 初期化リストによるコンストラクター
   explicit array2d(std::initializer_list<T> l) : arr(l) {}

   // 以下、constexpr, noexcept を忘れずに

   // よくある data()
   constexpr T *data() noexcept { return arr.data(); }
   constexpr T const *data() const noexcept { return arr.data(); }

   // at() は二次元仕様になる
   constexpr T &at(size_t r, size_t c)
   {
      return arr.at(r * C + c);
   }

   constexpr T const &at(size_t r, size_t c) const
   {
      return arr.at(r * C + c);
   }

   // operator() は二次元仕様
   // なお operator[] を提供するなら無理をしないといけない（本書の記述参照）
   constexpr T &operator()(size_t r, size_t c)
   {
      return arr[r * C + c];
   }

   // operator() は二次元仕様
   constexpr T const &operator()(size_t r, size_t c) const
   {
      return arr[r * C + c];
   }

   // arr.empty() とはしない？
   constexpr bool empty() const noexcept
   {
      return R == 0 || C == 0;
   }

   // これは説明を要する
   constexpr size_t size(int rank) const
   {
      if (rank == 1)
         return R;
      else if (rank == 2)
         return C;
      throw std::out_of_range("Rank is out of range!");
   }

   void fill(T const &value)
   {
      std::fill(std::begin(arr), std::end(arr), value);
   }

   void swap(array2d &other) noexcept
   {
      arr.swap(other.arr);
   }

   const_iterator begin() const noexcept { return arr.data(); }
   const_iterator end() const noexcept { return arr.data() + arr.size(); }
   iterator begin() noexcept { return arr.data(); }
   iterator end() noexcept { return arr.data() + arr.size(); }

   const_iterator cbegin() const noexcept { return begin(); }
   const_iterator cend() const noexcept { return end(); }
};

// p. 26 の説明を参照。
template <class T, size_t R, size_t C>
void print_array2d(array2d<T, R, C> const &arr)
{
   for (decltype(R) i = 0; i < R; ++i)
   {
      for (decltype(C) j = 0; j < C; ++j)
      {
         std::cout << arr.at(i, j) << ' ';
      }

      std::cout << std::endl;
   }
}

int main()
{
   {
      std::cout << "test fill" << std::endl;

      array2d<int, 2, 3> a;
      a.fill(1);

      print_array2d(a);
   }

   {
      std::cout << "test operator()" << std::endl;
      array2d<int, 2, 3> a;

      for (size_t i = 0; i < a.size(1); ++i)
      {
         for (size_t j = 0; j < a.size(2); ++j)
         {
            a(i, j) = 1 + i * 3 + j;
         }
      }

      print_array2d(a);
   }

   {
      std::cout << "test move semantics" << std::endl;

      // 冷静に考えると、この初期化コードはそれほどわかりやすくない。
      array2d<int, 2, 3> a{10, 20, 30, 40, 50, 60};
      print_array2d(a);

      array2d<int, 2, 3> b(std::move(a));
      print_array2d(b);
   }

   {
      std::cout << "test swap" << std::endl;

      array2d<int, 2, 3> a{1, 2, 3, 4, 5, 6};
      array2d<int, 2, 3> b{10, 20, 30, 40, 50, 60};

      print_array2d(a);
      print_array2d(b);

      a.swap(b);

      print_array2d(a);
      print_array2d(b);
   }

   {
      std::cout << "test capacity" << std::endl;

      array2d<int, 2, 3> const a{1, 2, 3, 4, 5, 6};

      for (size_t i = 0; i < a.size(1); ++i)
      {
         for (size_t j = 0; j < a.size(2); ++j)
         {
            std::cout << a(i, j) << ' ';
         }

         std::cout << std::endl;
      }
   }

   {
      std::cout << "test iterators" << std::endl;

      array2d<int, 2, 3> const a{1, 2, 3, 4, 5, 6};
      for (auto const e : a)
      {
         std::cout << e << ' ';
      }
      std::cout << std::endl;

      // ここに cbegin(), cend() を使いたい
      std::copy(
          std::cbegin(a), std::cend(a),
          std::ostream_iterator<int>(std::cout, " "));

      std::cout << std::endl;
   }
}

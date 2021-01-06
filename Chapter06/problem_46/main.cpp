// #46 リングバッファ
// 要件：
// - デフォルトコンストラクタを禁止する
// - 指定したサイズのオブジェクトの生成をサポートする
// - バッファの容量と状態をチェックする
// - 要素の追加
// - 要素の削除
// - 反復子
#include <iostream>
#include <vector>
#include <cassert>

// リングバッファクラステンプレートの前方宣言
template <class T>
class circular_buffer;

// 要件どおりに反復子を実装する
template <class T>
class circular_buffer_iterator
{
   typedef circular_buffer_iterator          self_type;
   typedef T                                 value_type;
   typedef T&                                reference;
   typedef T const&                          const_reference;
   typedef T*                                pointer;
   typedef std::random_access_iterator_tag   iterator_category; // 本当か？
   typedef ptrdiff_t                         difference_type;
public:
   circular_buffer_iterator(circular_buffer<T> const & buf, size_t pos, bool last) :
      buffer_(buf), index_(pos), last_(last)
   {}

   self_type & operator++ ()
   {
      if (last_)
         throw std::out_of_range("Iterator cannot be incremented past the end of range.");
      // リングバッファを指すので剰余計算が当然発生する。
      index_ = (index_ + 1) % buffer_.data_.size();
      last_ = index_ == buffer_.next_pos();
      return *this;
   }

   self_type operator++ (int)
   {
      self_type tmp = *this;
      ++*this;
      return tmp;
   }

   bool operator== (self_type const & other) const
   {
      assert(compatible(other));
      return index_ == other.index_ && last_ == other.last_;
   }

   bool operator!= (self_type const & other) const
   {
      return !(*this == other);
   }

   const_reference operator* () const
   {
      return buffer_.data_[index_];
   }

   const_reference operator-> () const
   {
      return buffer_.data_[index_];
   }
private:

   bool compatible(self_type const & other) const
   {
      return &buffer_ == &other.buffer_;
   }

   circular_buffer<T> const & buffer_;
   size_t index_;
   bool last_;
};

// リングバッファのクラステンプレート
template <class T>
class circular_buffer
{
   typedef circular_buffer_iterator<T> const_iterator;

   // 要件のとおりにデフォルトコンストラクタは禁止する
   circular_buffer() = delete;
public:
   explicit circular_buffer(size_t size) :data_(size)
   {}

   // 本書では void 型
   void clear() noexcept { head_ = -1; size_ = 0; }

   bool empty() const noexcept { return size_ == 0; }
   bool full() const noexcept { return size_ == data_.size(); }
   size_t capacity() const noexcept { return data_.size(); }
   size_t size() const noexcept { return size_; }

   // バッファに新たな要素を追加する。
   void push(T item)
   {
      // ヘッドポインタの次の位置に常に挿入する。
      head_ = next_pos();
      data_[head_] = item;
      if (size_ < data_.size()) size_++;
   }

   T pop()
   {
      if (empty()) throw std::runtime_error("empty buffer");

      // 常に最も古い要素を削除する。
      auto pos = first_pos();
      size_--;
      return data_[pos];
   }

   // 練習がてら他の反復子も提供してみよう？

   const_iterator begin() const
   {
      return const_iterator(*this, first_pos(), empty());
   }

   const_iterator end() const
   {
      return const_iterator(*this, next_pos(), true);
   }

private:
   std::vector<T> data_; // std::array にできないか？
   size_t head_ = -1; // 最近挿入した要素の位置
   size_t size_ = 0; // 実際の容量物の個数

   // リングバッファの急所
   size_t next_pos() const noexcept { return size_ == 0 ? 0 : (head_ + 1) % data_.size(); }
   size_t first_pos() const noexcept { return size_ == 0 ? 0 : (head_ + data_.size() - size_ + 1) % data_.size(); }

   friend class circular_buffer_iterator<T>;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const circular_buffer<T>& buf)
{
   for(const auto& e: buf)
   {
      os << e << ' ';
   }
   return os;
}

int main()
{
   // 以下、コンテナの内容については本書 pp. 90-91 参照。
   circular_buffer<int> cbuf(5);
   assert(cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 0);
   std::cout << cbuf << std::endl;

   cbuf.push(1);
   cbuf.push(2);
   cbuf.push(3);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 3);
   std::cout << cbuf << std::endl;

   auto item = cbuf.pop();
   assert(item == 1);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 2);

   cbuf.push(4);
   cbuf.push(5);
   cbuf.push(6);
   assert(!cbuf.empty());
   assert(cbuf.full());
   assert(cbuf.size() == 5);
   std::cout << cbuf << std::endl;

   cbuf.push(7);
   cbuf.push(8);
   assert(!cbuf.empty());
   assert(cbuf.full());
   assert(cbuf.size() == 5);
   std::cout << cbuf << std::endl;

   item = cbuf.pop();
   assert(item == 4);
   item = cbuf.pop();
   assert(item == 5);
   item = cbuf.pop();
   assert(item == 6);

   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 2);
   std::cout << cbuf << std::endl;

   item = cbuf.pop();
   assert(item == 7);
   item = cbuf.pop();
   assert(item == 8);

   assert(cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 0);
   std::cout << cbuf << std::endl;

   cbuf.push(9);
   assert(!cbuf.empty());
   assert(!cbuf.full());
   assert(cbuf.size() == 1);
   std::cout << cbuf << std::endl;
}

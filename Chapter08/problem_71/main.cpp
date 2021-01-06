// #71 観察可能なベクトルコンテナ
// Observer パターン
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

// 新式 enum
enum class collection_action
{
   add,
   remove,
   clear,
   assign
};

// to_string() を自前で実装する
std::string to_string(collection_action action)
{
   switch(action)
   {
      case collection_action::add: return "add";
      case collection_action::remove: return "remove";
      case collection_action::clear: return "clear";
      case collection_action::assign: return "assign";
   }
   // resolve warning control reaches end of non-void function
   return "";
}

struct collection_change_notification
{
   collection_action   action;
   std::vector<size_t> item_indexes;
};

// 通知を希望するオブジェクトの基底クラス
class collection_observer
{
public:
   virtual void collection_changed(collection_change_notification notification) = 0;
   virtual ~collection_observer(){}
};

// コンテナベースの
template <typename T, class Allocator = std::allocator<T>>
class observable_vector final // サブクラスを期待しない場合は final と宣言してしまうのがいい。
{
   typedef typename std::vector<T, Allocator>::size_type size_type;
public:
   observable_vector() noexcept(noexcept(Allocator()))
      : observable_vector( Allocator() ) {}
   explicit observable_vector( const Allocator& alloc ) noexcept
      : data(alloc){}
   observable_vector( size_type count, const T& value, const Allocator& alloc = Allocator())
      : data(count, value, alloc){}
   explicit observable_vector( size_type count, const Allocator& alloc = Allocator() )
      :data(count, alloc){}
   observable_vector(observable_vector&& other) noexcept
      :data(other.data){}
   observable_vector(observable_vector&& other, const Allocator& alloc)
      :data(other.data, alloc){}
   observable_vector(std::initializer_list<T> init,
                     const Allocator& alloc = Allocator())
      :data(init, alloc){}
   template<class InputIt>
   observable_vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      :data(first, last, alloc){}

   // コピー代入演算子
   observable_vector& operator=(observable_vector const & other)
   {
      if(this != &other)
      {
         data = other.data;

         for(auto o : observers)
         {
            // nullptr を格納させなければいいのに
            if(o != nullptr)
            {
               o->collection_changed({
                  collection_action::assign,
                  std::vector<size_t> {}
               });
            }
         }
      }

      return *this;
   }

   // ムーブ代入演算子
   observable_vector& operator=(observable_vector&& other)
   {
      if(this != &other)
      {
         data = std::move(other.data);

         for(auto o : observers)
         {
            if(o != nullptr)
            {
               o->collection_changed({
                  collection_action::assign,
                  std::vector<size_t> {}
               });
            }
         }
      }

      return *this;
   }

   // T&& とあるが完全転送はででこない。テンプレート引数はもう確定している。
   void push_back(T&& value)
   {
      data.push_back(value);

      for(auto o : observers)
      {
         if(o != nullptr)
         {
            o->collection_changed({
               collection_action::add,
               std::vector<size_t> {data.size()-1}
            });
         }
      }
   }

   void pop_back()
   {
      data.pop_back();

      for(auto o : observers)
      {
         if(o != nullptr)
         {
            o->collection_changed({
               collection_action::remove,
               std::vector<size_t> {data.size()+1}
            });
         }
      }
   }

   // 確かに noexcept であるべき操作だが、それが本当に期待できるか？
   void clear() noexcept
   {
      data.clear();

      for(auto o : observers)
      {
         if(o != nullptr)
         {
            // ここで noexcept である必要がある
            o->collection_changed({
               collection_action::clear,
               std::vector<size_t> {} // これが noexcept かどうか
            });
         }
      }
   }

   size_type size() const noexcept
   {
      return data.size();
   }

   // empty() を呼び出すときに戻り値をチェックしないということは考えられない。
   [[nodiscard]] bool empty() const noexcept
   {
      return data.empty();
   }

   void add_observer(collection_observer * const o)
   {
      observers.push_back(o);
   }

   void remove_observer(collection_observer const * const o)
   {
      observers.erase(
         std::remove(std::begin(observers), std::end(observers), o),
         std::end(observers));
   }

private:
   std::vector<T, Allocator> data;
   std::vector<collection_observer*> observers;
};

class observer : public collection_observer
{
public:
   virtual void collection_changed(collection_change_notification notification) override
   {
      std::cout << "action: " << to_string(notification.action);
      if(!notification.item_indexes.empty())
      {
         std::cout << ", indexes: ";
         for(auto i : notification.item_indexes)
            std::cout << i << ' ';
      }
      std::cout << std::endl;
   }
};

int main()
{
   observable_vector<int> v;
   observer o;

   v.add_observer(&o);

   v.push_back(1);
   v.push_back(2);

   v.pop_back();

   v.clear();

   v.remove_observer(&o);

   v.push_back(3);
   v.push_back(4);

   v.add_observer(&o);

   observable_vector<int> v2 {1,2,3};
   v = v2;

   v = observable_vector<int> {7,8,9};
}
// action: add, indexes: 0
// action: add, indexes: 1
// action: remove, indexes: 2
// action: clear
// action: assign
// action: assign

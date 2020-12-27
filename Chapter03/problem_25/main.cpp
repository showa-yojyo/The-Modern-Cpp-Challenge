// #25 英文タイトルのキャピタライズ
#include <string>
#include <sstream>
#include <cctype>
#include <cassert>

// std::basic_string<T> に別名をつける
template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

// std::basic_stringstream<T> に別名をつける
template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
   tstringstream<Elem> result;

   auto newWord = true;
   for (auto const ch : text)
   {
      // 単語の先頭かそれ以外かで分岐したい。
      newWord = newWord || std::ispunct(ch) || std::isspace(ch);
      if (std::isalpha(ch))
      {
         if (newWord)
         {
            result << static_cast<Elem>(std::toupper(ch));
            newWord = false;
         }
         else
            result << static_cast<Elem>(std::tolower(ch));
      }
      else result << ch;
   }

   return result.str();
}

int main()
{
   // リテラル文字列の suffix に s を付けると std::basic_string オブジェクトになる。
   using namespace std::string_literals;

   std::string text = "THIS IS an ExamplE, should wORk!";
   std::string expected = "This Is An Example, Should Work!";
   assert(expected == capitalize(text));

   assert(
          L"The C++ Challenger"s ==
          capitalize(L"the c++ challenger"s));

   assert(
      L"This Is An Example, Should Work!"s ==
      capitalize(L"THIS IS an ExamplE, should wORk!"s));
}

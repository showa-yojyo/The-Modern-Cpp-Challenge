// #40 二つの日付間の日数
// インクルードがごっそり欠けているので補う

#include <iostream>
#include "date.h"

// こちらは左ひく右
inline int number_of_days(
   int y1, unsigned int m1, unsigned int d1,
   int y2, unsigned int m2, unsigned int d2)
{
   using namespace date;

   return (sys_days{ year{ y1 } / month{ m1 } / day{ d1 } } -
      sys_days{ year{ y2 } / month{ m2 } / day{ d2 } }).count();
}

// こちらは右ひく左
inline int number_of_days(date::sys_days const & first,
                          date::sys_days const & last)
{
   return (last - first).count();
}

int main()
{
   unsigned int y1 = 0, m1 = 0, d1 = 0;
   std::cout << "First date" << std::endl;
   std::cout << "Year:"; std::cin >> y1;
   std::cout << "Month:"; std::cin >> m1;
   std::cout << "Date:"; std::cin >> d1;

   std::cout << "Second date" << std::endl;
   unsigned int y2 = 0, m2 = 0, d2 = 0;
   std::cout << "Year:"; std::cin >> y2;
   std::cout << "Month:"; std::cin >> m2;
   std::cout << "Date:"; std::cin >> d2;

   std::cout << "Days between:" << number_of_days(y1, m1, d1, y2, m2, d2) << std::endl;

   using namespace date::literals;
   std::cout << "Days between:" << number_of_days(2018_y/jun/1, 15_d/sep/2018) << std::endl;
}

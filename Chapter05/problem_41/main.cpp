// #41 曜日
#include <iostream>
#include "date.h"
#include "iso_week.h"

constexpr unsigned int week_day(int y, unsigned int m, unsigned int d)
{
   using namespace date;

   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   // 火曜日ならば 2 を返すようだ。
   return static_cast<unsigned int>(tiso.weekday());
}

int main()
{
   // 年は符号が付く
   int y = 0;
   unsigned int m = 0, d = 0;
   std::cout << "Year:"; std::cin >> y;
   std::cout << "Month:"; std::cin >> m;
   std::cout << "Day:"; std::cin >> d;

   std::cout << "Day of week:" << week_day(y, m, d) << std::endl;
}

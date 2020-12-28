// #42 年間の日と週
#include <iostream>
#include "date.h"
#include "iso_week.h"

constexpr unsigned int calendar_week(int y, unsigned int m, unsigned int d)
{
   using namespace date;

   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return static_cast<unsigned int>(tiso.weeknum());
}

constexpr int day_of_year(int y, unsigned int m, unsigned int d)
{
   using namespace date;

   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   return (sys_days{ year{ y } / month{ m } / day{ d } } -
      sys_days{ year{ y } / jan / 0 }).count();
}

int main()
{
   int y = 0;
   unsigned int m = 0, d = 0;
   std::cout << "Year:"; std::cin >> y;
   std::cout << "Month:"; std::cin >> m;
   std::cout << "Day:"; std::cin >> d;

   std::cout << "Calendar week:" << calendar_week(y, m, d) << std::endl;
   std::cout << "Day of year:" << day_of_year(y, m, d) << std::endl;
}

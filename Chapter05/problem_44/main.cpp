// #44 月間カレンダー
#include <iostream>
#include <iomanip>
#include "date.h"
#include "iso_week.h"

constexpr unsigned int week_day(int y, unsigned int m, unsigned int d)
{
   using namespace date;

   if(m < 1 || m > 12 || d < 1 || d > 31) return 0;

   auto const dt = date::year_month_day{ year{ y }, month{ m }, day{ d } };
   auto const tiso = iso_week::year_weeknum_weekday{ dt };

   return static_cast<unsigned int>(tiso.weekday());
}

void print_month_calendar(int y, unsigned int m)
{
   using namespace date;

   std::cout << "Mon Tue Wed Thu Fri Sat Sun" << std::endl;

   auto first_day_weekday = week_day(y, m, 1);
   auto last_day = static_cast<unsigned int>(year_month_day_last(
      year{ y }, month_day_last{ month{ m } }).day());

   unsigned int index = 1;
   for (decltype(first_day_weekday) day = 1; day < first_day_weekday; ++day, ++index)
   {
      std::cout << "    ";
   }

   for (decltype(last_day) day = 1; day <= last_day; ++day)
   {
      std::cout
         << std::right << std::setfill(' ') << std::setw(3)
         << day << ' ';
      if (index++ % 7 == 0)
         std::cout << std::endl;
   }

   std::cout << std::endl;
}

int main()
{
   unsigned int y = 0, m = 0;
   std::cout << "Year:"; std::cin >> y;
   std::cout << "Month:"; std::cin >> m;

   print_month_calendar(y, m);
}

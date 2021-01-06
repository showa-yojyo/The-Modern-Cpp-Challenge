// #32 Pascal の三角形
#include <string>
#include <iostream>
#include <cmath>

// この十進数は何桁あるか
unsigned int number_of_digits(unsigned int i)
{
   // warning: narrowing conversion of i from unsigned int to double
   return i > 0 ? (unsigned int){log10(double{i})} + 1 : 1;
}

void print_pascal_triangle(int n)
{
   for (int i = 0; i < n; i++)
   {
      auto x = 1;
      // spacing
      std::cout << std::string((n - i - 1)*(n / 2), ' ');
      for (int j = 0; j <= i; j++)
      {
         auto y = x;
         x = x * (i - j) / (j + 1);
         auto maxlen = number_of_digits(x) - 1;
         // spacing
         std::cout << y << std::string(n - 1 - maxlen - n%2, ' ');
      }
      std::cout << std::endl;
   }
}

int main()
{
   int n = 0;
   std::cout << "Levels (up to 10): ";
   std::cin >> n;
   if (n > 10)
      std::cout << "Value too large" << std::endl;
   else
      print_pascal_triangle(n);
}

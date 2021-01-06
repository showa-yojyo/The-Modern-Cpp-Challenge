// #60 ライフゲーム
#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <thread>
#include <chrono>
#include <algorithm> // std::generate()
#include <functional> // std::ref()

class universe
{
private:
   size_t rows;
   size_t columns;

   std::vector<unsigned char> grid;
   const unsigned char alive = 1;
   const unsigned char dead = 0;

   std::uniform_int_distribution<> dist;
   std::mt19937 mt;

   // デフォルトコンストラクターは提供しない。
   universe() = delete;

public:
   // 新式 enum
   enum class seed
   {
      random,
      ten_cell_row,
      small_explorer,
      explorer
   };

public:
   // ライフゲームのコンストラクター
   universe(size_t width, size_t height):
      rows(height), columns(width), grid(width * height), dist(0, 4)
   {
      // 乱数
      std::random_device rd;
      auto seed_data = std::array<int, std::mt19937::state_size> {};
      std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
      std::seed_seq seq(std::cbegin(seed_data), std::cend(seed_data));
      mt.seed(seq);
   }

   void run(
      seed s,
      int generations,
      std::chrono::milliseconds ms = std::chrono::milliseconds(100))
   {
      reset();
      initialize(s);
      display();

      int i = 0;
      do
      {
         next_generation();
         display();

         using namespace std::chrono_literals;
         // 1ms を ms と書けるのか。
         std::this_thread::sleep_for(ms);

      } while (i++ < generations || generations == 0);
   }

private:
   void next_generation()
   {
      std::vector<unsigned char> newgrid(grid.size());

      for (decltype(rows) r = 0; r < rows; ++r)
      {
         for (decltype(columns) c = 0; c < columns; ++c)
         {
            // 生きている隣接細胞はいくつか
            auto count = count_neighbors(r, c);

            if (cell(c, r) == alive)
            {
               newgrid[r * columns + c] = (count == 2 || count == 3) ? alive : dead;
            }
            else
            {
               newgrid[r * columns + c] = (count == 3) ? alive : dead;
            }
         }
      }

      grid.swap(newgrid);
   }

   void reset_display()
   {
#ifdef _WIN32
      system("cls");
#endif
   }

   void display()
   {
      reset_display();

      for (decltype(rows) r = 0; r < rows; ++r)
      {
         for (decltype(columns) c = 0; c < columns; ++c)
         {
            std::cout << (cell(c, r) ? '*' : ' ');
         }
         std::cout << std::endl;
      }
   }

   void initialize(seed s)
   {
      if (s == seed::small_explorer)
      {
         auto mr = rows / 2;
         auto mc = columns / 2;

         cell(mc, mr) = alive;
         cell(mc - 1, mr + 1) = alive;
         cell(mc, mr + 1) = alive;
         cell(mc + 1, mr + 1) = alive;
         cell(mc - 1, mr + 2) = alive;
         cell(mc + 1, mr + 2) = alive;
         cell(mc, mr + 3) = alive;
      }
      else if (s == seed::explorer)
      {
         auto mr = rows / 2;
         auto mc = columns / 2;

         cell(mc - 2, mr - 2) = alive;
         cell(mc    , mr - 2) = alive;
         cell(mc + 2, mr - 2) = alive;

         cell(mc - 2, mr - 1) = alive;
         cell(mc + 2, mr - 1) = alive;
         cell(mc - 2, mr    ) = alive;
         cell(mc + 2, mr    ) = alive;
         cell(mc - 2, mr + 1) = alive;
         cell(mc + 2, mr + 1) = alive;

         cell(mc - 2, mr + 2) = alive;
         cell(mc    , mr - 2) = alive;
         cell(mc + 2, mr + 2) = alive;
      }
      else if (s == seed::ten_cell_row)
      {
         for (decltype(columns) c = columns / 2 - 5; c < columns / 2 + 5; c++)
            cell(c, rows / 2) = alive;
      }
      else
      {
         for (decltype(rows) r = 0; r < rows; ++r)
         {
            for (decltype(columns) c = 0; c < columns; ++c)
            {
               cell(c, r) = dist(mt) == 0 ? alive : dead;
            }
         }
      }
   }

   // すべての細胞を死亡状態にする
   void reset()
   {
      for (decltype(rows) r = 0; r < rows; ++r)
      {
         for (decltype(columns) c = 0; c < columns; ++c)
         {
            cell(c, r) = dead;
         }
      }
   }

   constexpr int count_alive() const noexcept { return 0; }

   // パラメーターパックに注意
   template<typename T1, typename... T>
   auto count_alive(T1 s, T... ts) const noexcept { return s + count_alive(ts...); }

   // 生きている隣接細胞はいくつか。
   // ひじょうに面倒。
   int count_neighbors(size_t row, size_t col) const
   {
      if (row == 0 && col == 0)
         return count_alive(cell(1, 0), cell(1,1), cell(0, 1));
      if (row == 0 && col == columns - 1)
         return count_alive(cell(columns - 2, 0), cell(columns - 2, 1), cell(columns - 1, 1));
      if (row == rows - 1 && col == 0)
         return count_alive(cell(0, rows - 2), cell(1, rows - 2), cell(1, rows - 1));
      if (row == rows - 1 && col == columns - 1)
         return count_alive(cell(columns - 1, rows - 2), cell(columns - 2, rows - 2), cell(columns - 2, rows - 1));
      if (row == 0 && col > 0 && col < columns - 1)
         return count_alive(cell(col - 1, 0), cell(col - 1, 1), cell(col, 1), cell(col + 1, 1), cell(col + 1, 0));
      if (row == rows - 1 && col > 0 && col < columns - 1)
         return count_alive(cell(col - 1, row), cell(col - 1, row - 1), cell(col, row - 1), cell(col + 1, row - 1), cell(col + 1, row));
      if (col == 0 && row > 0 && row < rows - 1)
         return count_alive(cell(0, row - 1), cell(1, row - 1), cell(1, row), cell(1, row + 1), cell(0, row + 1));
      if (col == columns - 1 && row > 0 && row < rows - 1)
         return count_alive(cell(col, row - 1), cell(col - 1, row - 1), cell(col - 1, row), cell(col - 1, row + 1), cell(col, row + 1));

      return count_alive(cell(col - 1, row - 1), cell(col, row - 1), cell(col + 1, row - 1), cell(col + 1, row), cell(col + 1, row + 1), cell(col, row + 1), cell(col - 1, row + 1), cell(col - 1, row));
   }

   // lvalue としてアクセスする。
   unsigned char& cell(size_t col, size_t row)
   {
      return grid[row * columns + col];
   }

   unsigned char cell(size_t col, size_t row) const
   {
      return grid[row * columns + col];
   }
};

int main()
{
   using namespace std::chrono_literals;

   universe u(50, 20);
   u.run(universe::seed::random, 100, 100ms);
}

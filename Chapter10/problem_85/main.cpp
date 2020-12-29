// #85 SQLite データベースから映画を読み込む
#include <iostream>
#include <vector>

#include "sqlite3.h"
// C++17 と SQLCipher をサポートする sqlite_modern_cpp を採用。
#include "sqlite_modern_cpp.h"
// 自作ヘッダーファイル
#include "movies.h"

void print_movie(movie const & m)
{
   std::cout << "[" << m.id << "] "
      << m.title << " (" << m.year << ") "
      << m.length << "min" << std::endl;
   std::cout << " directed by: ";
   for (auto const & d : m.directors) std::cout << d << ",";
   std::cout << std::endl;
   std::cout << " written by: ";
   for (auto const & w : m.writers) std::cout << w << ",";
   std::cout << std::endl;
   std::cout << " cast: ";
   for (auto const & r : m.cast) std::cout << r.actor << " (" << r.role << "),";
   std::cout << std::endl << std::endl;
}

std::vector<std::string> get_directors(sqlite3_int64 movie_id,
                                       sqlite::database & db)
{
   std::vector<std::string> result;

   // この operator<<() と operator>>() の使われ方は面白い
   db << R"(select p.name from directors as d
            join persons as p on d.personid = p.rowid
            where d.movieid = ?;)"
      << movie_id
      >> [&result](std::string name) // ここは auto と書けない！
   {
      // 今まであまり見かけなかった emplate_back()
      result.emplace_back(name);
   };

   return result;
}

std::vector<std::string> get_writers(sqlite3_int64 movie_id,
                                     sqlite::database & db)
{
   std::vector<std::string> result;
   db << R"(select p.name from writers as w
         join persons as p on w.personid = p.rowid
         where w.movieid = ?;)"
      << movie_id
      >> [&result](std::string name) // ここは auto と書けない！
   {
      result.emplace_back(name);
   };

   return result;
}

std::vector<casting_role> get_cast(sqlite3_int64 movie_id,
                                   sqlite::database & db)
{
   std::vector<casting_role> result;
   db << R"(select p.name, c.role from casting as c
         join persons as p on c.personid = p.rowid
         where c.movieid = ?;)"
      << movie_id
      >> [&result](std::string name, std::string role) // ここは auto と書けない！
   {
      result.emplace_back(casting_role{ name, role });
   };

   return result;
}

movie_list get_movies(sqlite::database & db)
{
   movie_list movies;

   db << R"(select rowid, * from movies;)"
      >> [&movies, &db](sqlite3_int64 rowid, std::string const & title,
                        int year, int length)
   {
      movies.emplace_back(movie{
         static_cast<unsigned int>(rowid),
         title,
         year,
         static_cast<unsigned int>(length),
         get_cast(rowid, db),
         get_directors(rowid, db),
         get_directors(rowid, db)
         });
   };

   return movies;
}

int main()
{
   try
   {
      // このデータベースは cmake の段階で作成する
      sqlite::database db(R"(cppchallenger85.db)");

      auto movies = get_movies(db);
      for (auto const & m : movies)
         print_movie(m);
   }
   catch (sqlite::sqlite_exception const & e)
   {
      std::cerr << e.get_code() << ": " << e.what() << " during "
                << e.get_sql() << std::endl;
   }
   catch (std::exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }
}
// [1] The Matrix (1999) 196min
//  directed by: Lana Wachowski,Lilly Wachowski,
//  written by: Lana Wachowski,Lilly Wachowski,
//  cast: Keanu Reeves (Neo),Laurence Fishburne (Morpheus),Carrie-Anne Moss (Trinity),Hugo Weaving (Agent Smith),
//
// [2] Forrest Gump (1994) 202min
//  directed by: Robert Zemeckis,
//  written by: Robert Zemeckis,
//  cast: Tom Hanks (Forrest Gump),Sally Field (Mrs. Gump),Robin Wright (Jenny Curran),Mykelti Williamson (Bubba Blue),

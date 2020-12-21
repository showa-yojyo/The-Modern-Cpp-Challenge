// #76 JSON からデータを deserialize する
#include <iostream>
#include <string_view>
#include <fstream>
#include <cassert>

// 前項と同じ
#include "json.hpp"
#include "movies.h"

using json = nlohmann::json;

movie_list deserialize(std::string_view filepath)
{
   movie_list movies;

   // 前項と同じ
   std::ifstream ifile(filepath.data());
   if (ifile.is_open())
   {
      json jdata;

      try
      {
         // operator>>() で一気に読む
         ifile >> jdata;

         if (jdata.is_object())
         {
            // JSON オブジェクトの movies の値を反復する
            for (auto & element : jdata.at("movies"))
            {
               movie m;

               // この get() は何だ？ キャストか？
               m.id = element.at("id").get<unsigned int>();
               m.title = element.at("title").get<std::string>();
               m.year = element.at("year").get<unsigned int>();
               m.length = element.at("length").get<unsigned int>();

               for (auto & role : element.at("cast"))
               {
                  m.cast.push_back(casting_role{
                     role.at("star").get<std::string>(),
                     role.at("name").get<std::string>() });
               }

               // assign()?
               for (auto & director : element.at("directors"))
               {
                  m.directors.push_back(director);
               }

               // assign()?
               for (auto & writer : element.at("writers"))
               {
                  m.writers.push_back(writer);
               }

               // 最後の push_back() に std::move() を伴う状況はよくあるかもしれない。
               movies.push_back(std::move(m));
            }
         }
      }
      // ひじょうに雑な例外ハンドル
      // これなら何もしないのと変わらない
      catch (std::exception const & ex)
      {
         std::cout << ex.what() << std::endl;
      }
   }

   return movies;
}

int main()
{
   auto movies = deserialize("movies.json");

   assert(movies.size() == 2);
   assert(movies[0].title == "The Matrix");
   assert(movies[1].title == "Forrest Gump");
}

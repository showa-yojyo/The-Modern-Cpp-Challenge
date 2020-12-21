// #74 XPath を使って XML からデータを抽出する
// C++17 の学習にはあまり向いていいない
#include <iostream>
#include <string>
#include <string_view>

// 前項と同じライブラリーを採用
#include "pugixml.hpp"

int main()
{
	// ダブルクォーテーションが頻出する文字列を定義するのに生文字列が有用だ。
	std::string text = R"(
<?xml version="1.0"?>
<movies>
	<movie id="11001" title="The Matrix" year="1999" length="196">
		<cast>
			<role star="Keanu Reeves" name="Neo" />
			<role star="Laurence Fishburne" name="Morpheus" />
			<role star="Carrie-Anne Moss" name="Trinity" />
			<role star="Hugo Weaving" name="	Agent Smith" />
		</cast>
		<directors>
			<director name="Lana Wachowski" />
			<director name="Lilly Wachowski" />
		</directors>
		<writers>
			<writer name="Lana Wachowski" />
			<writer name="Lilly Wachowski" />
		</writers>
	</movie>
	<movie id="9871" title="Forrest Gump" year="1994" length="202">
		<cast>
			<role star="Tom Hanks" name="Forrest Gump" />
			<role star="Sally Field" name="Mrs. Gump" />
			<role star="Robin Wright" name="Jenny Curran" />
			<role star="Mykelti Williamson" name="Bubba Blue" />
		</cast>
		<directors>
			<director name="Robert Zemeckis" />
		</directors>
		<writers>
			<writer name="Winston Groom" />
			<writer name="Eric Roth" />
		</writers>
	</movie>
</movies>
)";

	pugi::xml_document doc;
	// なぜ C 形式の文字列を要求するのだ？
	if (doc.load_string(text.c_str()))
	{
		try
		{
			// auto としか書けない
			auto titles = doc.select_nodes("/movies/movie[@year>1995]");
			for (auto it : titles)
			{
				std::cout << it.node().attribute("title").as_string() << std::endl;
			}
		}
		catch (pugi::xpath_exception const &e)
		{
			std::cout << e.result().description() << std::endl;
		}

		try
		{
			auto titles = doc.select_nodes("/movies/movie/cast/role[last()]");
			for (auto it : titles)
			{
				std::cout << it.node().attribute("star").as_string() << std::endl;
			}
		}
		catch (pugi::xpath_exception const &e)
		{
			std::cout << e.result().description() << std::endl;
		}
	}
}

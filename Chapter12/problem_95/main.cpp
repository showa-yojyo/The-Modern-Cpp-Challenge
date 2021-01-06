// #95 ホストの IP を調べる
#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#define ASIO_STANDALONE // Boost に依存させないようにこれを定義
// ヘッダーファイルだけからなるライブラリー Asio
#include "asio.hpp"

// ホスト名に対する IPv4 アドレスを示す文字列を返す
std::vector<std::string> get_ip_address(std::string_view hostname)
{
   std::vector<std::string> ips;

   try
   {
      // 非同期 I/O 機能
      asio::io_context context;
      // 問い合わせをエンドポイントに解決する機能
      asio::ip::tcp::resolver resolver(context);
      auto endpoints = resolver.resolve(
         asio::ip::tcp::v4(), hostname.data(), "");

      for (const auto& e: endpoints)
         // 本書のコードに置き換える
         ips.push_back(e.endpoint().address().to_string());
   }
   catch (std::exception const & e)
   {
      // やる気のない例外処理
      std::cerr << "exception: " << e.what() << std::endl;
   }

   return ips;
}

int main()
{
   auto ips = get_ip_address("packtpub.com");

   for (auto const & ip : ips)
      std::cout << ip << std::endl;
}

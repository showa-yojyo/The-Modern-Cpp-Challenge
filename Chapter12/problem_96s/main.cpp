// #96 クライアント・サーバー Fizz-Buzz (server side)
#include <iostream>
#include <string>
// なぜか抜けているので補足
#include <array>
#include <memory>

// 前項参照
#define ASIO_STANDALONE
#include "asio.hpp"

// 本書の説明 (p. 257) 参照
std::string fizzbuzz(int number)
{
   // コードを見ればわかるか
   if (number != 0)
   {
      auto m3 = number % 3;
      auto m5 = number % 5;
      if (m3 == 0 && m5 == 0) return "fizzbuzz";
      else if (m5 == 0) return "buzz";
      else if (m3 == 0) return "fizz";
   }

   return std::to_string(number);
}

// std::enable_shared_from_this は説明を要する。
// これを継承するサブクラスは、メンバー関数内で shared_from_this() により
// サブクラス自身の std::shared_ptr オブジェクトを得る。
class session : public std::enable_shared_from_this<session>
{
public:
   session(asio::ip::tcp::socket socket) :
      tcp_socket(std::move(socket))
   {
   }

   void start()
   {
      read();
   }

private:
   void read()
   {
      // これが std::shared_ptr<sesson> 型となる
      auto self(shared_from_this());

      // ソケット操作
      // ラムダ式でインラインに処理を定義する。
      tcp_socket.async_read_some(
         asio::buffer(data, data.size()),
         [this, self](std::error_code ec, std::size_t length)
      {
         if (!ec)
         {
            auto number = std::string(data.data(), length);
            // この atoi() はダサい気がする
            auto result = fizzbuzz(std::atoi(number.c_str()));

            std::cout << number << " -> " << result << std::endl;

            write(result);
         }
      });
   }

   void write(std::string_view response)
   {
      auto self(shared_from_this());

      // ソケット操作
      tcp_socket.async_write_some(
         asio::buffer(response.data(), response.length()),
         [this, self](std::error_code ec, std::size_t)
      {
         if (!ec)
         {
            read();
         }
      });
   }

   // メンバー変数
   std::array<char, 1024>  data; // std::array のよい利用例と思われる
   asio::ip::tcp::socket   tcp_socket;
};

class server
{
public:
   server(asio::io_context& context, short port)
      : tcp_acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
      , tcp_socket(context)
   {
      std::cout << "server running on port " << port << std::endl;

      accept();
   }

private:
   void accept()
   {
      tcp_acceptor.async_accept(tcp_socket, [this](std::error_code ec)
      {
         if (!ec)
         {
            std::make_shared<session>(std::move(tcp_socket))->start();
         }

         accept();
      });
   }

   asio::ip::tcp::acceptor tcp_acceptor;
   asio::ip::tcp::socket   tcp_socket;
};

// Ctrl+C するまで稼働し続ける
void run_server(short port)
{
   try
   {
      asio::io_context context;
      server srv(context, port);
      context.run();
   }
   catch (std::exception const & e)
   {
      std::cerr << "exception: " << e.what() << std::endl;
   }
}

int main()
{
   run_server(11234);
}

// #96 クライアント・サーバー Fizz-Buzz (client side)
// C++ コードの学習としては「？」
#include <iostream>
#include <array>

// 前項参照
#define ASIO_STANDALONE
#include "asio.hpp"

void run_client(std::string_view host, short port)
{
   try
   {
      // 接続処理
      asio::io_context context;
      asio::ip::tcp::socket tcp_socket(context);
      asio::ip::tcp::resolver resolver(context);
      asio::connect(tcp_socket,
                    resolver.resolve({ host.data(), std::to_string(port) }));

      while (true)
      {
         std::cout << "number [1-99]: ";

         int number;
         std::cin >> number;
         if (std::cin.fail() || number < 1 || number > 99)
            // 本書で break を見るのは珍しい
            break;

         auto request = std::to_string(number);
         tcp_socket.write_some(asio::buffer(request, request.length()));

         // この std::array の使い方はしっくり来る
         std::array<char, 1024> reply;
         auto reply_length = tcp_socket.read_some(asio::buffer(reply, reply.size()));

         std::cout << "reply is: ";
         std::cout.write(reply.data(), reply_length);
         std::cout << std::endl;
      }
   }
   catch (std::exception const & e)
   {
      std::cerr << "exception: " << e.what() << std::endl;
   }
}

int main()
{
   run_client("localhost", 11234);
}

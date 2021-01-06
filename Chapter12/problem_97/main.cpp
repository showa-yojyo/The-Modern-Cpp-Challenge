// #97 ビットコインの交換レート
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <map>

// curlcpp
#include "curl_easy.h"
#include "curl_exception.h"

// Chapter09 で習ったライブラリー
#include "json.hpp"

using json = nlohmann::json;

struct exchange_info
{
   double delay_15m_price;
   double latest_price;
   double buying_price;
   double selling_price;
   std::string symbol;
};

// この手の using 文は本書で初めて出てきたのでは？
using blockchain_rates = std::map<std::string, exchange_info>;

void from_json(const json& jdata, exchange_info& info)
{
   info.delay_15m_price = jdata.at("15m").get<double>();
   info.latest_price = jdata.at("last").get<double>();
   info.buying_price = jdata.at("buy").get<double>();
   info.selling_price = jdata.at("sell").get<double>();
   info.symbol = jdata.at("symbol").get<std::string>();
}

std::stringstream get_json_document(std::string_view url)
{
   std::stringstream str;

   try
   {
      // 独特なインターフェイス
      curl::curl_ios<std::stringstream> writer(str);
      curl::curl_easy easy(writer);

      easy.add<CURLOPT_URL>(url.data());
      easy.add<CURLOPT_FOLLOWLOCATION>(1L);

      // サーバーからの応答を str に書き込む
      easy.perform();
   }
   catch (curl::curl_easy_exception const & error)
   {
      auto errors = error.get_traceback();
      error.print_traceback();
   }

   return str;
}

int main()
{
   auto doc = get_json_document("https://blockchain.info/ticker");

   json jdata;
   doc >> jdata;

   blockchain_rates rates = jdata;

   for (auto const & kvp : rates)
   {
      std::cout << "1BPI = " << kvp.second.latest_price
                << " " << kvp.first << std::endl;
   }
}
// 1BPI = 30540.4 AUD
// 1BPI = 120833 BRL
// 1BPI = 29755.7 CAD
// 1BPI = 20552.7 CHF
// 1BPI = 1.65404e+07 CLP
// 1BPI = 151500 CNY
// 1BPI = 141205 DKK
// 1BPI = 19012.4 EUR
// 1BPI = 17119.4 GBP
// 1BPI = 179573 HKD
// 1BPI = 1.71033e+06 INR
// 1BPI = 2.95949e+06 ISK
// 1BPI = 2.396e+06 JPY
// 1BPI = 2.56041e+07 KRW
// 1BPI = 32616.6 NZD
// 1BPI = 85486.6 PLN
// 1BPI = 1.74058e+06 RUB
// 1BPI = 191726 SEK
// 1BPI = 30829.5 SGD
// 1BPI = 700183 THB
// 1BPI = 176956 TRY
// 1BPI = 650986 TWD
// 1BPI = 23162.6 USD
//
// 出力書式を考えるほうがいいかもしれない

#pragma once
#include<iostream>
#include <string>

#include "curl.h"
#include "easy.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

using namespace rapidjson;
using namespace std;

static char error_buffer[CURL_ERROR_SIZE];

enum {
    LIMIT_BUY_ORDER = 0,
    LIMIT_SELL_ORDER,

    MARKET_BUY_ORDER,
    MARKET_SELL_ORDER,

    CANCEL_ORDER,
};

enum {
    QUERY_POSITION = 0,
    QUERY_ENTRUSTS,
    QUERY_CANCEL_ENTRUSTS,

    QUERY_TRADES,
};


class CZtTrader {
  public:
    CZtTrader();
    CZtTrader(const string& base_url);
    ~CZtTrader();
  public:
    bool new_stock();
    bool send_order();
    bool cancel_order();
    bool get_position();
  public:
    //static functions
    static int writer(char* data, size_t size, size_t nmemb, std::string* writer_data);
    static CURLcode init(CURL*& conn, const string& url, std::string* p_buffer);
    static CURLcode curl_get(const string& url, std::string& buffer);
    static CURLcode curl_post(const string& url, const string& data, std::string& buffer);

  private:
    //order
    string m_limit_buy_url;

    string m_limit_sell_url;

    string m_market_buy_url;

    string m_market_sell_url;

    string m_cancel_entrust_url;

    //query
    string m_position_url;

    string m_today_entrusts_url;

    string m_today_trades_url;

    string m_cancel_entrusts_url;

    //auto ipo
    string m_auto_ipo;
};


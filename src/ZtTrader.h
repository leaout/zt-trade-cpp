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

class CZtTrader {
  public:
    CZtTrader();
    CZtTrader(const string& base_url);
    ~CZtTrader();
  public:
    bool new_stock();
  public:
    //static functions
    static int writer(char* data, size_t size, size_t nmemb, std::string* writer_data);
    static CURLcode init(CURL*& conn, const string& url, std::string* p_buffer);
    static CURLcode curl_get(const string& url, std::string& buffer);
    static CURLcode curl_post(const string& url, const string& data, std::string& buffer);

  private:
    string m_trade_url;
};


#include<iostream>
#include"curl.h"
#include "easy.h"
using namespace std;

const string REAL_URL = "http://127.0.0.1:3001";

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static char error_buffer[CURL_ERROR_SIZE];

static int writer(char* data, size_t size, size_t nmemb, std::string* writer_data) {
    unsigned long sizes = size * nmemb;

    if (NULL == writer_data) {
        return 0;
    }

    writer_data->append(data, sizes);

    return sizes;
}

static bool init(CURL*& conn, const char* url, std::string* p_buffer) {
    CURLcode code;

    //conn = curl_easy_init();
    if (NULL == conn) {
        std::cout << stderr << " Failed to create CURL connection" << std::endl;
        exit(EXIT_FAILURE);
    }

    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
    if (code != CURLE_OK) {
        std::cout << stderr << " Failed to set error buffer " << code << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_URL, url);
    if (code != CURLE_OK) {
        std::cout << stderr << " Failed to set URL " << error_buffer << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
    if (code != CURLE_OK) {
        std::cout << stderr << " Failed to set redirect option " << error_buffer << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    if (code != CURLE_OK) {
        std::cout << stderr << " Failed to set writer " << error_buffer << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, p_buffer);
    if (code != CURLE_OK) {
        std::cout << stderr << " Failed to set write data " << error_buffer << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char*argv[]) {
    CURL *conn;
    CURLcode res;
    std::string readBuffer;

    res = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != res) {
        cout << "curl init failed" << endl;
        return 1;
    }

    conn = curl_easy_init();
    string str_buf;
    init(conn, (REAL_URL + "/api/position").c_str(), &str_buf);

    auto code = curl_easy_perform(conn);
    cout << str_buf.c_str() << endl;
    getchar();
    return 0;
}
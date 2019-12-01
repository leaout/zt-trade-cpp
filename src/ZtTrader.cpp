#include "ZtTrader.h"



CZtTrader::CZtTrader() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CZtTrader::CZtTrader(const string& base_url):m_trade_url(base_url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

CZtTrader::~CZtTrader() {

}


int CZtTrader::writer(char* data, size_t size, size_t nmemb, std::string* writer_data) {
    unsigned long sizes = size * nmemb;

    if (NULL == writer_data) {
        return 0;
    }

    writer_data->append(data, sizes);

    return sizes;
}

CURLcode CZtTrader::init(CURL*& conn, const string& url, std::string* p_buffer) {
    CURLcode code;

    assert(conn);

    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, error_buffer);
    if (code != CURLE_OK) {
        std::cout << stderr << "CURLOPT_ERRORBUFFER Failed" << code << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str());
    if (code != CURLE_OK) {
        std::cerr << stderr << "CURLOPT_URL Failed" << error_buffer << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
    if (code != CURLE_OK) {
        std::cerr << "CURLOPT_FOLLOWLOCATION Failed" << error_buffer << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    if (code != CURLE_OK) {
        std::cerr << "CURLOPT_WRITEFUNCTION Failed " << error_buffer << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, p_buffer);
    if (code != CURLE_OK) {
        std::cerr<< "CURLOPT_WRITEDATA  Failed " << error_buffer << std::endl;
        return code;
    }

    return code;
}

CURLcode CZtTrader::curl_get(const string& url, std::string& buffer) {
    CURL *conn = NULL;
    CURLcode code;

    conn = curl_easy_init();
    code = init(conn, url, &buffer);
    if (code != CURLE_OK) {
        std::cerr <<" Connection initializion failed" << std::endl;
        return code;
    }

    code = curl_easy_perform(conn);

    if (code != CURLE_OK) {
        std::cerr <<" Failed to get" << url << error_buffer << std::endl;
        return code;
    }

    curl_easy_cleanup(conn);

    return code;
}

CURLcode CZtTrader::curl_post(const string& url, const string& data,
                              std::string& buffer) {
    CURL *conn = NULL;
    CURLcode code;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (!init(conn, url, &buffer)) {
        std::cerr<< "init Failed" << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_POST, true);

    if (code != CURLE_OK) {
        std::cerr << "CURLOPT_POST Failed:" << error_buffer << std::endl;
        return code;
    }

    code = curl_easy_setopt(conn, CURLOPT_POSTFIELDS, data);
    if (code != CURLE_OK) {
        std::cerr << "CURLOPT_POSTFIELDS  Failed:" << error_buffer << std::endl;
        return code;
    }

    code = curl_easy_perform(conn);

    if (code != CURLE_OK) {
        std::cerr << " Post  Failed :" << url << error_buffer << std::endl;
        return code;
    }

    curl_easy_cleanup(conn);

    return code;

}

bool CZtTrader::new_stock() {
    string out_buf;
    if (curl_get(m_trade_url + "/api/auto_ipo", out_buf) != CURLE_OK) {
        std::cerr << "new_stock curl_get failed" << endl;
        return false;
    }
    std::cout << out_buf << endl;
    return true;
}

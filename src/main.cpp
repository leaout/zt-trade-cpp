#include<iostream>
#include <assert.h>
#include <thread>
#include "ZtTrader.h"

using namespace std;

const string REAL_URL = "http://127.0.0.1:3001";

int main(int argc, char*argv[]) {

    CZtTrader zt_trader(REAL_URL);
    zt_trader.new_stock();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return 0;
}
#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <utility>
#include <set>
#include <queue>
#include <string.h>
#include <deque>
#include <stack>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cctype>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
using namespace std;


class Historical_Trades
{
    public:
    string entryDate;
    string exitDate;
    double entryPrice;
    double exitPrice;
    double PnL;
    int numberOfTrades;
    public:
    Historical_Trades(string entryDate, string exitDate, double entryPrice, 
    double exitPrice, double PnL, int numberOfTrades): 
    entryDate(entryDate), exitDate(exitDate), entryPrice(entryPrice), exitPrice(exitPrice), 
    PnL(PnL), numberOfTrades(numberOfTrades)
    {}
    
};
// lista på active trades, denna aktiveras efter en signal från strat
class Active_Trades
{
    public:
    string entryDate;
    double entryPrice;
    public:
    Active_Trades(string entryDate, double entryPrice, double currentPnL)
    :entryDate(entryDate), entryPrice(entryPrice)
    {}
    

};
/*
kommer ta emot beräkningar från parser
sparar dem för att sedan kunna skicka till strat
*/
class indicators
{
    double vwap_p1;
    double vwap_p2;
    double vwap_p3;
    double vwap_n1;
    double vwap_n2;
    double vwap_n3;
    double vwap_mean;

    indicators(double vwap_p1, double vwap_p2, double vwap_p3, double vwap_n1, double vwap_n2,
    double vwap_n3, double vwap_mean):
    vwap_p1(vwap_p1), vwap_p2(vwap_p2), vwap_p3(vwap_p3), vwap_n1(vwap_n1), vwap_n2(vwap_n2),
    vwap_n3(vwap_n3), vwap_mean(vwap_mean)
    {}

    

};

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
#include "market-parser.h"
#include "MarketStrategy.hpp"
using namespace std;
// En samling av gamla trades
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


void OrderControlPanel(int confirmation)
{
   switch(confirmation)
   {
    case 1:

   }
}

void BuyOrder()
{
    
}




/*
1. calculate pnl
2. funktion som tar in de olika vwap
3. uppdatera parser att inkludera x2 + x3 div
4. lösa tidsintervallet
5. funktioner som sparar saker i active + history list
6.en funktion som tar in start period och sista perioden, den kommer anropa resterande
den kommer i sin tur skicka in separat varje vwap[i] och pris[i].close till strat, strat skickar
tillbaka signaler om det är köp eller sälj
*/

int main(void)
{
    // Dessa kommer flytta sen till engineStarter för att det är där main är
    vector<Historical_Trades> history;
    vector<Active_Trades> liveTrades;
    vector<indicators> indicators_Vector;

}
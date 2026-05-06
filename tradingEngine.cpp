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
#include "market-strategy.hpp"
using namespace std;
// En samling av gamla trades

// NOTE THIS PART IS NOT YET DONE*******
class Historical_Trades
{
    public:
    string entryDate;
    string exitDate;
    double entryPrice;
    double exitPrice;
    int numberOfTrades;
    double positionSize;
    double realized_PnL;
    double realized_PnL_Prc;
    public:
    Historical_Trades(string entryDate, string exitDate, double entryPrice, 
    double exitPrice, int numberOfTrades, double realized_PnL, double realized_PnL_Prc): 
    entryDate(entryDate), exitDate(exitDate), entryPrice(entryPrice), exitPrice(exitPrice),
    numberOfTrades(numberOfTrades), positionSize(positionSize), realized_PnL(realized_PnL),
    realized_PnL_Prc(realized_PnL_Prc)
    {}
    
};
// lista på active trades, denna aktiveras efter en signal från strat
// Member initalizer list
class Active_Trades
{
    public:
    string entryDate;
    double entryPrice;
    double stopLoss;
    double positionSize;
    double unrealized_PnL;
    double unrealized_PnL_Prc;
    public:
    Active_Trades(string entryDate, double entryPrice, double stopLoss, double positionSize, 
    double unrealized_PnL, double unrealized_PnL_Prc)
    :entryDate(entryDate), entryPrice(entryPrice), stopLoss(stopLoss), positionSize(positionSize),
    unrealized_PnL(unrealized_PnL), unrealized_PnL_Prc(unrealized_PnL_Prc)
    {}
    

};


enum class portfolioResponses
{
    AddedTradeSuccessfully,
    insufficientFunds,
    TooManyLiveTradesCurrently,
    WeShouldNotBuy,
    AddedTradeFailed

};

class Portfolio
{
    public:
    double balance;
    double PnL_prc;
    double positionSize_Allocation;
    double MinimumPositionSize;

    public:
    // Notera de två metoderna att initializera, skriver du i {balance = 1000;}, så skapas skräp först
    // Använd alltid intializer list istället för assignment constructur
    /*
    i assignment skapas variabel med skräp först, sedan blir den tilldelad ett värde
    medan i init list så skapas varibeln direkt med värdet, ett steg istället för två
    */
    Portfolio(): balance(1000), PnL_prc(0.0), positionSize_Allocation(0.1), MinimumPositionSize(50)
    {}

    bool isMinimumSizeGreaterThanBalance()
    {
        if(MinimumPositionSize > balance)
        {
            return true;
        }
        return false;
    }

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




// en som räknar amount och en som räknar procent
double calculate_PnL_Value(const vector<MarketData>& data, int index, double entryPrice)
{
    double currentPrice = data[index].close;
    double resultat = currentPrice - entryPrice;
    return resultat;
    
}

double calculate_PnL_Precent(const vector<MarketData>& data, int index, double entryPrice)
{
    // Formel: (current/entry - 1) * 100 = antal precent
    double currentPrice = data[index].close;
    double resultat = (currentPrice / entryPrice) - 1;
    resultat = resultat * 100;
    return resultat;

}

bool isPositionSize_GreaterThanMinimum(double positionSize)
{
    const double Minimum_Position_Size = 50;
    if(positionSize >= Minimum_Position_Size)
    {
        return true;
    }
    return false;

}


portfolioResponses AddTradeToActiveTrades(vector<MarketData>& data, int index,
vector<Active_Trades>& liveTrades, Portfolio &portfolio)
{
    
    if(!doWeHaveLessThan5Trades(liveTrades))
    {
        return portfolioResponses::TooManyLiveTradesCurrently;
    }
    double entryPrice = data[index].close;

    if(!ShouldWeBuy(data, index, entryPrice))
    {
        return portfolioResponses::WeShouldNotBuy;
    }
    // kanske sätter denna under positionSize blir väl bättre flöde och tydligare fördelning?
    // Blev löst med enum

    string entryDate = data[index].date;
    double stopLoss = stopLoss_10p(data, index, entryPrice);
    // Retunerar stoploss priset

    double positionSize = portfolio.balance * portfolio.positionSize_Allocation;
    if(!portfolio.isMinimumSizeGreaterThanBalance())
    {
        return portfolioResponses::insufficientFunds;
    }
    // Kontroll att vi har minst 50
    if(!isPositionSize_GreaterThanMinimum(positionSize))
    {
        positionSize = portfolio.MinimumPositionSize;
    }
    // Justering av ps vid < 50
    double unrealized_pnl = calculate_PnL_Value(data, index, entryPrice);
    double unrealized_pnl_prc = calculate_PnL_Precent(data, index, entryPrice);

    liveTrades.emplace_back(entryDate, entryPrice, stopLoss, positionSize, unrealized_pnl,
    unrealized_pnl_prc);


    reduceBalance(portfolio, positionSize);
    return portfolioResponses::AddedTradeSuccessfully;    
}



void reduceBalance(Portfolio& portfolio, double positionSize)
{
    portfolio.balance = portfolio.balance - positionSize;
}

bool doWeHaveLessThan5Trades(vector<Active_Trades>liveTrades)
{
    size_t length = liveTrades.size();
    if(length <= 5)
    {
        return true;
    }
    return false;
}







/*
1. calculate pnl
2. funktin som tar in de olika vwap
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
    Portfolio portfolio;

}

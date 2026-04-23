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
#include "market-strategy.hpp"
#include "market-parser.h"
#include "trading-engine.h"

 /*
    Jag behöver kanske inte tillgång till listan?
    Straten ska bara kontrollera om price > vwap
    det är väl engine som bör hålla koll på dagar
    skilj på SIGNAL & ACTION
    Strat skickar ENDAST signaler, den gör ingen bedömningen på huruvida en position
    är öppen eller stängd
    jag beböve också snöa in mig på EN strategi, inte om går upp eller ner, endat om den är nere
    eller endat om den är uppe.
    bygga små funktioner som kontrollerar 
    Behöver lägga till trendfunktion + volymfunktion i parser

    */

    /*
    --------Köpdelen---------
    *note: så himla mycket bättre när funktionsnamnen verkligen beskriver vad den gör
    speciellet när man har varit borta ett tag
    1. Mekanismer som avgör NÄR vi köper
    2. håller mig helt till VWAP 2nd div köpläge
    3. Lägger till en liten volymdel
    */

    bool IsPriceLowerThan_1stdLower_Vwap(vector<MarketData>& data, int period, double price)
    {
        double std1 = Std1_Below_VWAP(data, period);
        if(price < std1)
        {
            return true;
        }
        return false;
    }

    bool IsPriceLowerThan_2std_vwap_Plus30p(vector<MarketData>& data, int period, double price)
    {
        double std2 = std2_below_VWAP(data, period);
        double deviation = One_Deviation_VWAP(data, period);
        deviation = deviation*1.3;
        //inom 2nd div -> 30% efter den så om 2nd div är 5, lägg på 30%
        if(price < std2+deviation)
        {
            return true;
        }
        return false;
    }

    bool isTodaysVol_Greater_than_AVG(vector<MarketData>& data, int period)
    {
        double todaysVol = todaysVolume(data, period);
        double avg_vol = AVG_Volume(data, period);
        if(todaysVol > avg_vol)
        {
            return true;
        }
        return false;
    }


    /*
    ------ Stop-loss
    */

    bool isCurrentPrice10precent_Lower(vector<MarketData>& data, int index, double entryPrice)
    {
        // Behåller denna som den är så att jag kan ändra den senare
        double todaysPrice = data[index].close;
        double diff = 0.9;
        if(todaysPrice < (entryPrice*diff))
        /*
        ex: 80 < 100*0.9 = 90
        */
        {
            return true;
        }
        return false;
    }



    /*
    ------ Sell---- inte short
    */


    bool isPriceAbove2std_minus10precent(vector<MarketData>& data, int index)
    {
        // skickar bara en signal om att prsiet har nått en viss gräns, gör ingen värdering
        double currentPrice = data[index].close;
        double diff = 0.9;
        double vwap2 = Std2_Above_VWAP(data, index);
        if(currentPrice >= (vwap2*diff))
        {
            return true;
        }
        return false;

    }

    /*
    -------- Execution
    */

    bool ShouldWeBuy(vector<MarketData>& data, int index, double price)
    {
    /* 
    om nån av dessa inte är sant finns det ingen anledningen att ha en till funktion som kontrollerar
    negationen av dessa
    Notera: vid avgVol hårdkodar 10 eftersom jag vill bara ha de senaste 10 dagarna
    */
    if(IsPriceLowerThan_1stdLower_Vwap(data, index, price) && 
    IsPriceLowerThan_2std_vwap_Plus30p(data, index, price) && 
    isTodaysVol_Greater_than_AVG(data, 10))
    {
        return true;
    }
    return false;
    }


    bool isPriceBelow_Stop_Loss(vector<MarketData>& data, int index, double price)
    {
        bool stop_loss = isCurrentPrice10precent_Lower(data, index, price);
        return stop_loss;
    }

    bool ShouldWeSell(vector<MarketData>& data, int index, double price)
    {
        bool sell_signal = isPriceAbove2std_minus10precent(data, index);
        return sell_signal;
    }



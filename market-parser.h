#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cmath>
#pragma once

using namespace std;
class MarketData
{
    public:
    string date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    double volume;
    public:
    MarketData(const string date, double open, double high, double low, double close, double adjClose, double volume)
    {

    }

};

double EMA_Calculator(vector<MarketData>& data, int period);

double std2_below_VWAP(const vector<MarketData>& data, int period);

double std3_below_VWAP(const vector<MarketData>& data, int period);

double AVG_Volume(vector<MarketData>& data, int period);

double todaysVolume(vector<MarketData>& data, int endIndex);

ostream& operator<<(ostream& os, MarketData data);

double MovingAverage (const vector<MarketData> data, int period);

double Total_VWAP(const vector<MarketData> data, int period);

double One_Deviation_VWAP (const vector<MarketData> data, int period);

double DailyPrice(vector<MarketData>& data, int period);

double std1_Above_VWAP (const vector<MarketData> data, int period);

double Std1_Below_VWAP(const vector<MarketData> data, int period);

double Std2_Above_VWAP (const vector<MarketData>& data, int period);

MarketData DailyStats (const vector<MarketData> data, string day);

MarketData HighestPrice (const vector<MarketData> data);

MarketData LowestPrice (const vector<MarketData> data);

bool readFromFile(vector<MarketData> data, const string name);


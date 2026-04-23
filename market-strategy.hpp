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

bool IsPriceLowerThan_1stdLower_Vwap(vector<MarketData>& data, int period, double price);

bool IsPriceLowerThan_2std_vwap_Plus30p(vector<MarketData>& data, int period, double price);

bool isTodaysVol_Greater_than_AVG(vector<MarketData>& data, int period);

bool isCurrentPrice10precent_Lower(vector<MarketData>& data, int index, double entryPrice);

bool isPriceAbove2std_minus10precent(vector<MarketData>& data, int index);

bool ShouldWeBuy(vector<MarketData>& data, int index, double price);

bool ShouldWeSell(vector<MarketData>& data, int index, double price);

bool isPriceBelow_Stop_Loss(vector<MarketData>& data, int index, double price);

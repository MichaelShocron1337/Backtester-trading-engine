# Backtester Trading Engine

This project is a continuation of my previous project *market-parser*.  
It aims to provide a modular backtesting framework for evaluating trading strategies on historical data.

## Overview

The system is divided into three main components:

- **Market Parser**  
  Responsible for calculating indicators and processing raw market data (e.g. moving averages, VWAP, volume metrics).

- **Market Strategy**  
  Contains the trading logic and rules (e.g. when to buy, sell, or trigger stop-loss).  
  The current implementation is a basic VWAP-based strategy, but this module is designed to be easily replaceable.

- **Trading Engine**  
  Acts as a reusable simulation engine that:
  - iterates over historical data
  - executes trades based on strategy signals
  - tracks positions, capital, and trade history
  - produces a summary of performance

## Design Goal

The primary goal of this project is separation of concerns:

- The **strategy** defines *what* to do (signals and rules)
- The **engine** handles *how* trades are executed and tracked
- The **parser** provides the required market calculations

This makes it possible to swap strategies without modifying the engine.

## Current Strategy

The current implementation uses a simple VWAP-based strategy with predefined entry and exit rules.  
This is mainly intended as a proof of concept and will be extended or replaced.

## Future Improvements

- Additional strategies (trend-based, momentum, etc.)
- More advanced performance metrics (drawdown, Sharpe ratio, etc.)
- Parameterization of strategies
- Optional CLI for running different configurations
- Improved data handling and validation

## Status

This project is ongoing and not yet fully developed.

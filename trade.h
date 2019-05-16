// David Hernandez
// c++
// Project Demo: trade.h
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Trading {
private:
	int numOfShares;
	int stockSelected;
	int buyOrSell;
	int numMarketOrder;
	int numLimitOrder;
	int buyOrderType;
	int sellOrderType;

	double accountSize;
	double low;
	double high;
	double stockPrice;
	double openPL;
	double closePL;
	double currentPrice;
	double newPrice;
	double limitPrice;
	double points;
	double percentage;
	double limitSellPrice;

	string strOrderType;
	string strBuyOrSell;
	string buy, sell;
	string ticker;
	string stock;

public:
	Trading();
	Trading(string stock, double MarketPrice);
	Trading(string stock, int numOfShares, double price);
	Trading(string stock);
	int getNumOfShares();
	void setNumOfShares(int numOfShares);
	double getPrice();
	void setPrice(double price);
	double getCurrentPrice();
	void setCurrentPrice(double currentPrice);
	double getLimitPrice();
	void setLimitPrice(double limitPrice);
	int getBuyOrderType();
	void setBuyOrderType(int buyOrderType);
	void setSellOrderType(int sellOrderType);
	void setBuyOrSell(int buyOrSell);
	double getNewPrice();
	void setNewPrice(double newPrice);
	double getLimtitSellPrice();
	void setLimitSellPrice(double limitSellPrice);
	string getStock();
	void setStock(string stock);
	double getAccountSize();
	void setAccountSize(double accountSize);
	string stocks[12] = { "AAPL", "AMZN", "BA", "BABA", "FB", "GOOGL", "JPM", "MSFT", "NFLX", "NVDA", "TSLA" };
	double generatePrice(double min, double max);
	double showPrice(string stock);
	double calcMarketTotal(string stock, int numOfShares, double price);
	double calcLimitTotal(string stock, int numOfShares, double limitPrice);
	void orders(string stock, int numOfShares, double price);
	double calcOpenPL(string stock, int numOfShares, double price, double newPriec);
	double calcClosedPL(string stock, int numOfShares, double price, double theNewPrice);
	void accountInfo(double account, double accountPL, double initalAccountBalance);
	void positions(string stock, int numOfShares, double price, double newPrice);
	void showTrading(double price);
};
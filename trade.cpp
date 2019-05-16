// David Hernandez
// c++
// Project demo: trade.cpp

#include "trade.h"
#include<string>
#include<iomanip>

Trading::Trading() {}

Trading::Trading(string stock, double MarketPrice) {
	this->stock = stock;
	this->currentPrice = MarketPrice;
}

Trading::Trading(string stock, int numOfShares, double marketPrice) {
	this->stock = stock;
	this->numOfShares = numOfShares;
	this->stockPrice = marketPrice;
}

Trading::Trading(string stock) {
	this->stock = stock;
}

int Trading::getNumOfShares() {
	return numOfShares;
}

void Trading::setNumOfShares(int numOfShares) {
	this->numOfShares = numOfShares;
}

double Trading::getPrice() {
	return stockPrice;
}

void Trading::setPrice(double price) {
	this->stockPrice = price;
}

double Trading::getCurrentPrice() {
	return currentPrice;
}

void Trading::setCurrentPrice(double currentPrice) {
	this->currentPrice = currentPrice;
}

double Trading::getLimitPrice() {
	return limitPrice;
}

void Trading::setLimitPrice(double limitPrice) {
	this->limitPrice = limitPrice;
}

int Trading::getBuyOrderType() {
	return buyOrderType;
}

void Trading::setBuyOrderType(int buyOrderType) {
	this->buyOrderType = buyOrderType;
}

void Trading::setSellOrderType(int sellOrderType) {
	this->sellOrderType = sellOrderType;
}

void Trading::setBuyOrSell(int buyOrSell) {
	this->buyOrSell = buyOrSell;
}

double Trading::getNewPrice() {
	return newPrice;
}

void Trading::setNewPrice(double newPrice) {
	this->newPrice = newPrice;
}

double Trading::getLimtitSellPrice() {
	return limitSellPrice;
}

void Trading::setLimitSellPrice(double limitSellPrice) {
	this->limitSellPrice = limitSellPrice;
}

string Trading::getStock() {
	return stock;
}

void Trading::setStock(string stock) {
	this->stock = stock;
}

double Trading::getAccountSize() {
	return accountSize;
}

void Trading::setAccountSize(double accountSize) {
	this->accountSize = accountSize;
}

double Trading::generatePrice(double min, double max) {
	return (min + 1) + (((double)rand()) / (double)RAND_MAX) * (max - (min + 1));
}

double Trading::showPrice(string stock) {
	double price = 0;
	if (stock == "AAPL") {
		price = generatePrice(176.99, 178.45);
	}
	else if (stock == "AMZN") {
		price = generatePrice(1519.80, 1530.45);
	}
	else if (stock == "BA") {
		price = generatePrice(317.75, 320.45);
	}
	else if (stock == "BABA") {
		price = generatePrice(149.97, 150.45);
	}
	else if (stock == "FB") {
		price = generatePrice(135.19, 137.87);
	}
	else if (stock == "GOOGL") {
		price = generatePrice(1044.40, 1049.45);
	}
	else if (stock == "JPM") {
		price = generatePrice(107.90, 110.15);
	}
	else if (stock == "MSFT") {
		price = generatePrice(103.19, 105.45);
	}
	else if (stock == "NFLX") {
		price = generatePrice(262.50, 265.48);
	}
	else if (stock == "NVDA") {
		price = generatePrice(145.20, 148.00);
	}
	else if (stock == "TSLA") {
		price = generatePrice(338.25, 342.48);
	}
	return price;
}

double Trading::calcMarketTotal(string stock, int numOfShares, double price) {
	double cost;
	cost = numOfShares * price;
	return cost;
}

double Trading::calcLimitTotal(string stock, int numOfShares, double price) {
	double cost;
	cost = numOfShares * price;
	return cost;
}

void Trading::orders(string stock, int numOfShares, double price) {
	if (buyOrSell == 1) {
		strBuyOrSell = "Buy";
		cout << "ORDERS -------------------------------------|" << endl;
		cout << "| Symbol    Shares    Price    Type          " << endl;
		cout << "|  " << stock << "        " << numOfShares << "   $" << price << "     " << strBuyOrSell << endl;
		cout << "|-------------------------------------------|" << endl;
	}
	else if (buyOrSell == 2) {
		strBuyOrSell = "Sell";
		cout << "ORDERS -------------------------------------|" << endl;
		cout << "| Symbol    Shares    Price    Type         " << endl;
		cout << "|  " << stock << "        " << numOfShares << "   $" << price << "     " << strBuyOrSell << endl;
		cout << "|-------------------------------------------|" << endl;
	}
}

double Trading::calcOpenPL(string stock, int numOfShares, double price, double theNewPrice) {
	double total = 0.0;
	if (buyOrderType == 1) {
		total = calcMarketTotal(stock, numOfShares, price);
	}
	else if (buyOrderType == 2) {
		total = calcLimitTotal(stock, numOfShares, price);
	}
	double openPL = 0;
	openPL = (theNewPrice * numOfShares) - total;
	return openPL;
}

double Trading::calcClosedPL(string stock, int numOfShares, double price, double price2) {
	double closedPL = 0;
	if (buyOrSell == 2) {
		double total;
		if (sellOrderType == 1) {
			if (buyOrderType == 1) {
				total = calcMarketTotal(stock, numOfShares, price);
				closedPL = (price2 * numOfShares) - total;
			}
			else if (buyOrderType == 2) {
				total = calcLimitTotal(stock, numOfShares, price);
				closedPL = (price2 * numOfShares) - total;
			}
		}
		else if (sellOrderType == 2) {
			if (buyOrderType == 1) {
				total = calcMarketTotal(stock, numOfShares, price);
				closedPL = total - (price2 * numOfShares);
			}
			else if (buyOrderType == 2) {
				total = calcLimitTotal(stock, numOfShares, price);
				closedPL = total - (price2 * numOfShares);
			}
		}
	}
	return closedPL;
}

void Trading::accountInfo(double account, double accountPL, double initialAccountBalance) {
	double gainLossPercentage = (accountPL / initialAccountBalance) * 100;
	cout << "Account Info --------------------------------------------|" << endl;
	cout << "| Intial Account Balance: $" << initialAccountBalance << endl;
	account = account + accountPL;
	cout << "| Current Acount Balance: $" << fixed << setprecision(2) << account << endl;
	cout << "| Gain/Loss Percentage %" << fixed << setprecision(2) << gainLossPercentage << endl;
	cout << "|--------------------------------------------------------|" << endl;
}

void Trading::positions(string stock, int numOfShares, double price, double price2) {
	openPL = calcOpenPL(stock, numOfShares, price, price2);
	closePL = calcClosedPL(stock, numOfShares, price, price2);
	double newPrice = showPrice(stock);
	if (buyOrSell == 1) {
		cout << "Positions -----------------------------------------------|" << endl;
		cout << "| Symbol    Shares    Price    Open P&L   Closed P&L     " << endl;
		cout << "|  " << stock << "      " << numOfShares << "      $" << price2 << "   $"
			<< openPL << "              $0" << endl;
		cout << "|--------------------------------------------------------|" << endl;
	}
	else if (buyOrSell == 2) {
		cout << "Positions -----------------------------------------------|" << endl;
		cout << "| Symbol    Shares    Price    Open P&L   Closed P&L     " << endl;
		cout << "|  " << stock << "      " << numOfShares << "      $" << newPrice << "   $0"
			<< "              $" << closePL << endl;
		cout << "|--------------------------------------------------------|" << endl;
	}
}

void Trading::showTrading(double price) {
	low = showPrice(stock);
	high = showPrice(stock);

	cout << "Trading--------------------------------------------------|" << endl;
	cout << "| Symbol       Current Price       High            low        " << endl;
	if (low <= high) {
		cout << "| " << stock << "          $" << fixed << setprecision(2) << price << "            $"
			<< fixed << setprecision(2) << high << "       $" << fixed << setprecision(2) << low << endl;
	}
	else if (low >= high) {
		cout << "| " << stock << "             $" << fixed << setprecision(2) << price << "         $" <<
			fixed << setprecision(2) << low << "     $" << fixed << setprecision(2) << high << endl;
	}
	cout << "|--------------------------------------------------------|" << endl;
}
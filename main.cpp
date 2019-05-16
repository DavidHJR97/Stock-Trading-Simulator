// David Hernandez
// c++
// Project Demo: main.cpp

#include<iostream>
#include<iomanip>
#include<string>
#include "trade.h"
#include<vector>

using namespace std;

// vectors and arrays declared
string stocks[11] = { "AAPL", "AMZN", "BA", "BABA", "FB", "GOOGL", "JPM", "MSFT", "NFLX", "NVDA", "TSLA" };
vector<string> stocksBought;
vector<int> sharesBought;
vector<double> marketPrice;
vector<double> limitPrice;
vector<double> limtitSellPrice;
vector<int> buyTypeOrder;

int main() {

	// Two objects delcared. One for the stock that is bought
	// the other for the stock that is being sold.
	Trading stock1 = Trading();
	Trading stock2 = Trading();

	// double variables declared
	double initialAccountBalance;
	double accountSize;
	double accountTotal;
	double newStockPrice;
	double buyMarketPrice;
	double buyLimitPrice;
	double cost;
	double theLimitPrice;
	double limitSellPrice;

	// string variables declared
	string sellStock;
	string buyStock;

	// int variables declared
	int stockSelected;
	int buyOrSell;
	int buyAnotherStock;
	int count = 0;
	int numOfShares = 0;
	int buyOrderType;
	int sellOrderType;

	cout << "Welcome to Hernandez Investments!$!$!$!" << endl;
	cout << "Please enter the amount you want to trade with: ";
	cin >> accountSize;
	initialAccountBalance = accountSize;

	if (accountSize < 0) {
		cout << "Please enter a number!" << endl;
	}
	else {
		cout << "Your account is now worth: $" << fixed << setprecision(2) << accountSize << endl << endl;

		do {
			// User decides if they want to buy or sell a stock
			cout << "Do you want to buy or sell a stock? Press 1 for buy, 2 for sell: ";
			cin >> buyOrSell;
			if (buyOrSell == 1) { // the user selects to buy a stock
								  // Ask the user for the stock they want to trade once the stocks are displayed
				cout << "Please type the number for the stock you want to trade" << endl;
				for (int i = 0; i < 11; i++) {
					cout << i << ": " << stocks[i] << endl;
				}
				cout << "Stock Selected: ";
				cin >> stockSelected; // acepts the stock that was selected
				cout << endl;

				if (stockSelected < 0 || stockSelected > 10) {
					cout << "Please enter a stock that was displayed, try again next time" << endl << endl;
				}
				else {
					buyMarketPrice = stock1.showPrice(stocks[stockSelected]); // creates a market price for the selected stock
					marketPrice.push_back(buyMarketPrice); // adds the market price to the vector
					stock1 = Trading(stocks[stockSelected], buyMarketPrice); // instantiates stock1 to the stock selected and market price
					stock1.setCurrentPrice(buyMarketPrice); // sets the current price of stock1 to the market price
					stock1.showTrading(buyMarketPrice); // displays stock1 information
					newStockPrice = stock1.showPrice(stocks[stockSelected]); // creates a new price for stock1

					cout << "Please enter the number of shares: ";
					cin >> numOfShares;

					if (numOfShares < 0) {
						cout << "Share size must be greater than 0" << endl << endl;
						exit(0);
					}
					else {
						cout << "Which order type do you want? Press 1 for market, 2 for limit: ";
						cin >> buyOrderType;
						buyTypeOrder.push_back(buyOrderType);

						if (buyOrderType == 1) { // the user selects to buy a stock with a market order 
							stock1 = Trading(stocks[stockSelected], numOfShares, buyMarketPrice); // instantiates stock1 with the stock selected, number of shares, and market price
							stock1.setBuyOrSell(1);
							stock1.setBuyOrderType(1);
							cost = stock1.calcMarketTotal(stocks[stockSelected], numOfShares, buyMarketPrice); // calculates the cost for stock1
							if (cost > accountSize) {
								cout << "Amount exceeded";
							}
							else if (cost <= accountSize) {
								stocksBought.push_back(stocks[stockSelected]); // adds the stock that was selected to the vector
								sharesBought.push_back(numOfShares);
								stock1.orders(stocks[stockSelected], numOfShares, buyMarketPrice); // displays the users order with the stock that was selected
								stock1.positions(stocks[stockSelected], numOfShares, buyMarketPrice, newStockPrice); // displays the user current position
							}
						}
						else if (buyOrderType == 2) { // the user selects to buy a stock with a limit order
							cout << "Please enter the limit amount: ";
							cin >> buyLimitPrice;
							if (buyLimitPrice <= 0) {
								cout << "Please enter a number" << endl << endl;
								exit(0);
							}
							else {
								limitPrice.push_back(buyLimitPrice); // adds the limit buy price to the vector
								stock1 = Trading(stocks[stockSelected], numOfShares, buyLimitPrice); // instantiates stock1 with stock selected, number of shares, limit price
								stock1.setBuyOrSell(1);
								stock1.setBuyOrderType(2);
								cost = stock1.calcLimitTotal(stocks[stockSelected], numOfShares, buyLimitPrice); // calculates the total for buying the stock with a limit price
								if (cost > accountSize) {
									cout << "Amount exceeded";
								}
								else if (cost <= accountSize) {
									stocksBought.push_back(stocks[stockSelected]); // adds the stock that was selected to the vector
									sharesBought.push_back(numOfShares);
									stock1.orders(stocks[stockSelected], numOfShares, buyLimitPrice); // displays the users order 
									stock1.positions(stocks[stockSelected], numOfShares, buyLimitPrice, newStockPrice); // displays the users current position
								}
							}

						}
						else {
							cout << "Incorrect Input" << endl;
						}
					}
					cout << endl;
				}
			}
			else if (buyOrSell == 2) { // user selects to sell a stock
				stock1.setBuyOrSell(2);
				if (numOfShares <= 0) {
					cout << "You dont have anything to sell" << endl;
				}
				else if (numOfShares >= 0) {
					// Displays the stocks that have been bought
					cout << "Please select the stock you are going to sell " << endl;
					for (int i = 0; i < stocksBought.size(); i++) {
						cout << i << ": " << stocksBought[i] << " " << sharesBought[i] << endl;
					}
					cout << "Stock Selected: ";
					cin >> stockSelected;

					// assigns the proper market price to the stock that was chosen to sell
					for (int i = 0; i < marketPrice.size(); i++) {
						if (stocksBought[stockSelected] == stocksBought[i]) {
							stock2 = Trading(stocksBought[stockSelected], numOfShares, marketPrice[i]);
							stock2.setBuyOrSell(2);
							newStockPrice = stock2.showPrice(stocksBought[stockSelected]);
							break;
						}
					}

					// assigns the proper number of shares to the stock that was selected
					for (int i = 0; i < sharesBought.size(); i++) {
						if (stocksBought[stockSelected] == stocksBought[i]) {
							stock2.setNumOfShares(sharesBought[i]);
							break;
						}
					}

					// assigns the proper buy order type to the stock that was selected
					for (int i = 0; i < buyTypeOrder.size(); i++) {
						if (stocksBought[stockSelected] == stocksBought[i]) {
							stock2.setBuyOrderType(buyTypeOrder[i]);
							break;
						}
					}

					cout << "Please enter the number of shares: ";
					cin >> numOfShares;

					if (numOfShares > stock1.getNumOfShares()) {
						cout << "You dont have " << numOfShares << " please enter the correct number of shares next time." << endl;
						exit(0);
					}
					else {
						// Displays the info of the stock that is going to be sold
						stock2.showTrading(newStockPrice);

						cout << "Which order type do you want? Press 1 for market, 2 for limit: ";
						cin >> sellOrderType;

						if (sellOrderType == 1) { // users wants to sell the stock with a market order
							stock2.setSellOrderType(1);
							if (stock2.getBuyOrderType() == 1) {
								/*
								The stock was was selected was bought using a market order, and the user is going to
								sell the stock with a market order. The total profit/loss amount will be added to the users
								account. It will display the users account after a trade made, it will display the order,
								and it will display the users closed position.
								*/
								accountTotal = stock2.calcClosedPL(stocksBought[stockSelected], numOfShares, stock2.getPrice(), newStockPrice);
								stock2.accountInfo(accountSize, accountTotal, initialAccountBalance);
								accountSize = accountSize + accountTotal;
								stock2.orders(stocksBought[stockSelected], numOfShares, newStockPrice);
								stock2.positions(stocksBought[stockSelected], numOfShares, stock2.getPrice(), newStockPrice);
							}
							// Asigns the limit buy order to the stock that was selected
							else if (stock2.getBuyOrderType() == 2) {
								for (int i = 0; i < limitPrice.size(); i++) {
									if (stocksBought[stockSelected] == stocksBought[i]) {
										stock2 = Trading(stocksBought[stockSelected], numOfShares, limitPrice[i]);
										break;
									}
								}
								/*
								The stock that was selected to be sold was bought using a limit order. The user is going to sell
								the stock with a market order. The total profit/loss amount will be added to the user's
								account. Then it will display the users account value after the trade was made. It will also display
								the user's order and the user's closed position.
								*/
								accountTotal = stock2.calcClosedPL(stocksBought[stockSelected], numOfShares, buyLimitPrice, newStockPrice);
								stock2.accountInfo(accountSize, accountTotal, initialAccountBalance);
								stock2.orders(stocksBought[stockSelected], numOfShares, newStockPrice);
								stock2.positions(stocksBought[stockSelected], numOfShares, buyLimitPrice, newStockPrice);
							}
						}
						else if (sellOrderType == 2) { // user wants to sell the stock with a limit order
							stock2.setSellOrderType(2);
							cout << "Please enter the limit price which you want to sell: ";
							cin >> limitSellPrice;
							if (limitSellPrice <= 0) {
								cout << "Please enter a number near the range of the stock" << endl;
								exit(0);
							}
							else {
								if (stock2.getBuyOrderType() == 1) {
									/*
									The stock that was selected was to be sold was bought with a market order and will be sold with a limit
									order. The total profit/loss amount will be added to the user's account. It will displays the users account
									after the trade. It will also display the user's order and the user's closed position.
									*/
									accountTotal = stock2.calcClosedPL(stocksBought[stockSelected], numOfShares, limitSellPrice, stock2.getPrice());
									stock2.accountInfo(accountSize, accountTotal, initialAccountBalance);
									stock2.orders(stocksBought[stockSelected], numOfShares, limitSellPrice);
									stock2.positions(stocksBought[stockSelected], numOfShares, limitSellPrice, stock2.getPrice());
								}
								// Assigns the correct limit buy price to the stock that was selected to be sold
								else if (stock2.getBuyOrderType() == 2) {
									for (int i = 0; i < limitPrice.size(); i++) {
										if (stocksBought[stockSelected] == stocksBought[i]) {
											stock2 = Trading(stocksBought[stockSelected], numOfShares, limitPrice[i]);
											break;
										}
										stock2.setLimitSellPrice(limitPrice[i]);
									}
									/*
									The stock was was selected to be sold was bought with a limit order. The user wants to sell the stock
									with a limit order. It will then calculate the profit/loss and it will be added to the user's account.
									It will then display the users account after the trade. It will also display the user's order and the
									closed position.
									*/
									stock2.calcClosedPL(stocksBought[stockSelected], numOfShares, limitSellPrice, stock2.getLimtitSellPrice());
									stock2.accountInfo(accountSize, accountTotal, initialAccountBalance);
									stock2.orders(stocksBought[stockSelected], numOfShares, limitSellPrice);
									stock2.positions(stocksBought[stockSelected], numOfShares, limitSellPrice, stock2.getLimtitSellPrice());
								}
							}
						}
						else {
							cout << "Incorrect input" << endl;
						}
					}
				}
			}
			else {
				cout << "Incorrect input" << endl;
			}
		} while (true);
	}
	system("pause");
	return 0;
}
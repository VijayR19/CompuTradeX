#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>

// Define a struct to represent a stock or Bitcoin
struct Asset
{
    std::string symbol;
    double price;
};

// Define a class to represent a user's portfolio
class Portfolio
{
private:
    std::unordered_map<std::string, int> assets_; // Map of asset 0symbols to number of shares owned
    double balance_;                              // Cash balance in the account

public:
    // Constructor
    Portfolio(double balance)
    {
        balance_ = balance;
    }

    // Method to add an asset to the portfolio
    void addAsset(Asset asset, int shares)
    {
        // Check if the asset is already in the portfolio
        auto search = assets_.find(asset.symbol);
        if (search != assets_.end())
        {
            // If it is, update the number of shares owned
            search->second += shares;
        }
        else
        {
            // If it isn't, add a new entry to the map
            assets_.insert({asset.symbol, shares});
        }
        // Subtract the cost of the purchase from the balance
        balance_ -= shares * asset.price;
    }

    // Method to sell an asset from the portfolio
    void sellAsset(Asset asset, int shares)
    {
        // Check if the asset is in the portfolio
        auto search = assets_.find(asset.symbol);
        if (search != assets_.end())
        {
            // If the number of shares owned is greater than or equal to the number being sold,
            // update the number of shares owned and add the proceeds to the balance
            if (search->second >= shares)
            {
                search->second -= shares;
                balance_ += shares * asset.price;
            }
            else
            {
                std::cout << "Error: You do not own enough shares of " << asset.symbol << std::endl;
            }
        }
        else
        {
            std::cout << "Error: You do not own any shares of " << asset.symbol << std::endl;
        }
    }

    // Method to get the current market value of an asset in the portfolio
    double getAssetMarketValue(Asset asset)
    {
        // Check if the asset is in the portfolio
        auto search = assets_.find(asset.symbol);
        if (search != assets_.end())
        {
            // If it is, return the market value
            return search->second * asset.price;
        }
        else
        {
            // If it isn't, return 0
            return 0;
        }
    }

    // Getter method for the balance
    double getBalance()
    {
        return balance_;
    }
};

int main()
{
    // Define an Asset object for IBM with a price of $100.00
    Asset ibm = {"IBM", 100.00};

    // Define a Portfolio object with a cash balance of $1000.00
    Portfolio portfolio(1000.00);

    // Buy 10 shares of IBM
    portfolio.addAsset(ibm, 10);

    // Print the current market value of the IBM shares in the portfolio
    std::cout << "Market value of IBM shares in portfolio: $" << portfolio.getAssetMarketValue(ibm) << std::endl;

    // Sell 5 shares of IBM
    portfolio.sellAsset(ibm, 5);

    // Print the current market value of the IBM shares in the portfolio
    std::cout << "Market value of IBM shares in portfolio: $" << portfolio.getAssetMarketValue(ibm) << std::endl;

    return 0;
}

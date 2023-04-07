#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <vector>
#include <iomanip>

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

    
    // Method to display a summary of the user's portfolio
    void displaySummary(const std::vector<Asset> &assets)
    {
        std::cout << "Portfolio Summary:\n\n";
        std::cout << "Symbol\tShares\tMarket Value\n";
        std::cout << "------\t------\t------------\n";

        double total_value = balance_;

        for (const Asset &asset : assets)
        {
            auto search = assets_.find(asset.symbol);
            if (search != assets_.end())
            {
                double market_value = search->second * asset.price;
                total_value += market_value;
                std::cout << asset.symbol << "\t" << search->second << "\t$" << std::fixed << std::setprecision(2) << market_value << std::endl;
            }
        }

        std::cout << "\nCash Balance: $" << std::fixed << std::setprecision(2) << balance_ << std::endl;
        std::cout << "Total Portfolio Value: $" << std::fixed << std::setprecision(2) << total_value << std::endl;
    }
    
};
// Function to update asset prices
void updateAssetPrices(std::vector<Asset> &assets)
{
    // Simulate price changes by updating the prices with a random percentage change
    for (Asset &asset : assets)
    {
        double change = ((std::rand() % 1001) - 500) / 10000.0; // Random price change between -5% and 5%
        asset.price *= (1 + change);
    }
}


int main()
{
// Define Asset objects
    Asset ibm = {"IBM", 100.00};
    Asset btc = {"BTC", 30000.00};

    // Define a vector to store the assets
    std::vector<Asset> assets = {ibm, btc};

    // Define a Portfolio object with a cash balance of $1000.00
    Portfolio portfolio(1000.00);

    // Buy 10 shares of IBM
    portfolio.addAsset(ibm, 10);

    // Buy 0.01 shares of Bitcoin
    portfolio.addAsset(btc, 0.01);

    // Display the portfolio summary
    portfolio.displaySummary(assets);

    // Wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Update asset prices
    updateAssetPrices(assets);

    // Display the updated portfolio summary
    portfolio.displaySummary(assets);

    return 0;
}

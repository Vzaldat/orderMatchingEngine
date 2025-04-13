#ifndef TRADE_LOGGER_HPP
#define TRADE_LOGGER_HPP

#include <fstream>
#include <string>

class TradeLogger {
    public: 
        TradeLogger(const std::string& fileName) : file(fileName, std::ios::app){}

        void log(int quantity, double price, int buyId, int sellId){
            file << "TRADE: " << quantity << " @ " << price << " | Buy ID: " << buyId << ", Sell ID: "<< sellId <<"\n";
        }
    private:
        std::ofstream file;
};

#endif
#ifndef TRADE_LOGGER_HPP
#define TRADE_LOGGER_HPP

#include <fstream>
#include <string>

class TradeLogger {
    public: 
        TradeLogger(const std::string& fileName) : file(fileName, std::ios::app){
            if(!file.is_open()){
                throw std::runtime_error("Failed to open trade log file.");
            }
        }

        void log(int quantity, double price, int buyId, int sellId){
            file << "TRADE: " << quantity << " @ " << price << " | Buy ID: " << buyId << ", Sell ID: "<< sellId <<"\n";
            file.flush();
        }
        ~TradeLogger(){
            file.flush();
        }
    private:
        std::ofstream file;
};

#endif
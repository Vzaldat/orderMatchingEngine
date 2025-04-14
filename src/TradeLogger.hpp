#ifndef TRADE_LOGGER_HPP
#define TRADE_LOGGER_HPP

#include <fstream>
#include <string>
#include <deque>
#include <sstream>

struct TradeEvent {
    int quantity;
    double price;
    int buyId;
    int sellId;
    std::string toString() const{
        std::ostringstream oss;
        oss << quantity << " @ " << price << " | B: " << buyId << " | S: " << sellId;
        return oss.str();
    }
};

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
            if(trades.size() >= maxFeedSize)
                trades.pop_front();
            trades.push_back({quantity, price, buyId, sellId});
        }

        const std::deque<TradeEvent>&getTrades() const {return trades; }
        ~TradeLogger(){
            file.flush();
        }
    private:
        std::ofstream file;
        std::deque<TradeEvent> trades;
        const size_t maxFeedSize = 10;
};

#endif
#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <sstream>
#include "Order.hpp"

class InputHandler {
    public:
        static bool parse(const std::string &input, Order& Orderout){
            std::istringstream iss(input);
            std::string cmd, typeStr, sideStr;
            double price = 0.0;
            int quantity = 0;

            iss >> cmd >> typeStr >> sideStr;

            if(typeStr == "LIMIT"){
                iss >> price >> quantity;
                if(iss.fail()) return false;
            }
            else if(typeStr == "MARKET"){
                iss >> quantity;
                if(iss.fail()) return false;
            }
            else{
                return false;
            }

            OrderType type = (typeStr == "LIMIT") ? OrderType::LIMIT : OrderType::MARKET;
            OrderSide side = (sideStr == "BUY") ? OrderSide::BUY : OrderSide::SELL;

            Orderout = Order(type, side, price, quantity);
            return true;
        }
};

#endif
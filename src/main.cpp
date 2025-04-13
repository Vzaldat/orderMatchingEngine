#include <iostream>
#include "Order.hpp"
#include <string>
#include "InputHandler.hpp"
#include "OrderQueue.hpp"
#include "Orderbook.hpp"

int main(){
    OrderQueue queue;
    OrderBook book;
    std::string input;
    int orderId = 1;

    std::cout << "Enter order (e.g.,  'new LIMIT BUY 100.5 10' or 'new MARKET SELL 10'):\n";
    while(true) {
        std::getline(std::cin, input);
        if (input == "exit") break;

        if (input.rfind("new", 0) == 0){
            Order order(OrderType::LIMIT, OrderSide::BUY, 0.0, 0);
            if (InputHandler::parse(input, order)){
                // queue.push(order);
                // std::cout << "Order Accepted: ID = "<<order.id<<", Side = " 
                // << (order.side == OrderSide::BUY ? "BUY" : "SELL") 
                // << ", Quantity = "<<order.quantity<<
                // ", Price = "<<order.price<<"\n";

                std::cout << " Adding Order ID: "<< order.id << "\n";
                book.addOrder(order);
                orderId++;
            }
            else{
                std::cout << "Invalid order format \n";
            }
        }
        else{
            std::cout<<"Unknown command\n";
        }
    }
    return 0;
}
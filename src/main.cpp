#include <iostream>
#include "Order.hpp"
#include <string>
#include <ncurses.h>
#include "InputHandler.hpp"
#include "OrderQueue.hpp"
#include "Orderbook.hpp"
#include "NcursesUI.hpp"

int main(){
    // OrderQueue queue;
    // OrderBook book;
    // std::string input;
    // int orderId = 1;

    // std::cout << "Enter order (e.g.,  'new LIMIT BUY 100.5 10' or 'new MARKET SELL 10'):\n";
    // while(true) {
    //     std::getline(std::cin, input);
    //     if (input == "exit") break;
        
    //     if (input == "book"){
    //         book.printOrderBook();
    //         continue;
    //     }

    //     if (input.rfind("new", 0) == 0){
    //         Order order(OrderType::LIMIT, OrderSide::BUY, 0.0, 0);
    //         if (InputHandler::parse(input, order)){
    //             // queue.push(order);
    //             // std::cout << "Order Accepted: ID = "<<order.id<<", Side = " 
    //             // << (order.side == OrderSide::BUY ? "BUY" : "SELL") 
    //             // << ", Quantity = "<<order.quantity<<
    //             // ", Price = "<<order.price<<"\n";

    //             std::cout << " Adding Order ID: "<< order.id << "\n";
    //             book.addOrder(order);
    //             orderId++;
    //         }
    //         else{
    //             std::cout << "Invalid order format \n";
    //         }
    //     }
    //     else{
    //         std::cout<<"Unknown command\n";
    //     }
    // }
    OrderBook book;
    int OrderId = 1;

    NCursesUI::init();
    NCursesUI::setupColors();

    bool running = true;
    while(running) {
        NCursesUI::render(book.getBids(), book.getAsks(), book.getLogger().getTrades());

        int ch = getch();
        switch(ch) {
            case 'n': {
                echo();
                curs_set(1);
                char buf[100];
                mvprintw(0, 0, "Enter order (e.g., new LIMIT BUY 100 2): ");
                getnstr(buf, 100);
                noecho();
                curs_set(0);

                std::string input(buf);

                Order order(OrderType::LIMIT, OrderSide::BUY, 0.0, 0);
                if(InputHandler::parse(input, order)){
                    book.addOrder(order);
                }
                break;
            }

            case 'q':{
                running = false;
                break;
            }
        }
    }
    NCursesUI::shutdown();
    return 0;
}
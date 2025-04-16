#include <iostream>
#include "Order.hpp"
#include <string>
#include <ncurses.h>
#include "InputHandler.hpp"
#include "OrderQueue.hpp"
#include "Orderbook.hpp"
#include "NcursesUI.hpp"
#include <atomic>
#include <thread>
#include <mutex>

std::mutex uiMutex;

void matchingThreadFunc(OrderQueue& queue, OrderBook& book){
    int ordersProcessed = 0;
    auto startTime = std::chrono::high_resolution_clock::now();

    while(true){
        Order order = queue.pop();
        if(order.id == -1)break;
        auto start = std::chrono::high_resolution_clock::now();
        book.addOrder(order);
        auto end = std::chrono::high_resolution_clock::now();

        auto latency = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "[Latency] Order " << order.id << " matched in " << latency << " ms\n";

        ordersProcessed++;
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

        if(elapsed >= 1){
            std::cout << "[Throughput] " << ordersProcessed << " orders/sec\n";
            ordersProcessed = 0;
            startTime = now;
        }
    }
}

void inputThreadFunc(OrderQueue & queue, std::atomic<bool>& running){
    while(running) {
        int ch = getch();
        switch(ch) {
            case 'n': {
                std::lock_guard<std::mutex> lock(uiMutex);
                echo();
                curs_set(1);
                char buf[100];
                mvprintw(0, 0, "Enter order (e.g., new LIMIT BUY 100 2): ");
                clrtoeol();
                getnstr(buf, 100);
                noecho();
                curs_set(0);

                std::string input(buf);

                Order order(OrderType::LIMIT, OrderSide::BUY, 0.0, 0);
                if(InputHandler::parse(input, order)){
                    queue.push(order);
                }
                else{
                    mvprintw(0, 0, "Invalid input");
                    clrtoeol();
                }
                break;
            }

            case 'q':{
                running = false;
                queue.push(Order(OrderType::LIMIT, OrderSide::BUY, 0, 0));
                break;
            }

        } 
    }
}


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
    // bool run = true;
    std::atomic<bool> running(true);
    OrderQueue queue;
    OrderBook book;
    int OrderId = 1;
    int ordersProcessed = 0;
    NCursesUI::init();
    NCursesUI::setupColors();
    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread matcher(matchingThreadFunc, std::ref(queue), std::ref(book));
    std::thread input(inputThreadFunc, std::ref(queue), std::ref(running));

    while(running) {
        NCursesUI::render(book.getBids(), book.getAsks(), book.getLogger().getTrades());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));    
    }
    input.join();
    matcher.join();

    NCursesUI::shutdown();
    return 0;
}
#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include <deque>
#include <iostream>
#include "Order.hpp"

class OrderBook{
    public:
        void addOrder(const Order& order) {
            if(order.side == OrderSide::BUY){
                match(order, asks_, bids_, OrderSide::SELL);
            }
            else{
                match(order, bids_, asks_, OrderSide::BUY);
            }
        }
    
    private:
        std::map<double, std::deque<Order>> bids_;
        std::map<double, std::deque<Order>> asks_;

        void match(Order incoming, std::map<double, std::deque<Order>> &oppositeBook, std::map<double, std::deque<Order>> &ownBook, OrderSide oppSide){
            // auto it = (incoming.side == OrderSide::BUY) ? oppositeBook.begin() : std::map<double, std::deque<Order>>::reverse_iterator();
            if(incoming.side != OrderSide::BUY){
                auto it = oppositeBook.begin();
                while(incoming.quantity > 0 && it != oppositeBook.end()){
                    bool isPriceMatch = (incoming.side == OrderSide::BUY) ? it->first <= incoming.price || incoming.type == OrderType::MARKET : it->first >= incoming.price || incoming.type == OrderType::MARKET;
                    if(!isPriceMatch) break;
    
                    auto &queue = it->second;
    
                    while(!queue.empty() && incoming.quantity > 0){
                        Order &top = queue.front();
                        int tradeQuantity = std::min(incoming.quantity, top.quantity);
    
                        std::cout << "[TRADE] " << tradeQuantity << " @ " << top.price << " | Buy ID: "
                         << (incoming.side == OrderSide::BUY ? incoming.id : top.id) << " , Sell ID: " <<( incoming.side == OrderSide::SELL ? incoming.id : top.id)<<"\n";
                        
                        
                        top.quantity -= tradeQuantity;
                        incoming.quantity -= tradeQuantity;
                        if (top.quantity == 0) queue.pop_front();
                    }
    
                    if(queue.empty()){
                        // if(incoming.side == OrderSide::BUY)
                        //     oppositeBook.erase(it++);
                        // else{
                        //     auto rev = std::next(it).base();
                        //     oppositeBook.erase(rev);
                        //     it = std::make_reverse_iterator(rev);
                        // }
                        it = oppositeBook.erase(it);
                    }
                    else{
                        break;
                    }
    
                }
        }
        else{
            auto it = oppositeBook.rbegin();
            while(incoming.quantity > 0 && it !=oppositeBook.rend()){
                bool isPriceMatch = (incoming.side == OrderSide::BUY) ? it->first <= incoming.price || incoming.type == OrderType::MARKET : it->first >= incoming.price || incoming.type == OrderType::MARKET;
                if(!isPriceMatch) break;

                auto &queue = it->second;

                while(!queue.empty() && incoming.quantity > 0){
                    Order &top = queue.front();
                    int tradeQuantity = std::min(incoming.quantity, top.quantity);

                    std::cout << "[TRADE] " << tradeQuantity << " @ " << top.price << " | Buy ID: "
                    << (incoming.side == OrderSide::BUY ? incoming.id : top.id) << " , Sell ID: " <<( incoming.side == OrderSide::SELL ? incoming.id : top.id)<<"\n";
                    
                    
                    top.quantity -= tradeQuantity;
                    incoming.quantity -= tradeQuantity;
                    if (top.quantity == 0) queue.pop_front();
                }

                if(queue.empty()){
                    auto toerase = std::next(it).base();
                    oppositeBook.erase(toerase);
                    it = std::make_reverse_iterator(toerase);
                }
                else{
                    break;
                }
            }
            if(incoming.quantity > 0 && incoming.type == OrderType::LIMIT){
                ownBook[incoming.price].push_back(incoming);
            }
        }    
    }
};

#endif
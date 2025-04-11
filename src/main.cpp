#include <iostream>
#include "Order.hpp"

int main(){
    Order order1(1, OrderType::LIMIT, OrderSide::BUY, 100.5, 10);
    std::cout<<"Order created: ID = "<<order1.id<<", Side = " << (order1.side == OrderSide::BUY ? "Buy":"Sell")<<", Price = " << order1.price << ", Quantity = "<<order1.quantity<<std::endl;

    return 0;
}
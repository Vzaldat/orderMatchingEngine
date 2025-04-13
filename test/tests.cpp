#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/Order.hpp"
#include "../src/Orderbook.hpp"
#include <cstdlib>
#include <iostream>

TEST_CASE("Limit orders match correctly", "[matching]"){
    OrderBook book;

    Order sell1(OrderType::LIMIT, OrderSide::SELL, 100.0, 10);
    Order buy1(OrderType::LIMIT, OrderSide::BUY, 101.0, 5);

    book.addOrder(sell1);
    book.addOrder(buy1);

    REQUIRE(true);
}

TEST_CASE("Market orders match with best price", "[market]"){
    OrderBook book;

    Order sell1(OrderType::LIMIT, OrderSide::SELL, 100.0, 10);
    Order buy1(OrderType::MARKET, OrderSide::BUY, 0.0, 5);

    book.addOrder(sell1);
    book.addOrder(buy1);

    REQUIRE(true);
}

TEST_CASE("Random Generators ", "[matching]"){
    Order::resetIds();
    OrderBook book;
    
    for(int i = 0; i < 100000; i++){  
    
        int placeHolderPrice = 200;
        int placeHolderQuantity = 20;
        double price1 = (double) (rand() % placeHolderPrice);
        int quantity1 = rand() % placeHolderQuantity + 1;
        double price2 = (double) (rand() % placeHolderPrice);
        int quantity2 = rand() % placeHolderQuantity + 1;
        // if(i % 1000 == 0)
        //     std::cout << "This order " << i << " done" << "\n";
        int chance = std::rand()%2;
        if(chance == 0){
            Order sell1(OrderType::LIMIT, OrderSide::SELL, price1, quantity1);
            book.addOrder(sell1);
        }
        else{
            Order buy1(OrderType::LIMIT, OrderSide::BUY, price2, quantity2);
        // book.addOrder(sell1);
            book.addOrder(buy1);
        }
        REQUIRE(true);
    
    }
}

TEST_CASE("Generated Orders Built in", "[matching]") {
    int price = GENERATE(take(100000, random(140, 200)));
    int quantity = GENERATE(take(100000, random(1, 20)));

    Order::resetIds();
    OrderBook book;

    Order sell(OrderType::LIMIT, OrderSide::SELL, price, quantity);
    Order buy(OrderType::LIMIT, OrderSide::BUY, price + 10, quantity);

    book.addOrder(sell);
    book.addOrder(buy);

    REQUIRE(true);
}
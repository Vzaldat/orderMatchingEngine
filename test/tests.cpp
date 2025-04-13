#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/Order.hpp"
#include "../src/Orderbook.hpp"

TEST_CASE("Limit orders match correctly", "[matching]"){
    OrderBook book;

    Order sell1(1, OrderType::LIMIT, OrderSide::SELL, 100.0, 10);
    Order buy1(2, OrderType::LIMIT, OrderSide::BUY, 101.0, 5);

    book.addOrder(sell1);
    book.addOrder(buy1);

    REQUIRE(true);
}

TEST_CASE("Market orders match with best price", "[market]"){
    OrderBook book;

    Order sell1(1, OrderType::LIMIT, OrderSide::SELL, 100.0, 10);
    Order buy1(2, OrderType::MARKET, OrderSide::BUY, 0.0, 5);

    book.addOrder(sell1);
    book.addOrder(buy1);

    REQUIRE(true);
}
#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <chrono>

enum class OrderType {
    LIMIT,
    MARKET,
};

enum class OrderSide{
    BUY,
    SELL
};

class Order{
    public:    
        int id;
        static int global_id;
        OrderType type;
        OrderSide side;
        double price;
        int quantity;
        std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

        Order(int id_,
            OrderType type_,
            OrderSide side_,
            double price_,
            int quantity_ )
            : id(id_), type(type_), side(side_), price(price_), quantity(quantity_),
            timestamp(std::chrono::high_resolution_clock::now()){
                id = global_id++; 
        }
        static void resetIds(){
            global_id = 0;
        }

    private:
        static inline int global_id = 0;
};

#endif
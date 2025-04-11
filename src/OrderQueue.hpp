#ifndef ORDER_QUEUE_HPP
#define ORDER_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Order.hpp"

class OrderQueue{
    public:
        void push(const Order &order){
            std::lock_guard<std::mutex> lock(mtx_);
            queue_.push(order);
            cond_var_.notify_one();
        }
        Order pop(){
            std::unique_lock<std::mutex> lock(mtx_);
            cond_var_.wait(lock, [this]() { return !queue_.empty(); });
            Order orderOut = queue_.front();
            queue_.pop();
            return orderOut;
        }
        bool empty(){
            std::lock_guard<std::mutex> lock(mtx_);
            return queue_.empty();
        }
    private:
        std::queue<Order> queue_;
        std::mutex mtx_;
        std::condition_variable cond_var_;
};

#endif
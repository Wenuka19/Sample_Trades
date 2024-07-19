#pragma once

#include "Order.h"
#include <map>
#include <unordered_map>
#include <list>

class OrderBook{
    private:
        OrderBook();
        struct OrderEntry{
            OrderPointer order_{nullptr};
            std::list<OrderPointer>::iterator location_;
        };
        static OrderBook* orderBook;

        std::map<Price, std::list<OrderPointer>, std::greater<Price>> bids_;
        std::map<Price, std::list<OrderPointer>, std::less<Price>> asks_;
        std::unordered_map<OrderId, OrderEntry> orders_;

    public:
        OrderBook(const OrderBook& ob) =  delete;     

        static OrderBook* getOrderBook(){
           if (orderBook == NULL) {
            orderBook = new OrderBook(); 
            return orderBook; 
        }
            else{
                return orderBook;
            }
        }

        void processOrder(OrderPointer order);
        void insertOrder(OrderPointer newOrder);
        void cancelOrder(OrderId orderId);


};

OrderBook* orderBook = NULL; 
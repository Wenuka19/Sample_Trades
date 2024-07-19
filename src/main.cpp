#include <iostream>
#include "OrderBook.h"

int main(){
    OrderBook* oderBook = OrderBook::getOrderBook();
    orderBook->processOrder(std::make_shared<Order>("ABC123",Side::Buy,100,10));
    orderBook->processOrder(std::make_shared<Order>("ABC125",Side::Buy,300,20));
    orderBook->processOrder(std::make_shared<Order>("ABC123",Side::Sell,200,5));
}
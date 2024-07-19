#include "OrderBook.h"
#include "Side.h"

void OrderBook::processOrder(OrderPointer order){
    if (order->GetSide()==Side::Buy){
        while(true){
            if (bids_.empty()) break;
            auto& [bidPrice, bids] = *bids_.begin();
            if (bidPrice >= order->GetPrice()) break;
            
            while (bids.size() && order->GetRemainingQuantity()>=0){
                auto& bid = bids.front();
                Quantity quantity = std::min(bid->GetRemainingQuantity(),order->GetRemainingQuantity());
                bid->Fill(quantity);
                order->Fill(quantity);

                if(bid->IsFilled()){
                    bids.pop_front();
                    orders_.erase(bid->GetOrderId());
                }

                if(bids.empty()){
                    bids_.erase(bidPrice);
                }
                //TODO : IMPLEMENT TRADE ADDITION
            }   
        }
        if (order->GetRemainingQuantity()){
            insertOrder(order);
        }
    }else{
        while(true){
            if (asks_.empty()) break;
            auto& [askPrice, asks] = *asks_.begin();
            if (askPrice <= order->GetPrice()) break;
            while (asks.size() && order->GetRemainingQuantity()>=0){
                auto& ask = asks.front();
                Quantity quantity = std::min(ask->GetRemainingQuantity(),order->GetRemainingQuantity());
                ask->Fill(quantity);
                order->Fill(quantity);

                if(ask->IsFilled()){
                    asks.pop_front();
                    orders_.erase(ask->GetOrderId());
                }
                if(asks.empty()){
                    asks_.erase(askPrice);
                }
                //TODO : IMPLEMENT TRADE ADDITION
            }   
        }
        if (order->GetRemainingQuantity()){
            insertOrder(order);
        }
    }

}

void OrderBook::insertOrder(OrderPointer newOrder){
    if (orders_.find(newOrder->GetOrderId())== orders_.end()){
        return;
    }

    std::list<OrderPointer>::iterator iter;

    if (newOrder->GetSide()==Side::Buy){
        auto& orders = asks_[newOrder->GetPrice()];
        orders.push_back(newOrder);
        iter = std::next(orders.begin(),orders.size()-1);
    }else{
        auto& orders = bids_[newOrder->GetPrice()];
        orders.push_back(newOrder);
        iter = std::next(orders.begin(),orders.size()-1);
    }
    orders_.insert({newOrder->GetOrderId(),OrderEntry{newOrder,iter}});
}

void OrderBook::cancelOrder(OrderId orderId){

}
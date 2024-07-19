#pragma once


#include "Aliases.h"
#include "Side.h"
#include <stdexcept>
#include <memory>


class Order{
    public:
        Order(OrderId orderId, Side side, Price price,Quantity quantity)
        : orderId_ {orderId}
        , side_ {side}
        , price_ {price}
        , quantity_ {quantity}
        , initialQuantity_{ quantity }
        , remainingQuantity_{ quantity }
        {

        }

        OrderId GetOrderId() const { return orderId_; }
        Side GetSide() const { return side_; }
        Price GetPrice() const { return price_; }
        Quantity GetInitialQuantity() const { return initialQuantity_; }
        Quantity GetRemainingQuantity() const { return remainingQuantity_; }
        Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
        
        bool IsFilled() const { return GetRemainingQuantity() == 0; }

        void Fill(Quantity quantity)
        {
            if (quantity > GetRemainingQuantity())
                throw std::logic_error("Orders cannot be filled for more than its remaining quantity.");

            remainingQuantity_ -= quantity;
        }
        
    private:
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity quantity_;
        Quantity initialQuantity_;
        Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
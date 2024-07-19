#pragma once

#include "Aliases.h"
#include "Side.h"

class Trade{
    public:
        Trade(OrderId orderId, Side side, Quantity quantity,Price price)
        : orderId_{orderId}
        , side_{side}
        , quantity_{quantity}
        , price_{price}
        {}

    private:
        OrderId orderId_;
        Side side_;
        Quantity quantity_;
        Price price_;
};
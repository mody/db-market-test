#pragma once

#include "commodity.h"
#include "price.h"

#include <map>
#include <variant>
#include <vector>

namespace market {

class Market
{
    std::multimap<Price, Commodity> listing_;

public:
    void sell(Commodity commodity, Price price_per_unit);

    using Item = std::pair<Commodity, Price>;
    std::vector<Item> buy(const Commodity& commodity, const Price max_price_per_unit);
};


}  // namespace market

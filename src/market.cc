#include "market.h"

namespace market {

void Market::sell(Commodity commodity, Price price_per_unit)
{
    if (price_per_unit.value() > 0.f) {
        listing_.insert({std::move(price_per_unit), std::move(commodity)});
    }
}

std::vector<Market::Item> Market::buy(const Commodity& commodity, const Price max_price_per_unit)
{
    std::vector<Market::Item> result;

    auto requested = commodity.amount();
    if (requested <= 0) {
        return result;
    }

    const auto from = listing_.lower_bound(max_price_per_unit.zero());
    const auto to = listing_.upper_bound(max_price_per_unit);
    if (from == to) {
        return result;
    }

    for (auto it = from; it != to; ++it) {
        Commodity& c = it->second;
        if (c.type() != commodity.type()) {
            continue;
        }

        Commodity&& bought = c.substract(requested);
        requested -= bought.amount();
        result.push_back({std::move(bought), it->first});

        if (requested == 0) {
            break;
        }
    }

    for (auto it = from; it != to;) {
        const Commodity& c = it->second;
        if (c.type() != commodity.type()) {
            continue;
        }
        if (c.amount() == 0) {
            auto d = it++;
            listing_.erase(d);
        } else {
            ++it;
        }
    }

    return result;
}

}  // namespace market

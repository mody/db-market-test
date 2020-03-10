#pragma once

#include <cstdlib>
#include <ostream>

namespace market {

enum class Currency
{
    EUR = 0,
    USD = 1
};

struct Price {
    Price(Currency currency, float value)
        : currency_ {currency}
        , value_ {value}
    {}

    bool operator<(const Price& rhs) const
    {
        return currency_ == rhs.currency_ ? value_ < rhs.value_ : currency_ < rhs.currency_;
    };

    bool operator==(const Price& rhs) const
    {
        return currency_ == rhs.currency_ && value_ == rhs.value_;
    };

    float value() const {
        return value_;
    }

    Price zero() const {
        return Price(currency_, 0.);
    }

    friend std::ostream& operator<<(std::ostream& os, const Price& t);
private:
    Currency currency_;
    float value_;
};

Price operator "" _USD(const char* p);
Price operator "" _EUR(const char* p);


}  // namespace market

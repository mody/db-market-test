#include "price.h"

namespace market {

Price operator "" _USD(const char* p)
{
    float val = 0.;
    if (p) {
        val = std::strtof(p, nullptr);
    }
    return Price(Currency::USD, val);
}

Price operator "" _EUR(const char* p)
{
    float val = 0.;
    if (p) {
        val = std::strtof(p, nullptr);
    }
    return Price(Currency::EUR, val);
}


std::ostream& operator<<(std::ostream& os, const Price& t) {
    switch(t.currency_) {
    case Currency::EUR:
        os << t.value_ << "EUR";
        break;
    case Currency::USD:
        os << "$" << t.value_;
        break;
    }
    return os;
}

}  // namespace market

#include "commodity.h"

namespace market {

std::ostream& operator<<(std::ostream& os, const Commodity::Type& t)
{
    switch (t) {
    case Commodity::Type::COW: os << "COW"; break;
    case Commodity::Type::ORANGE: os << "ORANGE"; break;
    default: os << "-invalid-";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Commodity& c)
{
    os << c.type() << "\t" << c.amount();
    return os;
}

}  // namespace market

#pragma once

#include <memory>
#include <ostream>
#include <variant>

namespace market {

class Commodity
{
public:
    using Amount = unsigned int;

    enum class Type
    {
        COW,
        ORANGE
    };

    static Commodity make_cows(Amount heads_count) {
        return Commodity(Type::COW, heads_count);
    }

    static Commodity make_oranges(Amount weight) {
        return Commodity(Type::ORANGE, weight);
    }

    Type type() const {
        return type_;
    }

    Amount amount() const {
        return amount_;
    }

    Commodity substract(Amount amount) {
        auto requested = std::min(amount, amount_);
        auto result = Commodity(type_, requested);
        amount_ -= requested;
        return result;
    }

    bool operator== (const Commodity& rhs) const {
        return type_ == rhs.type_ && amount_ == rhs.amount_;
    }

private:
    Commodity(Type type, unsigned int unit_count)
        : type_ {type}
        , amount_ {unit_count}
    {}

    Type type_;
    Amount amount_;
};


std::ostream& operator<<(std::ostream& os, const Commodity::Type& t);
std::ostream& operator<<(std::ostream& os, const Commodity& c);

}  // namespace market

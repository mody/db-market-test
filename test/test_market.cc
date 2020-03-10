#define BOOST_TEST_MODULE test_market

#include <market.h>

#include <boost/test/included/unit_test.hpp>

using namespace market;

BOOST_AUTO_TEST_CASE(test_empty)
{
    Market m;
}

BOOST_AUTO_TEST_CASE(test_price)
{
    auto ten_eur = 10_EUR;
    auto cent_eur = 0.1_EUR;
    BOOST_CHECK(cent_eur < ten_eur);

    auto five_usd = 5_USD;
    auto quater_usd = 0.25_USD;
    BOOST_CHECK(quater_usd < five_usd);
}

BOOST_AUTO_TEST_CASE(test_commodity)
{
    auto ten_cows = Commodity::make_cows(10);
    BOOST_CHECK_EQUAL(ten_cows.type(), Commodity::Type::COW);
    BOOST_CHECK_EQUAL(ten_cows.amount(), 10);
    BOOST_CHECK_EQUAL(ten_cows, Commodity::make_cows(10));

    auto oranges = Commodity::make_oranges(1000);
    BOOST_CHECK_EQUAL(oranges.type(), Commodity::Type::ORANGE);
    BOOST_CHECK_EQUAL(oranges.amount(), 1000);

    auto one_less_cow = ten_cows.substract(1);
    BOOST_CHECK_EQUAL(one_less_cow.type(), Commodity::Type::COW);
    BOOST_CHECK_EQUAL(one_less_cow.amount(), 1);
    BOOST_CHECK_EQUAL(ten_cows.amount(), 9);
    BOOST_CHECK_NE(ten_cows, Commodity::make_cows(10));

    auto rest_of_cows = ten_cows.substract(100);
    BOOST_CHECK_EQUAL(rest_of_cows.type(), Commodity::Type::COW);
    BOOST_CHECK_EQUAL(rest_of_cows.amount(), 9);
    BOOST_CHECK_EQUAL(ten_cows.amount(), 0);

    auto one_less_orange = oranges.substract(1000);
    BOOST_CHECK_EQUAL(one_less_orange.type(), Commodity::Type::ORANGE);
    BOOST_CHECK_EQUAL(one_less_orange.amount(), 1000);
    BOOST_CHECK_EQUAL(oranges.amount(), 0);
}

BOOST_AUTO_TEST_CASE(test_market1)
{
    Market m;

    const auto one_cow = Commodity::make_cows(1);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 1_EUR);

    const auto r1 = m.buy(one_cow, 3_EUR);
    BOOST_REQUIRE_EQUAL(1, r1.size());
    const auto& [c1, p1] = r1.at(0);
    BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
    BOOST_REQUIRE_EQUAL(c1.amount(), 1);
    BOOST_REQUIRE_EQUAL(p1, 1_EUR);
}

BOOST_AUTO_TEST_CASE(test_market2)
{
    Market m;

    const auto one_cow = Commodity::make_cows(1);
    m.sell(one_cow, 0_EUR);
    m.sell(one_cow, 0_EUR);

    const auto r1 = m.buy(one_cow, 3_EUR);
    BOOST_REQUIRE_EQUAL(0, r1.size());
}

BOOST_AUTO_TEST_CASE(test_market3)
{
    Market m;

    const auto one_cow = Commodity::make_cows(1);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 2_EUR);
    m.sell(one_cow, 3_EUR);
    m.sell(one_cow, 4_EUR);
    m.sell(one_cow, 5_EUR);

    {
        const auto r1 = m.buy(one_cow, 3_EUR);
        BOOST_REQUIRE_EQUAL(1, r1.size());
        const auto& [c1, p1] = r1.at(0);
        BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c1.amount(), 1);
        BOOST_REQUIRE_EQUAL(p1, 1_EUR);
    }

    const auto r2 = m.buy(one_cow, 1_EUR);
    BOOST_REQUIRE_EQUAL(0, r2.size());

    {
        const auto r3 = m.buy(Commodity::make_cows(2), 4_EUR);
        BOOST_REQUIRE_EQUAL(2, r3.size());
        const auto& [c1, p1] = r3.at(0);
        BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c1.amount(), 1);
        BOOST_REQUIRE_EQUAL(p1, 2_EUR);

        const auto& [c2, p2] = r3.at(1);
        BOOST_REQUIRE_EQUAL(c2.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c2.amount(), 1);
        BOOST_REQUIRE_EQUAL(p2, 3_EUR);
    }

    const auto r4 = m.buy(one_cow, 1_EUR);
    BOOST_REQUIRE_EQUAL(0, r4.size());

    const auto r5 = m.buy(one_cow, 5_USD);
    BOOST_REQUIRE_EQUAL(0, r5.size());
}

BOOST_AUTO_TEST_CASE(test_market_currencies)
{
    Market m;

    const auto one_cow = Commodity::make_cows(1);
    m.sell(one_cow, 3_EUR);
    m.sell(one_cow, 2_EUR);
    m.sell(one_cow, 1_EUR);
    m.sell(one_cow, 1_USD);
    m.sell(one_cow, 2_USD);

    {
        const auto r1 = m.buy(one_cow, 3_EUR);
        BOOST_REQUIRE_EQUAL(1, r1.size());
        const auto& [c1, p1] = r1.at(0);
        BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c1.amount(), 1);
        BOOST_REQUIRE_EQUAL(p1, 1_EUR);
    }

    {
        const auto r2 = m.buy(one_cow, 3_USD);
        BOOST_REQUIRE_EQUAL(1, r2.size());
        const auto& [c1, p1] = r2.at(0);
        BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c1.amount(), 1);
        BOOST_REQUIRE_EQUAL(p1, 1_USD);
    }

    const auto r3 = m.buy(one_cow, 1_USD);
    BOOST_REQUIRE_EQUAL(0, r3.size());

    {
        const auto r4 = m.buy(one_cow, 3_USD);
        BOOST_REQUIRE_EQUAL(1, r4.size());
        const auto& [c1, p1] = r4.at(0);
        BOOST_REQUIRE_EQUAL(c1.type(), Commodity::Type::COW);
        BOOST_REQUIRE_EQUAL(c1.amount(), 1);
        BOOST_REQUIRE_EQUAL(p1, 2_USD);
    }

    const auto r5 = m.buy(one_cow, 3_USD);
    BOOST_REQUIRE_EQUAL(0, r5.size());
}

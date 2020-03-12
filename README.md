### Market library exercise

Design and implement a Market library for trading animals, fruit all under one roof.

Public interface example ( pseudo code ):

```
Class Market
{
public:
     Item Buy(ItemType , price);
     void Sell(“What is being sold”, price);

};
```

Assumptions:
- Animals are traded for price per head ( example 1 cow sells for 125.25$ )
- Fruit is traded with price per kilo ( 1kg of Oranges sells for 10.70$ )
- Other currencies should be also possible , but limit the tests to Dollar and Euro
- For the sake of exercise it’s enough to focus on 2 examples in unit tests

### Implementation

#### Market

Stores sell offers ordered by _price-per-unit_, different currencies are sorted separately within the same container.
_Sell_ always succeeds, _buy_ tries to fulfill the order from the lowest price up to the max price and up to the requested amount of the _buy_ request.

#### Commodities

Only _cows_ and _oranges_ are implemented.

#### Currencies

Only _EUR_ and _USD_ are implemented.

No currency conversion. Didn't make sense. Should be handled outside of the _Market_.

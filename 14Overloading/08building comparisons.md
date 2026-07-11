# Building Comparisons from `<`

You do not need to hand-write every relational operator. Implement **`==`** and **`<`**, then derive the rest with clear logic.

## The six operators

| Operator | Typical definition from `<` and `==` |
|----------|--------------------------------------|
| `==` | Direct equality |
| `!=` | `!(a == b)` |
| `<` | Direct less-than |
| `>` | `b < a` |
| `<=` | `!(b < a)` |
| `>=` | `!(a < b)` |

```cpp
#include <iostream>

class Score
{
public:
    Score(int value)
        : value_{value}
    {
    }

    int value() const { return value_; }

    bool operator==(const Score& other) const
    {
        return value_ == other.value_;
    }

    bool operator!=(const Score& other) const
    {
        return !(*this == other);
    }

    bool operator<(const Score& other) const
    {
        return value_ < other.value_;
    }

    bool operator>(const Score& other) const
    {
        return other < *this;
    }

    bool operator<=(const Score& other) const
    {
        return !(other < *this);
    }

    bool operator>=(const Score& other) const
    {
        return !(*this < other);
    }

private:
    int value_{};
};

int main()
{
    Score a{10};
    Score b{20};

    std::cout << std::boolalpha
              << (a < b) << ' '
              << (a <= b) << ' '
              << (a > b) << ' '
              << (a >= b) << ' '
              << (a == a) << ' '
              << (a != b) << '\n';
    return 0;
}
```

> PREFERENCE: Define **`==`** and **`<`** with real meaning. Define **`!=` `>` `<=` `>=`** as combinations so they stay consistent.

## C++20: `operator<=>`

Modern C++ offers **`operator<=>`** (the “spaceship” operator) to generate comparisons automatically. This book focuses on explicit operators first; when you adopt C++20, look up `std::strong_ordering` and `= default` for comparisons.

## Consistency rule

If `a == b`, then `a < b` and `b < a` should both be false. If `a < b`, then `b < a` should be false. Broken comparisons confuse `sort` and `set`.

## Try it now

### Exercise 1: Which pairs are enough?

Prompt: You want all six operators (`==`, `!=`, `<`, `>`, `<=`, `>=`). You will write **real logic** for only **two**, then derive the other four. Which of these pairs is enough?

1. `==` and `<`
2. `==` and `!=`
3. `<` and `>`
4. `<=` and `>=`
5. `==` and `>`
6. `<` and `<=`

:::details Answer

| Pair | Enough? | Why |
|------|---------|-----|
| `==` and `<` | **Yes** | Canonical pair in this section: `!=` from `==`; `>`, `<=`, `>=` from `<` |
| `==` and `!=` | **No** | Equality only; no ordering to build `<`, `>`, `<=`, or `>=` |
| `<` and `>` | **Yes** | `==` when neither is less; `!=` from `==`; `<=` and `>=` from `<` and `>` |
| `<=` and `>=` | **Yes** | `==` when both hold both ways; `<` and `>` from strict cases; `!=` from `==` |
| `==` and `>` | **Yes** | Mirror of `==` and `<`: swap operands when deriving `<` |
| `<` and `<=` | **Yes** | `<=` overlaps `<`; use both to recover `==`, then `!=`, `>`, `>=` |

> PREFERENCE: **`==` and `<`** remain the usual choice: clearest meaning and matches the table at the top of this section.

:::

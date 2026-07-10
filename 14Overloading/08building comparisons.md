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

### Exercise 1: Derive `>`

Prompt: `a > b` is implemented as `b < a`. Why swap the operands?

:::details Answer

**`<`** means “left is less than right.” “`a` greater than `b`” is the same as “`b` less than `a`.”

:::

### Exercise 2: Minimal set

Prompt: Which two operators must you define with real logic before deriving the other four?

:::details Answer

**`==`** and **`<`** (as in the table above).

:::

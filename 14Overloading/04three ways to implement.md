# Three Ways to Implement Operators

For a class you control, there are three common patterns:

1. **Member function**: defined inside the class
2. **Friend function**: declared inside the class, defined outside
3. **Normal (free) function**: no `friend`, uses public interface only

Same `Fraction` type, three styles for `operator+`:

## Member function

The left operand is `*this`. Only works when **your class** is on the **left**.

```cpp
#include <iostream>

class Fraction
{
public:
    Fraction(int num, int den)
        : numerator{num}
        , denominator{den}
    {
    }

    Fraction operator+(const Fraction& other) const
    {
        return Fraction{
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator};
    }

private:
    int numerator{};
    int denominator{};
};

int main()
{
    Fraction a{1, 2};
    Fraction b{1, 3};
    Fraction c{a + b};
    std::cout << c.numerator << '/' << c.denominator << '\n';
    return 0;
}
```

`a + b` becomes `a.operator+(b)`.

## Friend function

Needs access to **private** members, but the left operand is **not** your class (or you want a symmetric binary form defined outside).

```cpp
#include <iostream>

class Fraction
{
    friend Fraction operator+(const Fraction& left, const Fraction& right);

public:
    Fraction(int num, int den)
        : numerator{num}
        , denominator{den}
    {
    }

private:
    int numerator{};
    int denominator{};
};

Fraction operator+(const Fraction& left, const Fraction& right)
{
    return Fraction{
        left.numerator * right.denominator + right.numerator * left.denominator,
        left.denominator * right.denominator};
}

int main()
{
    Fraction a{1, 2};
    Fraction b{1, 3};
    std::cout << (a + b).numerator << '\n';
    return 0;
}
```

> NOTE: `friend` grants one function access to private members. See also [Friend Functions](../12Classes/20friend%20functions.md).

## Normal free function

Works when **public** getters (or public fields) expose enough data:

```
#include <iostream>

class Fraction
{
public:
    Fraction(int num, int den)
        : numerator{num}
        , denominator{den}
    {
    }

    int num() const { return numerator; }
    int den() const { return denominator; }

private:
    int numerator{};
    int denominator{};
};

Fraction operator+(const Fraction& left, const Fraction& right)
{
    return Fraction{
        left.num() * right.den() + right.num() * left.den(),
        left.den() * right.den()};
}
```

> PREFERENCE: Prefer a **normal free function** when public accessors are enough. Use **member** when the left operand is your class and the operation is clearly a member responsibility. Use **friend** when you need private access and a member does not fit (common for `operator<<`).

## Try it now

### Exercise 1: Left operand

Prompt: Can `operator<<` be a member of `Point` with `std::cout << p`?

:::details Answer

**No.** The left operand is `std::cout` (`std::ostream`), not `Point`. `operator<<` is almost always a **free** or **friend** function.

:::

### Exercise 2: Private fields

Prompt: `Fraction` has private `numerator` and `denominator` and no getters. Which styles can implement `operator+` without adding getters?

:::details Answer

**Member** (inside `Fraction`) or **friend** (free function granted access).

:::

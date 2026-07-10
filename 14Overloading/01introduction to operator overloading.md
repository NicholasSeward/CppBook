# Introduction to Operator Overloading

You already know **function overloading**: same name, different parameter lists ([Function Overloading](../02Functions/13function%20overloading.md)).

C++ also lets you overload **operators** for your own types: `+`, `<<`, `==`, `[]`, and many more. The compiler turns an expression like `a + b` into a function call:

```cpp
a + b   //  means something like:  operator+(a, b)
```

## A `Fraction` example

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
    Fraction half{1, 2};
    Fraction third{1, 3};
    Fraction sum{operator+(half, third)};

    std::cout << sum.numerator << '/' << sum.denominator << '\n';
    return 0;
}
```

After `operator+` exists, you can also write `half + third`. The compiler rewrites it to `operator+(half, third)`.

> NOTE: This example keeps `numerator` and `denominator` public for clarity. Later sections use private members and pick **member**, **friend**, or **free** implementations.

## Why bother?

| Without overloading | With overloading |
|---------------------|------------------|
| `addFraction(a, b)` | `a + b` |
| `printPoint(out, p)` | `out << p` |
| `lessThan(a, b)` | `a < b` |

Overload when the operator spelling matches how people already think about the operation.

## Try it now

### Exercise 1: Desugaring

Prompt: If `w` and `h` are `Fraction` objects, what function call does `w + h` become?

:::details Answer

**`operator+(w, h)`** (or an equivalent member form like `w.operator+(h)` when defined that way).

:::

### Exercise 2: Built-in types

Prompt: Can you change how `int` values add with `operator+`?

:::details Answer

**No.** Overloading applies to **user-defined** types (classes, enums you define, etc.). You cannot redefine `int + int`.

:::

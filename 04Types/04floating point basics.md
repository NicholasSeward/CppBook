# Floating Point Basics

Floating point types (`float` and `double`) store decimals. They are extremely useful, but they have quirks that surprise beginners.

## `float` and `double`

Both `float` and `double` store a number in a form similar to scientific notation:

```text
sign * mantissa * 2^exponent
```

The number of bits and their roles are split as follows (according to the IEEE 754 standard):

- **float** (32 bits total):
    - 1 bit for the sign
    - 8 bits for the exponent
    - 23 bits for the mantissa (fraction, also called significand)

- **double** (64 bits total):
    - 1 bit for the sign
    - 11 bits for the exponent
    - 52 bits for the mantissa (fraction, or significand)

This structure allows both types to represent very large and very small numbers, but with limited precision. The extra bits in `double` provide more precision and a greater range compared to `float`.

You will hear these parts called:

- sign
- exponent
- mantissa (also called significand)

You do not need to memorize the bit layout now. The takeaway is precision is limited.

Typical precision:

- `float` has about 7 significant decimal digits. This comes from its 23-bit mantissa: since there are 2^23 possible distinct values for the fractional part, this roughly translates to 7 significant digits in decimal.
- `double` has about 15 to 16 significant decimal digits, thanks to its 52-bit mantissa. The 2^52 possible values provide much finer granularity, which allows for higher precision and about 15 to 16 digits in decimal notation.

PREFERENCE: Use `double` by default unless you have a strong reason to use `float`.

## Scientific notation in code

You can write scientific notation with `e`:

```cpp
#include <iostream>

int main()
{
    double a{1.2e4};     // 12000
    double b{3.5e-3};    // 0.0035
    std::cout << a << '\n';
    std::cout << b << '\n';
    return 0;
}
```

## Formatting output with `std::setprecision`

The default printing rules can hide what is really stored. You can control precision with `std::setprecision` from `<iomanip>`.

Reference: [cppreference: `std::setprecision`](https://en.cppreference.com/cpp/io/manip/setprecision)

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double x{1.0 / 3.0};

    std::cout << x << '\n';
    std::cout << std::setprecision(3) << x << '\n';
    std::cout << std::setprecision(17) << x << '\n';
    return 0;
}
```

NOTE: `std::setprecision` is sticky for the stream. It stays until you change it again.

## Rounding error

Many decimals cannot be represented exactly in binary. This is not a C++ bug. It is a property of how floating point works.

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double x{0.1};
    std::cout << std::setprecision(17) << x << '\n';
    return 0;
}
```

You may see something like `0.10000000000000001`. The stored value is very close to 0.1, but not identical.

Another classic demo:

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double x{1.0 / 3.0};
    std::cout << std::setprecision(17) << x << '\n';
    std::cout << std::setprecision(17) << (x + x + x) << '\n';
    return 0;
}
```

Sometimes `x + x + x` prints as `0.9999999999999999` instead of `1`.

PREFERENCE: Do not compare floating point values for exact equality unless you have a very specific reason. Compare within a tolerance instead.

## Special values

Floating point can represent some special values:

- positive zero (+0.0)
- negative zero (-0.0)
- positive infinity
- negative infinity
- NaN (not a number)

You can produce them with certain operations:

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double pos_zero{+0.0};
    double neg_zero{-0.0};
    double pos_inf{1.0 / 0.0};
    double neg_inf{-1.0 / 0.0};
    double nan{0.0 / 0.0};

    std::cout << "positive zero: " << pos_zero << '\n';
    std::cout << "negative zero: " << neg_zero << '\n';
    std::cout << "positive infinity: " << pos_inf << '\n';
    std::cout << "negative infinity: " << neg_inf << '\n';
    std::cout << "NaN: " << nan << '\n';
    return 0;
}
```

NOTE: Printing and behavior depends on your standard library and platform. You do not normally rely on these values in beginner programs, but it is good to know they exist.
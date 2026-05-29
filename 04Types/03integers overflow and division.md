# Integers, Overflow, and Division

Integers store whole numbers. They are fast, common, and also a common source of bugs when values get too large or when division behaves differently than you expect.

## Signed integers and range

Most integer types you use early are **signed**, meaning they can hold negative and positive values.

On many modern systems, `int` uses 32 bits. That means it can usually store values from about -2 billion to 2 billion.

> NOTE: The C++ standard does not promise that `int` is exactly 32 bits, but on typical desktops it is.

```cpp
#include <iostream>
#include <limits>

int main()
{
    std::cout << "int min: " << std::numeric_limits<int>::min() << '\n';
    std::cout << "int max: " << std::numeric_limits<int>::max() << '\n';
    std::cout << "long min: " << std::numeric_limits<long>::min() << '\n';
    std::cout << "long max: " << std::numeric_limits<long>::max() << '\n';
    return 0;
}
```

## Overflow

**Overflow** happens when you try to store a value that does not fit in the type.

In C++, signed integer overflow is **undefined behavior**. That means the language does not guarantee what happens. You cannot rely on a wraparound effect being consistent across compilers or optimization settings.

Example. This code is a demonstration only:

```cpp
#include <iostream>
#include <limits>

int main()
{
    int x{std::numeric_limits<int>::max()};
    std::cout << "max int: " << x << '\n';

    x = x + 1; // overflow, undefined behavior
    std::cout << "after +1: " << x << '\n';

    return 0;
}
```

> PREFERENCE: Pick an integer type that is big enough for your problem. If you might count billions of items, `int` is a risk. Use `long`, or use a fixed width type if you need a known range.

### Rough estimates

Do quick back of the napkin math:

- Houses in a small town might fit in `int`
- People in a large country might still fit in `int`, but be careful
- Counting world population or global events across time can easily exceed `int`

You can often avoid bugs by choosing a bigger type early.

## Integer division

When you divide one integer by another integer, you get an integer result. The fractional part is discarded.

```cpp
#include <iostream>

int main()
{
    std::cout << "1/2 = " << 1 / 2 << '\n';
    std::cout << "50/7 = " << 50 / 7 << '\n';
    return 0;
}
```

Output is:

- `1/2` becomes `0`
- `50/7` becomes `7`

This trips up almost every new programmer once.

> NOTE: This behavior is often what you want. If you need to split a fixed width into 7 columns, you cannot have fractional characters. Integer division gives you a usable integer width.

## Getting a decimal result

If either operand is a floating point type, the division is floating point:

```cpp
#include <iostream>

int main()
{
    std::cout << "1.0/2 = " << 1.0 / 2 << '\n';
    std::cout << "1/2.0 = " << 1 / 2.0 << '\n';
    return 0;
}
```

If you have integer variables and want a `double` result, one simple approach is to multiply by `1.0`:

```cpp
#include <iostream>

int main()
{
    int x{1};
    int y{2};

    double result = x * 1.0 / y;
    std::cout << result << '\n';
    return 0;
}
```

You can also convert with `static_cast<double>(x)`, which you will learn in the conversions chapter.

## Unsigned integers

C++ also has **unsigned** integer types. They can store larger positive values, but they introduce surprises:

- subtracting can underflow easily
- mixing signed and unsigned in an expression can change the result type

Example:

```cpp
#include <iostream>

int main()
{
    unsigned int u{0};
    std::cout << (u - 1) << '\n'; // wraps around on typical machines
    return 0;
}
```

> PREFERENCE: Avoid unsigned types unless you have a clear reason. You will see `std::size_t` in real code (for container sizes and indices), but this book will usually stick with `int` and `long` in early chapters to reduce surprises.


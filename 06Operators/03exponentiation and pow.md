# Exponentiation and `std::pow`

C++ does not have a built in `**` or `^` operator for powers the way some calculators do.

## `^` is not exponentiation

In C++, `^` is **bitwise XOR**, not "to the power of."

```cpp
#include <iostream>
#include <cmath>

int main()
{
    std::cout << (5 ^ 2) << '\n';        // 7 (XOR), not 25
    std::cout << std::pow(5, 2) << '\n'; // 25.0
    return 0;
}
```

NOTE: There is no exponent operator in C++. Use `<cmath>` and `std::pow`, or multiply by hand for small powers.

## `std::pow` for floating point

```cpp
#include <iostream>
#include <cmath>

int main()
{
    std::cout << std::pow(2.0, 10.0) << '\n';  // 1024
    return 0;
}
```

`std::pow` works in floating point. If you need an integer result, round and cast:

```cpp
#include <iostream>
#include <cmath>

int main()
{
    double result = std::pow(2.0, 10.0);
    int asInt = static_cast<int>(std::lround(result));
    std::cout << asInt << '\n';
    return 0;
}
```

NOTE: There is no standard library integer power function. Round and cast is fine for rare cases but slower than integer math.

## Small powers by hand

Squaring and cubing are easy:

```cpp
int x{7};
int square = x * x;
int cube = x * x * x;
```

## Exponentiation by squaring (when performance matters)

```cpp
#include <iostream>

long powInt(long base, int exp)
{
    long result{1};
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main()
{
    std::cout << powInt(2, 10) << '\n';  // 1024
    return 0;
}
```

PREFERENCE: Use `x * x` for squares. Use `std::pow` for general floating powers. Use `powInt` only when you need speed or exact integer math.

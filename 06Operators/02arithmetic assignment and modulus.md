# Arithmetic, Assignment, and Modulus

This chapter covers everyday math operators, compound assignment, and the remainder operator `%`.

## Unary `+` and `-`

A `+` or `-` in front of a value is **unary**:

```
int x{5};
int a{-x};   // -5
int b{+x};   // 5 (unary plus, rare in practice)
```

## The five binary arithmetic operators

| Operator | Name |
|----------|------|
| `+` | addition |
| `-` | subtraction |
| `*` | multiplication |
| `/` | division |
| `%` | remainder (modulus, integers only) |

```cpp
#include <iostream>

int main()
{
    std::cout << 10 + 3 << '\n';
    std::cout << 10 - 3 << '\n';
    std::cout << 10 * 3 << '\n';
    std::cout << 10 / 3 << '\n';  // integer division: 3
    std::cout << 10 % 3 << '\n';  // remainder: 1
    return 0;
}
```

## Integer division vs floating division

If **both** operands are integers, `/` does **integer division** (fraction dropped).

If either operand is floating point, you get a floating result:

```cpp
#include <iostream>

int main()
{
    int a{1};
    int b{2};

    std::cout << a / b << '\n';                       // 0
    std::cout << a * 1.0 / b << '\n';                 // 0.5
    std::cout << static_cast<double>(a) / b << '\n';  // 0.5
    return 0;
}
```

## Divide by zero

**Integer** divide by zero is undefined behavior. Do not do it.

**Floating** divide by zero may produce `inf` or `nan`:

```cpp
#include <iostream>
#include <cmath>

int main()
{
    double a{1.0};
    double b{0.0};
    std::cout << a / b << '\n';    // often inf
    std::cout << 0.0 / 0.0 << '\n'; // often nan
    return 0;
}
```

## Compound assignment

Changing and assigning in one step is so common that C++ has shorthand:

| Operator | Same as |
|----------|---------|
| `+=` | `x = x + ...` |
| `-=` | `x = x - ...` |
| `*=` | `x = x * ...` |
| `/=` | `x = x / ...` |
| `%=` | `x = x % ...` |

```cpp
#include <iostream>

int main()
{
    int x{10};
    x = x + 6;
    std::cout << x << '\n';  // 16

    x += 6;
    std::cout << x << '\n';  // 22
    return 0;
}
```

## Modulus `%`

`/` does integer division. `%` gives what is left over:

```cpp
#include <iostream>

int main()
{
    std::cout << 17 / 5 << '\n';  // 3
    std::cout << 17 % 5 << '\n';  // 2
    return 0;
}
```

### Negative numbers

In many languages, `%` always returns a non negative remainder. In C++, the sign can follow the left operand.

If you want a positive wrap style result (useful for grid or Pac Man style wrapping):

```
int positiveMod(int x, int y)
{
    return (x % y + y) % y;
}
```

```cpp
#include <iostream>

int main()
{
    int width{10};
    for (int x{8}; x < 13; ++x)
    {
        int wrapped = (x % width + width) % width;
        std::cout << "x=" << x << " wraps to " << wrapped << '\n';
    }
    return 0;
}
```

### Even, odd, and multiples

```cpp
#include <iostream>

int main()
{
    int n{14};
    std::cout << std::boolalpha;
    std::cout << "even: " << (n % 2 == 0) << '\n';
    std::cout << "multiple of 5: " << (n % 5 == 0) << '\n';
    return 0;
}
```

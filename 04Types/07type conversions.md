# Type Conversions

Sometimes you need to convert a value from one type to another.

Examples:

- `int` to `double` so division keeps decimals
- `char` to `int` to see the ASCII code
- `double` to `int` to discard the fractional part

Conversions can happen implicitly, or you can be explicit with a cast.

## Implicit conversions

If you put a more restricted type into a less restricted one, the compiler often converts automatically.

Common direction:

```text
bool -> int -> float -> double
```

Example:

```cpp
#include <iostream>

int main() {
    int a{5};
    double b{a}; // implicit int to double
    std::cout << b << '\n';
    return 0;
}
```

This creates a new `double` value. It does not change the original `int` variable.

## Narrowing conversions

Going the other way can lose data:

```text
double -> float -> int -> bool
```

Example:

```cpp
#include <iostream>

int main() {
    double pi{3.14159};
    int x{pi};
    std::cout << x << '\n';
    return 0;
}
```

The fractional part is dropped. That is sometimes correct, sometimes a bug.

NOTE: Many compilers warn when a conversion can lose information. Treat these warnings seriously.

## `static_cast`

`static_cast<T>(value)` is the standard way to do an explicit, visible conversion.

Examples you already saw:

```cpp
double result = static_cast<double>(x) / y;
int asciiCode = static_cast<int>('A');
```

Why use it:

- the conversion is obvious to the reader
- you avoid accidental implicit conversions in complex expressions

## Division example

If both operands are integers, the result is integer division. Cast one side to get a `double` result.

```cpp
#include <iostream>

int main() {
    int x{1};
    int y{2};

    std::cout << x / y << '\n';
    std::cout << static_cast<double>(x) / y << '\n';

    return 0;
}
```
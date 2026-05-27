# Relational Operators

Relational operators compare two values and produce a `bool`.

| Operator | Meaning |
|----------|---------|
| `==` | equal to |
| `!=` | not equal to |
| `<` | less than |
| `>` | greater than |
| `<=` | less than or equal |
| `>=` | greater than or equal |

```cpp
#include <iostream>

int main() {
    int a{3};
    int b{7};

    std::cout << std::boolalpha;
    std::cout << (a < b) << '\n';
    std::cout << (a == b) << '\n';
    std::cout << (a != b) << '\n';
    return 0;
}
```

## Comparing booleans

Redundant:

```cpp
bool isRaining{true};
if (isRaining == true) { }
```

Better:

```cpp
if (isRaining) { }
if (!isRaining) { }
```

## Do not use `==` with floating point

`float` and `double` values are often not exact:

```cpp
#include <iostream>

int main() {
    double a{0.1 + 0.1 + 0.1};
    double b{0.3};

    std::cout << std::boolalpha;
    std::cout << (a == b) << '\n';  // often false
    return 0;
}
```

For "close enough," compare the absolute difference to a small epsilon:

```cpp
#include <iostream>
#include <cmath>

int main() {
    double a{0.1 + 0.1 + 0.1};
    double b{0.3};
    double epsilon{1e-9};

    bool close = std::abs(a - b) <= epsilon;
    std::cout << std::boolalpha << close << '\n';
    return 0;
}
```

PREFERENCE: Use `<` and `>` freely with floats. Use approximate equality with `std::abs` when you need "about equal."

# Logical Operators

Logical operators take `bool` values (or things that convert to `bool`) and produce a `bool`.

| Operator | Name | Meaning |
|----------|------|---------|
| `!` | NOT | flip true/false |
| `&&` | AND | true only if both sides are true |
| `\|\|` | OR | true if either side is true |

```cpp
#include <iostream>

int main() {
    bool isRaining{false};
    bool isWarm{true};

    if (!isRaining) {
        std::cout << "Not raining\n";
    }

    if (isWarm && !isRaining) {
        std::cout << "Go to the park\n";
    }

    return 0;
}
```

## Short circuit evaluation

- **`||` (OR):** if the left side is true, the right side is **not** evaluated.
- **`&&` (AND):** if the left side is false, the right side is **not** evaluated.

```cpp
#include <iostream>

bool expensive() {
    std::cout << "expensive() ran\n";
    return true;
}

int main() {
    bool ok{true};
    if (ok || expensive()) { }  // expensive() does not run

    ok = false;
    if (ok && expensive()) { }  // expensive() does not run

    return 0;
}
```

NOTE: Do not put important side effects only on the right side of `&&` or `||`. It might never run.

## Mixing `&&` and `||`

Use parentheses when logic gets long:

```cpp
if ((age >= 13 && age <= 19) || isStudent) {
    // ...
}
```

## De Morgan's laws

- `!(x < y)` is the same as `x >= y`
- `!(x && y)` is the same as `!x || !y`
- `!(x || y)` is the same as `!x && !y`

Think of `!` like a negative sign. Two `!` cancel for `bool` values.

```cpp
#include <iostream>

int main() {
    bool isRaining{true};
    bool isWarm{false};

    if (isRaining || !isWarm) {
        std::cout << "Stay home\n";
    }

    if (!isRaining && isWarm) {
        std::cout << "Go to the park\n";
    }

    int x{3};
    int y{7};
    std::cout << std::boolalpha;
    std::cout << (!(x < y)) << '\n';  // same as x >= y
    std::cout << (x >= y) << '\n';

    return 0;
}
```

## `and`, `or`, `not`

C++ allows `and`, `or`, and `not` as alternative spellings for `&&`, `||`, and `!`. They are uncommon in real world code. This book uses `&&`, `||`, and `!`.

```cpp
if (not isRaining and isWarm) { }  // legal, unusual
```
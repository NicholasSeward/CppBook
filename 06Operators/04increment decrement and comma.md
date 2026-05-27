# Increment, Decrement, and Comma

## Prefix vs postfix `++` and `--`

Both forms add or subtract 1, but they differ when used **inside a larger expression**:

- **Prefix** (`++x`): increment first, then use the new value
- **Postfix** (`x++`): use the old value, then increment

```cpp
#include <iostream>

int main() {
    int a{5};
    int b{5};

    std::cout << ++a << '\n';  // prints 6, a is 6
    std::cout << b++ << '\n';  // prints 5, then b becomes 6
    std::cout << b << '\n';    // 6
    return 0;
}
```

### Bad: `++` buried in a bigger expression

```cpp
#include <iostream>

int main() {
    int i{0};
    int j{0};

    // Which value of i is added? You must know postfix rules.
    j = i++ + 10;
    std::cout << "i=" << i << ", j=" << j << '\n';  // i=1, j=10

    int a{0};
    int b{0};
    b = ++a + 10;
    std::cout << "a=" << a << ", b=" << b << '\n';  // a=1, b=11

    int x{1};
    std::cout << x++ << ' ' << x << '\n';  // prints "1 2", not "2 2"

    return 0;
}
```

### Good: `++` on its own line

```cpp
#include <iostream>

int main() {
    int i{0};
    int j{0};

    ++i;
    j = i + 10;
    std::cout << "i=" << i << ", j=" << j << '\n';  // i=1, j=11

    for (int k{0}; k < 3; ++k) {
        std::cout << k << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

PREFERENCE: Put `++` and `--` on their own line. Do not wonder whether a bigger expression uses the value before or after the change. Prefix is sometimes slightly faster, but clarity matters more.

## The comma operator

The comma `,` is an operator. It evaluates the left side, then the right side, and the **result** is the right side.

You will see commas most often in function calls, not as a clever trick.

```cpp
#include <iostream>

int main() {
    int a{1};
    int b{2};
    int c = (a++, b + 10);  // a becomes 2, c becomes 12
    std::cout << a << ' ' << c << '\n';
    return 0;
}
```

PREFERENCE: Do not get fancy with the comma operator. Use two statements instead.

### Fancy comma (discouraged)

```cpp
// Hard to read
if ((std::cout << "x=", x), x > 0) { }

// Better
std::cout << "x=" << x << '\n';
if (x > 0) { }
```

The comma operator has very low precedence. That is one more reason to avoid it in expressions.

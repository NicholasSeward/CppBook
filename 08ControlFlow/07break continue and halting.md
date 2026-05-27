# Break, Continue, and Halting

Loops can be controlled with `break`, `continue`, `return`, and `std::exit`. Each means something different.

## `break`: leave the loop

`break` exits the **innermost** loop immediately.

```cpp
#include <iostream>

int main() {
    for (int i{0}; i < 10; ++i) {
        if (i == 5) {
            break;
        }
        std::cout << i << ' ';
    }
    std::cout << '\n';  // prints 0 1 2 3 4
    return 0;
}
```

In nested loops, `break` only leaves one level:

```cpp
for (int r{0}; r < 3; ++r) {
    for (int c{0}; c < 3; ++c) {
        if (c == 1) {
            break;  // leaves inner loop only
        }
        std::cout << r << ',' << c << ' ';
    }
}
```

## `continue`: skip the rest of this iteration

`continue` jumps to the next iteration of the loop.

```cpp
#include <iostream>

int main() {
    for (int i{0}; i < 10; ++i) {
        if (i % 2 == 0) {
            continue;
        }
        std::cout << i << ' ';  // odd numbers only
    }
    std::cout << '\n';
    return 0;
}
```

## `return` vs `break`

- **`break`**: exit the loop, stay inside the function.
- **`return`**: exit the whole function immediately.

```cpp
#include <iostream>

void printUntil(int stopAt) {
    for (int i{0}; i < 10; ++i) {
        if (i == stopAt) {
            return;  // leaves the whole function
        }
        std::cout << i << ' ';
    }
    std::cout << "(after loop)\n";
}

int main() {
    printUntil(3);  // prints 0 1 2 then stops
    std::cout << "back in main\n";
    return 0;
}
```

## With vs without `break` / `continue`

Same goal, with `break`:

```cpp
for (int i{0}; i < 100; ++i) {
    if (i * i > 50) {
        break;
    }
    std::cout << i << ' ';
}
```

Without `break`:

```cpp
for (int i{0}; i < 100 && i * i <= 50; ++i) {
    std::cout << i << ' ';
}
```

Both can be fine. PREFERENCE: Use `break` or `continue` when they make the loop body simpler to read. Avoid them when they hide logic.

## `std::exit`

`std::exit` ends the **entire program** immediately (from `<cstdlib>`).

```cpp
#include <cstdlib>
#include <iostream>

int main() {
    std::cout << "Starting\n";
    if (true) {
        std::exit(1);  // non zero often means error
    }
    std::cout << "This never runs\n";
    return 0;
}
```

The integer passed to `std::exit` is the process exit code (like `return` from `main`).

PREFERENCE: Use `return` from `main` or functions for normal exits. Use `std::exit` only when there is no reasonable way to unwind (rare in beginner programs).

NOTE: `return` from `main` is the normal, readable way to finish. `std::exit` skips destructors and cleanup in more complex programs. Keep it simple early on.

## Try it

- Search for the first number over 100 in a list using `break`.
- Print only numbers not divisible by 3 using `continue`.
- Rewrite a `break` loop using only the `for` condition instead, and compare readability.

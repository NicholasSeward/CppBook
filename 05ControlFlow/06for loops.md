# For Loops

Looping a known number of times is so common that C++ has a **`for` loop** that bundles initialization, condition, and update in one line.

## Same job as `while`

A counting `while`:

```
int i{0};
while (i < 10)
{
    std::cout << i << ' ';
    ++i;
}
```

The same idea as `for`:

```
for (int i{0}; i < 10; ++i)
{
    std::cout << i << ' ';
}
```

## Anatomy of a `for` loop

```
for (initialization; condition; update)
{
    body
}
```

1. **Initialization** runs once at the start.
2. **Condition** is checked before each iteration. If false, leave the loop.
3. **Body** runs.
4. **Update** runs, then go back to step 2.

## Standard counting loop

```cpp
#include <iostream>

int main()
{
    for (int i{0}; i < 10; ++i)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

This prints `0` through `9`. Ten iterations because `i` starts at 0 and stops before 10.

> NOTE: Prefer `<` with a clear end value. Using `!=` can fail if the update skips a value or overshoots.

```
// Risky if update is not exactly +1 each time
for (int i{0}; i != 10; ++i)
{
}
```

## Off by one

Being off by one is common. If you wanted `1` through `10`:

```
for (int i{0}; i < 10; ++i)
{
}
```

If you wanted ten iterations starting at 0, use `i < 10`.

> NOTE: Compilers are fast. Compile, run, see what prints, adjust. Iteration beats guessing.

> AI: Tools and agents also iterate. Modern assistants often need several compile and fix cycles for loops and edge cases, same as humans.

## Parts you can omit

```
int i{0};
for (; i < 5; ++i)
{
} // no init in for
for (int j{0}; j < 5; ) // no update in for
{
    ++j;
}
```

> PREFERENCE: Use the standard `for (int i = 0; i < n; ++i)` form when you can. It is the easiest to read and debug.

Avoid `for (;;)` as an infinite loop. Prefer `while (true)` if you truly need an infinite loop.

## Non standard but legal loops

```cpp
#include <iostream>

int main()
{
    for (int i{10}; i >= 0; --i)
    {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (int n{1}; n < 100; n *= 2)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

> PREFERENCE: Prefer the standard counting form unless you have a clear reason not to.

## Nested `for` loops

```cpp
#include <iostream>

int main()
{
    int rows{3};
    int cols{5};
    for (int r{0}; r < rows; ++r)
    {
        for (int c{0}; c < cols; ++c)
        {
            std::cout << '*';
        }
        std::cout << '\n';
    }
    return 0;
}
```

Refactor with a function when nesting gets hard to follow:

```
void printLine(int cols)
{
    for (int c{0}; c < cols; ++c)
    {
        std::cout << '*';
    }
    std::cout << '\n';
}
```

## `for` vs `while`

| Use | When |
|-----|------|
| `for` | you know how many iterations (or have a clear counter) |
| `while` | you repeat until a condition changes (input, unknown length) |

```
// Countdown with for
for (int t{10}; t >= 0; --t)
{
    std::cout << t << "... ";
}

// Repeat until user says stop (while fits better)
std::string cmd;
while (cmd != "quit")
{
    std::cout << "Command: ";
    std::cin >> cmd;
}
```

## Try it

- Print a multiplication table row `7 * 1` through `7 * 10` with a `for`.
- Write both `i < 10` and `i <= 9` loops and confirm they run the same number of times.
- Print a rectangle with nested `for`, then with a `printLine` helper.

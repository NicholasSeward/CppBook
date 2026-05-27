# While Loops

Printing `1` through `10` with ten `std::cout` lines works once. Printing `1` through `1000` does not scale. You need a **loop**.

A **`while` loop** is basically an `if` that tries again until the condition becomes false.

## Basic `while`

```cpp
#include <iostream>

int main()
{
    int i{1};
    while (i <= 10)
    {
        std::cout << i << ' ';
        ++i;
    }
    std::cout << '\n';
    return 0;
}
```

How it works:

1. Check the condition (`i <= 10`).
2. If false, skip the loop.
3. If true, run the body.
4. Go back to step 1.

Comment out `++i` and the condition never becomes false. You get an **infinite loop**.

NOTE: Every loop needs a path to eventually make the condition false. Usually that means updating a loop variable inside the body.

## Intentional infinite loops

Sometimes you want to repeat until the user quits:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string again{"y"};
    while (again == "y" || again == "Y")
    {
        std::cout << "Did something useful...\n";
        std::cout << "Again (y/n)? ";
        std::cin >> again;
    }
    return 0;
}
```

`return 0` still exits `main` when the loop ends.

## Unintentional infinite loops

### Semicolon on the `while` line

```cpp
int i{0};
while (i < 5);  // null statement, condition checked once forever
{
    std::cout << i << '\n';
    ++i;
}
```

The body is **not** attached to the `while`. The empty statement loops forever.

### Wrong condition

```cpp
int i{0};
while (i >= 0)
{  // never becomes false if i only increases
    std::cout << i << '\n';
    ++i;
}
```

## Loop variable names

Short names are common in tiny loops: `i`, `j`, `k`. Descriptive names help in longer loops: `count`, `index`, `row`.

## `if` inside `while`

```cpp
#include <iostream>

int main()
{
    int n{1};
    while (n <= 12)
    {
        std::cout << n;
        if (n % 4 == 0)
        {
            std::cout << '\n';
        }
        else
        {
            std::cout << ' ';
        }
        ++n;
    }
    return 0;
}
```

## Nested `while` loops

```cpp
#include <iostream>

int main()
{
    int row{1};
    while (row <= 4)
    {
        int col{1};
        while (col <= row)
        {
            std::cout << '*';
            ++col;
        }
        std::cout << '\n';
        ++row;
    }
    return 0;
}
```

Nested loops get confusing fast. A function can clarify:

```cpp
#include <iostream>

void printStars(int n)
{
    int i{0};
    while (i < n)
    {
        std::cout << '*';
        ++i;
    }
}

int main()
{
    int row{1};
    while (row <= 4)
    {
        printStars(row);
        std::cout << '\n';
        ++row;
    }
    return 0;
}
```

## `do while` (mentioned, not used here)

`do { ... } while (condition);` runs the body once, then checks the condition. Everything you need in this course can be done with `while` and `for`. This book will not use `do while`.

PREFERENCE: Use `while` when you do not know how many iterations you need ahead of time (user input, read until done).

## Try it

- Print powers of two up to 1000 with a `while`.
- Cause an infinite loop on purpose, then fix it.
- Print a 5 row triangle with nested `while`, then refactor with a helper function.

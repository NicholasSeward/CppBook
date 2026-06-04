# Return Values

Some functions produce a value.

That value is called the function's **return value**.

## A function that returns an `int`

```cpp
#include <iostream>

int getFive()
{
    return 5;
}

int main()
{
    int value{getFive()};

    std::cout << value << "\n";
    return 0;
}
```

The call `getFive()` is replaced by the value it returns.

You can save that value in a variable or use it directly.

## Return type

The return type comes before the function name:

```
int getFive()
```

This says `getFive` returns an `int`.

The function body must return a value that matches the return type.

## Getting a value from the user

Consider this program:

```cpp
#include <cmath>
#include <iostream>

int main()
{
    int value{};

    std::cout << "Number? ";
    std::cin >> value;

    std::cout << std::sqrt(value) << "\n";
    return 0;
}
```

Reading the integer is a small job. We can move that job into a function.

This first attempt does not work:

```cpp
#include <cmath>
#include <iostream>

void getInt()
{
    int value{};

    std::cout << "Number? ";
    std::cin >> value;
}

int main()
{
    getInt();
    std::cout << std::sqrt(value) << "\n"; // Error: value is not in scope

    return 0;
}
```

The variable `value` only exists inside `getInt`. `main` cannot see it.

## Returning the value

To send the value back, change the return type from `void` to `int` and use `return`.

```cpp
#include <cmath>
#include <iostream>

int getInt()
{
    int value{};

    std::cout << "Number? ";
    std::cin >> value;

    return value;
}

int main()
{
    int value{getInt()};

    std::cout << std::sqrt(value) << "\n";
    return 0;
}
```

Now `getInt()` produces an `int`, and `main` stores it.

> PROTIP: If you find yourself repeating the same few lines in several places, look for a small function. This is often called DRY: don't repeat yourself. It is a guideline, not a law.

## Returning from `main`

`main` returns an `int` too.

```cpp
int main()
{
    return 0;
}
```

The program sends that value back to the environment that ran it.

By convention, `0` means success. Nonzero values usually mean something went wrong.

## Missing returns

If a function promises to return a value, every normal path should return one.

This is wrong:

```cpp
#include <iostream>

int getNumber()
{
    std::cout << "No return here.\n";
}

int main()
{
    std::cout << getNumber() << "\n";
    return 0;
}
```

Many compilers warn about this, but do not rely on warnings alone. Write functions so the return paths are obvious.

> PREFERENCE: Keep return logic simple. If a function has many tangled branches, it becomes harder for humans and compilers to see whether every path returns correctly.

## Returning one value

A function returns one value, but that value can be a compound type such as a `std::vector` or a `struct`.

```cpp
#include <iostream>
#include <vector>

std::vector<int> makeScores()
{
    return {90, 88, 95};
}

int main()
{
    std::vector<int> scores{makeScores()};

    std::cout << scores.at(0) << "\n";
    return 0;
}
```

## Try it now

### Exercise 1: Return a number

Prompt: Write a function named `getTen` that returns `10`.

```cpp
#include <iostream>

// TODO: Write getTen here.

int main()
{
    std::cout << getTen() << "\n";
    return 0;
}
```

### Exercise 2: Read and return

Prompt: Complete `getAge` so it reads an integer and returns it.

```cpp
#include <iostream>

int getAge()
{
    int age{};

    // TODO: Prompt and read age.
    // TODO: Return age.
}

int main()
{
    int age{getAge()};

    std::cout << "Age: " << age << "\n";
    return 0;
}
```

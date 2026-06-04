# Why Use Functions

Functions are not only about saving keystrokes.

They make programs easier to understand, test, and change.

## Organization

A function gives a name to a group of statements.

Compare this:

```cpp
std::cout << "First number: ";
std::cin >> first;
std::cout << "Second number: ";
std::cin >> second;
std::cout << first + second << "\n";
```

to this:

```
int first{getInt("First number: ")};
int second{getInt("Second number: ")};

std::cout << add(first, second) << "\n";
```

The second version reads more like the problem.

## Reusability

If a job happens more than once, a function can prevent copy-and-paste code.

```cpp
#include <iostream>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    std::cout << prompt;
    std::cin >> value;

    return value;
}

int main()
{
    int width{getInt("Width: ")};
    int height{getInt("Height: ")};
    int depth{getInt("Depth: ")};

    std::cout << width * height * depth << "\n";
    return 0;
}
```

If input handling later becomes more robust, you can improve `getInt` once.

## Testing

Small functions are easier to test.

```cpp
int add(int left, int right)
{
    return left + right;
}
```

You can call `add(2, 3)` and check that it returns `5`.

A function that mixes input, math, printing, and file writing is much harder to test.

## Abstraction

An abstraction hides details behind a useful name.

```
int total{calculateTotal(scores)};
```

The reader does not need to know every step of `calculateTotal` to understand the main idea.

Good function names let the high-level program read like a plan.

## When to create a function

Consider writing a function when:

- the same group of statements repeats
- a chunk of code has clear inputs and outputs
- a function is getting long
- you want to test one small job
- a name would make the program easier to read

## Common beginner function types

Many beginner programs use functions for three jobs:

- reading input
- calculating a result
- printing or displaying output

```cpp
#include <iostream>
#include <string>

int getInt(const std::string& prompt)
{
    int value{};

    std::cout << prompt;
    std::cin >> value;

    return value;
}

int area(int width, int height)
{
    return width * height;
}

void printArea(int value)
{
    std::cout << "Area: " << value << "\n";
}

int main()
{
    int width{getInt("Width: ")};
    int height{getInt("Height: ")};

    printArea(area(width, height));
    return 0;
}
```

Each function has one clear job.

> PREFERENCE: Keep functions small and focused. A function that does one main thing is easier for humans, compilers, and AI tools to work with.

## Refactoring

**Refactoring** means changing the structure of code without changing what it does.

Moving repeated code into a function is a common refactor.

Start with working code. Then look for repeated or unclear chunks and give them names.

## Try it now

### Exercise 1: Split the jobs

Prompt: Complete the three functions so `main` reads clearly.

```cpp
#include <iostream>

int getNumber()
{
    // TODO: Read and return an int.
}

int triple(int value)
{
    // TODO: Return value times 3.
}

void printResult(int value)
{
    // TODO: Print value.
}

int main()
{
    int number{getNumber()};
    int result{triple(number)};

    printResult(result);
    return 0;
}
```

### Exercise 2: Find a function

Prompt: Look at a recent program you wrote. Identify one repeated or named job that could become a function.

```cpp
#include <iostream>

int main()
{
    // TODO: Paste a small program here.
    // TODO: Mark a chunk that could become a function.

    return 0;
}
```

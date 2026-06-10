# Kinds of Errors

Not every mistake looks the same. Some stop the compiler. Some crash at runtime. Some let the program finish with the wrong answer.

Knowing which kind of error you have tells you where to look first.

## Syntax errors

A **syntax error** means the compiler cannot understand your source code. The program never runs.

Common causes:

- missing semicolon
- mismatched braces or parentheses
- typo in a keyword or type name
- using a variable before it is declared

```cpp
#include <iostream>

int main()
{
    int x{5}
    std::cout << x << '\n';  // forgot semicolon after int x{5}
    return 0;
}
```

The compiler reports an error near the problem line. Fix syntax errors before worrying about logic.

> PROTIP: Read the **first** compiler error carefully. Later errors are often side effects of the first mistake.

## Logic errors

A **logic error** (also called a **semantic error**) means the program compiles and runs, but behavior does not match what you intended.

Example: you meant to save a file, but the program deleted it instead. Nothing crashed. The program is still wrong.

```cpp
#include <iostream>

int main()
{
    int first{};
    int second{};

    std::cout << "Enter two numbers: ";
    std::cin >> first >> second;

    // Intended: print the sum. Bug: prints the product.
    std::cout << "Sum: " << first * second << '\n';

    return 0;
}
```

Type `3` and `4`. The program prints `12` instead of `7`. That is a logic error.

Logic errors are often the hardest to find because nothing obvious fails. You have to compare actual output to expected output.

## Runtime errors

A **runtime error** happens while the program is running. C++ catches many problems at compile time, but not everything.

Examples:

- dividing by zero (undefined behavior for integers)
- reading past the end of a container (when bounds are not checked)
- opening a file that does not exist
- running out of memory

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    // Bug: index 3 is out of range for a size-3 vector.
    std::cout << values.at(3) << '\n';

    return 0;
}
```

`at()` checks bounds and throws an exception when the index is invalid. Other access patterns may not fail as clearly.

Some runtime problems do not crash immediately. They corrupt state and fail later in a different place. That is why **reproducible** test cases matter.

## How the kinds relate

| Kind | When you notice | Typical fix |
|------|-----------------|-------------|
| Syntax | Compile time | Fix spelling, punctuation, types |
| Logic | After checking output | Rethink the algorithm or conditions |
| Runtime | Crash or exception while running | Guard inputs, check return values, use safer APIs |

You will spend time on all three. Syntax errors are usually quick. Logic and runtime bugs need debugging skills from the next chapters.

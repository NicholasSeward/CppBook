# Program Design With Functions

Functions are one tool for designing programs.

The larger the program gets, the more important structure becomes.

## Start with the goal

Before writing code, ask:

- What should the program do?
- What input does it need?
- What output should it produce?
- What tools or libraries will help?

This is not wasted time. It prevents you from wandering through code without a plan.

## Break the problem down

There are two common ways to think about a problem.

**Top-down design** starts with the big job and breaks it into smaller jobs.

```
Run grade calculator
    read scores
    calculate average
    print result
```

**Bottom-up design** starts with useful small pieces and combines them.

```
getInt
average
printResult
```

Most real work uses a little of both.

> NOTE: It is normal to write a small helper first, test it, then return to the bigger plan.

## Incremental programming

Do not write a huge program all at once.

A safer loop is:

1. Add a small piece.
2. Compile.
3. Run.
4. Test.
5. Repeat.

If something breaks, the last small change is probably where the bug is.

## Start simple

Your first version does not have to be perfect.

Prefer code that is:

- readable
- maintainable
- easy to test
- correct for the current requirements

You can optimize later if measurement shows that the simple version is too slow.

## Example design

Suppose the goal is:

> Ask for three scores and print the average.

Possible functions:

- `getScore`
- `average`
- `printAverage`

```cpp
#include <iostream>

int getScore()
{
    int score{};

    std::cout << "Score: ";
    std::cin >> score;

    return score;
}

double average(int first, int second, int third)
{
    return (first + second + third) / 3.0;
}

void printAverage(double value)
{
    std::cout << "Average: " << value << "\n";
}

int main()
{
    int first{getScore()};
    int second{getScore()};
    int third{getScore()};

    printAverage(average(first, second, third));
    return 0;
}
```

The functions make the program's plan visible.

## Test small pieces

You can test a function with known inputs.

```cpp
#include <iostream>

double average(int first, int second, int third)
{
    return (first + second + third) / 3.0;
}

int main()
{
    std::cout << average(3, 6, 9) << "\n"; // Should print 6
    return 0;
}
```

This is not a full testing framework, but it is a useful beginner habit.

## Design advice

- Keep functions focused.
- Give functions clear names.
- Avoid mixing input, calculation, and output unless the function name says so.
- Test after small changes.
- Refactor repeated or confusing code into functions.
- Use headers and namespaces as programs grow.

## Try it now

### Exercise 1: Plan the functions

Prompt: For a program that calculates the area of a rectangle, write three function names you might use.

```cpp
#include <iostream>

int main()
{
    // TODO: Write possible function names as comments.
    // TODO: Example: getWidth

    return 0;
}
```
# Logic Errors

A **logic error** means the program runs to completion (or loops forever) but does not do what you intended.

No compiler error points at the mistake. You compare expected behavior to actual behavior.

## A classic mix-up

```cpp
#include <iostream>

int main()
{
    int first{};
    int second{};

    std::cout << "Enter two integers: ";
    std::cin >> first >> second;

    // Bug: should add, but multiplies.
    std::cout << "Sum: " << first * second << '\n';

    return 0;
}
```

The user asked for a sum. The code computes a product. Everything "worked."

## Wrong conditions

Using `>` when you meant `>=` (or the reverse) changes who passes a threshold.

```cpp
#include <iostream>

int main()
{
    int score{60};

    if (score > 60)  // bug: 60 should pass if passing is 60+
    {
        std::cout << "Pass\n";
    }
    else
    {
        std::cout << "Fail\n";
    }

    return 0;
}
```

A score of exactly `60` fails when the rule is "60 or higher."

## Infinite loops

A loop that never updates its exit condition runs forever.

```cpp
#include <iostream>

int main()
{
    int count{0};

    while (count < 5)
    {
        std::cout << count << '\n';
        // forgot ++count;
    }

    return 0;
}
```

If the program never stops, check whether the loop variable moves toward the condition.

## Off-by-one errors

An **off-by-one** bug is often wrong by a single iteration or index.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{10, 20, 30};

    // Bug: i < values.size() is correct; i <= values.size() reads past the end.
    for (std::size_t i{0}; i <= values.size(); ++i)
    {
        std::cout << values.at(i) << '\n';
    }

    return 0;
}
```

Use `at()` so out-of-range access fails loudly.

> NOTE: Compiling and running is cheap. Do not expect perfection on the first try. Experienced programmers get nervous when something works the first time without a test.

## Operator precedence

Multiplication and division bind tighter than addition.

```cpp
#include <iostream>

int main()
{
    int result{2 + 3 * 4};  // 14, not 20
    std::cout << result << '\n';

    int intended{(2 + 3) * 4};
    std::cout << intended << '\n';

    return 0;
}
```

When in doubt, add parentheses that match your intent.

## Floating-point precision

`float` and `double` cannot represent every decimal fraction exactly.

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    double a{0.1};
    double b{0.2};
    double sum{a + b};

    std::cout << std::setprecision(17) << sum << '\n';  // not exactly 0.3

    if (sum == 0.3)
    {
        std::cout << "equal\n";
    }
    else
    {
        std::cout << "not exactly equal\n";
    }

    return 0;
}
```

For money or strict comparisons, use integers (cents) or compare with a small tolerance.

## Integer division

Dividing two integers discards the fractional part.

```cpp
#include <iostream>

int main()
{
    std::cout << 5 / 2 << '\n';      // 2, not 2.5
    std::cout << 5 / 2.0 << '\n';   // 2.5 when one operand is floating point

    return 0;
}
```

Average of integers often needs a cast: `(a + b) / 2.0`.

## Null statement after `if`

A semicolon right after `if (condition)` creates an empty statement controlled by the `if`. The following block is **not** part of the `if`.

```cpp
#include <iostream>

int main()
{
    int x{5};

    if (x > 0);  // null statement
    {
        std::cout << "This always runs\n";
    }

    return 0;
}
```

## Missing braces

Only the statement immediately after `if` is conditional.

```cpp
#include <iostream>

int main()
{
    int score{90};

    if (score >= 60)
        std::cout << "Pass\n";
        std::cout << "Celebration\n";  // always runs

    return 0;
}
```

Both lines looked indented, but only the first is inside the `if`.

## Assignment instead of comparison

`=` assigns. `==` compares.

```cpp
#include <iostream>

int main()
{
    int x{5};

    if (x = 10)  // bug: assigns 10, always true
    {
        std::cout << "x is ten?\n";
    }

    std::cout << "x is now " << x << '\n';
    return 0;
}
```

Modern compilers often warn about `if (x = 10)`. Enable warnings.

## Forgetting to call a function

Function names without `()` do not run the function.

```cpp
#include <iostream>

int getAnswer()
{
    return 42;
}

int main()
{
    // Bug: prints address or meaningless representation, not 42.
    std::cout << getAnswer << '\n';
    std::cout << getAnswer() << '\n';
    return 0;
}
```

## Try it now

### Exercise 1: Fix the sum program

Prompt: The program should print the sum of `a` and `b`. Find and fix the logic bug.

```cpp
// @file: main.cpp
#include <iostream>

int main()
{
    int a{5};
    int b{7};
    int sum{a - b};  // bug: should add, not subtract

    std::cout << "Sum is: " << sum << '\n';
    return 0;
}
```

### Exercise 2: Correct the passing test

Prompt: A score of 60 should pass when the rule is "60 or above." Fix the condition.

```cpp
// @file: main.cpp
#include <iostream>

int main()
{
    int score{60};

    if (score > 60)  // bug: does not include 60
    {
        std::cout << "You passed!\n";
    }
    else
    {
        std::cout << "You failed.\n";
    }

    return 0;
}
```

### Exercise 3: Fix the off-by-one loop

Prompt: Change the loop so it prints all five values without going out of bounds.

```cpp
// @file: main.cpp
#include <iostream>

int main()
{
    int arr[5]{1, 2, 3, 4, 5};

    for (int i{0}; i <= 5; ++i)  // bug: i goes one past the last index
    {
        std::cout << arr[i] << ' ';
    }

    std::cout << '\n';
    return 0;
}
```

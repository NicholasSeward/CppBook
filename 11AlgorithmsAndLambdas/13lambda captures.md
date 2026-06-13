# Lambda Captures

A lambda's parameter list only receives what the **caller** passes in. Sometimes the lambda also needs **local variables** from the surrounding function.

**Captures** list those outer variables in the `[]` before the parameter list.

## Named capture by value

`[name]` copies the current value into the lambda.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string label{"Score"};

    auto show = [label]()
    {
        std::cout << label << '\n';
    };

    show();
    return 0;
}
```

Captures are **const by default** inside the lambda body. You cannot assign to `label` there when captured by value.

## Multiple captures

```cpp
#include <iostream>

int main()
{
    int minScore{60};
    int maxScore{100};

    auto inRange = [minScore, maxScore](int value)
    {
        return value >= minScore && value <= maxScore;
    };

    std::cout << std::boolalpha << inRange(75) << '\n';
    std::cout << inRange(42) << '\n';
    return 0;
}
```

## Capture by reference

`[&name]` gives the lambda a **reference** to the outer variable.

```cpp
#include <iostream>

int main()
{
    int ammo{3};

    auto shoot = [&ammo]()
    {
        if (ammo > 0)
        {
            --ammo;
            std::cout << "Bang! ammo=" << ammo << '\n';
        }
    };

    shoot();
    shoot();
    return 0;
}
```

`ammo` in `main` drops because the lambda refers to the same `int`.

> PREFERENCE: If a value is really an **input** that might change call to call, prefer a **parameter** over a capture. Use captures for limits, labels, or context that the lambda needs from the surrounding scope (for example a max limit or `pi`).

## Capture all locals: `[=]` and `[&]`

| Capture | Meaning |
|---------|---------|
| `[=]` | copy every used outer variable by value |
| `[&]` | refer to every used outer variable by reference |

**By value (`[=]`):**

```cpp
#include <iostream>

int main()
{
    int bonus{5};
    int base{10};

    auto total = [=]()
    {
        return base + bonus;
    };

    std::cout << total() << '\n';
    return 0;
}
```

**By reference (`[&]`):**

```cpp
#include <iostream>

int main()
{
    int count{0};

    auto bump = [&]()
    {
        ++count;
    };

    bump();
    bump();
    std::cout << count << '\n';
    return 0;
}
```

`[&]` is direct and matches how you expect outer variables to behave, but you can accidentally alias something that later goes out of scope.

`[=]` copies and can protect you from changing outer variables, at the cost of extra copies.

## Lifetime warning

Capture happens when the lambda is **created**, not when it runs.

A reference capture to a local variable is dangerous if the lambda outlives that variable:

```cpp
std::function<int()> makeBad()
{
    int x{10};
    return [&]() { return x; };  // x dies when makeBad returns
}
```

Safe patterns for this course:

- use the lambda **immediately** (typical STL algorithm call)
- capture by value `[=]` or `[x]` when the lambda might outlive the scope
- pass changing inputs as **parameters** instead of reference captures

## Parameters vs captures (quick guide)

| Need | Prefer |
|------|--------|
| Value the algorithm passes each step | parameter |
| Outer limit/label/context | capture by value |
| Must modify outer state in place | capture by reference `[&x]` or `[&]` with care |
| Unsure | named function instead of a big lambda |

## Try it now

### Exercise 1: Threshold capture

Prompt: Capture `minPass` by value and use a lambda with `find_if` to locate the first score at or above it.

```cpp
// @file: main.cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> scores{55, 72, 90, 61};
    int minPass{60};

    // TODO: find_if with [minPass](int s) { ... }

    return 0;
}
```

### Exercise 2: `[&]` counter

Prompt: Use `[&]` so a lambda increments `count` for each even number in a `for_each`.

```cpp
// @file: main.cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5, 6};
    int count{0};

    // TODO: for_each with [&](int n) { ... }

    std::cout << "evens: " << count << '\n';
    return 0;
}
```

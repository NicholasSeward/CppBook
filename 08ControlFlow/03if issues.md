# If Issues

## Braces: optional but recommended

You may write a one line `if` without braces:

```cpp
if (score >= 60) std::cout << "Pass\n";
```

That is legal. It is also easy to break when you add a second line:

```cpp
if (score >= 60)
    std::cout << "Pass\n";
    std::cout << "Extra\n";  // always runs, not inside the if!
```

PREFERENCE: Always use `{}` on `if` / `else` branches in this course. If you ever skip braces, keep the controlled statement on the same line as the `if` so the scope stays obvious.

## Nesting vs chaining

**Nesting** puts an `if` inside another `if`:

```cpp
#include <iostream>

int main()
{
    int age{20};
    bool hasTicket{true};

    if (age >= 18)
    {
        if (hasTicket)
        {
            std::cout << "Enter\n";
        }
        else
        {
            std::cout << "Need a ticket\n";
        }
    }
    else
    {
        std::cout << "Too young\n";
    }

    return 0;
}
```

**Chaining** uses `else if` on one level when cases are flat:

```cpp
if (age < 13)
{
    std::cout << "child\n";
}
else if (age < 18)
{
    std::cout << "teen\n";
}
else
{
    std::cout << "adult\n";
}
```

PREFERENCE: Prefer chaining when it reads like a flat list of cases. Nest when the logic is truly nested (ticket only matters if age already passed). Ask whether a chained form would be clearer.

## `else` without `if`

An `else` must follow an `if` or `else if`. This does not compile:

```cpp
// else { }  // error: else without matching if
```

## Null statements

A lone `;` is a **null statement** (does nothing). Sometimes people put it after `if` by mistake:

```cpp
if (x > 0);  // null statement attached to if
{
    std::cout << "This always runs\n";
}
```

The `if` controls only the empty statement. The block always runs.
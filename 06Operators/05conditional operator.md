# Conditional Operator (`?:`)

The **conditional operator** (ternary) is the only operator with three operands:

```text
condition ? valueIfTrue : valueIfFalse
```

It is like a tiny inline `if` that produces a value.

## Basic use

```cpp
#include <iostream>
#include <string>

int main()
{
    int age{16};

    if (age >= 18)
    {
        std::cout << "adult\n";
    }
    else
    {
        std::cout << "minor\n";
    }

    std::cout << (age >= 18 ? "adult" : "minor") << '\n';
    return 0;
}
```

PREFERENCE: Avoid ternaries unless the case is very short and obvious. Use a normal `if` when you need multiple statements per branch.

## Precedence

`?:` binds just above assignment (`=`). Without parentheses, parsing can surprise you:

```cpp
#include <iostream>

int main()
{
    int x{5};

    int z = x > 0 ? 1 : 2 + 3;  // parsed as (x > 0) ? 1 : (2 + 3)
    std::cout << z << '\n';      // 1

    int w = (x > 0) ? (1) : (2 + 3);
    std::cout << w << '\n';      // 1

    return 0;
}
```

PREFERENCE: If you use a ternary, wrap parts in parentheses when mixing with other operators. Try not to use it unless very simple and short.
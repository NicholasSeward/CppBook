# Precedence and Associativity

When an expression has more than one operator, C++ needs rules for what runs first. Those rules are **precedence** (priority) and **associativity** (direction).

You already saw a simple case: `1 + 2 * 3` is `7`, not `9`, because `*` happens before `+`.

## Precedence

**Precedence** answers: which operator binds tighter, 

Higher in the list below runs first (tighter binding):

| Level | Associativity | Operators (examples) | Description |
|-------|---------------|----------------------|-------------|
| 1 | left to right | `::` | scope |
| 2 | left to right | `()` | parentheses, function call |
| 3 | left to right | `[]` `->` `.` | member access |
| 4 | right to left | `++` `--` (unary) | increment, decrement |
| 5 | right to left | `+` `-` `!` `*` `&` | unary operators |
| 6 | left to right | `*` `/` `%` | multiply, divide, remainder |
| 7 | left to right | `+` `-` | add, subtract |
| 8 | left to right | `<<` `>>` | shift and stream I/O |
| 9 | left to right | `<` `>` `<=` `>=` | comparisons |
| 10 | left to right | `==` `!=` | equality |
| 11 | left to right | `&` | bitwise AND |
| 12 | left to right | `^` | bitwise XOR |
| 13 | left to right | `\|` | bitwise OR |
| 14 | left to right | `&&` | logical AND |
| 15 | left to right | `\|\|` | logical OR |
| 16 | right to left | `, :` | conditional (ternary) |
| 17 | right to right | `=` `+=` `-=` `*=` `/=` `%=` | assignment |
| 18 | left to right | `,` | comma |

This is a **beginner** table. It is not every C++ operator, but it covers what you will use most early on.

> PREFERENCE: If you are unsure, add parentheses. They make your intent obvious.

## Associativity

**Associativity** answers: if operators have the same precedence, which side groups first, 

- Most operators are **left to right**: `10 - 3 - 2` is `(10 - 3) - 2` which is `5`.
- Assignment is **right to left**: `a = b = 5` assigns `5` to `b`, then assigns that result to `a`.

```cpp
#include <iostream>

int main()
{
    int a{};
    int b{};
    a = b = 5;
    std::cout << a << ' ' << b << '\n';
    return 0;
}
```

## Parentheses win

```cpp
#include <iostream>

int main()
{
    std::cout << 2 + 3 * 4 << '\n';      // 14
    std::cout << (2 + 3) * 4 << '\n';    // 20
    return 0;
}
```


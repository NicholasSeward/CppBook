# Operators

You have already written expressions like `1 + 1` and used `<<` to print. An **operator** is a symbol that performs an action on one or more **operands** (the values it works on).

```cpp
#include <iostream>

int main()
{
    std::cout << 1 + 1 << '\n';
    return 0;
}
```

Here, `+` is the operator. `1` and `1` are the operands. The expression `1 + 1` evaluates to `2`, and `<<` sends that result to `std::cout`.

You have also seen:

- `<<` **insertion** (output to a stream)
- `>>` **extraction** (input from a stream)
- `=` **assignment** (store a value into a variable)

## Unary, binary, and ternary

Operators are grouped by how many operands they take.

### Unary (one operand)

```cpp
#include <iostream>

int main()
{
    int x{5};
    std::cout << -x << '\n';   // unary minus: makes a negative value
    x++;
    std::cout << x << '\n';    // adds 1 to x (now 6)
    return 0;
}
```

Common unary operators:

| Operator | Name | Example |
|----------|------|---------|
| `-` | unary minus | `-5`, `-x` |
| `+` | unary plus (rare in practice) | `+x` |
| `++` | increment | `x++`, `++x` |
| `--` | decrement | `x--`, `--x` |

### Binary (two operands)

Most operators are **binary**: they take a left operand and a right operand.

| Operator | Name | Example |
|----------|------|---------|
| `+` | addition | `a + b` |
| `-` | subtraction | `a - b` |
| `*` | multiplication | `a * b` |
| `/` | division | `a / b` |
| `<<` | insertion | `std::cout << x` |
| `>>` | extraction | `std::cin >> x` |
| `=` | assignment | `x = 5` |

> NOTE: `+` and `-` can be **unary** or **binary** depending on context. `-5` is unary minus. `a - b` is binary subtraction.

### Ternary (three operands)

C++ has one ternary operator: the **conditional operator**.

```cpp
#include <iostream>

int main()
{
    int age{20};
    std::cout << (age >= 18 ? "adult" : "minor") << '\n';
    return 0;
}
```

It reads as: if the condition is true, use the first value; otherwise use the second.

> NOTE: You will soon learn `if` and `else` statements. They are usually clearer than ternaries when you are starting out. Use the ternary operator sparingly even as you get more experienced.

## Chaining operators

You can build longer expressions:

```cpp
#include <iostream>

int main()
{
    std::cout << 1 + 2 * 3 << '\n';
    return 0;
}
```

Does this print `7` or `9`? It prints `7`, because multiplication happens before addition.

You can also chain stream operators (because `<<` returns the stream on the left):

```
std::cout << "Score: " << score << '\n';
```

## Order of operations (precedence)

C++ follows rules similar to what you learned in math class (PEMDAS), with a few differences:

- **P**arentheses `()` go first.
- **E**xponents are not a single C++ operator (we skip them here).
- **M**ultiplication and **D**ivision have higher precedence.
- **A**ddition and **S**ubtraction are next.
- For operators at the **same** precedence level, evaluation is usually **left to right** (for example `10 - 3 - 2` is `(10 - 3) - 2`).

When in doubt, use parentheses. They make your intent obvious.

### Abbreviated precedence (beginner version)

Higher operators are evaluated first:

1. `()` parentheses
2. unary `++` `--` `!` unary `-` `+`
3. `*` `/` `%`
4. `+` `-` (binary)
5. `=` assignment operator

If you have trouble remembering the order (and the list of operators will get much longer as you learn more), using parentheses is always helpful. Parentheses enforce exactly the order you want and make your code clearer.

## Step-by-step evaluation

Consider:

```
int result = 2 + 3 * 4 - 6 / 2;
```

Let's break it down, doing only one operation per step, and showing the full assignment each time:

1. Start:  
   `int result = 2 + 3 * 4 - 6 / 2;`
2. Do `3 * 4`:  
   `int result = 2 + 12 - 6 / 2;`
3. Do `6 / 2`:  
   `int result = 2 + 12 - 3;`
4. Do `2 + 12`:  
   `int result = 14 - 3;`
5. Do `14 - 3`:  
   `int result = 11;`

So `result` becomes `11`.

With parentheses you control the order and can show each step similarly:

```
int result = (2 + 3) * (4 - 6 / 2);
```

1. Start:  
   `int result = (2 + 3) * (4 - 6 / 2);`
2. Do `2 + 3`:  
   `int result = 5 * (4 - 6 / 2);`
3. Do `6 / 2`:  
   `int result = 5 * (4 - 3);`
4. Do `4 - 3`:  
   `int result = 5 * 1;`
5. Do `5 * 1`:  
   `int result = 5;`

So `result` becomes `5`.

## Expressions

An **expression** is a combination of values, variables, operators, and function calls that **produces a single value**.

When the compiler runs your program, it **evaluates** expressions: it applies operators and functions step by step until one value remains, just like in the examples above.

### A statement that only computes a value

This program is legal:

```
int main()
{
    1 + 2;
    return 0;
}
```

It computes `3` and then throws the result away. Nothing is printed and nothing is stored.

Imagine walking into a room, saying `89`, and leaving. People might look at you oddly, then go back to what they were doing. The number did not change anything because nothing used it.

If you want to keep a result, **store it** with assignment or initialization:

```
int total = 1 + 2;
int counter{0};
```

### Assignment is an expression too

Even `x = 6` is an expression. The `=` stores `6` into `x` and the whole expression **evaluates to** `6` (the value that was assigned).

That is why chaining works:

```cpp
#include <iostream>

int main()
{
    int x{};
    int y{};

    y = x = 6;

    std::cout << "x = " << x << ", y = " << y << '\n';
    return 0;
}
```

Both `x` and `y` end up as `6`. The assignment runs from right to left: `x = 6` runs first, then `y =` receives the value `6` that the inner assignment produced.

> NOTE: Chained assignment is easy to misread. `y = x = 6` is fine for a demo. In real code, two separate assignments are often clearer.

### Takeaway

Every expression evaluates down to **one value**.
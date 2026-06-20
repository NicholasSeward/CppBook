# Struct vs Class: When to Use Which

C++ lets you bend the rules. Structs can have member functions. Classes can be all-public. You can even define types that hold only functions and no data. **Convention** keeps code readable.

## Typical patterns in this book

| Use | Tool | Why |
|-----|------|-----|
| Bundle of related variables, no rules to enforce | **`struct`** | Public members, minimal ceremony |
| Object with invariants, constructor, controlled access | **`class`** | Private data, public interface |

```cpp
#include <iostream>
#include <string>

struct Color
{
    int red{};
    int green{};
    int blue{};
};

class BankAccount
{
private:
    std::string owner;
    double balance{};

public:
    BankAccount(std::string name, double startBalance)
        : owner{std::move(name)}
        , balance{startBalance}
    {
    }

    double balanceAmount() const
    {
        return balance;
    }
};

int main()
{
    Color pixel{255, 128, 0};
    BankAccount acct{"Ada", 100.0};

    std::cout << pixel.red << ' ' << pixel.green << ' ' << pixel.blue << '\n';
    std::cout << acct.balanceAmount() << '\n';

    return 0;
}
```

`Color` is three ints that travel together. `BankAccount` should not let random code set `balance` without going through methods you trust (deposits, withdrawals, etc.).

## Weird but legal (usually avoid)

- Struct with many private members and complex methods (works, but readers expect `class`)
- Class with all public data members (works, but use `struct`)
- Class or struct with **only** static functions and no data (prefer a **namespace** of free functions)

> PREFERENCE: Start with the simple split above. Advanced patterns (mixins, policy classes, empty tag types) come later. Most day-to-day OOP is "struct for data bags, class for objects with behavior and boundaries."

## Same feature, different defaults

Remember: **`struct` and `class` are the same except for default access.**

```cpp
#include <iostream>

struct S
{
    int a{};  // public by default
};

class C
{
    int a{};  // private by default
public:
    int b{};
};

int main()
{
    S s{};
    s.a = 10;
    std::cout << s.a << '\n';

    C c{};
    // c.a = 10;  // error: a is private
    c.b = 20;
    std::cout << c.b << '\n';

    return 0;
}
```

Everything you learn about constructors, member functions, and `const` applies to both. This chapter focuses on **`class`** because that is where encapsulation matters most.

## Try it now

### Exercise 1: Pick struct or class

Prompt: For each description, write either `struct` or `class` in the comment.

1. A 2D point with `x` and `y`, no validation needed.
2. A password box that must never expose the raw string in logs.
3. A trio of RGB values passed into a graphics function.

(No code to run; short reflection.)

Answers: 1 → struct, 2 → class, 3 → struct

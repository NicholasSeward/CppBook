# Friend Functions

Sometimes a **non-member** function needs access to **private** members. **`friend`** grants that access without making the function a member.

## Printing with a friend

```cpp
#include <iostream>

class Point
{
private:
    int x{};
    int y{};

public:
    Point(int xVal, int yVal)
        : x{xVal}
        , y{yVal}
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p);
};

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << '(' << p.x << ", " << p.y << ')';
    return out;
}

int main()
{
    Point p{3, 4};
    std::cout << p << '\n';
    return 0;
}
```

`operator<<` is declared **inside** `Point` with `friend`, but **defined outside** like a normal function. Being listed in the class tells the compiler it may read private `x` and `y`.

## Friend without getters?

If you already expose everything through getters, a friend may be unnecessary:

```cpp
#include <iostream>

class Point
{
public:
    Point(int xVal, int yVal)
        : x{xVal}
        , y{yVal}
    {
    }

    int xValue() const { return x; }
    int yValue() const { return y; }

private:
    int x{};
    int y{};
};

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << p.xValue() << ", " << p.yValue();
    return out;
}

int main()
{
    Point p{3, 4};
    std::cout << p << '\n';
    return 0;
}
```

> PREFERENCE: **`friend` is most common for `operator<<` and similar operators.** Do not mark half your codebase as friends. Each friend increases the code that can bypass your interface.

## Multiple friends and forward declarations

```cpp
#include <iostream>

class Vault
{
private:
    int code{};

public:
    Vault(int c)
        : code{c}
    {
    }

    friend void audit(const Vault& v);
};

void audit(const Vault& v)
{
    std::cout << "Audit code: " << v.code << '\n';
}

int main()
{
    Vault v{1234};
    audit(v);
    return 0;
}
```

Forward-declare friend functions before the class if needed.

## Class friends

One class can be a **friend** of another (see `friend class Secret` above). Useful for tightly coupled collaborator types. Rare in introductory projects.

## Friends in multiple files

Pattern:

- Declare `friend` in **`Point.h`**
- Define `operator<<` in **`Point.cpp`** or a dedicated **`Point_io.cpp`**
- Include the header wherever you stream `Point`

Same ODR rules as other functions: one definition in the program.

## Try it now

### Exercise 1: Friend or getter?

Prompt: `Wallet` stores private `balance`. You want `printBalance(Wallet)` as a free function. Would you use (A) a `balance()` getter only, or (B) `friend void printBalance(const Wallet&)`? Justify in one sentence.

Sample answer: **A** if `balance()` is already part of the public API; **B** only if printing needs private fields you deliberately do not expose.

### Exercise 2: Complete `operator<<`

Prompt: Add `friend std::ostream& operator<<` to `Rectangle` (private `width`, `height`) so `std::cout << r` prints `4x5` for a 4×5 rectangle.

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};

public:
    Rectangle(double w, double h)
        : width{w}
        , height{h}
    {
    }

    // TODO: friend declaration
};

// TODO: define operator<< outside class

int main()
{
    Rectangle r{4.0, 5.0};
    std::cout << r << '\n';
    return 0;
}
```

Expected: `4x5` (or similar format you choose, match your implementation)

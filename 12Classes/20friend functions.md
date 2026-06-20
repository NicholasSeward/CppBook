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

One class can be a **`friend`** of another. That class's member functions may access the other's **private** members. Two classes can **friend each other** when they are tight collaborators (use sparingly).

Forward-declare the second class when the first needs to name it:

```cpp
#include <iostream>

class Sensor;

class Display
{
    friend class Sensor;

private:
    int brightness{};

public:
    Display(int level)
        : brightness{level}
    {
    }

    void showFrom(const Sensor& s);
};

class Sensor
{
    friend class Display;

private:
    int reading{};

public:
    Sensor(int value)
        : reading{value}
    {
    }

    void showFrom(const Display& d)
    {
        std::cout << "Display brightness: " << d.brightness << '\n';
    }
};

void Display::showFrom(const Sensor& s)
{
    std::cout << "Sensor reading: " << s.reading << '\n';
}

int main()
{
    Display screen{80};
    Sensor probe{42};
    screen.showFrom(probe);
    probe.showFrom(screen);
    return 0;
}
```

Each class declares **`friend class Other`**. Then **`Display::showFrom`** reads private **`s.reading`**, and **`Sensor::showFrom`** reads private **`d.brightness`**. Without friendship, neither could reach into the other's private data.

> PREFERENCE: Mutual class friends are rare in introductory projects. Prefer a small public interface or one-way friendship when you can.

## Friends in multiple files

Pattern:

- Declare `friend` in **`Point.h`**
- Define `operator<<` in **`Point.cpp`** or a dedicated **`Point_io.cpp`**
- Include the header wherever you stream `Point`

Same ODR rules as other functions: one definition in the program.

## Try it now

### Exercise 1: Friend or getter?

Prompt: `Wallet` stores private `balance`. You want `printBalance(Wallet)` as a free function. Would you use (A) a `balance()` getter only, or (B) `friend void printBalance(const Wallet&)`? Justify in one sentence.

:::details Answer

**A (getter)** is the usual choice: `printBalance` calls `w.balance()` and stays outside the class. **B (friend)** only pays off when `printBalance` must read private state you refuse to expose through any public member.

:::

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

:::details Hint

Declare **`friend std::ostream& operator<<`** inside `Rectangle`. Define the function **outside** the class; the **`friend`** declaration lets it use **`r.width`** and **`r.height`**.

:::

:::details Solution

**Reasoning:** `operator<<` must be a free function (left operand is `std::ostream`). Friendship grants access to private members without adding getters just for printing.

Inside `Rectangle`:

```
friend std::ostream& operator<<(std::ostream& out, const Rectangle& r);
```

Outside the class:

```
std::ostream& operator<<(std::ostream& out, const Rectangle& r)
{
    out << r.width << 'x' << r.height;
    return out;
}
```

Expected output: `4x5`

:::

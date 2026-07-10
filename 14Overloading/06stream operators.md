# Stream Operators `<<` and `>>`

Printing and reading custom types should match built-in types: use **`operator<<`** and **`operator>>`** with streams.

## Output: `operator<<`

`std::cout` is a `std::ostream`. The left operand of `<<` is always the stream, so `operator<<` cannot be a member of your class.

```cpp
#include <iostream>

class Point
{
    friend std::ostream& operator<<(std::ostream& out, const Point& p);

public:
    Point(int x, int y)
        : x_{x}
        , y_{y}
    {
    }

private:
    int x_{};
    int y_{};
};

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << '(' << p.x_ << ", " << p.y_ << ')';
    return out;
}

int main()
{
    Point p{3, 4};
    std::cout << p << '\n';
    return 0;
}
```

Return the **same stream reference** so chaining works: `cout << a << b`.

> NOTE: This pattern appears in [Copying, Printing, and Nesting Structs](../04Types/13copying%20printing%20and%20nesting%20structs.md) for structs and in [Friend Functions](../12Classes/20friend%20functions.md) for classes.

## Input: `operator>>`

Mirror the output format. On bad input, put the stream in a **failed state**, same as reading a bad `int`.

```cpp
#include <iostream>
#include <string>

class Point
{
    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& in, Point& p);

public:
    Point(int x = 0, int y = 0)
        : x_{x}
        , y_{y}
    {
    }

    int x() const { return x_; }
    int y() const { return y_; }

private:
    int x_{};
    int y_{};
};

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << '(' << p.x_ << ", " << p.y_ << ')';
    return out;
}

std::istream& operator>>(std::istream& in, Point& p)
{
    char open{};
    char comma{};
    char close{};
    int x{};
    int y{};

    in >> open >> x >> comma >> y >> close;
    if (open != '(' || comma != ',' || close != ')')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    p.x_ = x;
    p.y_ = y;
    return in;
}

int main()
{
    Point p;
    std::cout << "Enter (x, y): ";
    if (std::cin >> p)
    {
        std::cout << "You entered " << p << '\n';
    }
    else
    {
        std::cout << "Invalid format. Expected (x, y)\n";
    }
    return 0;
}
```

Test with `(3, 4)` and with `3 4` to see failure handling.

## Try it now

### Exercise 1: Return type

Prompt: Why does `operator<<` return `std::ostream&` instead of `void`?

:::details Answer

So expressions like **`std::cout << a << b`** chain: the first `<<` returns `cout`, which the second `<<` uses.

:::

### Exercise 2: Member form

Prompt: Could `Point::operator<<(std::ostream&)` make `cout << p` work?

:::details Answer

**No.** That would require **`p << cout`**, because the member’s left operand is `p`.

:::

# The `this` Pointer and Chaining

Inside a member function, **`this`** is a pointer to the object the function was called on.

- **`this`** → pointer to current object (`Rectangle*`)
- **`(*this)`** → the object itself
- **`this->member`** → access a member through the pointer

You saw `this->width` when a parameter shadowed `width`.

## Returning `*this` for chaining

Member functions can return a reference to the current object so calls can be **chained**:

```cpp
#include <iostream>

class Counter
{
private:
    int value{};

public:
    Counter& add(int n)
    {
        value += n;
        return *this;
    }

    int read() const
    {
        return value;
    }
};

int main()
{
    Counter c{};
    c.add(5).add(3).add(2);
    std::cout << c.read() << '\n';
    return 0;
}
```

`add` returns `Counter&` (reference), not a copy. Each call operates on the same `c`.

Return type must be a **reference** (`Counter&`). Returning `Counter` by value would copy and break chaining.

## "Nuclear option": assign through `*this`

Rarely, you replace the entire object's state:

```cpp
#include <iostream>

class Score
{
private:
    int points{};

public:
    Score& reset()
    {
        *this = Score{};  // assign a fresh default-constructed Score
        return *this;
    }

    Score& add(int n)
    {
        points += n;
        return *this;
    }

    int value() const
    {
        return points;
    }
};

int main()
{
    Score s{};
    s.add(50).add(25);
    std::cout << s.value() << '\n';
    s.reset();
    std::cout << s.value() << '\n';
    return 0;
}
```

Use chaining when it reads clearly (`builder.add(1).add(2)`). Do not chain just to look clever.

## Arrow vs dot

| Syntax | Use |
|--------|-----|
| `obj.member` | `obj` is an object |
| `ptr->member` | `ptr` is a pointer to an object |

`this->width` is the pointer form inside member functions.

## Try it now

### Exercise 1: Chain `scale`

Prompt: Make `scale(double factor)` return `Rectangle&` and chain two scales on one rectangle. Start from width 2, height 3, scale by 2, then by 0.5, print area (should be 6).

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

    Rectangle& scale(double factor)
    {
        width *= factor;
        height *= factor;
        return *this;  // already done for you
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{2.0, 3.0};
    // TODO: r.scale(...).scale(...);
    std::cout << r.area() << '\n';
    return 0;
}
```

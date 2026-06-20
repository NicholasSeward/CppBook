# Const Member Functions

You can mark a member function **`const`** to promise it will not modify the object's data members (except `mutable` members, rarely used at this level).

```cpp
#include <iostream>

class Thermometer
{
private:
    double celsius{};

public:
    Thermometer(double temp)
        : celsius{temp}
    {
    }

    double read() const
    {
        return celsius;
    }

    void setCelsius(double temp)
    {
        celsius = temp;
    }
};

int main()
{
    const Thermometer room{20.0};
    std::cout << room.read() << '\n';
    // room.setCelsius(25.0);  // error: setCelsius is not const

    return 0;
}
```

On a **`const` object**, only **`const` member functions** may be called. Non-`const` functions are rejected at compile time.

## Why `area() const`?

Inspectors like `area()`, `width()`, and `isEmpty()` usually leave the object unchanged. Mark them `const` so they work on `const` objects and document intent.

## Passing `const` references

You will often write:

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

    double area() const
    {
        return width * height;
    }
};

void printArea(const Rectangle& r)
{
    std::cout << r.area() << '\n';
}

int main()
{
    Rectangle r{4.0, 5.0};
    printArea(r);
    return 0;
}
```

`printArea` will not modify `r`. Inside it, you may only call **`const` member functions** on `r`. If `area()` were missing `const`, this would not compile.

> NOTE: This book rarely marks every member function `const` in examples to reduce noise. Python gets by without a `const` keyword at all. Learn the rule so you can read other people's code and add `const` when you pass objects by `const` reference.

## `const` and non-`const` overloads

You can provide two versions of the same function; the compiler picks based on whether the object is `const`. That is uncommon in introductory code.

## Try it now

### Exercise 1: Add `const`

Prompt: Mark `heightValue()` as `const` so this compiles:

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

    double heightValue() /* TODO: add const here */
    {
        return height;
    }
};

void printHeight(const Rectangle& r)
{
    std::cout << r.heightValue() << '\n';
}

int main()
{
    Rectangle r{3.0, 4.0};
    printHeight(r);
    return 0;
}
```

# Constructors and Initializer Lists

A **constructor** is a special member function that runs when an object is **created**. Its job: put every data member into a valid starting state.

Constructors:

- Have the **same name as the class**
- Have **no return type** (not even `void`)
- Are called with **`()`** or **`{}`** syntax: `Rectangle r{4.0, 5.0};`

## Member initializer list

C++ prefers initializing members in the **initializer list** after the colon:

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

int main()
{
    Rectangle r{4.0, 5.0};
    std::cout << r.area() << '\n';
    return 0;
}
```

Read `width{w}` as "initialize the member `width` from parameter `w`." When names match, `width{width}` means member ← parameter.

You *could* assign inside `{ }`:

```cpp
#include <iostream>

class Rectangle
{
private:
    double width{};
    double height{};

public:
    Rectangle(double w, double h)
    {
        width = w;   // assignment after default construction
        height = h;
    }

    double area() const
    {
        return width * height;
    }
};

int main()
{
    Rectangle r{4.0, 5.0};
    std::cout << r.area() << '\n';
    return 0;
}
```

That works for many types but is slower for some (extra default-construct then assign). This book uses **initializer lists** for consistency.

## Java-style mental model (optional)

Java often looks like:

```
public Rectangle(double w, double h) {
    this.width = w;
    this.height = h;
}
```

C++ separates **initialization** (initializer list) from **body code** (extra logic after `{`). For simple classes the body can be empty.

## Formatting long lists

Both styles are fine if you stay consistent:

```
: width{w}
, height{h}
, area{0.0}
```

```
width{w}, height{h}, area{0.0}
```

Put the colon at the start of the line or end of the previous line. Pick one style per project.

## Order of initialization

Members initialize in **declaration order** in the class, **not** the order listed in the initializer list.

```cpp
#include <iostream>

class BadOrder
{
private:
    int a{};
    int b{};

public:
    BadOrder(int value)
        : b{value}
        , a{b + 1}  // risky: b may not be initialized yet when a is built
    {
    }

    int aValue() const { return a; }
    int bValue() const { return b; }
};

int main()
{
    BadOrder obj{5};
    std::cout << obj.aValue() << ' ' << obj.bValue() << '\n';
    return 0;
}
```

Keep **data member order** and **initializer list order** aligned to avoid surprises.

## Runnable example

```cpp
#include <iostream>

class Player
{
private:
    std::string name;
    int health{};

public:
    Player(std::string playerName, int hp)
        : name{std::move(playerName)}
        , health{hp}
    {
    }

    std::string playerName() const
    {
        return name;
    }

    int healthPoints() const
    {
        return health;
    }
};

int main()
{
    Player p{"Ada", 100};
    std::cout << p.playerName() << " " << p.healthPoints() << '\n';
    return 0;
}
```

## Try it now

### Exercise 1: Initializer list

Prompt: Complete the constructor initializer list for `Circle` (member `radius`).

```cpp
#include <iostream>

class Circle
{
private:
    double radius{};

public:
    Circle(double r)
        /* TODO: initialize radius from r */
    {
    }

    double radiusValue() const
    {
        return radius;
    }
};

int main()
{
    Circle c{5.0};
    std::cout << c.radiusValue() << '\n';
    return 0;
}
```

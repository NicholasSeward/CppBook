# Abstract Classes and Interfaces

Sometimes the base class **cannot** implement a function meaningfully. **`Animal::speak()`** might need to differ for every species, and **`Shape::area()`** depends on geometry the base does not know.

## Pure virtual functions

Mark a virtual function with **`= 0`** to make it **pure virtual**. The base provides no body:

```
virtual void speak() const = 0;   // pure virtual: no body in Animal
```

A class with at least one pure virtual function is **abstract**. You **cannot** create **`Animal animal{}`**. Every concrete derived class **must** define **`speak()`** (or stay abstract too).

```cpp
#include <iostream>

class Animal
{
public:
    virtual void speak() const = 0;
    virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
    void speak() const override
    {
        std::cout << "Woof!\n";
    }
};

int main()
{
    Dog dog{};
    dog.speak();
    // Animal generic{};  // error: cannot instantiate abstract class
    return 0;
}
```

## Many shapes, one loop

Abstract bases shine when you store different concrete types together:

```cpp
#include <iostream>
#include <vector>

class Polygon
{
public:
    virtual double area() const = 0;
    virtual ~Polygon() = default;
};

class Rectangle : public Polygon
{
private:
    double w{};
    double h{};

public:
    Rectangle(double width, double height)
        : w{width}
        , h{height}
    {
    }

    double area() const override
    {
        return w * h;
    }
};

class Triangle : public Polygon
{
private:
    double base{};
    double height{};

public:
    Triangle(double b, double hgt)
        : base{b}
        , height{hgt}
    {
    }

    double area() const override
    {
        return 0.5 * base * height;
    }
};

int main()
{
    Rectangle rect{4.0, 5.0};
    Triangle tri{6.0, 3.0};

    std::vector<Polygon*> shapes{};
    shapes.push_back(&rect);
    shapes.push_back(&tri);

    for (Polygon* shape : shapes)
    {
        std::cout << shape->area() << '\n';
    }

    return 0;
}
```

Each shape calls **its own** **`area()`** through [virtual dispatch](07virtual%20functions.md). **`Polygon`** defines the contract; **`Rectangle`** and **`Triangle`** supply the math.

## Interfaces

An **interface** is often a class where **every** virtual function is pure virtual and there is little or no data, only contracts:

```
class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};
```

`Drawable` says "anything that draws must implement **`draw()`**," without picking a single implementation. A concrete **`Sprite`** or **`Label`** class inherits and defines **`draw()`**.

> NOTE: C++ has no separate `interface` keyword. An interface is usually an abstract class with pure virtual functions and a virtual destructor.

## Try it now

### Exercise 1: Abstract `Shape`

Prompt: Make **`Shape`** abstract with pure virtual **`area()`**. Implement **`Circle`** with radius **`r`** and area **`3.14159 * r * r`**. Print one circle's area.

```cpp
#include <iostream>

class Shape
{
public:
    // TODO: pure virtual area()
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    explicit Circle(double radius)
        : r_{radius}
    {
    }

    // TODO: override area()

private:
    double r_{};
};

int main()
{
    Circle c{2.0};
    Shape* s = &c;
    std::cout << s->area() << '\n';
    return 0;
}
```

:::details Solution

**Reasoning:** **`= 0`** makes **`area()`** pure virtual, so **`Shape`** is abstract. **`Circle`** must provide a concrete **`area()`** with **`override`**.

```
virtual double area() const = 0;
```

In **`Circle`**:

```
double area() const override
{
    return 3.14159 * r_ * r_;
}
```

:::

### Exercise 2: Abstract or concrete?

Prompt: Class **`Logger`** has one pure virtual **`log(std::string)`** and no other virtual functions. Can you write `Logger l;`?

:::details Answer

**No.** Any pure virtual function makes the class **abstract**.

:::

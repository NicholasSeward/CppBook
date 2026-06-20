# Object Slicing and Polymorphism

**Polymorphism** sounds fancy. It means "many forms": code can treat different derived types through a common base idea, and each object runs **its own** version of a function.

A **`Rectangle`** and **`Triangle`** can both expose **`area()`**. Code that holds a **`Polygon*`** can call **`area()`** on each shape and get the right math for that object.

That only works reliably with **pointers** or **references**. Copying into a base **object** causes **object slicing**.

## Slicing: the top layer is cut off

A **`Person`** object only has room for **`Person`** data. Assign an **`Employee`** into a **`Person`** variable and the **`employeeId`** (and any other derived-only members) are **sliced off**:

```cpp
#include <iostream>
#include <string>

class Person
{
protected:
    std::string name;
    int age{};

public:
    Person(std::string personName, int personAge)
        : name{std::move(personName)}
        , age{personAge}
    {
    }

    virtual void describe() const
    {
        std::cout << name << ", age " << age << ", person\n";
    }

    virtual ~Person() = default;
};

class Employee : public Person
{
private:
    int employeeId{};

public:
    Employee(std::string personName, int personAge, int id)
        : Person{personName, personAge}
        , employeeId{id}
    {
    }

    void describe() const override
    {
        std::cout << name << ", employee " << employeeId << '\n';
    }
};

int main()
{
    Employee dev{"Lin", 28, 101};

    Person sliced = dev;  // slices: only Person part is copied
    sliced.describe();    // calls Person::describe

    return 0;
}
```

Output: **`Lin, age 28, person`** (not employee id 101).

## Pointers preserve the full object

```cpp
#include <iostream>
#include <string>

class Person
{
protected:
    std::string name;
    int age{};

public:
    Person(std::string personName, int personAge)
        : name{std::move(personName)}
        , age{personAge}
    {
    }

    virtual void describe() const
    {
        std::cout << name << ", age " << age << ", person\n";
    }

    virtual ~Person() = default;
};

class Employee : public Person
{
private:
    int employeeId{};

public:
    Employee(std::string personName, int personAge, int id)
        : Person{personName, personAge}
        , employeeId{id}
    {
    }

    void describe() const override
    {
        std::cout << name << ", employee " << employeeId << '\n';
    }
};

int main()
{
    Employee dev{"Lin", 28, 101};
    Person* ptr = &dev;  // points to full Employee in memory
    ptr->describe();     // Employee::describe (virtual dispatch)

    return 0;
}
```

Output: **`Lin, age 28, employee 101`**.

## Many shapes, one loop

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

Each shape calls **its own** **`area()`**. That is polymorphism. **`virtual`** on the base function and a **virtual destructor** make it work through pointers.

> NOTE: **`virtual`** and **`override`** are the machinery behind runtime polymorphism. The idea is simple: the object decides which function runs. The keywords make that decision reliable.

## Try it now

### Exercise 1: Sliced or not?

Prompt: Does `Person p = employee;` call `Employee::describe` or `Person::describe` when `describe` is virtual?

:::details Answer

**`Person::describe`**. The **`Employee`** part was sliced off; **`p`** is a **`Person`** object.

:::

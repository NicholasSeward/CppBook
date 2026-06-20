# Extending and Hiding Base Behavior

Inheritance is for **adding** behavior and **specializing** what the base already does.

## Call the base version

A derived **`describe()`** can delegate to the base, then add more output:

```cpp
#include <iostream>
#include <string>

class Person
{
protected:
    std::string name;

public:
    Person(std::string personName)
        : name{std::move(personName)}
    {
    }

    virtual void describe() const
    {
        std::cout << name;
    }

    virtual ~Person() = default;
};

class Employee : public Person
{
private:
    int employeeId{};

public:
    Employee(std::string personName, int id)
        : Person{personName}
        , employeeId{id}
    {
    }

    void describe() const override
    {
        Person::describe();
        std::cout << " (id " << employeeId << ")\n";
    }
};

int main()
{
    Employee dev{"Lin", 101};
    dev.describe();
    return 0;
}
```

**`Person::describe()`** names the base function explicitly.

## Hide a base overload

If the derived class declares a member with the **same name** as a base function, the derived declaration **hides** the base overloads (even if signatures differ):

```cpp
#include <iostream>

class Base
{
public:
    void log(int value)
    {
        std::cout << "int: " << value << '\n';
    }

    void log(double value)
    {
        std::cout << "double: " << value << '\n';
    }
};

class Derived : public Base
{
public:
    void log(int value)
    {
        std::cout << "derived int: " << value << '\n';
    }
};

int main()
{
    Derived d{};
    d.log(5);      // Derived::log(int)
    // d.log(3.5); // error: Base::log(double) is hidden
    return 0;
}
```

Uncommenting **`d.log(3.5)`** fails because **`Derived::log(int)`** hides **both** **`Base::log`** overloads.

## Restore hidden names with `using`

Rarely, you pull base overloads back into scope:

```
class Derived : public Base
{
public:
    using Base::log;

    void log(int value)
    {
        std::cout << "derived int: " << value << '\n';
    }
};
```

Now **`d.log(3.5)`** can call **`Base::log(double)`** again.

> NOTE: **`using Base::member;`** to expose **`protected`** base members as **`public`** in the derived class is possible but uncommon. Prefer a clean public interface on the base instead.

## Try it now

### Exercise 1: Who runs?

Prompt: In the `describe()` override example, does `Employee::describe` print the employee id if it never calls `Person::describe()`?

:::details Answer

**Only what `Employee::describe` prints.** Without **`Person::describe()`**, the base formatting is skipped unless you duplicate it.

:::

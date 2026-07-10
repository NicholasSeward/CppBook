# `dynamic_cast` and Polymorphic Patterns

[Virtual functions](07virtual%20functions.md) let code call the right override through a base pointer. Sometimes you also need **derived-only** members, or you must recover the **actual** type at run time. That is where downcasting and small design patterns come in.

## Base references hide derived-only members

A base **reference** or **pointer** sees only the **base subobject**. Derived-only members are invisible through that view, even when the object really is a **`Dog`**:

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
    void speak() const override { std::cout << "Woof!\n"; }
    void fetch() const { std::cout << "Fetched!\n"; }
};

int main()
{
    Dog dog{};
    Animal& generic = dog;
    generic.speak();     // OK: virtual Woof
    // generic.fetch();  // error: Animal has no fetch()

    // Uncommenting the next line will cause a compile-time error:
    // generic.fetch();

    return 0;
}
```

That is not a bug. The type system says "you only promised this thing is an **`Animal`**."

## `dynamic_cast`: when you need the derived type

If you have **`Animal*`** but need a **`Dog*`** to call **`fetch()`**, use **`dynamic_cast`** (requires a polymorphic base, usually via at least one **`virtual`** function):

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
    void speak() const override { std::cout << "Woof!\n"; }
    void fetch() const { std::cout << "Fetched!\n"; }
};

class Cat : public Animal
{
public:
    void speak() const override { std::cout << "Meow!\n"; }
};

int main()
{
    Dog dog{};
    Animal* pet = &dog;

    if (Dog* asDog = dynamic_cast<Dog*>(pet))
    {
        asDog->fetch();
    }

    Cat cat{};
    pet = &cat;
    if (Dog* asDog = dynamic_cast<Dog*>(pet))
    {
        asDog->fetch();
    }
    else
    {
        std::cout << "Not a dog\n";
    }

    return 0;
}
```

> PREFERENCE: Prefer **pointers** (or references) to base for polymorphic collections and algorithms. Reach for **`dynamic_cast`** when you truly need derived-only behavior, not as a substitute for a well-designed virtual interface.

## Printing: `operator<<` and a virtual `identify()`

You might want **`std::cout << pet`** for any **`Animal`**. You **cannot** make **`operator<<`** a **virtual member of `Animal`**, because the **left** operand of **`<<`** is **`std::ostream`**, not your object. Virtual member functions dispatch on the **left** operand's type.

Pattern: a **virtual** string hook, and a **friend** or free **`operator<<`** that calls it (same spirit as [Stream Operators](../14Overloading/06stream%20operators.md)):

```cpp
#include <iostream>
#include <string>

class Animal
{
    friend std::ostream& operator<<(std::ostream& out, const Animal& a);

public:
    virtual std::string identify() const = 0;
    virtual ~Animal() = default;
};

std::ostream& operator<<(std::ostream& out, const Animal& a)
{
    return out << a.identify();
}

class Dog : public Animal
{
public:
    std::string identify() const override { return "Dog"; }
};

int main()
{
    Dog dog{};
    std::cout << dog << '\n';
    return 0;
}
```

Each derived class implements **`identify()`**; **`<<`** stays one non-virtual function that delegates to the vtable through **`identify()`**.

## Try it now

### Exercise 1: `dynamic_cast` to call `trim()`

Prompt: **`Plant`** has virtual **`describe()`**. **`Bonsai`** adds **`trim()`**. Given **`Plant* p = &tree`**, use **`dynamic_cast`** to call **`trim()`** when **`p`** points at a **`Bonsai`**.

```cpp
#include <iostream>
#include <string>

class Plant
{
public:
    virtual std::string describe() const = 0;
    virtual ~Plant() = default;
};

class Bonsai : public Plant
{
public:
    std::string describe() const override { return "Bonsai"; }
    void trim() const { std::cout << "Snip snip\n"; }
};

class Fern : public Plant
{
public:
    std::string describe() const override { return "Fern"; }
};

int main()
{
    Bonsai tree{};
    Plant* p = &tree;

    std::cout << p->describe() << '\n';

    // TODO: dynamic_cast to Bonsai* and call trim()

    Fern f{};
    p = &f;
    // TODO: try dynamic_cast again; print "Not a bonsai" if it fails

    return 0;
}
```

:::details Solution

**Reasoning:** **`dynamic_cast<Bonsai*>(p)`** returns a valid pointer when the object really is a **`Bonsai`**, otherwise **`nullptr`** (for pointers).

```
if (Bonsai* b = dynamic_cast<Bonsai*>(p))
{
    b->trim();
}

Fern f{};
p = &f;
if (Bonsai* b = dynamic_cast<Bonsai*>(p))
{
    b->trim();
}
else
{
    std::cout << "Not a bonsai\n";
}
```

:::

### Exercise 2: Why not virtual `<<`?

Prompt: Could `virtual std::ostream& operator<<(std::ostream& out) const` on **`Animal`** make `std::cout << dog` work?

:::details Answer

**No.** A member **`operator<<`** would require **`dog << std::cout`**, because the member's left operand is **`dog`**. The stream must stay on the left for normal printing syntax.

:::

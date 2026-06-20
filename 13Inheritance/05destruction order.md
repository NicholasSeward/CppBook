# Destruction Order

Construction runs **base first, derived last**. Destruction is the **reverse**: the most derived part is destroyed first, then its parent, then the grandparent, and so on.

## A short chain

```cpp
#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "A born\n";
    }

    ~A()
    {
        std::cout << "A dying\n";
    }
};

class B : public A
{
public:
    B()
    {
        std::cout << "B born\n";
    }

    ~B()
    {
        std::cout << "B dying\n";
    }
};

class C : public B
{
public:
    C()
    {
        std::cout << "C born\n";
    }

    ~C()
    {
        std::cout << "C dying\n";
    }
};

int main()
{
    C obj{};
    return 0;
}
```

Output:

```
A born
B born
C born
C dying
B dying
A dying
```

Think of nesting dolls: the outer **`C`** wrapper comes off first on the way out.

## Why it matters

If the base destructor ran first while derived data still existed, derived destructors could touch members that were already torn down. C++ destroys **top down** so each layer cleans up while its own sub-object is still valid.

This mirrors [destructors](../12Classes/18destructors.md) on a single class: when the object leaves scope, cleanup runs automatically.

## Try it now

### Exercise 1: Destruction order

Prompt: For classes `D : public C : public B : public A` (each with logging destructors like above), what is the **first** destructor message when `D` is destroyed?

:::details Answer

**`D dying`** (or whatever message `D`'s destructor prints). Destruction starts at the most derived class.

:::

# Pointers to Pointers and `void` Pointers

Two more pointer forms show up in real code. You will not need them often, but you should recognize them and know their limits.

## Pointers to pointers

A pointer variable lives in memory, so you can point at it too. A **pointer to a pointer** uses `**`:

```cpp
#include <iostream>

int main()
{
    int x = 5;
    int* p = &x;      // p points to x
    int** pp = &p;    // pp points to p

    std::cout << **pp << '\n';   // 5: follow two hops
    return 0;
}
```

Reading `**pp` follows two hops: `pp` to `p`, then `p` to `x`. Pointers to pointers appear in some algorithms and older C APIs, but each extra layer of indirection makes code harder to follow.

> PREFERENCE: For most everyday code, **one level of indirection is enough**. NASA's "Power of 10" rules recommend that pointers use no more than one level of dereferencing. If you find yourself writing `***`, step back and look for a simpler design.

## `void` pointers

A **`void*`** is a generic pointer: it can hold the address of any type, but it has forgotten **what** type that is.

```cpp
#include <iostream>

int main()
{
    int x = 42;
    void* v = &x;   // generic pointer to x

    // std::cout << *v;   // error: cannot dereference void*, unknown type

    int* ip = static_cast<int*>(v);   // cast back to the real type first
    std::cout << *ip << '\n';         // 42
    return 0;
}
```

You cannot dereference a `void*` directly, because the compiler does not know how many bytes to read or how to interpret them. You must **cast** it back to the correct type first, then dereference.

For the same reason, you must never `delete` a `void*`: the program would not know how much memory to free or which destructor to run. In practice this is rarely an issue, because a `void*` you receive is usually owned by someone else.

> PREFERENCE: Avoid `void*` in your own code. When you need to handle many types generically, prefer **polymorphism** with a common base class (see [Virtual Functions](../13Inheritance/07virtual%20functions.md)). Some older C libraries still hand you a `void*`, so it is worth recognizing.

## Try it now

### Exercise 1: Follow the hops

Prompt: Run this program. What does it print? For each `*` in `**pp`, which hop does it take?

```cpp
#include <iostream>

int main()
{
    int n = 9;
    int* p = &n;
    int** pp = &p;
    std::cout << **pp << '\n';
    return 0;
}
```

:::details Answer

Prints **`9`**. The first `*` (on `pp`) gives `p`; the second `*` gives the `int` that `p` points to, which is `n`.

:::

### Exercise 2: Fix the void pointer

Prompt: This does not compile. Fix the marked line so the program prints the stored `double`.

```cpp
#include <iostream>

int main()
{
    double d = 3.5;
    void* v = &d;
    std::cout << *v << '\n';   // TODO: fix this line
    return 0;
}
```

:::details Hint

A `void*` has no type, so you cannot dereference it directly. Cast it to `double*` first.

:::

:::details Solution

**Reasoning:** Restore the type with `static_cast<double*>`, then dereference that pointer.

```cpp
#include <iostream>

int main()
{
    double d = 3.5;
    void* v = &d;
    double* dp = static_cast<double*>(v);
    std::cout << *dp << '\n';
    return 0;
}
```

:::

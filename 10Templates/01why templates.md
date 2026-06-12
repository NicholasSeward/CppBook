# Why Templates

You already know one way to reuse the same **idea** for different types: [function overloading](../02Functions/13function%20overloading.md). Write `max` for `int`, write `max` for `double`, and let the compiler pick.

That works. It also gets repetitive fast.

## The overload pile

Suppose you want `max` for several types:

```cpp
#include <iostream>

int max(int a, int b)
{
    return a > b ? a : b;
}

double max(double a, double b)
{
    return a > b ? a : b;
}

long max(long a, long b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << max(3, 7) << '\n';
    std::cout << max(3.5, 2.1) << '\n';
    return 0;
}
```

The logic is identical. Only the types change. Every new type means another copy of the same function body.

## What you want instead

It would be nice if you could write the pattern **once** and have the compiler generate the right version for each type you use.

That is what **templates** do. You treat a **type like a parameter** of the function itself.

You saw a short preview in [Templates Teaser](../02Functions/16templates%20teaser.md). This chapter goes deeper.

| Approach | You write | Compiler does |
|----------|-----------|---------------|
| Overloading | one function per type | picks by argument types |
| Templates | one pattern with a type placeholder | generates functions at compile time |

> NOTE: Templates are resolved at **compile time**. The compiler builds the concrete `max` for `int`, the concrete `max` for `double`, and so on before your program runs.

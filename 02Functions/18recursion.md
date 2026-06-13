# Recursion

A function that **calls itself** is **recursive**. You saw a taste of this in [Declarations, Definitions, and Forward Declarations](08declarations%20definitions%20and%20forward%20declarations.md) with mutual calls. Here is the pattern to use every time.

## Nibble, callback, terminating condition

Think of every recursive function as three steps:

| Step | Meaning |
|------|---------|
| **Terminating condition** | how you know you are done (no more callbacks) |
| **Nibble** | do one small part of the problem **right now** |
| **Callback** | ask the **same function** to finish what is left |

```
if (terminating condition)
{
    return simple answer;
}
nibble on current piece;
return combine(nibble result, callback on smaller problem);
```

Skip the terminating condition and callbacks never stop. That leads to a **stack overflow**.

## First example: `printN`

Start with the simplest callback: print a string `n` times.

```cpp
#include <iostream>
#include <string>

void printN(int n, const std::string& str)
{
    if (n <= 0)              // terminating condition
    {
        return;
    }
    std::cout << str;        // nibble: print once right now
    printN(n - 1, str);      // callback: print str the remaining times
}

int main()
{
    printN(3, "ha");
    std::cout << '\n';
    return 0;
}
```

Output:

```
hahaha
```

`printN(3, "ha")` nibbles one `"ha"`, then callbacks `printN(2, "ha")` to handle the rest. `printN(0, ...)` is the terminating condition: nothing left to print.

The same job with a loop (no callbacks):

```
for (int i{0}; i < n; ++i)
{
    std::cout << str;
}
```

For `printN`, the loop is clearer. The recursive version is here to show **nibble / callback / terminating condition** before math examples.

## Factorial: loop vs recursion

**Iterative** (preferred for this job):

```cpp
#include <iostream>

int factorialIter(int n)
{
    int product{1};
    for (int i{2}; i <= n; ++i)
    {
        product *= i;
    }
    return product;
}

int main()
{
    std::cout << factorialIter(5) << '\n';
    return 0;
}
```

One loop does all the work. No callbacks.

**Recursive** (nibble / callback / terminating condition):

```cpp
#include <iostream>

int factorialRec(int n)
{
    if (n <= 1)                    // terminating condition
    {
        return 1;
    }
    return n * factorialRec(n - 1); // nibble: multiply by n
                                    // callback: factorialRec(n - 1)
}

int main()
{
    std::cout << factorialRec(5) << '\n';
    return 0;
}
```

Both print `120`. `factorialRec(5)` nibbles `5`, then callbacks `factorialRec(4)`, which nibbles `4`, and so on until `factorialRec(1)` hits the terminating condition and returns `1`.

## Sum 1 through n: loop vs recursion

**Iterative**:

```cpp
#include <iostream>

int sumIter(int n)
{
    int total{0};
    for (int i{1}; i <= n; ++i)
    {
        total += i;
    }
    return total;
}

int main()
{
    std::cout << sumIter(10) << '\n';
    return 0;
}
```

**Recursive**:

```cpp
#include <iostream>

int sumRec(int n)
{
    if (n <= 0)           // terminating condition
    {
        return 0;
    }
    return n + sumRec(n - 1); // nibble: add n
                              // callback: sumRec(n - 1)
}

int main()
{
    std::cout << sumRec(10) << '\n';
    return 0;
}
```

Both print `55`.
## Downsides of recursion

| Issue | What happens |
|-------|----------------|
| Stack growth | each call waits for the next; deep input can overflow the call stack |
| Speed | function call overhead on every step |
| Debugging | harder to trace than a straight loop |
| Memory | each frame holds local state until the call unwinds |

> PREFERENCE: For straightforward counting, summing, or walking a `vector` by index, use an **iterative** loop. It is simpler, faster, and safer on large inputs.

## When recursion still shines

Recursion is a good mental model when the problem is naturally **self-similar** or when you must **explore branches**:

- choose among several next moves (paths in a maze, game trees)
- walk a **tree** (folders, parse trees, decision structures)
- divide a problem in half repeatedly (sorting ideas you will see later)

The structure is often: nibble on one choice, callback to explore the rest, backtrack or combine when the callback returns. That “try many paths” shape is awkward with one plain `for` loop.

## Turning recursion into iteration (BFS and DFS)

In practice, many recursive “explore the graph/tree” algorithms become **iterative** once you add the right **data structure**:

| Recursive idea | Iterative tool | Algorithm family |
|----------------|----------------|------------------|
| go deep first, backtrack | `stack` (or explicit state) | depth-first search (DFS) |
| go level by level | `queue` | breadth-first search (BFS) |

You will meet those containers and traversals in later chapters. The point for now: recursion is often a clear way to **think** about the problem; iteration with a stack or queue is often what you **ship** in production C++.

## Tail recursion

Some languages guarantee **tail call optimization** (TCO): when a function’s last action is a recursive call, the runtime reuses the current stack frame instead of growing the stack.

Languages where tail recursion is a first-class, guaranteed (or strongly idiomatic) idea include **Scheme**, **Haskell**, **Erlang**, **Elixir**, **OCaml**, **F#**, **Racket**, and **Kotlin** (`tailrec`).

**C++** and **Python** are **not** in that group. C++ compilers may sometimes optimize tail calls, but you must not rely on it. Python’s designers explicitly chose not to guarantee TCO; deep recursion can overflow even when the call looks “tail shaped.”

> NOTE: If you write recursive code in C++ for this course, assume each recursive call costs a real stack frame. Prefer iteration unless the recursive structure clearly helps you understand or express the algorithm.

## Try it now

### Exercise 1: Power function both ways

Prompt: Write `powerIter(base, exp)` with a loop and `powerRec(base, exp)` for `exp >= 0`. Compare readability; use the iterative version for large exponents.

```cpp
// @file: main.cpp
#include <iostream>

int powerIter(int base, int exp)
{
    // TODO
    return 0;
}

int powerRec(int base, int exp)
{
    // TODO: terminating condition exp == 0 returns 1
    // TODO: nibble + callback for the rest
    return 0;
}

int main()
{
    std::cout << powerIter(2, 10) << '\n';
    std::cout << powerRec(2, 10) << '\n';
    return 0;
}
```

### Exercise 2: Label the three parts

Prompt: In `factorialRec`, point to the terminating condition, the nibble, and the callback in one sentence each.

1. Why does `factorialRec(1000000)` risk crashing but `factorialIter(1000000)` usually does not?
2. Name one problem shape where recursion is a natural way to describe “try each branch.”

# `std::unique_ptr`

**`std::unique_ptr`** is the smart pointer you will reach for most. It represents **exclusive ownership**: exactly one `unique_ptr` owns the object, and when it goes out of scope, the object is deleted. There is no reference counting, so it is as cheap as a raw pointer.

## Creating one with `make_unique`

Prefer **`std::make_unique`** to create a `unique_ptr`. It allocates and wraps in one step:

```cpp
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<int> p = std::make_unique<int>(42);

    std::cout << *p << '\n';   // 42, dereference like a normal pointer
    *p = 7;
    std::cout << *p << '\n';   // 7

    return 0;   // p goes out of scope: the int is deleted automatically
}
```

You use `*p` and `p->member` just like a raw pointer. You never call `delete`; the `unique_ptr` does it.

> PREFERENCE: A `unique_ptr` is almost always the pointer you want when you need heap ownership. Start here and only switch to `shared_ptr` if you genuinely need shared ownership.

## Exclusive means no copying

Because only one owner is allowed, you **cannot copy** a `unique_ptr`. You can **move** it, transferring ownership. That is where [move semantics](07move%20semantics.md) pays off.

```cpp
#include <iostream>
#include <memory>

std::unique_ptr<int> makeNumber()
{
    return std::make_unique<int>(7);   // returning transfers ownership out
}

void consume(std::unique_ptr<int> p)   // takes ownership
{
    std::cout << "consumed " << *p << '\n';
}

void useRaw(int* p)                    // just borrows, no ownership
{
    std::cout << "raw sees " << *p << '\n';
}

int main()
{
    auto p = makeNumber();      // p now owns the int

    useRaw(p.get());            // pass a raw pointer; p still owns it
    consume(std::move(p));      // move ownership into consume; p is now empty

    return 0;
}
```

Three patterns to notice:

- **Return** a `unique_ptr` from a function to hand ownership to the caller (no `std::move` needed on return).
- **Pass** a `unique_ptr` by value with **`std::move`** to transfer ownership in.
- **Borrow** without giving up ownership by passing a **raw pointer** from `p.get()`.

> PREFERENCE: A common design is to let the `unique_ptr` stay put as the single owner, and hand a **raw pointer** (or reference) to anything that just needs temporary access. Ownership stays in one clear place.

## Two ways to misuse it

`make_unique` avoids a trap. If you wrap an existing raw pointer by hand, you can create two owners of the same memory:

```
int* raw = new int{5};
std::unique_ptr<int> a{raw};
std::unique_ptr<int> b{raw};   // BAD: a and b both think they own it
// both destructors run delete on the same memory: double free
```

Using `make_unique` never exposes a raw pointer for you to reuse, so this cannot happen. The two hazards of hand-wrapping are:

- Making **two** `unique_ptr`s from the same raw pointer (double free).
- Keeping the raw pointer and `delete`ing it yourself out from under the smart pointer (dangling).

> PREFERENCE: Always create owners with **`make_unique`**. Only wrap a raw pointer directly when a library hands you one and documents that you must take ownership.

## Try it now

### Exercise 1: Fix the ownership transfer

Prompt: This does not compile because `unique_ptr` cannot be copied. Make it transfer ownership instead.

```cpp
#include <memory>
#include <iostream>

void consume(std::unique_ptr<int> p)   // takes ownership
{
    std::cout << "consumed " << *p << '\n';
}

int main()
{
    auto p = std::make_unique<int>(3);
    consume(p);   // error: tries to copy
    return 0;
}
```

:::details Answer

Move it:

```
consume(std::move(p));
```

After the move, `p` is empty and `consume` owns the int.

:::

### Exercise 2: Borrow vs own

Prompt: A function only needs to read the value, not keep it. Should it take `std::unique_ptr<int>`, or `int*` from `p.get()`?

:::details Answer

Take a raw **`int*`** (from `p.get()`) or a reference. Taking a `unique_ptr` by value would steal ownership, which a read-only helper should not do.

:::

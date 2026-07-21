# `std::shared_ptr` and `std::weak_ptr`

Sometimes several parts of a program need to keep the same object alive, with no single clear owner. That is what **`std::shared_ptr`** is for. Its companion **`std::weak_ptr`** solves a problem that shared ownership can create.

## `shared_ptr`: counted ownership

A `shared_ptr` keeps a **reference count** of how many `shared_ptr`s point at the object. Each copy increases the count; each destruction decreases it. When the count hits zero, the object is deleted.

Use **`std::make_shared`** to create one:

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto a = std::make_shared<int>(42);
    std::cout << a.use_count() << '\n';   // 1

    {
        auto b = a;                        // copy: now two owners
        std::cout << a.use_count() << '\n';   // 2
    }                                      // b leaves scope: count drops

    std::cout << a.use_count() << '\n';   // 1
    return 0;                              // count hits 0: int deleted
}
```

Unlike `unique_ptr`, copying a `shared_ptr` is allowed and is exactly how ownership is shared.

> PREFERENCE: Reach for `shared_ptr` only when ownership is truly shared. If one owner is enough, a [`unique_ptr`](08unique%20ptr.md) is simpler and cheaper. Remember you can always hand out a raw pointer or a reference for non-owning access.

## The cycle problem

Reference counting has one weakness: a **cycle**. If two objects hold `shared_ptr`s to each other, each keeps the other's count above zero, so neither is ever freed. That is a leak:

```cpp
#include <iostream>
#include <memory>

struct Node
{
    std::shared_ptr<Node> other;
    ~Node() { std::cout << "Node destroyed\n"; }
};

int main()
{
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->other = b;
    b->other = a;   // cycle: a keeps b alive and b keeps a alive

    return 0;       // prints nothing: neither Node is destroyed
}
```

Running this prints **no** `Node destroyed` messages. The two nodes leak.

## `weak_ptr`: observe without owning

A **`std::weak_ptr`** points at an object managed by a `shared_ptr` **without** increasing the count. It does not keep the object alive. Before using it, you call **`lock()`**, which returns a `shared_ptr` if the object still exists, or an empty one if it is gone.

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp = sp;    // observes, does not own

    if (auto locked = wp.lock())   // still alive?
    {
        std::cout << "alive: " << *locked << '\n';
    }

    sp.reset();                    // last owner gone; int is deleted

    if (wp.expired())
    {
        std::cout << "gone\n";
    }
    return 0;
}
```

Make one side of a two-way link a `weak_ptr` to break the cycle:

```cpp
#include <iostream>
#include <memory>

struct Node
{
    std::shared_ptr<Node> next;   // owns the next
    std::weak_ptr<Node> prev;     // observes the previous, no ownership
    ~Node() { std::cout << "Node destroyed\n"; }
};

int main()
{
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->next = b;
    b->prev = a;   // weak: does not keep a alive

    return 0;      // both Nodes destroyed
}
```

With `prev` as a `weak_ptr`, there is no ownership cycle, and both nodes are destroyed correctly (this program prints two `Node destroyed` lines).

## Prefer `unique_ptr` plus raw pointers

Shared ownership is less common than it looks. A frequent, simpler design uses a `unique_ptr` for the thing you **own** and a **raw pointer** for the thing you only **observe**. In a doubly linked list, a node **owns** the next node but only needs to **know about** the previous one:

```cpp
#include <iostream>
#include <memory>

struct Node
{
    int value;
    std::unique_ptr<Node> next;   // owns the next node
    Node* prev = nullptr;         // observes the previous, no ownership

    explicit Node(int v) : value{v} {}
};

int main()
{
    auto head = std::make_unique<Node>(1);
    head->next = std::make_unique<Node>(2);
    head->next->prev = head.get();

    std::cout << head->value << " -> " << head->next->value << '\n';
    std::cout << head->next->value << " -> back to " << head->next->prev->value << '\n';
    return 0;
}
```

## Comparing the three smart pointers

| Feature | `unique_ptr` | `shared_ptr` | `weak_ptr` |
|---------|--------------|--------------|------------|
| **Ownership** | Exclusive (one owner) | Shared (many owners) | None (observer) |
| **Copyable?** | No (move only) | Yes (bumps count) | Yes |
| **Keeps object alive?** | Yes | Yes | **No** |
| **Reference counted?** | No | Yes | Uses the shared count, but does not add to it |
| **Overhead** | None (like a raw pointer) | Count + control block | Small |
| **Access** | `*`, `->`, `get()` | `*`, `->`, `get()` | `lock()` first, then use |
| **Create with** | `std::make_unique` | `std::make_shared` | Assign from a `shared_ptr` |
| **Main use** | Default choice for heap ownership | Genuinely shared ownership | Break cycles; safe non-owning reference |
| **Pairs with** | Raw pointers for observing | `weak_ptr` for observing | Requires a `shared_ptr` |

> NOTE: `weak_ptr` only works with `shared_ptr`. There is no weak companion for `unique_ptr`; for a `unique_ptr` you simply observe with a raw pointer.

## Try it now

### Exercise 1: Predict the count

Prompt: Run this program. What does it print?

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto a = std::make_shared<int>(1);
    auto b = a;
    auto c = b;
    std::cout << a.use_count() << '\n';
    return 0;
}
```

:::details Answer

**`3`**. Three `shared_ptr`s (`a`, `b`, `c`) share ownership of the same `int`.

:::

### Exercise 2: Break the cycle

Prompt: This program leaks (no destructor messages). Change one link so both nodes destroy. Run it to confirm.

```cpp
#include <iostream>
#include <memory>

struct Node
{
    std::shared_ptr<Node> other;
    ~Node() { std::cout << "Node destroyed\n"; }
};

int main()
{
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->other = b;
    b->other = a;   // TODO: break the cycle

    return 0;
}
```

:::details Hint

One of the two links should observe without owning. `weak_ptr` does that, but then the member type on one side must change.

:::

:::details Solution

**Reasoning:** Change one side to `std::weak_ptr` so it does not bump the reference count. Assign with `b->prev = a;` (or similar). Both counts can reach zero.

```cpp
#include <iostream>
#include <memory>

struct Node
{
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    ~Node() { std::cout << "Node destroyed\n"; }
};

int main()
{
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();

    a->next = b;
    b->prev = a;

    return 0;
}
```

:::

### Exercise 3: Is it still there?

Prompt: Run this program. What does it print, and which call checks that the object is still alive before use?

```cpp
#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp = sp;

    if (auto locked = wp.lock())
    {
        std::cout << "alive: " << *locked << '\n';
    }

    sp.reset();

    if (wp.expired())
    {
        std::cout << "gone\n";
    }
    return 0;
}
```

:::details Answer

Prints **`alive: 10`** then **`gone`**. Call **`lock()`** before using the object (it returns a valid `shared_ptr` while the object lives, or empty if it is gone). **`expired()`** is another way to check.

:::

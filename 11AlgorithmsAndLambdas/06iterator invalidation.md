# Iterator Invalidation

An iterator remembers **where** an element lives. If the container moves or destroys that memory, the iterator may become **invalid**. Using an invalid iterator is undefined behavior (crashes or garbage data).

## Do not modify what you are iterating

Safest rule: while walking a container, do not add, remove, or reallocate it.

Common pattern: collect changes in a **second** container, then process that after the loop.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> scores{40, 55, 90, 72};
    std::vector<int> passing;

    for (int score : scores)
    {
        if (score >= 60)
        {
            passing.push_back(score);
        }
    }

    std::cout << "Passing scores: ";
    for (int score : passing)
    {
        std::cout << score << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

## erase invalidates iterators

`erase` removes an element and shifts later items. Iterators at or after the erase point are invalid.

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3, 4, 5};

    auto it{values.begin()};
    ++it;  // points at 2

    values.erase(it);  // removes 2; 'it' is now invalid

    // Using 'it' after erase is undefined behavior!
    // For example, this might crash, print garbage, or appear to "work" by luck:
    std::cout << "Dereferencing invalidated iterator yields: " << *it << '\n';

    return 0;
}
```

After a modifying operation, get a new iterator with `begin()` or `end()` when that is cheap.

## vector growth can invalidate iterators

`push_back` may reallocate the whole vector to a bigger buffer. Any iterator from before the reallocation may point at old memory.

`list` is different: inserting in the middle at a valid iterator often **keeps that iterator valid** because list nodes are not shifted as a block.

```cpp
#include <iostream>
#include <list>

int main()
{
    std::list<int> values{1, 2, 3, 4, 5};

    auto it{values.begin()};
    ++it;
    ++it;  // points at 3

    values.insert(it, 99);  // insert before 3; it still valid for list
    values.insert(it, 99);  // insert another 99 with a still valid iterator

    for (int n : values)
    {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

If you switch the code above to use `vector` instead of `list`, inserting in the middle can invalidate iterators and is generally unsafe—what works safely with a `list` may become invalid or buggy with a `vector`.

> PREFERENCE: After a modification, grab a new iterator when that is cheap. Middle insert on a `list` at a held iterator is a rare case where keeping the old iterator is intentional.

## Quick reference

| Operation | vector iterators | list iterators |
|-----------|------------------|----------------|
| `erase(it)` | invalid at/after `it` | only erased node gone |
| `push_back` | may invalidate all | iterators stay valid |
| insert at held `it` (middle) | may invalidate all | `it` still valid |

Exact rules vary by container. When unsure, assume invalidation and refresh iterators.

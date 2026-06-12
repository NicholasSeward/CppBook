# STL Containers Overview

The C++ Standard Library includes **containers**: template types that hold collections of data.

You have already used `std::vector` heavily. This module adds the rest of the containers you need for everyday programs.

## What the STL gives you

**STL** (Standard Template Library) container types are templates:

```cpp
std::vector<int>
std::map<int, std::string>
std::unordered_set<std::string>
```

The compiler generates a concrete version for the types you pass in.

## Families of containers

| Family | Examples | Main idea |
|--------|----------|-----------|
| Sequence | `vector`, `list`, `deque` | ordered elements by position |
| Ordered associative | `map`, `set` | unique keys, sorted (tree) |
| Unordered associative | `unordered_map`, `unordered_set` | unique keys, hash table |

## What many containers share

Most containers support:

- `size()` and `empty()`
- `clear()`
- `begin()` and `end()` for iterators
- range-for loops

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> values{1, 2, 3};

    for (int v : values)
    {
        std::cout << v << ' ';
    }

    std::cout << "\nSize: " << values.size() << '\n';
    return 0;
}
```

Iterators connect containers to algorithms in a later chapter.

## Choosing a container

| Need | Good first choice |
|------|-------------------|
| Fast access by index `i` | `vector` |
| Push/pop both ends often | `deque` |
| Insert/erase in middle at iterator | `list` (less common) |
| Key to value, sorted keys | `map` |
| Unique values, sorted | `set` |
| Fastest average lookup, order irrelevant | `unordered_map` / `unordered_set` |

> PREFERENCE: `std::vector` is the default sequence container in this course. Reach for something else when you have a concrete reason.

## Try it now

1. For a program that maps student ID to name and prints IDs in sorted order, which container family fits?

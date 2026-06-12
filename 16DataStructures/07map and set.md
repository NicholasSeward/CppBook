# Map and Set (Ordered)

**Ordered associative** containers keep unique keys in sorted order using a balanced tree (see the previous chapter).

- `std::map<K, V>` maps each key to a value.
- `std::set<T>` stores unique keys only (no separate value).

`#include <map>` or `#include <set>`.

## std::map

### How it works

- each entry is a key-value pair
- keys are **unique**
- keys stay sorted by `<`
- lookup, insert, and erase are **O(log n)**

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| access / modify | `operator[]`, `insert()`, `emplace()`, `erase()` |
| lookup | `find()`, `count()`, `contains()` |
| traverse | range-for over `pair<const K, V>` |

### What map lacks

| Not provided | Why |
|--------------|-----|
| safe read-only `operator[]` | `[]` **inserts** a default value if the key is missing |
| O(1) average lookup | tree is O(log n); use `unordered_map` for hash speed |
| `push_back` / `[i]` | not a sequence; keyed access only |
| duplicate keys | use `multimap` if you need them |

Use `find()` or `contains()` when you only want to check membership, not create a new entry.

> Note: In this case, using square brackets (`[]`) is safe because you intend to insert or update a value. The `.at()` method does not work for inserting new keys.

### Student ID lookup

```cpp
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<int, std::string> roster;
    roster[103] = "Ada";
    roster[101] = "Lin";
    roster[102] = "Mo";

    int searchId{102};
    if (roster.contains(searchId))
    {
        std::cout << searchId << " -> " << roster.at(searchId) << '\n';
    }

    std::cout << "All students (sorted by ID):\n";
    for (auto entry : roster)
    {
        std::cout << entry.first << ": " << entry.second << '\n';
    }

    return 0;
}
```

Range-for walks the tree in key order, so IDs print as `101`, `102`, `103` even though you inserted `103` first.

## std::set

### How it works

- like `map`, but stores the key only
- each value appears **once**
- iteration is sorted order

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| modify | `insert()`, `emplace()`, `erase()` |
| lookup | `find()`, `count()` |
| traverse | range-for in sorted order |

### What set lacks

| Not provided | Why |
|--------------|-----|
| `operator[]` | no value slot; membership only |
| duplicates | by design; use `multiset` for duplicates |
| random access by index | tree, not array |

### Unique tags in sorted order

```cpp
#include <iostream>
#include <set>
#include <string>

int main()
{
    std::set<std::string> tags;
    tags.insert("cpp");
    tags.insert("stl");
    tags.insert("cpp");  // duplicate ignored
    tags.insert("debug");

    std::cout << "Tags (alphabetical):\n";
    for (auto tag : tags)
    {
        std::cout << tag << '\n';
    }

    if (tags.find("stl") != tags.end())
    {
        std::cout << "Already tagged stl\n";
    }

    return 0;
}
```

`insert` returns whether the value was new. A second `"cpp"` does nothing.

> PREFERENCE: Use `map` when you need key to value and sorted keys matter. Use `set` when you only need unique membership in sorted order.

## Try it now

### Exercise 1: Course code lookup

Prompt: Build a `map` from course code (`string`) to title (`string`). Look up one code with `contains` and `at`, then print all entries in sorted code order.

```cpp
// @file: main.cpp
#include <iostream>
#include <map>
#include <string>

int main()
{
    std::map<std::string, std::string> courses;

    // TODO: insert at least three courses
    // TODO: lookup "CS101" if present
    // TODO: print all courses sorted by code

    return 0;
}
```

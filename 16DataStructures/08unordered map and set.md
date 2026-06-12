# Unordered Map and Set

When you need fast average lookup and **do not** need sorted keys, use the **unordered** associative containers. They are hash tables under the hood.

- `std::unordered_map<K, V>`: key to value
- `std::unordered_set<T>`: unique keys only

`#include <unordered_map>` or `#include <unordered_set>`.

## std::unordered_map

### How it works

- hash function maps each key to a bucket
- average **O(1)** find, insert, and erase when keys spread well
- iteration order is **not** sorted and can change after **rehash**

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| access / modify | `operator[]`, `insert()`, `emplace()`, `erase()` |
| lookup | `find()`, `count()` |
| traverse | range-for (arbitrary order) |

### What unordered_map lacks

| Not provided | Why |
|--------------|-----|
| sorted iteration | buckets are not ordered by key |
| stable iteration order across runs | rehash changes layout |
| O(1) worst-case guarantee | bad hash or many collisions can degrade |

Same `operator[]` footgun as `map`: missing keys get inserted. Use `find` for read-only checks.

### Word frequency

```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

int main()
{
    std::string text{"to be or not to be"};
    std::unordered_map<std::string, int> counts;

    std::istringstream words{text};
    std::string word{};
    while (words >> word)
    {
        ++counts[word];
    }

    std::cout << "Word counts (order not guaranteed):\n";
    for (auto entry : counts)
    {
        std::cout << entry.first << ": " << entry.second << '\n';
    }

    return 0;
}
```

`++counts[word]` creates a zero count the first time a word appears, then increments.

## std::unordered_set

### How it works

- hash table of keys only (like `set`, but hashed)
- fast **"already seen?"** checks on average

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| modify | `insert()`, `emplace()`, `erase()` |
| lookup | `find()`, `count()`|
| traverse | range-for (unordered) |

### Detect duplicate user IDs

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>

int main()
{
    std::vector<int> submittedIds{101, 205, 101, 330, 205};
    std::unordered_set<int> seen;
    std::unordered_set<int> duplicates;

    for (int id : submittedIds)
    {
        if (!seen.insert(id).second)
        {
            duplicates.insert(id);
        }
    }

    std::cout << "Duplicate IDs: ";
    for (int id : duplicates)
    {
        std::cout << id << ' ';
    }
    std::cout << '\n';

    return 0;
}
```

`insert` returns a pair. The `.second` member is `false` when the value was already in the set.

> PREFERENCE: Reach for `unordered_map` when speed matters and print order does not. Use `map` when you need keys sorted without extra work.

## Try it now

### Exercise 1: Letter counts

Prompt: Count how many times each letter appears in a word using `unordered_map<char, int>`. Print each letter and count (order does not matter).

```cpp
// @file: main.cpp
#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::string word{"mississippi"};
    std::unordered_map<char, int> counts;

    // TODO: count each character
    // TODO: print letter: count lines

    return 0;
}
```

# Tree vs Hash: Choosing a Container

You now have two families of associative containers:

| Family | Types | Under the hood |
|--------|-------|----------------|
| Ordered (tree) | `map`, `set` | balanced binary search tree |
| Unordered (hash) | `unordered_map`, `unordered_set` | hash buckets |

Pick based on what your program needs, not habit.

## What each family gives you

**Tree-based (`map`, `set`)**

- keys iterate in **sorted** order
- O(log n) find, insert, erase
- needs `operator<` (or custom compare), not a hash function

**Hash-based (`unordered_map`, `unordered_set`)**

- no meaningful sort order when you iterate
- average O(1) find, insert, erase
- needs hash function and `operator==`
- **rehash** can change iteration order

## Comparison table

| | `map` / `set` | `unordered_map` / `unordered_set` |
|--|---------------|-----------------------------------|
| Under the hood | balanced tree | hash buckets |
| Key order | sorted | arbitrary |
| Lookup | O(log n) | average O(1) |
| Iterate sorted | yes | no |
| Range queries | yes | no |
| Memory | tree nodes + pointers | buckets + nodes |

## When to pick which

| Situation | Better fit |
|-----------|------------|
| Print keys alphabetically or by ID | `map` / `set` |
| Nearest key, range of keys | `map` |
| Fast membership or counts, order irrelevant | `unordered_*` |
| Small `n` (dozens of entries) | either; clarity wins |

Same word-count task, different print behavior:

- `std::map<std::string, int>` prints words in **sorted** order when you range-for.
- `std::unordered_map<std::string, int>` prints in **arbitrary** bucket order.

> PREFERENCE: Default to `unordered_map` for speed-heavy homework lookups. Switch to `map` when sorted output or range queries are part of the requirement.

## Quick reference: sequence and associative containers

| Container | push back | push front | pop back | pop front | `at(i)` / `[i]` | key lookup |
|-----------|-----------|------------|----------|-----------|-----------------|------------|
| `vector` | yes | no (expensive) | yes | no (expensive) | yes O(1) | no |
| `deque` | yes | yes | yes | yes | yes O(1) | no |
| `list` | yes | yes | yes | yes | no | no |
| `map` | n/a | n/a | n/a | n/a | n/a | find / `[]` O(log n) |
| `set` | insert | n/a | n/a | n/a | n/a | find O(log n) |
| `unordered_map` | n/a | n/a | n/a | n/a | n/a | find / `[]` avg O(1) |
| `unordered_set` | insert | n/a | n/a | n/a | n/a | find avg O(1) |

## Common patterns

Most containers support `size()`, `empty()`, `clear()`, and range-for where it makes sense.

For read-only key checks in maps, prefer `contains` or `find` over `operator[]`, which creates missing keys:

```cpp
// Bad for read-only check: inserts 999 with default value if missing
if (roster[999] == "Ada") { /* ... */ }

// Better
if (roster.find(999) != roster.end()) { /* ... */ }
```

## Common mistakes

| Mistake | Why it hurts |
|---------|--------------|
| `vector::erase(begin())` in a loop on large data | O(n) per erase → O(n²) total |
| `map[]` to read and accidentally inserting | silent new entries with default values |
| Assuming `unordered_map` iteration order is meaningful | order changes after rehash |
| Linear search in `vector` when `unordered_set` fits | O(n) lookup instead of average O(1) |
| `string +` in a loop instead of `+=` | extra temporaries and copies |

## Try it now

### Exercise 1: Pick a container

Prompt: For each scenario, name `vector`, `deque`, `map`, `set`, `unordered_map`, or `unordered_set` as the best first choice and one short reason.

1. Store test scores indexed by position (0, 1, 2, …).
2. Count how many times each word appears in a book.
3. Keep a sorted list of unique course codes for printing.
4. Recent undo history: drop oldest when more than 50 commands.

### Exercise 2: Sorted vs unsorted word count

Prompt: Run the word-frequency example twice: once with `std::map` and once with `std::unordered_map`. Compare print order.

```cpp
// @file: main.cpp
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

void printCountsMap(const std::string& text)
{
    std::map<std::string, int> counts;
    std::istringstream words{text};
    std::string word{};
    while (words >> word)
    {
        ++counts[word];
    }
    std::cout << "map order:\n";
    for (const auto& entry : counts)
    {
        std::cout << entry.first << ": " << entry.second << '\n';
    }
}

void printCountsUnordered(const std::string& text)
{
    // TODO: same logic with std::unordered_map, label output "unordered order:"
}

int main()
{
    std::string text{"dog cat ant dog"};
    printCountsMap(text);
    printCountsUnordered(text);
    return 0;
}
```

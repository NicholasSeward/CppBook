# List and Deque

`std::vector` is the default sequence container. Two alternatives matter when **where** you insert or remove matters as much as **what** you store.

## std::list

### How it works

`std::list` is a **doubly linked list**. Each element lives in a node with links to the previous and next node.

Elements are not contiguous in memory. There is no O(1) access by index.

```
Memory (nodes may sit far apart)
+------+------+------+------+------+------+------+------+------+------+
| slot |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |
+------+------+------+------+------+------+------+------+------+------+
| data |      |  A   |      |  C   |      |      |  B   |      |  D   |
| next |      |  ->6 |      |  ->8 |      |      |  ->3 |      | end  |
+------+------+------+------+------+------+------+------+------+------+

Logical order (follow next pointers):

HEAD
  |
  v
[A @1] ----> [B @6] ----> [C @3] ----> [D @8] ----> NULL
```

`A`, `B`, `C`, and `D` are adjacent in the **list order**, but not in memory.

### Insert between `B` and `C`

To insert `X` between `B` and `C`, allocate a node for `X` in any free slot. Update two links: `B` points to `X`, and `X` points to `C`. Nothing else moves.

```
Before

[A @1] ----> [B @6] ----> [C @3] ----> [D @8] ----> NULL

After (X stored at slot 5)

[A @1] ----> [B @6] ----> [X @5] ----> [C @3] ----> [D @8] ----> NULL
```

The key idea: no shifting of `A`, `C`, or `D` in memory. Only pointer updates.

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| ends | `front()`, `back()` |
| add | `push_back()`, `push_front()`, `insert()` |
| remove | `pop_back()`, `pop_front()`, `erase()` |
| traverse | range-for, iterators |

### What list lacks

| Not provided | Why |
|--------------|-----|
| `operator[]` / `at(i)` | must walk the chain: O(n) |
| `capacity()` | nodes allocated individually |

### Playlist insert example

```cpp
#include <iostream>
#include <list>
#include <string>

int main()
{
    std::list<std::string> playlist{"Intro", "Verse", "Outro"};

    auto it{playlist.begin()};
    ++it;
    playlist.insert(it, "Chorus");

    for (const std::string& track : playlist)
    {
        std::cout << track << '\n';
    }

    return 0;
}
```

Once you have an iterator at `"Verse"`, inserting `"Chorus"` there is cheap. No shifting the entire array like `vector`.

> PREFERENCE: Use `list` when middle insert/erase at a known iterator is the main job. Otherwise `vector` is simpler.

## std::deque

### How it works

`std::deque` (double-ended queue) is optimized for fast growth and shrink at **both ends**.

It is usually implemented as chunks rather than one contiguous block like `vector`.

### Common methods

| Category | Methods |
|----------|---------|
| size / state | `size()`, `empty()`, `clear()` |
| access | `at(i)`, `front()`, `back()` |
| ends | `push_back()`, `push_front()`, `pop_back()`, `pop_front()` |
| traverse | range-for, iterators |

### What deque lacks

| Not provided | Why |
|--------------|-----|
| guaranteed contiguous layout | chunk-based storage |
| `reserve()` like vector | different growth model |
| cheap middle insert | still costly |

### Command history example

```cpp
#include <deque>
#include <iostream>
#include <string>

void addCommand(const std::string& cmd, std::deque<std::string>& history, int maxSize)
{
    history.push_back(cmd);
    if (history.size() > maxSize)
    {
        history.pop_front();
    }
}

int main()
{
    std::deque<std::string> history;

    addCommand("open file", history, 3);
    addCommand("save", history, 3);
    addCommand("run", history, 3);
    addCommand("quit", history, 3);

    std::cout << "Recent commands (oldest to newest):\n";
    for (const std::string& cmd : history)
    {
        std::cout << cmd << '\n';
    }

    return 0;
}
```

`pop_front()` drops the oldest command when the deque holds more than three entries. That is awkward with `vector`, natural with `deque`.

## Vector vs deque

| Task | `vector` | `deque` |
|------|----------|---------|
| grow at back | excellent | excellent |
| pop front | O(n) | O(1) |
| index access | contiguous, cache-friendly | O(1), less contiguous |
| default choice | yes | when both ends matter |

## Try it now

### Exercise 1: Palindrome check with deque

Prompt: Push each character with `push_back`, then compare `front()` and `back()` while they match, removing both ends until the deque is empty or mismatched.

```cpp
// @file: main.cpp
#include <deque>
#include <iostream>
#include <string>

bool isPalindrome(const std::string& text)
{
    // TODO: fill deque, compare and pop front/back until empty or mismatch
    return false;
}

int main()
{
    std::cout << std::boolalpha << isPalindrome("racecar") << '\n';
    std::cout << isPalindrome("hello") << '\n';
    return 0;
}
```

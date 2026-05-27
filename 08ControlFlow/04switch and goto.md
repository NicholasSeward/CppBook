# Switch and `goto`

C++ has other ways to change control flow. This chapter covers `switch` (sometimes useful) and `goto` (avoid).

## `switch` statements

`switch` picks a branch based on an integer-like value:

```cpp
#include <iostream>

int main() {
    int day{3};

    switch (day) {
    case 1:
        std::cout << "Mon\n";
        break;
    case 2:
        std::cout << "Tue\n";
        break;
    case 3:
        std::cout << "Wed\n";
        break;
    default:
        std::cout << "Other\n";
        break;
    }

    return 0;
}
```

Each `case` labels a branch. `break` leaves the `switch`. Without `break`, execution **falls through** into the next case (usually a bug).

`default` runs when no case matches.

### Same idea with `if` / `else if`

```cpp
if (day == 1) {
    std::cout << "Mon\n";
} else if (day == 2) {
    std::cout << "Tue\n";
} else if (day == 3) {
    std::cout << "Wed\n";
} else {
    std::cout << "Other\n";
}
```

PREFERENCE: This book will mostly use `if` / `else if` chains. They are flexible and avoid `switch` details like forgotten `break` and fall through. Many programmers like `switch`. You may see them in other codebases. They do not unlock anything required here.

NOTE: Later you might use lookup tables or maps for many cases. That is an advanced topic. `if` chains are enough for now.

## `switch` vs `if` vs map (side by side)

Here are three ways to solve the same problem. Given an integer `day`, print a short name.

### One program that runs all three

```cpp
#include <iostream>
#include <unordered_map>

void printDaySwitch(int day) {
    switch (day) {
    case 1: std::cout << "Mon\n"; break;
    case 2: std::cout << "Tue\n"; break;
    case 3: std::cout << "Wed\n"; break;
    default: std::cout << "Other\n"; break;
    }
}

void printDayIf(int day) {
    if (day == 1) std::cout << "Mon\n";
    else if (day == 2) std::cout << "Tue\n";
    else if (day == 3) std::cout << "Wed\n";
    else std::cout << "Other\n";
}

void printDayMap(int day) {
    const std::unordered_map<int, const char*> names{
        {1, "Mon"},
        {2, "Tue"},
        {3, "Wed"},
    };
    auto it = names.find(day);
    std::cout << (it != names.end() ? it->second : "Other") << '\n';
}

int main() {
    int day{3};
    printDaySwitch(day);
    printDayIf(day);
    printDayMap(day);
    return 0;
}
```

PREFERENCE: My bias is clear. I do not like `switch` in beginner code. It adds mental overhead (`break`, fall through rules, and awkward edits) without teaching anything new that you cannot learn with `if` / `else if`.

## `goto`: do not use

`goto` jumps to a label elsewhere in the same function. It exists in C++ but makes debugging and reading the call stack very hard.

```cpp
#include <iostream>

int main() {
    std::cout << "Before goto\n";

    goto skip;

    std::cout << "This line is skipped!\n";

skip:
    std::cout << "After goto (label reached)\n";
    return 0;
}
```

Why avoid `goto`:

- Execution can jump in ways that are hard to follow
- Refactoring and debugging become painful
- Structured control (`if`, loops, functions) solves the same problems more clearly

PREFERENCE: Treat any `goto` in code as an immediate no. Use structured control flow instead.

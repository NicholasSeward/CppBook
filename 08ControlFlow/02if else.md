# If and Else

Programs often need to do one thing or another based on data. That is called **branching** or **control flow**.

In C++, the main branching tool is the `if` statement.

## The basic `if`

An `if` runs a block only when its condition evaluates to `true`.

```cpp
#include <iostream>

int main() {
    int temperature{95};

    if (temperature > 90) {
        std::cout << "It is hot\n";
    }

    return 0;
}
```

The expression in parentheses is a **condition**. It evaluates to a `bool`.

## Multiple statements

Curly braces let you run multiple statements in one branch:

```cpp
#include <iostream>

int main() {
    int score{42};

    if (score >= 40) {
        std::cout << "Pass\n";
        std::cout << "Nice work\n";
    }

    return 0;
}
```

PREFERENCE: Always use braces at first. They prevent bugs when you add a second line later.

## `if` with `else`

Use `else` for the opposite branch:

```cpp
#include <iostream>

int main() {
    int age{16};

    if (age >= 18) {
        std::cout << "adult\n";
    } else {
        std::cout << "minor\n";
    }

    return 0;
}
```

NOTE: With `if` and `else`, **exactly one** branch runs. Either the `if` block runs, or the `else` block runs.

If there is **no** `else`, **at most one** block runs. If the condition is true, the `if` block runs. If the condition is false, nothing runs and execution continues after the `if`.

## Multiple options with `else if`

Use `else if` when you have more than two cases:

```cpp
#include <iostream>

int main() {
    int grade{85};

    if (grade >= 90) {
        std::cout << "A\n";
    } else if (grade >= 80) {
        std::cout << "B\n";
    } else if (grade >= 70) {
        std::cout << "C\n";
    } else {
        std::cout << "Needs work\n";
    }

    return 0;
}
```

Only the first true condition runs. If none are true, the `else` runs (if present).

## Chaining vs separate `if` statements

When cases are connected, **chain** with `else if` instead of writing many separate `if` statements:

```cpp
// Repetitive and wrong logic risk
int g{85};
if (g >= 90) std::cout << "A\n";
if (g >= 80) std::cout << "B\n";  // might also run!
if (g >= 70) std::cout << "C\n";

// Chained: at most one block runs
if (g >= 90) {
    std::cout << "A\n";
} else if (g >= 80) {
    std::cout << "B\n";
} else if (g >= 70) {
    std::cout << "C\n";
}
```

PREFERENCE: Use chaining when the cases are mutually exclusive. Do not repeat yourself (DRY) when `else if` makes the intent clear.

## `=` vs `==`

`=` is assignment. `==` compares for equality.

```cpp
int x{0};
if (x = 10) { }   // assigns 10, condition is true (non zero)

if (x == 10) { }  // compares, no assignment
```

NOTE: Enable compiler warnings. Many compilers catch `if (x = 10)` mistakes.

## Non booleans as conditions

C++ allows non booleans in conditions. Zero is false. Non zero is true:

```cpp
#include <iostream>

int main() {
    int x{0};

    if (x) {
        std::cout << "x is non zero\n";
    } else {
        std::cout << "x is zero\n";
    }

    return 0;
}
```

PREFERENCE: Prefer explicit comparisons such as `x != 0` in beginner code.
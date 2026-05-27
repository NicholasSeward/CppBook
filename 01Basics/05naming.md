# Naming

Good names make code easier to read. Bad names turn small programs into puzzles. Naming is how you keep code **self-documenting** without extra noise.

## Keywords

C++ reserves certain words as **keywords**. You cannot use them as variable or function names. They have special meaning to the compiler.

- int
- char
- bool
- float
- double
- void
- if
- else
- for
- while
- return
- class
- struct
- public
- private
- namespace
- using
- const
- auto

This is not the full list. Your editor will often highlight keywords for you.

## Rules for names (identifiers)

A **name** (identifier) for a variable or function must follow these rules:

1. **Not a keyword** (`int score;` is fine, `int int;` is not).
2. **Only letters, digits, and underscore** (`_`). No spaces, no `-`, no `@`.
3. **Cannot start with a digit** (the compiler would read it as a number literal).

C++ is **case sensitive**. `score`, `Score`, and `SCORE` are three different names.

```cpp
#include <iostream>

int main() {
    int score{10};
    int Score{20};

    std::cout << score << '\n';  // prints 10
    std::cout << Score << '\n';  // prints 20
    return 0;
}
```

Valid vs invalid examples:

| Name | Valid? | Why |
|------|--------|-----|
| `playerScore` | yes | letters, camelCase |
| `_hidden` | yes | underscore allowed |
| `score2` | yes | digit not first |
| `2score` | no | starts with digit |
| `my-score` | no | hyphen not allowed |
| `my score` | no | spaces not allowed |
| `return` | no | keyword |

## Naming styles

Across programming (not only C++), you will see:

| Style | Example | Common use |
|-------|---------|------------|
| camelCase | `playerScore` | variables, functions |
| PascalCase (TitleCase) | `PlayerScore` | class names (later) |
| snake_case | `player_score` | some libraries, C code |
| SCREAMING_SNAKE_CASE | `MAX_PLAYERS` | constants and macros |

PREFERENCE: In this book, use **camelCase** for variables and functions. Use **PascalCase** for class names when we reach object-oriented programming.

NOTE: On a real team, match the **existing codebase**. If every file uses `snake_case`, do not introduce camelCase. When unsure here, use camelCase.

## Guidelines

- **Say what is stored.** `totalPrice` beats `tp` for anything that lives more than a few lines.
- **Short names are OK in tiny scopes.** Loop index `i`, `j` is normal. A one-line temp can be short if the meaning is obvious.
- **Scope matters.** A local variable in a five-line function can be shorter than a global setting read across the whole program.
- **Do not overdo length.** `numPrintableChars` is usually enough. If you need `numCharsExcludingWhitespaceAndPunctuation`, a shorter name plus a comment often reads better.

### Good, bad, and in-between

| Name | Verdict | Why |
|------|---------|-----|
| `age` | good | clear for a person's age |
| `a` | either | fine in a three-line loop, weak in a 50-line function |
| `data` | bad | too vague; data of what? |
| `numStudents` | good | count of students |
| `n` | either | OK as loop counter, poor for "number of students" at file scope |
| `temp` | either | OK for swap logic, vague for "tax rate" |
| `taxRatePercent` | good | units hinted in the name |
| `x1`, `x2` | either | OK for math coordinates, poor for "first user" and "second user" |
| `MAX_SIZE` | good | constant cap, screaming snake is conventional |

```cpp
// Harder to read at a glance
int x{};
int y{};
std::cin >> x >> y;
std::cout << x + y;

// Clearer names for the same idea
int homeScore{};
int awayScore{};
std::cin >> homeScore >> awayScore;
std::cout << homeScore + awayScore;
```

PROTIP: Rename while you learn. The first name you pick does not have to be permanent. Clear names save more time than clever short ones.

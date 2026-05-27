# Comments

Comments are notes in your source code that the compiler **ignores**. They exist for you and other humans—future you included. Comments are one of the first tools for explaining code, leaving reminders, and turning lines on or off without deleting them.

## What is a comment?

A **comment** is text that is not compiled into the program. The compiler skips it completely. Your program’s behavior does not change because of a comment (unless you use a comment to disable a line of real code).

## Single-line comments

C++ supports single-line comments with `//`. Everything from `//` to the end of that line is ignored.

A comment can take a full line:

```cpp
// Print a greeting (full-line comment)
#include <iostream>

int main() {
    std::cout << "Hello\n";  // end-of-line comment
    return 0;
}
```

Use full-line comments for bigger explanations; use end-of-line comments for short notes on the same line as code.

PREFERENCE: Prefer full-line `//` comments placed **immediately above** the code they describe. End-of-line comments are fine when they stay short and the line is still easy to read.

PROTIP: Most [integrated development environments](https://en.wikipedia.org/wiki/Integrated_development_environment) (IDEs) and the inline editor in this book let you toggle comments with **Ctrl+/** (or **Cmd+/** on macOS). Exact shortcuts vary by editor. If you repeat a tedious edit, look for a shortcut or command. There often is one.

## Multiline comments

Block comments start with `/*` and end with `*/`. They can span several lines or sit in the middle of a line:

```cpp
#include <iostream>

/* A multiline comment
   can cover several lines. */

int main() {
    std::cout << /* inline */ "Hi\n";
    return 0;
}
```

Some people align `*` down the left edge for readability—that is style only:

```cpp
/*
 * Comment block with aligned stars.
 * Still one block comment.
 */
```

You **cannot nest** block comments in standard C++. The first `*/` closes the comment:

```cpp
/* outer starts
   /* inner attempt */   // this */ ends the outer comment early!
   oops;                  // now the compiler sees this as code
*/
```

PROTIP: Your editor’s **syntax highlighter** shows what is inside a comment. Try “nesting” block comments and watch colors change—that makes it obvious where the compiler thinks the comment really ends.

## Why use comments?

Common reasons:

- **Explain** non-obvious logic (why, not what the syntax already says)
- **Deactivate** code temporarily while debugging
- **Mark work** left to do (`TODO`, `FIXME`)
- **Document** public APIs for tools that generate reference docs (later topics)

Comments do not earn extra credit. Use them when they add clarity.

## Good and bad comments

Apply the **“no duh” test**: read the comment aloud. If it only repeats what the code already says, delete it.

Good naming, small functions, and straightforward logic make code **self-documenting**. Many comments become unnecessary.

### Unnecessary

```cpp
#include <iostream>

int main() {
    int x = 5;           // set x to 5
    std::cout << x;      // print x
    return 0;            // return 0
}
```

Every comment here restates the obvious.

### Helpful

```cpp
#include <iostream>

int main() {
    // Billing uses net days; weekends are excluded in calculateDueDate().
    int dueDays = 14;
    std::cout << "Due in " << dueDays << " days\n";
    return 0;
}
```

The comment explains **why** `14` is there. Something the line of code alone does not convey.

### Clear enough without comments

```cpp
#include <iostream>

int totalPrice(int itemCount, int pricePerItem) {
    return itemCount * pricePerItem;
}

int main() {
    std::cout << totalPrice(3, 1200) << '\n';
    return 0;
}
```

The function and variable names carry the meaning. No comment is required for a reader who knows basic C++.

Do not stress over perfection. Comments are cheap. The main audience is **future you**: if something feels fuzzy today, it will be harder to parse tomorrow.

NOTE: This book sometimes adds comments inside examples to point at new syntax. In your own projects those lines would often be noise—we include them for teaching.

## Turn code on and off

Commenting out lines is a quick way to experiment. Only active (uncommented) statements run:

```cpp
#include <iostream>

int main() {
    std::cout << "Line 1\n";
    // std::cout << "Line 2\n";
    std::cout << "Line 3\n";
    return 0;
}
```

Run it, then remove the `//` before the second `cout` and run again. Try commenting out `Line 1` or `Line 3` and predict the output before you compile.
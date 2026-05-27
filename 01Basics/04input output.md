# Input and Output

Programs are more interesting when they can **interact** with a user. You have already printed text with `std::cout`. This chapter goes deeper on **output**, then adds **input** at runtime using the C++ standard library stream tools from [variables](03variables.md) and [hello world](01hello%20world.md).

## `iostream`

The C++ [standard library](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) provides `<iostream>` for common console I/O.

```cpp
#include <iostream>
```

Important objects:

| Name | Role |
|------|------|
| `std::cout` | character **output** stream (usually the terminal) |
| `std::cin` | character **input** stream (usually the keyboard) |

## Output with `std::cout`

`std::cout` sends data to the console so you can see it.

```cpp
#include <iostream>

int main() {
    std::cout << "Hello again\n";
    return 0;
}
```

### The insertion operator `<<`

`<<` is the **insertion operator**. It inserts the value on the **right** into the stream on the **left**. It also returns the stream on the left, so you can chain more insertions:

```cpp
#include <iostream>

int main() {
    std::cout << "Score: " << 42 << " points\n";
    return 0;
}
```

You can print **literals** and **variables**:

```cpp
#include <iostream>

int main() {
    int score{42};
    std::cout << "Score: " << score << '\n';
    return 0;
}
```

### New lines: `std::endl` vs `\n`

`std::endl` ends a line and **flushes** the output buffer (forces pending text to show up now):

```cpp
std::cout << "Line 1" << std::endl;
std::cout << "Line 2" << std::endl;
```

The escape sequence `\n` also starts a new line, but it does not flush by itself:

```cpp
std::cout << "Line 1\n";
std::cout << "Line 2\n";
```

NOTE: `\n` is often slightly faster for heavy logging because it skips the extra flush. For interactive prompts, `std::endl` can help make sure the user sees the prompt before input. In practice, either is fine in this course. This book uses both.

HISTORY: `\n` is an [ASCII](https://en.wikipedia.org/wiki/ASCII) **control character** (line feed, value 10). Printers and terminals adopted it long ago. Other escape sequences still show up in tools: `\r` (carriage return, value 13) returns to the start of the current line; `\b` (backspace, value 8) moves the cursor back one column.

A tiny progress-style loop using `\r`:

```cpp
#include <iostream>

int main() {
    for (int i{0}; i <= 1000000; ++i) {
        std::cout << "\rProgress: " << i << "/1000000 ";
    }
    std::cout << '\n';
    return 0;
}
```

`\r` lets you overwrite the same line instead of printing 1 million separate lines.

## Input with `std::cin`

For input, the operator direction flips. `>>` is the **extraction operator**. It reads from the stream on the left and stores into the variable on the right:

```cpp
#include <iostream>

int main() {
    int age{};

    std::cout << "Enter your age: ";
    std::cin >> age;
    std::cout << "You entered " << age << '\n';

    return 0;
}
```

### Prompts

Always **prompt** the user so they know what to type.

PREFERENCE: Print the prompt **without** a trailing newline so the cursor stays on the same line as the question. Put a **space** after the colon. It still works without the space, but it looks odd to many users.

```cpp
std::cout << "Enter your age: ";  // space after colon, no endl yet
```

### Multiple reads on one line

Whitespace (spaces, tabs, newlines) separates tokens. You can read more than one value:

```cpp
#include <iostream>

int main() {
    int a{};
    int b{};

    std::cout << "Enter two integers separated by a space: ";
    std::cin >> a >> b;
    std::cout << "a = " << a << ", b = " << b << '\n';

    return 0;
}
```

Typing `3 14` sets `a` to 3 and `b` to 14.

### Extra text stays in the buffer

If the user types extra characters after the numbers, `>>` for integers stops at the first non-number. The rest waits in the **input buffer**.

```cpp
#include <iostream>
#include <string>

int main() {
    int n{};
    std::string leftover;

    std::cout << "Enter an int, then some text: ";
    std::cin >> n;
    std::cin >> leftover;

    std::cout << "n = " << n << '\n';
    std::cout << "next token: " << leftover << '\n';

    return 0;
}
```

Try input: `42 is the answer`

- First read gets `42`
- Second read gets `is` (the next token)
- `the answer` remains buffered for a later read

Run the program twice with the same typing if your environment reuses input, or type fresh input each run, and watch what the second read picks up.

NOTE: Reading a full line of text, or recovering from bad input (letters when you expected a number), needs more tools (`std::getline`, clear the stream state, etc.). For now we assume the user follows directions.
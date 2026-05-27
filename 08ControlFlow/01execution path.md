# Execution Path

A program starts in `main` and normally runs **line by line** from top to bottom. That order is the **execution path**.

```cpp
#include <iostream>

int main() {
    std::cout << "Step 1\n";
    std::cout << "Step 2\n";
    std::cout << "Step 3\n";
    return 0;
}
```

Output is always Step 1, then 2, then 3. No surprises.

## When line by line is not enough

Real programs need to:

- **branch** (do this or that)
- **loop** (repeat until done)
- **call functions** (jump to helper code and come back)
- **stop** (end the program or a function)

Those are **control flow** tools. They change which line runs next.

## Kinds of control flow (overview)

| Kind | Examples | Meaning |
|------|----------|---------|
| Sequential | normal statements | run the next line |
| Conditional | `if`, `else`, `switch` | pick a branch |
| Loops | `while`, `for` | repeat while a condition holds |
| Function calls | `printHello();` | run another function, then return |
| Halts | `return`, `std::exit` | leave a function or end the program |
| Jumps | `goto` (avoid), `break`, `continue` | jump within loops (covered later) |
| Exceptions | `throw` (much later) | error handling |

This book focuses on **conditionals** and **loops** first.
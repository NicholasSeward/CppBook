# Debugging Tools

Once you know *that* something is wrong, tools help you learn *where* and *why*.

This chapter covers techniques you can use in any editor, plus the integrated debugger built into many IDEs.

## Commenting out code

If a large block fails, comment out the middle and see if the program works again. Then add lines back one at a time until the bug returns.

```cpp
#include <iostream>

int stepA()
{
    return 1;
}

int stepB()
{
    return 2;
}

int main()
{
    int total{stepA()};
    // total += stepB();  // comment out suspect code
    std::cout << total << '\n';
    return 0;
}
```

If `total` is correct without `stepB`, the bug is likely inside `stepB` or how its result is used.

## Validate control flow

Put a print at the start of each function so you know it was called.

```cpp
#include <iostream>

void loadData()
{
    std::cout << "loadData called\n";
}

void processData()
{
    std::cout << "processData called\n";
}

int main()
{
    loadData();
    processData();
    return 0;
}
```

If you expected `processData` but never see its message, control never reached it. Trace backward from there.

## Print values

Print variables at key points to see what the program actually holds.

```cpp
#include <iostream>

int main()
{
    int count{0};

    for (int i{0}; i < 5; ++i)
    {
        count += i;
        std::cout << "i=" << i << " count=" << count << '\n';
    }

    return 0;
}
```

Match the printed trail to what you expected step by step.

> NOTE: Debug prints are a great beginner tactic. As programs grow, too many prints clutter output and source code. Later you may prefer logging or a debugger, but prints remain useful forever for quick checks.

## Conditional debug output

Wrap noisy prints in a flag so you can turn them on and off.

```cpp
#include <iostream>

bool debugMode{true};

int add(int a, int b)
{
    int result{a + b};

    if (debugMode)
    {
        std::cout << "add(" << a << ", " << b << ") = " << result << '\n';
    }

    return result;
}

int main()
{
    std::cout << add(2, 3) << '\n';
    return 0;
}
```

For larger projects, people sometimes use the preprocessor:

```
#define DEBUG 1

#if DEBUG
    std::cout << "debug info\n";
#endif
```

Set `DEBUG` to `0` for a quiet build.

## Logging to a file

Instead of flooding the terminal, append messages to a log file. That helps when the bug only appears after many lines of output.

```cpp
#include <fstream>
#include <iostream>

void logMessage(const std::string& text)
{
    std::ofstream log{"debug.log", std::ios::app};

    if (log)
    {
        log << text << '\n';
    }
}

int main()
{
    logMessage("program started");
    std::cout << "Hello\n";
    logMessage("after hello");
    return 0;
}
```

Open `debug.log` after the run to review the trail.

## Integrated debugger

An **integrated debugger** attaches to your running program and lets you pause execution, inspect state, and step through code line by line.

Core ideas (names vary slightly by IDE):

| Action | What it does |
|--------|----------------|
| **Breakpoint** | Pause when execution reaches a line |
| **Continue / Resume** | Run until the next breakpoint |
| **Step over** | Run the current line; if it is a function call, run the whole call without stepping inside |
| **Step into** | Enter the function being called |
| **Step out** | Finish the current function and pause in the caller |
| **Stop** | End the debug session |
| **Watch** | Show the value of a variable or expression whenever you pause |
| **Call stack** | Show which functions called which to reach the current line |

There is usually **no step back** in everyday debuggers. Some research tools can reverse execution, but you should not expect it in VS Code or typical classroom setups. Do not mash "step" hoping to undo a line.

### VS Code basics

With the C++ extension and a `launch.json` debug configuration:

1. Click in the gutter left of a line number to set a **breakpoint** (red dot).
2. Press **F5** or use **Run and Debug** to start with the debugger.
3. When paused, hover variables to see values, or add them to the **Watch** panel.
4. Use **F10** (step over), **F11** (step into), **Shift+F11** (step out), **F5** (continue).

The **Call Stack** panel shows how you arrived at the current function. That is invaluable when the bug is three levels deep.

### Watching expressions

You can watch not only variable names but simple expressions: `count + 1`, `values.at(i)`, `std::cin.fail()`. If an expression is invalid at the current pause point, the watch may show an error until execution reaches a valid scope.

> PROTIP: Set a breakpoint just *after* the line you suspect, then step **back** in your head by reading the previous lines. Forward stepping is reliable; "undo" is not.

## Try it now

### Exercise 1: Trace a loop with prints

Prompt: The loop should print `Final count: 10`, but it hangs. Add `std::cout` lines to see `i` and `count` each iteration, then fix the bug.

```cpp
// @file: main.cpp
#include <iostream>

int main()
{
    int count{0};
    int i{0};

    while (i < 5)
    {
        // TODO: print i and count here
        count += i;
        // bug: i never increases
    }

    std::cout << "Final count: " << count << '\n';
    return 0;
}
```

### Exercise 2: Log to a file

Prompt: Finish `logStep` so each call appends one line to `debug.log`. Call it twice from `main`.

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

void logStep(const std::string& message)
{
    // TODO: open debug.log with std::ios::app and write message + '\n'
}

int main()
{
    logStep("program started");
    std::cout << "Working...\n";
    logStep("after work");

    return 0;
}
```

### Exercise 3: Debugger practice (IDE)

In your IDE (not the playground): set a breakpoint inside a `for` loop, run the debugger, and watch a variable change. Use **Step over** and **Step into** on one function call and read the **Call Stack** panel.

# The Programming Process

Programming is not only typing code. It matches the **engineering design process**: define the problem, explore options, build a small piece, test it, and repeat.

## The loop

1. **Define the problem**  
   What should the program do? For whom? What counts as success?

2. **Consider and research solutions**  
   What algorithms, libraries, or designs might work?  What have others done?

3. **Pick a small piece you can code and test**  
   Do not build everything at once. Choose the next slice that moves you forward.

4. **Test it**  
   Run the program. Check outputs, edge cases, and failures.

Then loop back to step 1, 2, or 3 based on what you learned.

```text
Define -> Research -> Build small -> Test -> (repeat)
```

## Why small steps matter

If you add fifty lines and something breaks, you do not know which line caused it. If you add five lines and test, you know exactly what changed.

> PREFERENCE: Use **iterative development**. Add a little, run a little. Keep the program working most of the time.

## Hello world fits the pattern

The tradition of starting with hello world is not just ceremony. A tiny program checks that your editor, compiler, linker, and runtime all work. When you start a new language, project, or machine, begin simple so you can tell whether a failure is **your code** or **the environment**.

> NOTE: Even hello world depends on a huge stack (OS, terminal, compiler, libraries). Starting small is how you isolate problems.

Here is a simple hello world program in C++:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```
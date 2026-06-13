# Command Line Arguments

So far, many programs get input from `std::cin` or from a fixed filename in code. Real tools often read **command-line arguments**: the extra words you type after the program name when you launch it.

```text
sumfile numbers.txt totals.txt
       ^^^^^^^^^ ^^^^^^^^^^^
       argv[1]   argv[2]
```

That style is better for **automation**: scripts, other programs, and servers can run your tool without a human typing answers at a prompt.

## `main` with `argc` and `argv`

A typical entry point that accepts arguments:

```cpp
int main(int argc, char* argv[])
```

| Parameter | Meaning |
|-----------|---------|
| `argc` | **argument count** (how many strings) |
| `argv` | **argument vector** (array of C-style strings) |

Index `0` is usually the program name. User arguments start at `1`.

```cpp
// @args: alpha beta gamma
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "argc = " << argc << '\n';
    for (int i{0}; i < argc; ++i)
    {
        std::cout << "argv[" << i << "] = " << argv[i] << '\n';
    }
    return 0;
}
```

On a normal shell you might run:

```text
./showargs alpha beta gamma
```

In TxtBook, the command line arg input supplies those tokens when you press **Run**.

> NOTE: `argv[0]` is the program name. In a playground it may look like a temp path, not the filename you typed in the lesson. That is fine. Real `argv[0]` behavior depends on how the OS launched the program.

## Why `argc` exists

C-style arrays do not store their own length. A C-style string ends at the first `'\0'` (null character), but a list of string pointers does not tell you how many slots are valid.

`argc` answers: **how many `argv` slots matter**.

> NOTE: `argv` uses **C-style strings** (`char*`), not `std::string`. Each `argv[i]` points at characters in memory ending with `'\0'`. A full pointer chapter comes later. For now: use `argv[i]` like a text literal, or copy into `std::string`.

## Interactive input vs command-line args

Imagine a program that sums integers from a file and writes the total to another file.

**Interactive** (human types paths each run):

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::string inPath{};
    std::string outPath{};
    std::cout << "Input file: ";
    std::cin >> inPath;
    std::cout << "Output file: ";
    std::cin >> outPath;

    std::ifstream fin{inPath};
    if (!fin)
    {
        std::cerr << "Could not open " << inPath << '\n';
        return 1;
    }

    std::ofstream fout{outPath};
    if (!fout)
    {
        std::cerr << "Could not open " << outPath << '\n';
        return 1;
    }

    int value{};
    int total{};
    while (fin >> value)
    {
        total += value;
    }

    fout << total << '\n';
    std::cout << "Wrote total " << total << " to " << outPath << '\n';
    return 0;
}

// @file: numbers.txt
10 20 5
```

> PROTIP: In the playground, when prompted type `numbers.txt` then `totals.txt`. After **Run**, open the `totals.txt` tab to see `35`.

Fine for a person at the keyboard. Awkward for a script that should run unattended.

**Command-line** (paths passed in at launch):

```cpp
// @args: numbers.txt totals.txt
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: sumfile <input> <output>\n";
        return 1;
    }

    std::ifstream fin{argv[1]};
    if (!fin)
    {
        std::cerr << "Could not open " << argv[1] << '\n';
        return 1;
    }

    std::ofstream fout{argv[2]};
    if (!fout)
    {
        std::cerr << "Could not open " << argv[2] << '\n';
        return 1;
    }

    int value{};
    int total{};
    while (fin >> value)
    {
        total += value;
    }

    fout << total << '\n';
    std::cout << "Wrote total " << total << " to " << argv[2] << '\n';
    return 0;
}

// @file: numbers.txt
10 20 5
```

No prompts. Another program (or a shell script) can call yours with the right paths every time.

## Use cases

| Situation | Why argv helps |
|-----------|----------------|
| Build scripts | `compiler main.cpp -o app` |
| Batch tools | process hundreds of files in a loop |
| Server calls a helper | thumbnail tool: `makeThumb upload.png 128` |
| Piping workflows | one program's output feeds the next |

A file-upload service might shell out to `makeThumb photo.jpg 200` when a user uploads an image. The web code does not reimplement thumbnail logic; it launches your CLI tool with arguments.

## Parsing numeric arguments

If an argument should be a number, convert from text.

**`std::stoi`** (simple):

```cpp
// @args: 42
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    int n{std::stoi(argv[1])};
    std::cout << n + 1 << '\n';
    return 0;
}
```

**`std::istringstream`** (when one argument holds multiple numbers):

```cpp
// @args: "10 20 30"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    std::istringstream input{argv[1]};
    int value{};
    int total{0};
    while (input >> value)
    {
        total += value;
    }

    std::cout << "Sum: " << total << '\n';
    return 0;
}
```

## Spaces and quotes

The operating system splits the command line into arguments. Usually splits happen at **spaces**.

To pass one argument that contains a space, use **quotes** in the shell. The quotes are not part of the argument text.

```cpp
// @args: one "two words" three
#include <iostream>

int main(int argc, char* argv[])
{
    for (int i{0}; i < argc; ++i)
    {
        std::cout << argv[i] << '\n';
    }
    return 0;
}
```

Output:

```text
(showargs or playground name)
one
two words
three
```

To put a literal quote inside a quoted argument, escape it the way your shell expects. In many shells:

```text
./showargs "say \"hi\""
```

passes one argument: `say "hi"`.

> NOTE: Quote rules are shell-specific. The lesson idea is the same: the shell builds `argv` before your program runs. Your C++ code only sees the finished strings in `argv[0]`, `argv[1]`, and so on.

> PREFERENCE: Prefer `std::string` and `std::vector<std::string>` in new code. Use `argc` / `argv` in `main` because that is how the OS hands you launch arguments.

## Try it now

### Exercise 1: Greet from argv

Prompt: If `argc >= 2`, print `Hello, <argv[1]>!` Otherwise print usage and return `1`.

```cpp
// @args: Ada
#include <iostream>

int main(int argc, char* argv[])
{
    // TODO: check argc, print greeting or usage

    return 0;
}
```

### Exercise 2: Repeat count from argv

Prompt: Use `std::stoi` on `argv[1]` to print `"ha"` that many times (reuse the `printN` idea from [Recursion](18recursion.md)).

```cpp
// @args: 4
#include <iostream>
#include <string>

void printN(int n, const std::string& str)
{
    if (n <= 0)
    {
        return;
    }
    std::cout << str;
    printN(n - 1, str);
}

int main(int argc, char* argv[])
{
    // TODO: stoi(argv[1]) and call printN

    return 0;
}
```

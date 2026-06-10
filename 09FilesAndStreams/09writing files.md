# Writing Files

Writing to a file is like printing to `std::cout`, but the bytes go to disk through `std::ofstream`.

This book will name stream objects `fin` and `fout` to match with `cin` and `cout`.

## Create an output stream

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path);

int main()
{
    std::ofstream fout{"scores.txt"};

    if (!fout)
    {
        std::cerr << "Could not open scores.txt for writing\n";
        return 1;
    }

    fout << "Ada 98\n";
    fout << "Grace 100\n";
    fout.close();

    showFileContents("scores.txt");
    return 0;
}

// @file: show_file.cpp hidden
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path)
{
    std::ifstream fin{path};

    if (!fin)
    {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::cout << "=================\n";
    std::cout << path << "\n";
    std::cout << "=================\n";

    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    std::cout << "=================\n";
}
```

Use `<<` the same way you do with `std::cout`.

`showFileContents` reads the file back and prints it to the console with clear dividers.

After **Run**, TxtBook also adds or updates a tab for `scores.txt` so you can inspect the file directly. The helper still helps later when you need to read back before `flush()` or `close()` and the tab may not reflect buffered data yet.

The helper lives in a **hidden** tab so you can focus on writing in `main.cpp`.

## Check that the file opened

Always test the stream after opening:

```
if (!fout)
{
    std::cerr << "Open failed\n";
    return 1;
}
```

A failed open might mean a bad path, missing folder, or permission problem.

## Buffering, flush, and close

`fout` is **buffered**. Characters may sit in memory until the buffer fills, you flush, or the stream closes.

### Reading back too soon

If you write but do not `flush()` or `close()`, another read of the file may not see the new text yet.

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path);

int main()
{
    std::ofstream fout{"pending.txt"};

    if (!fout)
    {
        std::cerr << "Could not open pending.txt\n";
        return 1;
    }

    fout << "Waiting in the buffer\n";
    showFileContents("pending.txt");

    return 0;
}

// @file: show_file.cpp hidden
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path)
{
    std::ifstream fin{path};

    if (!fin)
    {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::cout << "=================\n";
    std::cout << path << "\n";
    std::cout << "=================\n";

    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    std::cout << "=================\n";
}

// @file: pending.txt
```

Run this program. `showFileContents` often prints the dividers and the filename, but **no file lines** in between. The string you wrote is probably still in the output stream's buffer, not on disk yet.

When `main` ends, `fout` is destroyed and the buffer is usually flushed then. You still could not see the line when you read early.

### Using `flush()` and `close()`

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path);

int main()
{
    std::ofstream fout{"message.txt"};

    if (!fout)
    {
        std::cerr << "Could not open message.txt\n";
        return 1;
    }

    fout << "Important message\n";
    fout.flush();

    showFileContents("message.txt");

    fout << "Second line\n";
    fout.close();

    showFileContents("message.txt");
    return 0;
}

// @file: show_file.cpp hidden
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path)
{
    std::ifstream fin{path};

    if (!fin)
    {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::cout << "=================\n";
    std::cout << path << "\n";
    std::cout << "=================\n";

    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    std::cout << "=================\n";
}

// @file: message.txt
Important message
Second line
```

`flush()` pushes buffered output toward the file before you read it back.

`close()` ends the session with the file and flushes.

When `fout` is destroyed at the end of a block, the destructor also closes the file. Explicit `close()` makes the timing obvious in teaching examples.

> NOTE: If you need to be sure data reached disk before continuing, call `flush()` or `close()` before you assume another program can read the file.

## Formatted output to a file

Manipulators from `<iomanip>` work on `std::ofstream`:

```cpp
// @file: main.cpp
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

void showFileContents(const std::string& path);

int main()
{
    std::ofstream fout{"report.txt"};

    if (!fout)
    {
        std::cerr << "Could not open report.txt\n";
        return 1;
    }

    double average{87.5};
    fout << std::fixed << std::setprecision(2) << average << "\n";
    fout.close();

    showFileContents("report.txt");
    return 0;
}

// @file: show_file.cpp hidden
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path)
{
    std::ifstream fin{path};

    if (!fin)
    {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::cout << "=================\n";
    std::cout << path << "\n";
    std::cout << "=================\n";

    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    std::cout << "=================\n";
}
```

## Try it now

### Exercise 1: Write two lines

Prompt: Write your name and a number to `output.txt`, then call `showFileContents` to verify.

```cpp
// @file: main.cpp
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path);

int main()
{
    std::ofstream fout{"output.txt"};

    // TODO: Check fout, write two lines, close.
    // TODO: Call showFileContents("output.txt").

    return 0;
}

// @file: show_file.cpp hidden
#include <fstream>
#include <iostream>
#include <string>

void showFileContents(const std::string& path)
{
    std::ifstream fin{path};

    if (!fin)
    {
        std::cerr << "Could not open " << path << "\n";
        return;
    }

    std::cout << "=================\n";
    std::cout << path << "\n";
    std::cout << "=================\n";

    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    std::cout << "=================\n";
}
```
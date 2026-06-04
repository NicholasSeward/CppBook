# Append Mode, Reopen, and Seeking

Files are not only "create from scratch and overwrite."

Sometimes you **append** new lines to a log. Sometimes you **close and reopen** a file to continue work.

## Append mode with `app`

Open with `std::ios::app` to add at the **end** without erasing earlier content:

```cpp
#include <fstream>
#include <iostream>
#include <string>

void logEvent(const std::string& message)
{
    std::ofstream log{"events.log", std::ios::app};

    if (!log)
    {
        std::cerr << "Could not open log file\n";
        return;
    }

    log << message << "\n";
    log.flush();
}

void printLog()
{
    std::ifstream fin{"events.log"};
    std::string line{};

    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }
}

int main()
{
    logEvent("Program started");
    logEvent("User clicked Start");
    printLog();
    return 0;
}
```

Append mode is ideal for **log files** that grow over time.

## Write, close, reopen

```cpp
#include <fstream>
#include <iostream>

int main()
{
    {
        std::ofstream fout{"notes.txt"};
        fout << "Line 1\n";
        fout.close();
    }

    {
        std::ofstream fout{"notes.txt", std::ios::app};
        fout << "Line 2\n";
        fout.close();
    }

    std::ifstream fin{"notes.txt"};
    std::string line{};
    while (std::getline(fin, line))
    {
        std::cout << line << "\n";
    }

    return 0;
}
```

Without `app`, opening `notes.txt` again for output would typically **truncate** (erase) the file first.

| Open style | Typical effect on existing file |
|------------|----------------------------------|
| default output | truncate, then write from start |
| `std::ios::app` | keep content, add at end |

## `seekg` and `seekp`

Streams track a **position**:

- `seekg` moves the **get** position (reading)
- `seekp` moves the **put** position (writing)

```cpp
#include <fstream>
#include <iostream>

int main()
{
    std::fstream file{"data.txt", std::ios::in | std::ios::out};

    file.seekg(0);
    char ch{};
    file.get(ch);
    std::cout << "First character: " << ch << "\n";

    return 0;
}
```

You can move around inside a file, but many programs do not need to.

> NOTE: Data is often read in one or two passes into memory (vectors, structs, maps) where random access is easy. Searching back and forth inside a large file on disk is usually slower and harder to reason about.

## When to seek

Reasonable uses:

- jumping to a known record offset in a binary format
- rereading a header after writing it

For text homework and small projects, sequential read and write is enough.

## Try it now

### Exercise 1: Growing log

Prompt: Call a logging function three times. Confirm `events.log` has three lines.

```cpp
#include <fstream>
#include <iostream>
#include <string>

void appendLine(const std::string& path, const std::string& text)
{
    // TODO: Open with app, write text and newline, flush.
}

int main()
{
    // TODO: appendLine three times with different messages.

    return 0;
}
```
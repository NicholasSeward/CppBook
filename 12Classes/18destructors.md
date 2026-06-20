# Destructors

A **destructor** runs when an object is **destroyed**: it goes out of scope, or you `delete` a pointer to it.

Syntax:

- Same name as the class, with **`~`**
- **No arguments**, **no return type**
- Only **one** destructor per class

```cpp
#include <iostream>

class Message
{
private:
    std::string text;

public:
    Message(std::string msg)
        : text{std::move(msg)}
    {
        std::cout << "Born: " << text << '\n';
    }

    ~Message()
    {
        std::cout << "Dying: " << text << '\n';
    }
};

void greet()
{
    Message m{"Hello"};
    std::cout << "Inside greet\n";
}

int main()
{
    greet();
    std::cout << "Back in main\n";
    return 0;
}
```

Output order:

1. `Born: Hello`
2. `Inside greet`
3. `Dying: Hello` (destructor when `m` leaves `greet`)
4. `Back in main`

## Default destructor

If you write no destructor, the compiler generates an empty **default destructor** that destroys members in reverse order. For `std::string` and `std::vector` members, that is usually enough.

> NOTE: **RAII** (Resource Acquisition Is Initialization) means you **acquire** a resource when an object is **constructed** and **release** it when the object is **destroyed**. The destructor is the cleanup hook. `std::string` frees its memory, `std::ofstream` closes its file, and so on, without you writing extra code. That is RAII in action: scope ends, objects die, resources tidy themselves up.

Destructors mattered more when every class manually deleted raw memory. Smart pointers and STL containers push cleanup into members so destructors "just work."

## When you still write one

- Release a resource (file, socket, lock) not wrapped in RAII yet
- Log or flush on shutdown
- Debug tracing (like the example above)

```cpp
#include <fstream>
#include <iostream>
#include <string>

class LogFile
{
private:
    std::ofstream out;

public:
    LogFile(const std::string& path)
        : out{path, std::ios::app}
    {
    }

    void writeLine(const std::string& line)
    {
        out << line << '\n';
    }

    ~LogFile()
    {
        if (out.is_open())
        {
            out.flush();
        }
    }
};

int main()
{
    LogFile log{"session.log"};
    log.writeLine("Program started");
    return 0;
}
```

## Scope end vs `std::exit`

Normal path: when a local object goes out of scope, its destructor runs. **`std::exit`** ends the program **immediately** and **skips** destructors for local objects on that thread.

Run this, then change `std::exit(0)` to `return 0` and run again:

```cpp
#include <cstdlib>
#include <iostream>
#include <string>

class Message
{
private:
    std::string text;

public:
    Message(std::string msg)
        : text{std::move(msg)}
    {
        std::cout << "Born: " << text << '\n';
    }

    ~Message()
    {
        std::cout << "Dying: " << text << '\n';
    }
};

int main()
{
    Message m{"Goodbye"};
    std::cout << "Calling std::exit...\n";
    std::exit(0);
}
```

With **`std::exit(0)`**, output is:

```
Born: Goodbye
Calling std::exit...
```

No **`Dying:`** line. The destructor never runs.

Replace **`std::exit(0);`** with **`return 0;`**, run again:

```cpp
int main()
{
    Message m{"Goodbye"};
    std::cout << "Leaving main...\n";
    return 0;
}
```

Output:

```
Born: Goodbye
Leaving main...
Dying: Goodbye
```

> PREFERENCE: Prefer **`return`** from `main` or letting scope end. Reserve **`std::exit`** for rare shutdown paths where you accept that local destructors will not run (and any RAII cleanup tied to them is skipped).

## Closing thought

Destruction is the mirror of construction: objects **born** in a scope are **destroyed** when that scope ends. That automatic pairing is what makes RAII work. Write a destructor when your class owns cleanup the compiler cannot guess; otherwise trust members like `std::string` to destroy themselves. Just do not assume destructors run if you **`std::exit`** out of the middle of a function.

## Try it now

### Exercise 1: Count and order destructions

Prompt: Create two `Message` objects in `main` with different strings. Run the program. How many **`Dying:`** lines print, and **in what order** (which message text each time)?

```cpp
#include <iostream>
#include <string>

class Message
{
private:
    std::string text;

public:
    Message(std::string msg)
        : text{std::move(msg)}
    {
        std::cout << "Born: " << text << '\n';
    }

    ~Message()
    {
        std::cout << "Dying: " << text << '\n';
    }
};

int main()
{
    // TODO: create two Message objects (different strings)
    return 0;
}
```

:::details Answer

**Count:** **2** — one **`Dying:`** line per object.

**Order:** reverse of construction. If you wrote `Message first{"Alpha"};` then `Message second{"Beta"};`, you get **`Dying: Beta`**, then **`Dying: Alpha`**. Objects in the same scope are destroyed in **reverse order of construction** (the last one created is destroyed first).

Example full output:

```
Born: Alpha
Born: Beta
Dying: Beta
Dying: Alpha
```

:::

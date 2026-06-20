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

If you write no destructor, the compiler generates an empty **default destructor** that destroys members in reverse order. For `std::string` and `std::vector` members, that is usually enough (**RAII**).

Destructors mattered more when every class manually `delete`d raw memory. Smart pointers and STL containers push cleanup into members so destructors "just work."

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

Destructors for local objects run when their **scope** ends. **`std::exit`** terminates the program without running destructors for local objects on that thread (static objects may still be destroyed at process exit). Prefer returning from `main` or letting scope end normally during learning exercises.

## Try it now

### Exercise 1: Count destructions

Prompt: Create two `Message` objects in `main` (different strings). How many "Dying:" lines print when the program ends?

Answer: **2** (one per object)

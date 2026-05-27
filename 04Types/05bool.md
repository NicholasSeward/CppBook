# `bool`

Sometimes you need a value that is either on or off, yes or no, true or false. C++ has a dedicated type for that: `bool`.

## True and false

A `bool` can only be `true` or `false`.

```cpp
#include <iostream>

int main()
{
    bool isReady{true};
    bool isDone{false};

    std::cout << isReady << '\n';
    std::cout << isDone << '\n';
    return 0;
}
```

By default, printing a `bool` outputs `1` for true and `0` for false.

## Printing `true` and `false` with `std::boolalpha`

You can ask the stream to print the words instead:

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    bool isReady{true};
    std::cout << std::boolalpha;
    std::cout << isReady << '\n';
    return 0;
}
```

NOTE: `std::boolalpha` is sticky. Once enabled, it affects later output on the same stream until you disable it with `std::noboolalpha`.

## Initialization with `0` or `1`

It is legal to initialize a `bool` with `0` or `1`:

```cpp
bool a{0};
bool b{1};
```

But most of the time, `true` and `false` are clearer.

PREFERENCE: Use `true` and `false`. Save `0` and `1` for cases where the input format forces it.

## Input with `std::cin`

By default, `std::cin >> someBool` expects `0` or `1`.

```cpp
#include <iostream>

int main()
{
    bool answer{};
    std::cout << "Enter 0 or 1: ";
    std::cin >> answer;
    std::cout << "You typed: " << answer << '\n';
    return 0;
}
```

If you enable `std::boolalpha` on input, it will parse `true` and `false`:

```cpp
#include <iostream>
#include <iomanip>

int main()
{
    bool answer{};
    std::cin >> std::boolalpha;

    std::cout << "Type true or false: ";
    std::cin >> answer;

    std::cout << std::boolalpha << "You typed: " << answer << '\n';
    return 0;
}
```

NOTE: Input handling gets tricky when users type unexpected values. For now we assume users follow directions.

## Real world yes or no

It is uncommon to ask a user to type `true` or `false`. Many programs prefer `y/n` or `yes/no` and then convert to a `bool`.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string text;
    std::cout << "Continue (y/n): ";
    std::cin >> text;

    bool shouldContinue = (text == "y" || text == "Y" || text == "yes" || text == "YES");
    std::cout << "shouldContinue = " << std::boolalpha << shouldContinue << '\n';
    return 0;
}
```

This is not perfect input handling, but it shows the idea.

## `bool` as a return type

Functions often return `bool` to answer a question:

```cpp
#include <iostream>

bool isEven(int x)
{
    return (x % 2) == 0;
}

int main()
{
    int value;
    std::cout << "Enter an integer: ";
    std::cin >> value;

    if (isEven(value))
    {
        std::cout << value << " is even." << std::endl;
    }
    else
    {
        std::cout << value << " is odd." << std::endl;
    }

    return 0;
}
```



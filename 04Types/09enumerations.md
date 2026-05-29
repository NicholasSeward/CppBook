# Enumerations

An enumeration lets you create a type with a small set of named choices.

This is useful when a value should be one option from a list: a direction, menu choice, status, color, or character class.

## The Problem With Magic Numbers

A magic number is an unexplained value in code.

```cpp
#include <iostream>

int main()
{
    int direction{0};

    if (direction == 0)
    {
        std::cout << "Move north.\n";
    }

    return 0;
}
```

This code works, but `0` does not explain itself. The programmer has to remember that `0` means north.

Named constants are better:

```cpp
#include <iostream>

int main()
{
    const int north{0};
    const int south{1};

    int direction{north};

    if (direction == north)
    {
        std::cout << "Move north.\n";
    }

    return 0;
}
```

This is clearer, but `direction` is still just an `int`. It could accidentally be set to `99`.

## Plain Enums

A plain enum creates named choices.

```cpp
#include <iostream>

enum Direction
{
    North,
    South,
    East,
    West
};

int main()
{
    Direction direction{North};

    if (direction == North)
    {
        std::cout << "Move north.\n";
    }

    return 0;
}
```

The type is `Direction`. The choices are `North`, `South`, `East`, and `West`.

Plain enums are easy to use, but their names leak into the surrounding scope. This can easily cause confusion or errors if another part of the program declares the same name. For example:

```cpp
#include <iostream>

enum Direction
{
    North,
    South,
    East,
    West
};

enum Hemisphere
{
    North,  // Error: redefinition of 'North'
    South
};

int main()
{
    Direction direction{North};
    Hemisphere hemi{North}; // Which 'North' is this? Error or unexpected result!
    std::cout << direction << " " << hemi << "\n";
    return 0;
}
```

This code will not compile, because both enums define a `North` value in the same scope. Even if it did compile, it would be very unclear which value is being used in an assignment like `Hemisphere hemi{North};`.

## Scoped Enums With `enum class`

Modern C++ usually prefers `enum class`.

```cpp
#include <iostream>

enum class Direction
{
    North,
    South,
    East,
    West
};

int main()
{
    Direction direction{Direction::North};

    if (direction == Direction::North)
    {
        std::cout << "Move north.\n";
    }

    return 0;
}
```

`Direction::North` is more to type, but it is also safer. The name `North` belongs to `Direction`.

PREFERENCE: Use `enum class` unless the enum is already inside a namespace or class where the names are clearly contained.

## Naming Enum Values

Older C and C++ code often uses `SCREAMING_SNAKE_CASE` for enum values.

This book uses `TitleCase` for enum values:

```
enum class MenuChoice
{
    StartGame,
    LoadGame,
    Quit
};
```

`SCREAMING_SNAKE_CASE` is common for preprocessor macros, so avoiding it helps keep enum values visually separate from macros.

## Enums With `if`

Enums work well with `if` statements.

```cpp
#include <iostream>

enum class MenuChoice
{
    StartGame,
    LoadGame,
    Quit
};

int main()
{
    MenuChoice choice{MenuChoice::StartGame};

    if (choice == MenuChoice::StartGame)
    {
        std::cout << "Starting game...\n";
    }
    else if (choice == MenuChoice::LoadGame)
    {
        std::cout << "Loading game...\n";
    }
    else
    {
        std::cout << "Goodbye.\n";
    }

    return 0;
}
```

This is much easier to read than comparing against unexplained numbers.
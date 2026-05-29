# Enum Values, Input, and Output

Enums store named choices, but sometimes you need to see or control the values behind those choices.

This chapter uses `enum class`, because scoped enums are the safer default.

## Underlying Values

Enum values are usually backed by integers.

You can cast an enum value to `int` when you need to see that underlying value.

```cpp
#include <iostream>

enum class Color
{
    Red,
    Green,
    Blue
};

int main()
{
    Color color{Color::Green};

    std::cout << static_cast<int>(color) << "\n";
    return 0;
}
```

By default, the first value is `0`, the next is `1`, and so on.

## Setting Specific Values

You can give enum values specific numbers.

```cpp
#include <iostream>

enum class StatusCode
{
    Ok = 200,
    NotFound = 404,
    ServerError = 500
};

int main()
{
    StatusCode status{StatusCode::NotFound};

    std::cout << static_cast<int>(status) << "\n";
    return 0;
}
```

Specific values are useful when the numbers have meaning outside your program.

## Sparse Values

If you set one value and leave later values unspecified, C++ continues counting from the previous value.

```cpp
#include <iostream>

enum class Permission
{
    Read = 1,
    Write,
    Execute = 10,
    Admin
};

int main()
{
    std::cout << static_cast<int>(Permission::Read) << "\n";
    std::cout << static_cast<int>(Permission::Write) << "\n";
    std::cout << static_cast<int>(Permission::Execute) << "\n";
    std::cout << static_cast<int>(Permission::Admin) << "\n";

    return 0;
}
```

`Write` becomes `2`, and `Admin` becomes `11`.

## Turning an Enum Into Text

C++ does not automatically know how to print the name of an enum value.

You can write a function that converts the enum to a string.

```cpp
#include <iostream>
#include <string>

enum class Direction
{
    North,
    South,
    East,
    West
};

std::string toString(Direction direction)
{
    if (direction == Direction::North)
    {
        return "North";
    }
    if (direction == Direction::South)
    {
        return "South";
    }
    if (direction == Direction::East)
    {
        return "East";
    }

    return "West";
}

int main()
{
    Direction direction{Direction::East};

    std::cout << toString(direction) << "\n";
    return 0;
}
```

The function gives you one place to define how each enum value should display.

## Reading Input Into an Enum

You cannot use `std::cin` to read directly into an `enum class`.

The simplest option is to read an `int`, then cast it to the enum type.

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
    int input{};

    std::cout << "Choose a direction: 0=North, 1=South, 2=East, 3=West: ";
    std::cin >> input;

    Direction direction{static_cast<Direction>(input)};

    if (direction == Direction::North)
    {
        std::cout << "Going north.\n";
    }
    else
    {
        std::cout << "Going somewhere else.\n";
    }

    return 0;
}
```

This is short, but it trusts the user. If the user types `99`, the enum object can hold a value that is not one of the named choices.

You can also read text and convert it with a helper function.

```cpp
#include <iostream>
#include <string>

enum class Direction
{
    North,
    South,
    East,
    West
};

Direction directionFromText(const std::string& text)
{
    if (text == "north")
    {
        return Direction::North;
    }
    if (text == "south")
    {
        return Direction::South;
    }
    if (text == "east")
    {
        return Direction::East;
    }

    return Direction::West;
}

int main()
{
    std::string input{};

    std::cout << "Direction,  ";
    std::cin >> input;

    Direction direction{directionFromText(input)};

    if (direction == Direction::North)
    {
        std::cout << "Going north.\n";
    }
    else
    {
        std::cout << "Going somewhere else.\n";
    }

    return 0;
}
```

Both examples keep the conversion simple. Larger programs should handle invalid input explicitly.

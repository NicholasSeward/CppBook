# Struct Basics

A `struct` lets you group related values into one custom type.

This is useful when several variables describe one thing.

## A Simple Struct

Here is a `Fraction` type.

```cpp
#include <iostream>

struct Fraction
{
    int numerator{};
    int denominator{};
};

int main()
{
    Fraction half{1, 2};

    std::cout << half.numerator << "/" << half.denominator << "\n";
    return 0;
}
```

The struct definition is a blueprint. It says every `Fraction` has a `numerator` and a `denominator`.

> NOTE: A struct definition ends with a semicolon. That is different from functions and normal code blocks.

## Member Variables

The variables inside a struct are called members. You may also hear:

- data members
- member variables
- instance variables

This book usually says members.

```
struct Player
{
    std::string name;
    int health;
    int score;
};
```

That code is a type definition, not a specific player. A specific player is created later:

```
Player player{"Ada", 100, 0};
```

## Naming Custom Types

Custom type names usually use `TitleCase`.

```
struct Player
{
    std::string name;
    int health;
};
```

This is different from fundamental types like `int`, `double`, and `bool`, but it is a common convention across many programming languages.

> PREFERENCE: Use `TitleCase` for custom types such as structs, classes, and enum types.

## Initializing Structs

You can initialize a struct by listing member values in order.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name;
    int health;
    int score;
};

int main()
{
    Player player{"Ada", 100, 0};

    std::cout << player.name << "\n";
    std::cout << player.health << "\n";
    std::cout << player.score << "\n";

    return 0;
}
```

The order matters. `"Ada"` goes into `name`, `100` goes into `health`, and `0` goes into `score`.

## Default Values

You can give members default values.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{"unknown"};
    int health{100};
    int score{0};
};

int main()
{
    Player player{};

    std::cout << player.name << "\n";
    std::cout << player.health << "\n";
    std::cout << player.score << "\n";

    return 0;
}
```

`Player player{};` creates a player using the defaults.

## The Dot Operator

Use the dot operator to access a member.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name;
    int health;
    int score;
};

int main()
{
    Player player{"Ada", 100, 0};

    player.health -= 25;
    player.score += 10;

    std::cout << player.name << " has " << player.health << " health.\n";
    std::cout << "Score: " << player.score << "\n";

    return 0;
}
```

Members can be read and changed just like normal variables.

## Initialize Before Use

Uninitialized members can cause undefined behavior.

```cpp
#include <iostream>

struct Point
{
    int x;
    int y;
};

int main()
{
    Point point{};

    std::cout << point.x << ", " << point.y << "\n";
    return 0;
}
```

It is also acceptable to create the struct first and then fill every member before reading from it.

```cpp
#include <iostream>

struct Point
{
    int x;
    int y;
};

int main()
{
    Point point;

    std::cout << "x,  ";
    std::cin >> point.x;

    std::cout << "y,  ";
    std::cin >> point.y;

    std::cout << point.x << ", " << point.y << "\n";
    return 0;
}
```

`Point point;` leaves the members uninitialized at first. The program is okay because it writes to `point.x` and `point.y` with `std::cin` before printing them.

> PREFERENCE: Give members default values when there is a sensible default. Otherwise, initialize the whole struct clearly when you create it.

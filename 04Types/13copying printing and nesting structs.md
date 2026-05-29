# Copying, Printing, and Nesting Structs

Structs behave like regular values in many ways.

You can copy them, return them from functions, and place one struct inside another.

## Copying a Struct With `=`

You can copy one struct object into another with `=`.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

int main()
{
    Player first{"Ada", 100, 0};
    Player second{"Grace", 50, 10};

    second = first;

    second.health = 25;

    std::cout << first.name << ": " << first.health << "\n";
    std::cout << second.name << ": " << second.health << "\n";

    return 0;
}
```

`second = first;` copies each member from `first` into `second`. After that, `second` is still its own object. Changing `second.health` does not change `first.health`.

You may also see copy initialization:

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

int main()
{
    Player original{"Ada", 100, 0};
    Player copy{original};

    std::cout << copy.name << "\n";
    return 0;
}
```

For simple structs, C++ knows how to copy each member automatically.

## Printing a Struct With `operator<<`

C++ does not automatically know how to print a struct.

This will not work:

```
std::cout << player << "\n";
```

You can teach `std::cout` how to print your type by writing an `operator<<` function.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

std::ostream& operator<<(std::ostream& out, const Player& player)
{
    out << player.name << " ";
    out << "(health: " << player.health << ", ";
    out << "score: " << player.score << ")";
    return out;
}

int main()
{
    Player player{"Ada", 100, 0};

    std::cout << player << "\n";

    return 0;
}
```

The left side is an output stream, like `std::cout`. The right side is the `Player`.

The function returns the same stream so printing can keep going.

> NOTE: This is called operator overloading. A later chapter will cover it more carefully. For now, this pattern is enough when you want a clean way to print a struct.

## Returning a Struct

Functions can return structs.

```cpp
#include <iostream>

struct Vector2
{
    int x{};
    int y{};
};

Vector2 add(Vector2 left, Vector2 right)
{
    return {left.x + right.x, left.y + right.y};
}

int main()
{
    Vector2 a{2, 3};
    Vector2 b{4, 5};
    Vector2 result{add(a, b)};

    std::cout << result.x << ", " << result.y << "\n";
    return 0;
}
```

Because the function return type is `Vector2`, the `return` statement can use `{...}` to build the result.

## Structs Inside Structs

Structs can contain other structs.

```cpp
#include <iostream>
#include <string>

struct Vector2
{
    int x{};
    int y{};
};

struct Player
{
    std::string name{};
    Vector2 position{};
};

int main()
{
    Player player{"Ada", {3, 4}};

    std::cout << player.name << " is at ";
    std::cout << player.position.x << ", " << player.position.y << "\n";

    return 0;
}
```

Nested structs are useful when one idea naturally contains another idea.

Do not go overboard. If a type becomes hard to create, print, or explain, it may need a cleaner design.

Try adding a `move` function that takes a `Player&` and changes the player's `position`.

# Structs and Functions

Structs are especially useful with functions.

Instead of passing several related values separately, you can pass one object that keeps those values together.

## Too Many Separate Parameters

This function works, but the parameters are easy to mix up.

```cpp
#include <iostream>
#include <string>

void printPlayer(const std::string& name, int health, int score)
{
    std::cout << name << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Score: " << score << "\n";
}

int main()
{
    printPlayer("Ada", 100, 0);
    return 0;
}
```

As the list grows, the function call gets harder to read.

## Passing a Struct

A struct lets the function receive one meaningful object.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

void printPlayer(Player player)
{
    std::cout << player.name << "\n";
    std::cout << "Health: " << player.health << "\n";
    std::cout << "Score: " << player.score << "\n";
}

int main()
{
    Player player{"Ada", 100, 0};

    printPlayer(player);

    return 0;
}
```

Passing by value makes a copy. For small structs, that is often fine.

## Passing by Reference

If a function should modify the original struct, pass by reference.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

void heal(Player& player, int amount)
{
    player.health += amount;
}

int main()
{
    Player player{"Ada", 75, 0};

    heal(player, 25);

    std::cout << player.health << "\n";
    return 0;
}
```

`Player& player` means the function works with the original object, not a copy.

## Passing by Const Reference

If a struct is large and the function only needs to read it, pass by const reference.

```cpp
#include <iostream>
#include <string>

struct Player
{
    std::string name{};
    int health{};
    int score{};
};

void printPlayer(const Player& player)
{
    std::cout << player.name << "\n";
    std::cout << "Health: " << player.health << "\n";
    std::cout << "Score: " << player.score << "\n";
}

int main()
{
    Player player{"Ada", 100, 0};

    printPlayer(player);

    return 0;
}
```

`const Player& player` avoids copying and promises not to change the player.

PREFERENCE: If a struct is simple and copying is cheap, passing by value is fine. If it is larger and the function only reads it, use `const&`. If the function must modify it, use `&`.

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

NOTE: This is called operator overloading. A later chapter will cover it more carefully. For now, this pattern is enough when you want a clean way to print a struct.

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


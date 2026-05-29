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

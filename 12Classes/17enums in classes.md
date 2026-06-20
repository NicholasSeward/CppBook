# Enums Inside Classes

You can define an **enum** or **`enum class`** inside a class so its constants live with the type they describe. Outside the class, you qualify with the class name. With a nested **`enum class`**, you qualify **twice**, which gets cumbersome quickly.

## Nested plain `enum`

An unscoped enum nested in a class keeps names under the class:

```cpp
#include <iostream>

class TrafficLight
{
public:
    enum Color
    {
        Red,
        Yellow,
        Green
    };

private:
    Color state{Red};

public:
    void setColor(Color c)
    {
        state = c;
    }

    Color currentColor() const
    {
        return state;
    }
};

int main()
{
    TrafficLight light{};
    light.setColor(TrafficLight::Green);
    std::cout << static_cast<int>(light.currentColor()) << '\n';
    return 0;
}
```

Outside the class: **`TrafficLight::Green`**. Inside member functions, **`Green`** alone often works because the enum's names leak into the surrounding scope.

## Nested `enum class` (safe, but verbose)

The same idea with **`enum class`** is safer (no leaked names), but the syntax piles up:

```cpp
#include <iostream>

class TrafficLight
{
public:
    enum class Color
    {
        Red,
        Yellow,
        Green
    };

private:
    Color state{Color::Red};

public:
    void setColor(Color c)
    {
        state = c;
    }

    Color currentColor() const
    {
        return state;
    }
};

int main()
{
    TrafficLight light{};
    light.setColor(TrafficLight::Color::Green);
    std::cout << static_cast<int>(light.currentColor()) << '\n';
    return 0;
}
```

Compare the call sites:

| Style | From outside the class |
|-------|-------------------------|
| Nested plain `enum` | `TrafficLight::Green` |
| Nested `enum class` | `TrafficLight::Color::Green` |

Inside the class you write **`Color::Red`**, not `Red` alone. Every use carries the extra **`Color::`** (or the full **`TrafficLight::Color::`** path from outside).

That is why a nested plain **`enum`** is often the best fit **inside a class**: `TrafficLight::Green` is enough qualification. Nested **`enum class`** is safer but heavy (`TrafficLight::Color::Green`). For constants not tied to one class, see **`enum class`** at namespace scope in [Enumerations](../04Types/09enumerations.md).

## Why nest at all?

- Groups related constants with the type they describe
- Avoids a pile of loose `Red` / `Green` names at global scope
- Documents that these values belong to `TrafficLight` (or `GameLevel`, and so on)

> PREFERENCE: When constants belong to one class type, prefer a **nested plain `enum`**: grouped names like `TrafficLight::Green` without the double scope of nested **`enum class`**. Use **`enum class`** at namespace scope when the set is not owned by a single class. Avoid nested **`enum class`** unless you need strict scoping and can live with `ClassName::EnumName::Value`.

## Try it now

### Exercise 1: Nested enum

Prompt: Add `enum Difficulty { Easy, Normal, Hard };` to `GameLevel` and a `currentDifficulty()` getter. Set difficulty to `Normal` in `main` and print its integer value.

```cpp
#include <iostream>

class GameLevel
{
    // TODO: public enum Difficulty { ... }
    // TODO: private member + setter/getter as needed
};

int main()
{
    // TODO
    return 0;
}
```

:::details Answer

`1` if `Normal` is the second enumerator (`Easy` is `0`).

:::

:::details Solution

**Reasoning:** Nest the plain `enum` in `GameLevel`, store a `Difficulty` member, and qualify `Normal` as `GameLevel::Normal` from `main`.

```cpp
#include <iostream>

class GameLevel
{
public:
    enum Difficulty
    {
        Easy,
        Normal,
        Hard
    };

    void setDifficulty(Difficulty d)
    {
        level = d;
    }

    Difficulty currentDifficulty() const
    {
        return level;
    }

private:
    Difficulty level{Easy};
};

int main()
{
    GameLevel stage{};
    stage.setDifficulty(GameLevel::Normal);
    std::cout << static_cast<int>(stage.currentDifficulty()) << '\n';
    return 0;
}
```

:::

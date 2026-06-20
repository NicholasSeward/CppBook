# Enums Inside Classes

**Scoped enum classes** (`enum class`) solved many old C++ enum problems. Sometimes you still want a plain **`enum`** tied to one class type.

Nested enums live in the **class's namespace**:

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

Use **`TrafficLight::Green`** outside the class. Inside member functions, `Green` alone often works.

## Why nest?

- Groups related constants with the type they describe
- Avoids polluting the global namespace with `Red`, `Green` from unrelated domains
- Documents that these values belong to `TrafficLight`

For new code, **`enum class`** at namespace scope is often still clearer. Nested unscoped enums remain common in older APIs and generated bindings.

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

Normal is typically `1` if listed second after Easy.

# Public, Protected, and Private Inheritance

When you write **`class Derived : public Base`**, the **`public`** keyword controls how base members **appear inside the derived class**, not how outsiders see them.

This book **always uses `public` inheritance** so access stays the same as in the base:

```
class Employee : public Person
{
};
```

## What each inheritance keyword does

Base member access **as seen by code in the derived class**:

| Base member | `public` inheritance | `protected` inheritance | `private` inheritance |
|-------------|----------------------|---------------------------|------------------------|
| **`public`** | stays **public** | becomes **protected** | becomes **private** |
| **`protected`** | stays **protected** | stays **protected** | becomes **private** |
| **`private`** | not accessible | not accessible | not accessible |

Omitting the keyword (`class D : B`) defaults to **`private`** inheritance for **`class`**, like **`private`** members at the top of a class.

There is **no** inheritance mode that **upgrades** access (for example turning **`protected`** into **`public`**) without editing the base class itself.

> PREFERENCE: Use **`public` inheritance** for **is-a** relationships. **`protected`** or **`private`** inheritance hides parts of the base interface from users of the derived type. That is almost never what you want in introductory code.

## Why not private inheritance?

**`private` inheritance** makes **`public`** base members **`private`** in the derived class. Callers who know you have an **`Employee`** cannot treat it like a **`Person`** even when the relationship is truly **is-a**. Prefer **`public`** inheritance plus a tight public interface on the derived class.

## Try it now

### Exercise 1: Pick the keyword

Prompt: `Dog` **is-a** `Animal`. Should the header read `class Dog : public Animal` or `class Dog : private Animal`?

:::details Answer

**`public Animal`**. **`Dog`** should remain usable as an **`Animal`** where that makes sense.

:::

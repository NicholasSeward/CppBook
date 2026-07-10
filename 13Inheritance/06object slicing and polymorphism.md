# Object Slicing and Polymorphism

**Polymorphism** means "many forms": code treats different derived types through a common base idea, and each object runs **its own** version of a function. A **`Cat`** and a **`Dog`** can both **`speak()`**; a loop over **`Animal*`** should get the right sound for each pet.

That only works when you use **pointers** or **references** and **`virtual`** functions. Copying into a base **object** causes **object slicing**, which breaks the story before polymorphism even enters the picture.

## Slicing: the top layer is cut off

A **`Person`** variable only has room for **`Person`** data. Assign an **`Employee`** into it and the **`employeeId`** (and any other derived-only members) are **sliced off**:

```cpp
#include <iostream>
#include <string>

class Person
{
protected:
    std::string name;
    int age{};

public:
    Person(std::string personName, int personAge)
        : name{std::move(personName)}
        , age{personAge}
    {
    }

    void describe() const
    {
        std::cout << name << ", age " << age << ", person\n";
    }
};

class Employee : public Person
{
private:
    int employeeId{};

public:
    Employee(std::string personName, int personAge, int id)
        : Person{personName, personAge}
        , employeeId{id}
    {
    }

    void describe() const
    {
        std::cout << name << ", employee " << employeeId << '\n';
    }
};

int main()
{
    Employee dev{"Lin", 28, 101};

    Person sliced = dev;  // slices: only Person part is copied
    sliced.describe();    // Person::describe (sliced object is a Person)

    return 0;
}
```

Output: **`Lin, age 28, person`** (not employee id 101). The **`Employee`** data is gone from **`sliced`**.

## Pointers keep the full object in memory

A pointer to **`Employee`** still points at the whole **`Employee`** in memory. Slicing does not happen. Whether the **right** function runs depends on **`virtual`**, which the next sections cover.

```
Employee dev{"Lin", 28, 101};
Person* ptr = &dev;   // points to full Employee; no slice
ptr->describe();      // still Person::describe until speak is virtual (see next section)
```

> PROTIP: When you store mixed derived types together (cats, dogs, shapes), use **`std::vector<Animal*>`** (or smart pointers to base) so each element stays a full derived object.

## What comes next

| Section | Topic |
|---------|--------|
| [Virtual Functions](07virtual%20functions.md) | **`virtual`**, **`override`**, vtable, virtual destructors |
| [Abstract Classes and Interfaces](08abstract%20classes%20and%20interfaces.md) | Pure virtual, abstract bases, shape hierarchies |
| [`dynamic_cast` and Polymorphic Patterns](09dynamic%20cast%20and%20polymorphic%20patterns.md) | Derived-only members, downcasting, printing |

## Try it now

### Exercise 1: Sliced or not?

Prompt: Does `Person p = employee;` call `Employee::describe` or `Person::describe`?

:::details Answer

**`Person::describe`**. The **`Employee`** part was sliced off; **`p`** is a **`Person`** object.

:::

### Exercise 2: Pointer slice?

Prompt: `Employee e{"Lin", 28, 101};` `Person* p = &e;` Does **`p`** point at a sliced object?

:::details Answer

**No.** The **`Employee`** object in memory is still complete. Only **copying into a `Person` variable** slices.

:::

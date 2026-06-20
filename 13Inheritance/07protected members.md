# Protected Members

So far you have mostly used **`public`** and **`private`**. Inheritance adds a third level: **`protected`**.

| Access | Who can use it |
|--------|----------------|
| **`private`** | Only this class |
| **`protected`** | This class **and derived classes** |
| **`public`** | Everyone |

**`protected`** is still encapsulation: callers outside the hierarchy cannot reach the member. Derived classes can, which avoids getter boilerplate for every base field.

## Example

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

    void print() const
    {
        std::cout << name << ", age " << age << " (id " << employeeId << ")\n";
    }
};

int main()
{
    Employee dev{"Lin", 28, 101};
    dev.print();
    return 0;
}
```

`Employee::print` reads **`name`** directly because it is **`protected`** in **`Person`**.

If **`name`** were **`private`**, this would not compile unless **`Person`** offered a getter.

> NOTE: This book still prefers **`private`** data with a small public interface when you can test a class on its own. Use **`protected`** when many derived classes need the same base fields and getters would only exist for children.

## Try it now

### Exercise 1: Access check

Prompt: `class Child : public Parent` and `Parent` has `private int score`. Can `Child::report()` read `score` directly?

:::details Answer

**No.** **`private`** members are not visible in derived classes. Use **`protected`**, or a **`protected`** / **`public`** getter on **`Parent`**.

:::

# Modeling Person, Employee, and More

An **employee** has a name and age (like anyone) plus an id and salary. You could model that several ways:

| Approach | Idea |
|----------|------|
| **Four fields in one class** | `Employee` stores name, age, id, salary |
| **Person inside Employee** | `Employee` holds a `Person` member plus id/salary |
| **Inheritance** | `Employee` **is-a** `Person`, adds id and salary |

All three can work. Inheritance shines when **`Employee` really is a kind of `Person`** and you want shared behavior on `Person` to apply everywhere.

## Employee extends Person

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

    void print() const
    {
        std::cout << name << ", age " << age << '\n';
    }
};

class Employee : public Person
{
private:
    int employeeId{};
    double salary{};

public:
    Employee(std::string personName, int personAge, int id, double pay)
        : Person{personName, personAge}
        , employeeId{id}
        , salary{pay}
    {
    }

    void print() const
    {
        std::cout << name << " (id " << employeeId << ", salary " << salary << ")\n";
    }
};

int main()
{
    Employee dev{"Lin", 28, 101, 75000.0};
    dev.print();
    return 0;
}
```

`Employee::print` uses **`name`** from the base because it is **`protected`**.

## Volunteer: another branch

More than one type can inherit from **`Person`**:

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

class Volunteer : public Person
{
private:
    int hoursPerWeek{};

public:
    Volunteer(std::string personName, int personAge, int hours)
        : Person{personName, personAge}
        , hoursPerWeek{hours}
    {
    }

    void print() const
    {
        std::cout << name << " volunteers " << hoursPerWeek << " hrs/week\n";
    }
};

int main()
{
    Volunteer helper{"Sam", 19, 8};
    helper.print();
    return 0;
}
```

## Supervisor: inherit from a child

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
protected:
    int employeeId{};

public:
    Employee(std::string personName, int personAge, int id)
        : Person{personName, personAge}
        , employeeId{id}
    {
    }
};

class Supervisor : public Employee
{
private:
    int teamSize{};

public:
    Supervisor(std::string personName, int personAge, int id, int team)
        : Employee{personName, personAge, id}
        , teamSize{team}
    {
    }

    void print() const
    {
        std::cout << name << " supervises " << teamSize << " people\n";
    }
};

int main()
{
    Supervisor lead{"Mo", 40, 500, 12};
    lead.print();
    return 0;
}
```

## Change the base, touch every layer

If you change **`Person`**, every derived class feels it. That can save work (fix once, fix everywhere) or cause surprises (one base change breaks many types). Inheritance is a **layer cake**: the bottom layer is the base; each derived class adds another layer of data and behavior on top.

> PREFERENCE: When a type only **has-a** person (a contact record, a shipping label), prefer a **`Person` member**, not inheritance. Use **`is-a`** inheritance when the derived object truly **is** that base type.

## Try it now

### Exercise 1: Pick an approach

Prompt: `Student` has a name, age, and student id. Would you use inheritance from `Person` or a standalone class with three fields? One sentence.

:::details Answer

**Inheritance** if `Student` **is-a** `Person` and should reuse `Person` behavior. **Standalone three fields** if `Student` is just a record that happens to share some fields (often simpler for homework-sized programs).

:::

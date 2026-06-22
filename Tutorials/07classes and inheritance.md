# Tutorial: Classes and Inheritance (Module 7)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapters: [12 Classes](../12Classes/README.md), [13 Inheritance](../13Inheritance/README.md).

---

## Creating a basic class

Define a simple class with a member function.

### Starter code

```cpp
#include <iostream>

class Animal
{
public:
    void speak()
    {
        std::cout << "Animal speaks\n";
    }
};

int main()
{
    Animal a{};
    a.speak();
    return 0;
}
```

### 1.

What does the program print when run?

- A. `Animal speaks`
- B. Compilation error
- C. No output
- D. Runtime error

---

## Adding a constructor

Modify `Animal` to include a constructor:

```
public:
    Animal()
    {
        std::cout << "Animal created!\n";
    }
```

Keep `speak()` and the same `main`.

### 2.

True or false: the constructor is called automatically when an object is created.

- A. True
- B. False

---

## Adding a private data member

Modify the class to add:

```
private:
    int age{5};
```

Do not add getters yet. In `main`, try adding a direct access line:

```
std::cout << a.age << '\n';
```

### 3.

If you try to access `age` directly in `main()`, the compiler will give an error like:

`error: 'int Animal::age' is _____ within this context`

Fill in the blank: **_____**

---

## Adding getters and setters

Modify the class to add:

```
public:
    void setAge(int a)
    {
        age = a;
    }

    int getAge()
    {
        return age;
    }
```

Modify `main()`:

```
std::cout << a.getAge() << '\n';
```

(Remove or leave commented any direct access to `age`.)

### 4.

What does the program print?

- A. The memory address of `age`
- B. `5`
- C. Compilation error
- D. Undefined behavior

---

## Using an initializer list

Replace the default constructor with:

```
Animal(int ageValue)
    : age{ageValue}
{
    std::cout << "Animal created with age " << age << '\n';
}
```

Create the object in `main` with:

```
Animal a{5};
```

### 5.

How is the `age` member initialized?

- A. In the constructor body
- B. Using an initializer list
- C. Through a function call
- D. It is not initialized

---

## Default constructor parameters

Modify the constructor to:

```
Animal(int ageValue = 10)
    : age{ageValue}
{
}
```

Remove the body message if you like. In `main`:

```
Animal dog{5};
std::cout << dog.getAge() << '\n';
```

### 6.

True or false: if we call `Animal dog{5};`, the object uses the default parameter value `10` for its age.

- A. True
- B. False

---

## Friend function

Add inside `Animal`:

```cpp
friend void showAge(Animal a);
```

Add this function **outside** the class:

```
void showAge(Animal a)
{
    std::cout << "Age: " << a.age << '\n';
}
```

In `main()`:

```
Animal b{7};
showAge(b);
```

### 7.

Why can `showAge()` access `age`?

- A. It is a member function
- B. It is a friend function
- C. `age` is public
- D. It uses a pointer

---

## Overloading operators

Add a member `showAge()` and an `operator+`:

```
void showAge() const
{
    std::cout << "Age: " << age << '\n';
}

Animal operator+(Animal other)
{
    return Animal{age + other.age};
}
```

Modify `main()`:

```
Animal b{};   // default age 10
Animal c{11};
Animal d{b + c};
d.showAge();
```

> NOTE: `Animal b{}` creates an object with the default argument (`10`). `Animal b();` would **not** create an object (it declares a function). Use `{}` when you mean "make an object."

### 8.

The `operator+` function lets you use `+` between two `Animal` objects. The age of `d` is **_____**.

Fill in the blank.

---

## Composition (adding an `Engine`)

Create an `Engine` class **before** `Animal`:

```
class Engine
{
public:
    Engine()
    {
        std::cout << "Engine created!\n";
    }
};
```

Modify `Animal` to contain an engine:

```
private:
    int age{};
    Engine engine{};
```

Restore a default constructor on `Animal` that prints:

```
Animal()
{
    std::cout << "Animal created!\n";
}
```

In `main()`:

```
Animal a{};
```

### 9.

What prints when `Animal a{};` runs? (Member objects are constructed before the constructor body runs.)

- A. `Engine created!` only
- B. `Animal created!` only
- C. `Engine created!` followed by `Animal created!`
- D. `Animal created!` followed by `Engine created!`

---

## Inheritance

Modify `Animal` so `age` is **protected** instead of private:

```
protected:
    int age{};
```

Create a `Dog` class:

```
class Dog : public Animal
{
public:
    Dog(int ageValue)
        : Animal{ageValue}
    {
    }

    void showDogAge() const
    {
        std::cout << "Dog age: " << age << '\n';
    }
};
```

Modify `main()`:

```
Dog d{5};
d.showDogAge();
```

### 10.

True or false: a `protected` member is accessible in derived classes.

- A. True
- B. False

---

## Diamond problem

Use a **separate** program for this question (not the `Animal` code above).

### Starter code

```cpp
#include <iostream>

class A
{
public:
    void show()
    {
        std::cout << "A\n";
    }
};

class B : public A
{
};

class C : public A
{
};

class D : public B, public C
{
};

int main()
{
    D obj{};
    obj.show();
    return 0;
}
```

### 11.

What issue does the code above cause?

- A. Infinite recursion
- B. Ambiguity error due to multiple inheritance
- C. Memory leak
- D. Nothing, it runs correctly

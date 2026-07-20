# Tutorial: Polymorphism and Virtual Functions (Module 9)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapters: [13 Inheritance](../13Inheritance/README.md), especially [Object Slicing and Polymorphism](../13Inheritance/06object%20slicing%20and%20polymorphism.md), [Virtual Functions](../13Inheritance/07virtual%20functions.md), and [`dynamic_cast` and Polymorphic Patterns](../13Inheritance/09dynamic%20cast%20and%20polymorphic%20patterns.md).

---

## Polymorphism not working

Start with a base class `Animal` and derived classes `Cat` and `Dog`. Without `virtual`, polymorphism does not work: a base pointer calls the base version.

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

class Cat : public Animal
{
public:
    void speak()
    {
        std::cout << "Meow\n";
    }
};

class Dog : public Animal
{
public:
    void speak()
    {
        std::cout << "Woof\n";
    }
};

int main()
{
    Animal* a1 = new Cat();
    Animal* a2 = new Dog();

    a1->speak(); // What will this print?
    a2->speak(); // What will this print?

    delete a1;
    delete a2;
}
```

### 1.

Run the program. What does it print?

- A. `Meow` and `Woof`
- B. `Animal speaks` and `Animal speaks`
- C. Compilation error
- D. Undefined behavior

---

## Fixing with `virtual` and `override`

Add `virtual` to `speak()` in the base class and `override` in each derived class.

```cpp
#include <iostream>

class Animal
{
public:
    virtual void speak()
    {
        std::cout << "Animal speaks\n";
    }

    virtual ~Animal() = default; // needed because we delete through Animal*
};

class Cat : public Animal
{
public:
    void speak() override
    {
        std::cout << "Meow\n";
    }
};

class Dog : public Animal
{
public:
    void speak() override
    {
        std::cout << "Woof\n";
    }
};

int main()
{
    Animal* a1 = new Cat();
    Animal* a2 = new Dog();

    a1->speak(); // Now prints "Meow"
    a2->speak(); // Now prints "Woof"

    delete a1;
    delete a2;
}
```

> NOTE: The base class needs `virtual ~Animal() = default;` here. Once `Animal` has a virtual function, deleting a derived object through an `Animal*` requires a **virtual destructor**. Without it the code triggers a `-Wdelete-non-virtual-dtor` warning (and fails to compile when warnings are treated as errors, like on the TxtBook playground). The [Virtual destructor](#virtual-destructor) section below covers why.

### 2.

Run the modified program. Does it now correctly print `Meow` and `Woof`?

- A. Yes
- B. No

---

## Object slicing

When you assign a derived object to a base class **object** (by value), the derived part is sliced off.

```cpp
#include <iostream>

class Animal
{
public:
    virtual void speak()
    {
        std::cout << "Animal speaks\n";
    }
};

class Cat : public Animal
{
public:
    void speak() override
    {
        std::cout << "Meow\n";
    }
};

int main()
{
    Cat c;
    Animal a = c;  // Object slicing happens here!
    a.speak();     // What will this print?
}
```

### 3.

When an object of a derived class is assigned to a base class object, the ________ is removed, and only the ________ remains.

- A. base part; base class
- B. base part; derived class
- C. derived part; base class
- D. derived part; derived class

### 4.

Change `Animal a` to a **reference** (`Animal& a = c;`) and run it again. True or false: with a reference, `a.speak()` now prints `Meow`.

- A. True
- B. False

---

## Virtual destructor

When you delete a derived object through a base class pointer, a **virtual destructor** ensures the derived destructor runs too.

```cpp
#include <iostream>

class Animal
{
public:
    virtual ~Animal()
    {
        std::cout << "Animal destroyed\n";
    }
};

class Cat : public Animal
{
public:
    ~Cat()
    {
        std::cout << "Cat destroyed\n";
    }
};

int main()
{
    Animal* a = new Cat();
    delete a;  // Ensures Cat's destructor is called
}
```

Expected output:

```
Cat destroyed
Animal destroyed
```

### 5.

Match each `Animal` destructor definition with what prints when a `Cat` is deleted through an `Animal*`.

| Definition | Behavior |
|------------|----------|
| 1. `class Animal { ~Animal() {} };` | A. Both `Cat destroyed` and `Animal destroyed` print |
| 2. `class Animal { virtual ~Animal() {} };` | B. Only `Animal destroyed` prints |

---

## Overloading `<<` for output

You cannot make `operator<<` a virtual member (its left operand is the stream). Instead, write a free `operator<<` that calls a virtual function like `speak()`.

```cpp
#include <iostream>

class Animal
{
public:
    virtual void speak() = 0;  // Pure virtual function
    virtual ~Animal() = default;
};

class Cat : public Animal
{
public:
    void speak() override
    {
        std::cout << "Meow";
    }
};

std::ostream& operator<<(std::ostream& os, Animal& a)
{
    a.speak();
    return os;
}

int main()
{
    Cat c;
    std::cout << c << std::endl;  // Prints "Meow"
}
```

### 6.

What does `std::cout << c;` output in the final program?

- A. `Meow`
- B. `Animal speaks`
- C. Compilation error
- D. Undefined behavior

---

## Conclusion

- Without `virtual`, polymorphism does not work.
- Use `override` to prevent accidental signature mismatches.
- Object slicing occurs when assigning by value; use a pointer or reference.
- A virtual destructor prevents leaks when deleting through a base pointer.
- Overload `<<` by delegating to a virtual function.

### 7.

True or false: if an `Animal*` points to a `Cat`, deleting it **without** a virtual destructor will correctly call `Cat`'s destructor.

- A. True
- B. False

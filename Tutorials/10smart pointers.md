# Tutorial: Smart Pointers (Module 10)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapters: [15 Pointers](../15Pointers/README.md), especially [Introduction to Smart Pointers](../15Pointers/06introduction%20to%20smart%20pointers.md), [`std::unique_ptr`](../15Pointers/08unique%20ptr.md), and [`std::shared_ptr` and `std::weak_ptr`](../15Pointers/09shared%20and%20weak%20ptr.md).

---

## Setup: `Rectangle`

Every demo in this tutorial uses the same small class. It prints when it is constructed and destroyed so you can see ownership in action.

### Starter code

```cpp
// @file: main.cpp
#include "rectangle.h"

int main()
{
    Rectangle r{3, 2};
    r.printArea();
    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

Keep `rectangle.h` available for the rest of the tutorial.

---

## Part 1: `std::unique_ptr`

### Starter code

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <iostream>
#include <memory>

void createRectangle(std::unique_ptr<Rectangle>& ptr)
{
    ptr = std::make_unique<Rectangle>(7, 4);
}

int main()
{
    std::unique_ptr<Rectangle> rect1 = std::make_unique<Rectangle>(10, 5);
    rect1->printArea();

    std::unique_ptr<Rectangle> rect3 = std::move(rect1);
    if (!rect1)
    {
        std::cout << "rect1 is null after move\n";
    }

    std::unique_ptr<Rectangle> rect2;
    createRectangle(rect2);
    rect2->printArea();

    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 1.

What is printed when `rect1` is constructed?

Fill in the blanks: `Rectangle constructed: _____x_____`

### 2.

What happens if you try to copy `rect1` to another `unique_ptr` (for example `auto other = rect1;`)?

- A. It compiles
- B. Compilation error
- C. Runtime error

### 3.

What function name is used to transfer ownership of a `unique_ptr`?

Fill in the blank: `std::_____`

### 4.

What is printed when `rect1` is moved into `rect3` and then checked with `if (!rect1)`?

- A. `rect1 is null after move`
- B. Nothing
- C. `rect1` still works

### 5.

What happens when `rect3` goes out of scope?

- A. Memory leak
- B. Rectangle is destructed
- C. Compilation error

---

## Bad usage of `unique_ptr`

Try this (or reason about it carefully without running if your environment treats the double-delete as a crash):

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <memory>

int main()
{
    Rectangle* raw = new Rectangle(4, 3);
    std::unique_ptr<Rectangle> badPtr{raw};  // BAD!
    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 6.

What is wrong with wrapping an existing raw `new` pointer like that?

- A. It will not compile
- B. It could lead to a double delete
- C. It is totally fine

> PREFERENCE: When dealing with smart pointers, prefer not mixing in raw `new`. Stay with `make_unique` / `make_shared` to stay safe.

### 7.

What is the safer alternative?

Fill in the blank: `auto goodPtr = std::_____<Rectangle>(4, 3);`

---

## Passing `unique_ptr` by value

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <memory>

void takeOwnership(std::unique_ptr<Rectangle> r)
{
    r->printArea();
}

int main()
{
    auto rect = std::make_unique<Rectangle>(2, 3);
    takeOwnership(std::move(rect));
    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 8.

Why do we need `std::move(rect)` here?

- A. `unique_ptr` cannot be copied
- B. `rect` is null
- C. It is optional

---

## Returning `unique_ptr` from a function

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <memory>

std::unique_ptr<Rectangle> makeRect()
{
    return std::make_unique<Rectangle>(5, 5);
}

int main()
{
    auto r = makeRect();
    r->printArea();
    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 9.

Is `std::move` needed in the `return` statement?

- A. Yes
- B. No

---

## Passing `unique_ptr` by reference

You can pass a `unique_ptr` by reference to initialize or modify it inside a function (as in the Part 1 starter):

```
void createRectangle(std::unique_ptr<Rectangle>& ptr)
{
    ptr = std::make_unique<Rectangle>(7, 4);
}
```

### 10.

What gets printed when `createRectangle(rect2)` is called in the Part 1 starter?

Fill in the blanks: `Rectangle constructed: _____x_____`

### 11.

Why do we pass by reference?

- A. To avoid copying `unique_ptr`, which is not allowed
- B. So we can modify the caller's pointer
- C. Both A and B

### 12.

What would happen if you changed `createRectangle` to take the `unique_ptr` **by value** and called it with `std::move(rect2)`?

- A. It would compile, but `rect2` stays null
- B. It would compile and assign correctly
- C. It would not compile

---

## Part 2: `shared_ptr` and `weak_ptr`

### Starter code

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<Rectangle> r1 = std::make_shared<Rectangle>(10, 10);
    std::shared_ptr<Rectangle> r2 = r1;

    std::cout << "Use count: " << r1.use_count() << '\n';

    r1.reset();

    std::cout << "After r1.reset(), use count: " << r2.use_count() << '\n';

    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 13.

How many `Rectangle` objects are constructed in the code above?

- A. 0
- B. 1
- C. 2

### 14.

What does `r1.reset()` do here?

- A. Deletes the object immediately
- B. Reduces the reference count (and deletes only if the count hits zero)
- C. Nothing

### 15.

What is `r2.use_count()` after `r1.reset()`?

Fill in the blank: `_____`

### 16.

When does the `Rectangle` get destroyed?

- A. When `r1` resets
- B. When `r2` goes out of scope
- C. Never

---

## `weak_ptr` example

```cpp
// @file: main.cpp
#include "rectangle.h"
#include <iostream>
#include <memory>

int main()
{
    std::weak_ptr<Rectangle> weak;
    {
        auto shared = std::make_shared<Rectangle>(3, 3);
        weak = shared;
        std::cout << "Inside block: expired = " << weak.expired() << '\n';
    }
    std::cout << "Outside block: expired = " << weak.expired() << '\n';
    return 0;
}

// @file: rectangle.h
#pragma once

#include <iostream>

class Rectangle
{
public:
    Rectangle(int w, int h)
        : width{w}
        , height{h}
    {
        std::cout << "Rectangle constructed: " << width << "x" << height << '\n';
    }

    ~Rectangle()
    {
        std::cout << "Rectangle destructed: " << width << "x" << height << '\n';
    }

    void printArea() const
    {
        std::cout << "Area: " << width * height << '\n';
    }

private:
    int width{};
    int height{};
};
```

### 17.

What does `expired()` return outside the block?

- A. true / 1
- B. false / 0
- C. Error

---

## Dangerous cycles

```cpp
#include <iostream>
#include <memory>

struct Node
{
    std::shared_ptr<Node> next;

    Node()
    {
        std::cout << "Node constructed\n";
    }

    ~Node()
    {
        std::cout << "Node destructed\n";
    }
};

int main()
{
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->next = b;
    b->next = a;
    return 0;
}
```

### 18.

Do the nodes get destructed?

- A. Yes
- B. No

### 19.

How would you fix the memory leak?

- A. Use `unique_ptr`
- B. Use `weak_ptr` for one link
- C. Delete one manually

### 20.

How do you safely convert a `weak_ptr` to a `shared_ptr`?

Fill in the blank: `auto sp = weak._____();`

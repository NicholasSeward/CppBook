# Tutorial: Templates and STL Containers (Module 5)

Go play with and run the code below. You can use CodeBin, Codespaces, TxtBook, or whatever environment you like. Run it and get a feel for the code before you answer each question.

Work through each section in order. Change only what each question asks for unless a question says to keep earlier edits.

Related chapters: [10 Templates](../10Templates/README.md), [16 Data Structures](../16DataStructures/README.md).

---

## Default parameters

### Starter code

```cpp
#include <iostream>
#include <string>

void greet(std::string name = "Guest")
{
    std::cout << "Hello, " << name << "!\n";
}

int main()
{
    greet();
    greet("Alice");
    return 0;
}
```

### 1.

What is the output of the program?

- A. `Hello, Alice!`
- B. `Hello, Guest!` then `Hello, Alice!`
- C. `Hello, !` then `Hello, Alice!`
- D. Compiler error

---

## Multiple default parameters

### Starter code

```cpp
#include <iostream>
#include <string>

void introduce(std::string name = "Guest", int age = 18)
{
    std::cout << name << " is " << age << " years old.\n";
}

int main()
{
    introduce();
    introduce("Bob");
    introduce("Charlie", 25);
    return 0;
}
```

### 2.

What is the output of `introduce("Bob");`?

Fill in the blank: `Bob is _____ years old.`

---

## Default parameters in the middle

### Starter code

```cpp
#include <iostream>

void show(int a, int b = 5, int c = 10)
{
    std::cout << a << " " << b << " " << c << "\n";
}

int main()
{
    show(1, 2);
    return 0;
}
```

### 3.

What happens when `show(1, 2);` is called?

- A. `1 2 10`
- B. `1 5 10`
- C. Compiler error

---

## Ambiguous call (one overload has defaults)

### Starter code

```cpp
#include <iostream>

void test(int x = 1, double y = 2.5)
{
    std::cout << "First function\n";
}

void test(double x)
{
    std::cout << "Second function\n";
}

int main()
{
    test();
    return 0;
}
```

### 4.

What happens when `test();` is called?

- A. First function
- B. Second function
- C. Compiler error

---

## Ambiguous call (both overloads have defaults)

### Starter code

```cpp
#include <iostream>

void test(int x = 1, double y = 2.5)
{
    std::cout << "First function\n";
}

void test(double x = 4.5)
{
    std::cout << "Second function\n";
}

int main()
{
    test();
    return 0;
}
```

### 5.

What happens when `test();` is called?

- A. First function
- B. Second function
- C. Compiler error

---

## Simple template function

### Starter code

```cpp
#include <iostream>

struct Point
{
    int x;
    int y;
};

template<typename T>
void display(T value)
{
    std::cout << "Value: " << value << '\n';
}

int main()
{
    display(42);
    display(3.14);
    display("Hello");
    // display(Point{3, 4});  // try uncommenting this line
    return 0;
}
```

### 6.

Match each function call to its output.

| Call | Output |
|------|--------|
| `display(42);` | |
| `display(3.14);` | |
| `display("Hello");` | |
| `display(Point{3, 4});` | |

Choose from: `Value: 42`, `Value: 3.14`, `Value: Hello`, `Error`, `Value: (3,4)`

---

## Template function with `operator<<`

### Starter code

```cpp
#include <iostream>

struct Point
{
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

template<typename T>
void display(T value)
{
    std::cout << "Value: " << value << '\n';
}

int main()
{
    display(42);
    display(3.14);
    display("Hello");
    display(Point{3, 4});
    return 0;
}
```

### 7.

Match each function call to its output.

| Call | Output |
|------|--------|
| `display(42);` | |
| `display(3.14);` | |
| `display("Hello");` | |
| `display(Point{3, 4});` | |

Choose from: `Value: 42`, `Value: 3.14`, `Value: Hello`, `Value: (3, 4)`, `Error`

---

## Template with multiple types

### Starter code

```cpp
#include <iostream>
#include <string>

template <typename T, typename U>
void showPair(T a, U b)
{
    std::cout << a << " and " << b << '\n';
}

int main()
{
    showPair(10, 3.5);
    showPair("Alice", 42);
    return 0;
}
```

### 8.

What is the output of `showPair("Alice", 42);`?

Fill in the blank: `Alice and _____`

---

## `auto` and return-type deduction

### Starter code

```cpp
#include <iostream>

template <typename T, typename U>
auto max(T a, U b) -> decltype(a > b ? a : b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    std::cout << max(3, 4.5) << '\n';
    std::cout << max(7, 1.0f) << '\n';
    return 0;
}
```

> NOTE: The `-> decltype(...)` trailing return type is unusual syntax. You do not need to write templates this way in normal code. It is here so you can explore how the compiler picks a return type.

### 9.

Match each call to the **return type** of `max` (not the printed value).

| Call | Return type |
|------|-------------|
| `max(3, 4.5);` | |
| `max(7, 1.0f);` | |
| `max(1L, static_cast<short>(2));` | |
| `max(2L, static_cast<short>(1));` | |
| `max(444.4f, 222.2f);` | |

Choose from: `double`, `int`, `short`, `long`, `float`

---

## `push_back` timing

### Starter code

```cpp
#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main()
{
    const int N{10'000'000};

    std::vector<int> v;
    std::list<int> l;
    std::deque<int> d;

    auto start{std::chrono::high_resolution_clock::now()};
    for (int i{0}; i < N; ++i)
    {
        v.push_back(i);
    }
    auto end{std::chrono::high_resolution_clock::now()};
    std::cout << "Vector: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < N; ++i)
    {
        l.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "List: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < N; ++i)
    {
        d.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Deque: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    return 0;
}
```

### 10.

Which container is typically the **slowest** for pushing to the back?

- A. `std::list`
- B. `std::vector`
- C. `std::deque`

---

## `push_front` timing

### Starter code

```cpp
#include <chrono>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

int main()
{
    const int N{100'000};

    std::vector<int> v;
    std::list<int> l;
    std::deque<int> d;

    auto start{std::chrono::high_resolution_clock::now()};
    for (int i{0}; i < N; ++i)
    {
        v.insert(v.begin(), i);  // vector has no push_front; this is the same idea
    }
    auto end{std::chrono::high_resolution_clock::now()};
    std::cout << "Vector: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < N; ++i)
    {
        l.push_front(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "List: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    for (int i{0}; i < N; ++i)
    {
        d.push_front(i);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Deque: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    return 0;
}
```

### 11.

Which container is typically the **slowest** for pushing to the front?

- A. `std::list`
- B. `std::vector`
- C. `std::deque`

> PREFERENCE: Use `vector` for most things. If you need to add or remove from both ends often, use `deque`. Only reach for `list` when you need frequent insert/erase in the middle at a known iterator position.

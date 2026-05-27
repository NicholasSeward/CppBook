# Fundamental Types

C++ has many types, but a small set show up everywhere. Some languages call these **primitive** types. In C++ they are usually called **fundamental** types.

This chapter is an overview. Later chapters go deeper on integers, floating point, `bool`, and characters.

## The types we will use most

These are the main types you will see early in this book:

| Type | What it holds | Typical size | Notes |
|------|---------------|--------------|------|
| `bool` | true or false | 1 byte | prints as `0` or `1` by default |
| `char` | one character | 1 byte | often used for ASCII text |
| `int` | whole numbers | 4 bytes | common default integer |
| `long` | bigger whole numbers | 4 or 8 bytes | varies by platform |
| `float` | decimals | 4 bytes | about 7 digits of precision |
| `double` | decimals | 8 bytes | about 15 to 16 digits of precision |
| `void` | no value | n/a | used as a function return type |

NOTE: The size column says "typical" for desktop systems. C++ does not require exact sizes for most of these types.

## `void`

`void` means "no value". You cannot create a variable of type `void`, but you can have a function that returns `void`:

```cpp
#include <iostream>

void printHello() {
    std::cout << "Hello\n";
}

int main() {
    printHello();
    return 0;
}
```

## Sizes are platform dependent

You can check sizes with `sizeof`:

```cpp
#include <iostream>

int main() {
    std::cout << "int: " << sizeof(int) << " bytes\n";
    std::cout << "long: " << sizeof(long) << " bytes\n";
    std::cout << "double: " << sizeof(double) << " bytes\n";
    return 0;
}
```

NOTE: This is one reason C++ is used for many environments. The language can target an 8 bit microcontroller or a 64 bit server.

## Fixed width integer types

If you need an integer type with a guaranteed width for a file format or network protocol, C++ provides fixed width types in `<cstdint>`, such as `std::int32_t` and `std::uint64_t`.

Reference: [cppreference: `<cstdint>`](https://en.cppreference.com/cpp/header/cstdint)

NOTE: These are aliases for regular integer types that match the width. They do not create a new magical storage class. They are mostly used when the size must be exact.

Example: Using fixed width integer types

```cpp
#include <iostream>
#include <cstdint>

int main() {
    std::int32_t a{1234567890};   // exactly 32 bits, signed
    std::uint64_t b{9876543210ULL}; // exactly 64 bits, unsigned

    std::cout << "int32_t: " << a << '\n';
    std::cout << "uint64_t: " << b << '\n';
    std::cout << "size of int32_t: " << sizeof(a) << " bytes\n";
    std::cout << "size of uint64_t: " << sizeof(b) << " bytes\n";
    return 0;
}
```

This guarantees the sizes of `a` and `b` regardless of the platform.




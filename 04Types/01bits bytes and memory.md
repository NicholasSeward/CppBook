# Bits, Bytes, and Memory

All data in a computer becomes bits at some level. To understand types, it helps to know the shape of memory.

## Bits

A **bit** is the smallest unit of information in most digital systems. It has two states, often described as `0` and `1`.

You can imagine a bit as a light that is off or on. Real hardware uses voltage levels, charge in a capacitor, magnetic orientation, and other physical tricks. The big idea is the same. Two states.

## Bytes

Computers group bits into larger chunks. A **byte** is 8 bits.

Many C++ types are described in bytes:

- `char` is usually 1 byte
- `int` is often 4 bytes on desktop systems
- `double` is often 8 bytes

> NOTE: C++ does not promise exact sizes for most built in types. It promises relationships, minimum sizes, and rules. You can always check sizes with `sizeof`.

## Memory and addresses

Your computer's RAM can be viewed as a huge sequence of bytes. Each byte has an **address**. In C++, memory is addressable, which means the language lets you talk about addresses (later: pointers).

Addresses are often written in **hexadecimal** because it maps nicely to bits:

```text
0x00 0x01 0x02 0x03 0x04 0x05 ...
```

Here is a mental model:

```text
address:   0x1000  0x1001  0x1002  0x1003
byte:        3A      00      FF      7C
```

Each box is a byte. The address labels are not stored in RAM. They are how the CPU and OS refer to a location.

## Memory comes in bigger chunks

RAM is organized internally in larger blocks (often called **pages**). Even though you can read a single byte, the hardware typically moves data in bigger chunks.

This is one reason why placing data that is used together near each other can improve performance. The CPU caches nearby bytes.

> NOTE: You do not need to optimize memory layout in beginner programs. This idea becomes useful later when you work with arrays, vectors, and performance.

## Why types exist

If everything is bits, how does the computer know whether a sequence of bits means:

- the integer `42`
- the character `'A'`
- the floating point number `3.14`

It does not know by itself. We decide a meaning. A **type** is the agreement between you, the compiler, and the hardware about how to interpret the bits.

C++ lets you work at both levels:

- High level: `int age{20};`
- Low level: pointers, byte level work, and custom data layouts (later topics)

## Try it

Compile and run this program. It prints the size of a few types on your system.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "sizeof(char) = " << sizeof(char) << " byte(s)\n";
    std::cout << "sizeof(bool) = " << sizeof(bool) << " byte(s)\n";
    std::cout << "sizeof(int) = " << sizeof(int) << " byte(s)\n";
    std::cout << "sizeof(long) = " << sizeof(long) << " byte(s)\n";
    std::cout << "sizeof(double) = " << sizeof(double) << " byte(s)\n";
    return 0;
}
```

> PREFERENCE: Do not memorize sizes from this output. Learn the idea that sizes can vary and that `sizeof` tells the truth for your build.


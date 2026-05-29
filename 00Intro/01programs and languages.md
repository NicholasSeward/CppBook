# Programs and Languages

A **computer program** is a set of instructions that tell a computer what to do. Programs manipulate **data** (numbers, text, files, network messages) using logic you write.

**Programming languages** are how humans write those instructions. The computer does not understand English directly. Your source code must be turned into a form the machine can execute.

## Running and portability

**Running** (or **executing**) a program means the computer carries out your instructions. A program that works on your laptop might not work unchanged on a phone, a server, or an old operating system unless you plan for **portability**.

Portability is the ability to move software to another machine or OS with little or no change. Different CPUs, operating systems, and libraries all affect portability.

## Machine code, binary, and bits

At the bottom, computers work with **binary**: patterns of `0` and `1`. One binary digit is a **bit**. Groups of bits represent numbers, instructions, and characters.

**Machine code** is the CPU's native instruction set. **Binary** usually means the executable file or raw data stored as those 0s and 1s. You rarely write machine code by hand.

## High level and low level: a Venn diagram

Programming languages are often described as "high level" or "low level," but some (like C++) can span both.

Here’s a simple Venn diagram showing the intersection.

```
+----------------------------------+ 
|   High Level                     |
|  (Python, Java)                  | 
|                                  |  
|        +-------------------------+---------+
|        |        C++ (both)       |         |
+--------|-------------------------+         |
         |                                   |
         |     Low Level                     |
         |   (C, Assembly, Machine code)     |
         +-----------------------------------+
```
C++ is shown in the intersecting area where both rectangles meet: it can be used as both a high level and a low level language.

- **Python and Java:** These are purely high-level languages. You focus on problems, data structures, and logic, not hardware details.
- **C++:** This language can be high level (abstract, object-oriented code) or low level (direct hardware access, manual memory management). It sits in the overlap.
- **C, Assembly, Machine code:** These are low level. You control memory directly and interact closely with the CPU.

**High level**: Easier for humans to read and write. Hardware details are hidden. Code is focused on what to do, not how.

**Low level**: Close to the hardware. Gives you control over performance, timing, and memory, but code is harder to write and understand.

> NOTE: Higher level means more abstraction, not always "better." Sometimes you need lower level code for speed or hardware access.

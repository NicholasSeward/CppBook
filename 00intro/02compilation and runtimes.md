# Compilation and Runtimes

High level source code must reach the CPU somehow. Common paths are **compilation**, **interpretation**, and hybrids such as **JIT** (just-in-time compilation).

## Compilation

A **compiler** translates your entire source file (or project) into machine code (or near-machine code) **before** the program runs. C and C++ work this way.

Benefits:

- Fast execution once built
- Errors caught before you run (many syntax and type problems)

Tradeoffs:

- You must **rebuild** after changes
- The same source might need different builds for different platforms unless you plan carefully

**Cross platform** development means targeting more than one OS or CPU. Compilers and libraries help, but portability is never automatic.

## Interpretation

An **interpreter** reads source code line by line (or chunk by chunk) and performs actions immediately. There is often no separate compile step before the first run.

Benefits:

- Fast edit-run cycles for small scripts
- Easy to ship source and run anywhere an interpreter exists

Tradeoffs:

- Usually slower at runtime than optimized compiled code
- The interpreter must be installed on the target machine

## JIT compilation

A **JIT (Just-In-Time) compiler** translates code into machine instructions while the program is running—not entirely before, like a traditional compiler. This allows the runtime to make optimizations based on the exact hardware, program input, or behavior seen during execution. JIT compilation combines some benefits of compiled and interpreted code.

**Examples of JIT compilation:**
- The [JavaScript engine V8](https://v8.dev/) (used by Chrome and Node.js) JIT-compiles JavaScript code for fast execution in web browsers and 

**Benefits:**
- Programs may run nearly as fast as compiled code after the JIT is warmed up.
- Can optimize code for the specific machine in use.

**Tradeoffs:**
- Initial startup can be slower, since some compilation happens as the program runs.
- Complexity is added to the runtime system.

## Virtual machines

A **virtual machine (VM)** is software that simulates a computer, running code inside an isolated environment. Instead of compiling source code directly to a particular CPU's instructions, a compiler creates an **intermediate form**—such as Java bytecode or C#'s MSIL—which is executed by the VM. The VM can run this intermediate code, making it portable across different hardware and operating systems.

**Examples of language runtimes that use virtual machines:**
- [Java](https://en.wikipedia.org/wiki/Java_(programming_language)) programs run on the [Java Virtual Machine (JVM)](https://en.wikipedia.org/wiki/Java_virtual_machine).
- [C#](https://en.wikipedia.org/wiki/C_Sharp_(programming_language)) and other .NET languages run on the [.NET Common Language Runtime (CLR)](https://en.wikipedia.org/wiki/Common_Language_Runtime).
- [Python](https://en.wikipedia.org/wiki/Python_(programming_language)) code is compiled to bytecode and interpreted by the [CPython VM](https://en.wikipedia.org/wiki/CPython).
- [Lua](https://www.lua.org/) uses a stack-based virtual machine to run Lua bytecode.

The pattern for VM-based languages is: write code in a high level language, compile to an intermediate (portable) form, and let the virtual machine adapt to the local system. This improves portability and security at some cost in speed and complexity.

## How this course fits

C++ is **compiled**. You will edit `.cpp` files, build an executable, then run it. Later chapters assume that workflow.

But unlike some languages, C++ is **not portable by default**. The program you compile for one kind of computer (say, your laptop with an Intel CPU and Windows) probably won’t run as-is on a different kind of computer (like a Raspberry Pi or a Mac with an ARM chip). At the very least, you’ll need to **recompile** your C++ code for each type of CPU you want to support.

For most simple programs in this course, your C++ code itself should work across different operating systems—you won’t need to rewrite it just because you move between Windows, Mac, or Linux. But C++ gives you access to low-level features and system-specific details. As soon as you use those (for example: file paths, graphics, or networking), you might end up writing special-case code that only works on one operating system, or only with certain compilers. In bigger projects, this can turn into a maze where you need a version of the code for every OS, and you have to compile separately for each kind of CPU for every OS.

We’ll keep things simple in this course. Just know that, because C++ lets you write “close to the metal,” you almost always sacrifice some portability compared to languages that run entirely on virtual machines or have built-in interpreters.

NOTE: This book's runnable snippets in the browser may use other toolchains (such as compiling to [WebAssembly](https://en.wikipedia.org/wiki/WebAssembly)). Your local workflow for assignments will likely use **g++** unless stated otherwise.


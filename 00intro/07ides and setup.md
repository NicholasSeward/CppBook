# IDEs and Setup

You need a place to edit code, build it, and run it. An **IDE** (integrated development environment) combines editing, building, running, and debugging in one app.

## Common options

| Tool | Notes |
|------|--------|
| [Visual Studio](https://visualstudio.microsoft.com/) | Strong on Windows, MSVC, large C++ projects |
| [VS Code](https://code.visualstudio.com/) | Lightweight editor, extensions for C++ |
| [CLion](https://www.jetbrains.com/clion/) | C/C++ focused IDE (paid for many users) |
| Terminal + `g++` | Minimal, full control, works everywhere |

This course mainly uses **GitHub Codespaces** with **VS Code** in the browser. Codespaces is a remote Linux environment with tools preconfigured. VS Code is a capable editor with extensions; for C++ it is not a single dedicated IDE, but it is flexible.

## Basics by platform

You can also work locally:

**Codespaces (this course)**  
Open the repo in Codespace. Use the terminal for `g++` and the editor for `.cpp` files. The Run or play button often wraps the same compile command.

**Windows**  
Install a compiler (MSVC via Visual Studio Build Tools, or MinGW/`g++`). Use VS Code or Visual Studio.

**macOS**  
Install Xcode Command Line Tools (`xcode-select --install`) for `clang++`/`g++`, or use Homebrew. Edit in VS Code or another IDE.

**Linux**  
Install `g++` with your package manager (`sudo apt install g++` on Debian/Ubuntu). Edit in VS Code or any editor.

PREFERENCE: Name source files with the `.cpp` extension for C++ source. That helps tools pick the right compiler.

## Your first file

Let's make sure everything is working by creating a simple program from scratch.

1. Create a new file called `hello.cpp`.
2. Copy and paste this minimal **hello world** program into it:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world!\n";
    return 0;
}
```

3. Build and run it, either from the terminal or using the play button in your editor.

NOTE: Even a tiny program like this relies on many pieces: your editor, the file system, the compiler, linker, libraries, terminal, and even fonts. Starting with something small helps you pinpoint **which part** of the stack has a problem if it doesn't work as expected.

## Terminal first

Most class projects run in the **terminal**. Graphics and GUI topics come later. Terminal programs keep focus on logic, I/O, and problem solving without windowing complexity.

## VS Code play button vs `g++`

The play button (or Run task) usually runs a command like:

```bash
g++ -std=c++17 hello.cpp -o hello && ./hello
```

VS Code is a productivity layer. It is not required. You can always compile from a shell with `g++` if the editor misbehaves.
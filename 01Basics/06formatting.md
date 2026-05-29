# Formatting

Good formatting makes code easier for humans to read. It also helps AI tools, because predictable structure gives them less noise to sort through.

C++ mostly ignores whitespace, which means you can write truly awful-looking code that still compiles. Most classes, employers, and projects will not accept code unless it follows a formatting standard. This chapter covers the style this book will roughly use.

## Whitespace in C++

C++ is mostly **whitespace independent**. Spaces, tabs, and newlines usually do not change what the program means.

But whitespace is still needed to separate some tokens:

```
int x{5};   // OK
intx{5};    // not the same thing
```

Where one space can go, many spaces or newlines can often go:

```
int
x
{
    5
};
```

That is legal, but do not write code that way. The goal is not only to satisfy the compiler. The goal is to help the next reader.

> NOTE: Single-line comments are different. A `//` comment ends at the newline, so moving line breaks can change what is commented out.

## Bad formatting that still compiles

This program is valid C++, but it is painful to read:

```cpp
#include <iostream>
int main(){int x{5};if(x>0){std::cout<<"positive\n";}else{std::cout<<"not positive\n";}return 0;}
```

The compiler can understand it. Humans have to work harder.

## Better formatting

Same program, formatted for readability:

```cpp
#include <iostream>

int main()
{
    int x{5};

    if (x > 0)
    {
        std::cout << "positive\n";
    }
    else
    {
        std::cout << "not positive\n";
    }

    return 0;
}
```

The blank lines separate ideas. Indentation shows what belongs inside `main` and what belongs inside the `if`.

## Basic guidelines

- Put blank lines between functions.
- Keep lines near 80 characters when reasonable.
- Avoid splitting one simple statement across many lines.
- Align `{}` in a consistent style.
- Indent the body of every code block.
- When you open a block, indent.
- When you close a block, unindent.

> PREFERENCE: This book uses a style where the opening `{` starts on the line after the statement that owns it, and both `{` and `}` are aligned in the same column.

```
if (score >= 60)
{
    std::cout << "Pass\n";
}
else
{
    std::cout << "Try again\n";
}
```

## Another brace style

You will also see the opening brace kept on the same line:

```
if (score >= 60) {
    std::cout << "Pass\n";
} else {
    std::cout << "Try again\n";
}
```

This is also valid. The important thing is consistency.

> NOTE: This book uses vertically aligned `{}` unless the example is intentionally showing bad formatting or an alternate style.

## Tabs vs spaces

Indentation can use tabs or spaces. C++ does not care.

Your editor can make the Tab key insert either a tab character or a certain number of spaces. Most editors can detect the style already used in a file.

> NOTE: Whitespace matters more in languages like Python. If you copy and paste mixed tabs and spaces into a whitespace-dependent language, you can get bugs or syntax errors. In C++, it is mainly a readability issue.

## Line length

Many editors draw a vertical guide around 80 characters. That does not mean a line becomes evil at character 81. It means you should start asking whether the line would be easier to read if you split it.

> PROTIP: If a line goes a few characters past 80, leave it alone if it reads well. Avoid giant lines that require horizontal scrolling.

Bad:

```
std::cout << "The final price after tax and discount is " << finalPrice << " dollars\n";
```

Better if it gets too long:

```
std::cout << "The final price after tax and discount is "
          << finalPrice
          << " dollars\n";
```

## Formatting tools

Modern IDEs and AI tools can format code automatically.

> PROTIP: Make formatting part of your normal process. Write code, run the formatter, then read the result. Automatic formatting does not replace understanding, but it removes a lot of boring cleanup.

In many editors you can format the current file with a command like **Format Document**. For example, in Visual Studio Code, the default shortcut is **Shift+Alt+F**.

## Official style guides

Companies, classes, and projects may publish a style guide. If they do, follow it.

Examples:

- [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)
- [GCC Coding Conventions](https://gcc.gnu.org/codingconventions.html)

> PREFERENCE: This textbook will very roughly follow the C++ Core Guidelines, but the goal is beginner readability rather than strict professional style compliance.

## Try it now

Reformat the starter program by hand so the braces and indentation match this book's style.

```cpp
#include <iostream>
int main(){int score{72};if(score>=60){std::cout<<"Pass\n";}else{std::cout<<"Try again\n";}return 0;}
```

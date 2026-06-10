# Markdown

You already read Markdown every time you open a chapter in this book. The `.md` files are **Markdown**: a lightweight way to write formatted text using plain characters instead of a word processor menu.

## What Markdown is

**Markdown** is a markup language designed to be easy to read and write in a text editor. You add structure with symbols like `#`, `*`, and `` ` ``. A tool converts that source into HTML (or another display format) for browsers, GitHub, or TxtBook.

**Plain text** has no structure beyond line breaks. Everything looks the same. You cannot express a heading, link, or table without extra conventions that every reader must guess.

**HTML** (HyperText Markup Language) is the language web pages use. It is powerful but verbose:

```html
<h1>Title</h1>
<p>This is <strong>bold</strong> and a <a href="https://example.com">link</a>.</p>
```

The same idea in Markdown:

```markdown
# Title

This is **bold** and a [link](https://example.com).
```

Markdown is a shortcut layer. Most Markdown tools turn it into HTML behind the scenes.

## Compared to other markup languages

| Format | Typical use | Readability in source | Power |
|--------|-------------|------------------------|-------|
| Plain text | Notes, logs | High | Low |
| Markdown | Docs, READMEs, wikis, books | High | Medium |
| HTML | Web pages, email templates | Low | High |
| [LaTeX](https://www.latex-project.org/) | Academic papers, math-heavy PDFs | Medium | High (especially math) |

Markdown sits in a sweet spot for everyday documentation. You get headings, lists, links, and code blocks without typing angle brackets everywhere.

## Markdown in software development

If you use **Git** hosting, you see Markdown constantly:

- **GitHub** and **GitLab** render `.md` files in the browser
- **README.md** is the front page of a repository
- **Issues** and **pull request** descriptions support Markdown
- **Wikis** and project docs are often a folder of `.md` files
- **CHANGELOG.md** and **CONTRIBUTING.md** explain releases and how to help

This book is a GitHub repo full of Markdown chapters. Your assignments, notes, and portfolio projects benefit from the same skill.

> PROTIP: In **VS Code**, right-click a `.md` file in the Explorer or on its editor tab and choose **Open Preview** (or **Open Preview to the Side**). The upper-right corner of the editor often has icons to toggle between the raw Markdown source and the rendered preview. Use both views: edit in source, check formatting in preview.

## README.md

A **README** file answers: "What is this project, and how do I use it?"

Conventions:

- Name it `README.md` (all caps `README`, extension `.md`)
- Put it in the repository root (or sometimes in subfolders)
- GitHub and GitLab show it automatically on the project home page

A solid README often includes:

1. Project name and one-line summary
2. How to build or run the program
3. Requirements (compiler, OS, dependencies)
4. License or attribution (if applicable)
5. Links to docs, demos, or issue tracker

```markdown
# MyProject

A small C++ program that tracks scores.

## Build

    g++ -std=c++17 main.cpp -o app

## Run

    ./app
```

Notice the indented code block above. Fenced triple-backtick blocks (shown later) are usually clearer for copy-paste commands.

## Markdown in the AI age

Large language models produce and consume Markdown naturally. You will see it in:

- Chat replies with headings and bullet lists
- Generated documentation and tutorials
- `README` drafts and issue templates
- Structured prompts ("respond in Markdown with a table")

Markdown is a **portable format** both humans and tools understand. Plain text alone loses structure. Full HTML is heavier and harder to edit in a chat box or comment field.

> AI: When you ask an assistant for a plan, comparison, or checklist, requesting Markdown output often gives you something you can paste directly into a repo wiki or lecture notes with minimal cleanup.

## Headings

Use `#` at the start of a line. More `#` characters mean a deeper heading level.

```markdown
# Chapter title

## Section

### Subsection
```

Edit the playground below. Add a `##` line and a `###` line under the title.

```md
# My notes

Start here.
```

## Emphasis

```markdown
*italic* or _italic_
**bold** or __bold__
***bold italic***
`inline code`
```

```md
This course uses **C++** and `std::cout`.
```

## Lists

Unordered list:

```markdown
- compile
- run
- debug
```

Ordered list:

```markdown
1. Write code
2. Test
3. Commit
```

Task list (common on GitHub):

```markdown
- [x] Read chapter
- [ ] Finish exercise
```

```md
## Today

- [ ] Fix bug in `main.cpp`
- [x] Push to GitHub
```

## Links

```markdown
[visible text](https://example.com)
[README in this repo](../README.md)
```

```md
See the [C++ reference](https://en.cppreference.com/w/).
```

## Images

Images use a syntax similar to links, with a `!` prefix:

```markdown
![short description](test.png)
```

The text in brackets is **alt text** (accessibility and fallback if the image fails to load). This chapter folder includes `test.png` for practice:

```md
# Screenshot

![Sample image for Markdown practice](test.png)
```

On GitHub, image paths in Markdown are usually relative to the `.md` file, just like here.

## Code blocks

Inline code uses single backticks: `` `int main()` ``.

Fenced blocks use triple backticks. Optional language tag enables syntax highlighting:

````markdown
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello\n";
}
```
````

```md
Example command (indented):

    g++ main.cpp -o app
```

Or with a fence:

````md
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello\n";
}
```
````

## Blockquotes

Use `>` at the start of a line for quotations or callouts:

```markdown
> NOTE: Markdown blockquotes can stand in for sidebar notes.
```

```md
> NOTE: Commit often with clear messages.
> Small commits are easier to review.
```

## Tables

```markdown
| Tool | Role |
|------|------|
| g++ | Compiler |
| git | Version control |
| Markdown | Documentation |
```

```md
| Phase | Action |
|-------|--------|
| Edit | Write `.md` in VS Code |
| Preview | Open TxtBook or GitHub |
| Share | Push to GitLab or GitHub |
```

## Horizontal rules

Three or more dashes on their own line:

```markdown
---
```

Use sparingly to split major sections in long documents.

## Try it now

### Exercise 1: Mini README

Prompt: Turn the playground into a tiny project README with a title, one-sentence description, and a fenced code block showing a build command.

```md
# TODO: project name

TODO: one-line summary.

## Build

TODO: fenced code block with g++ command
```

### Exercise 2: Table and task list

Prompt: Add a table with two columns (`Step`, `Done`) and a task list with two items (one checked, one unchecked).

```md
# Sprint plan

## Tasks

TODO: task list here

## Progress

TODO: table here
```

### Exercise 3: Link, image, and quote

Prompt: Add a link to [GitHub](https://github.com), embed `test.png` with alt text, and add a blockquote note below the image.

```md
# Resources

TODO: link to GitHub

TODO: image test.png

TODO: blockquote about keeping docs up to date
```

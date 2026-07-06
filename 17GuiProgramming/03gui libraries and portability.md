# GUI Libraries and Portability

You rarely call macOS Cocoa, Windows Win32, or Linux X11/Wayland directly. You use a **library** as a middle layer.

## Two families

| Family | Examples | Good for |
|--------|----------|----------|
| **Game / multimedia** | SDL2, SFML, raylib, Allegro | 2D games, custom rendering, full-screen apps |
| **Windowing / widgets** | Qt, wxWidgets, GTK | Buttons, menus, dialogs, desktop apps with standard controls |

**SDL2** is this chapter's focus: cross-platform, widely used, low-level enough to see how init, events, and drawing actually work.

## What OpenGL, Vulkan, and friends are

Under many games and tools, the GPU draws through a **graphics API**:

| API | Typical platform |
|-----|------------------|
| **OpenGL** | Cross-platform (older but everywhere) |
| **Vulkan** | Modern, explicit, cross-platform |
| **Direct3D** | Windows / Xbox |
| **Metal** | Apple devices |

These APIs talk to the **GPU** with shaders, buffers, and draw calls. SDL2's **`SDL_Renderer`** hides most of that for **2D** work: you set colors, copy textures, and present frames without writing GPU shaders yourself. If you later need full 3D or custom effects, SDL can also help you create an OpenGL/Vulkan context — but that is outside this chapter's scope.

## Why SDL2 for portability

Each OS has its own windowing API. Portable code without a library needs `#ifdef _WIN32` branches and separate backends.

SDL2 **wraps** those differences. The same `SDL_CreateWindow` and draw calls run on Windows, macOS, Linux, and (in TxtBook) the browser via Emscripten.

SDL2 can also use **hardware acceleration** for 2D rendering when a GPU is available, without you writing OpenGL or Vulkan by hand.

## SDL2 feature snapshot

| Area | SDL2 provides |
|------|----------------|
| Window | Create, title, size, fullscreen flags |
| 2D draw | Renderer, rectangles, textures, copy/blit |
| Input | Keyboard, mouse, game controller basics |
| Events | Unified queue for quit, input, resize |
| Extensions | Image, font, audio, extra gfx (separate libs) |

> PREFERENCE: If you need **windowing and widgets in C++** (forms, menus, file dialogs), **Qt** is a common option — not tied to one OS, but not "free" native widgets on every platform without extra work. Pick **SDL2** when you own the whole framebuffer (games, tools, visualizations).

## Program types (rough map)

| You are building | Often use |
|------------------|-----------|
| 2D game | SDL2, SFML, raylib |
| Desktop form app | Qt, wxWidgets |
| Terminal tool | No GUI library |
| Browser-only UI | HTML/JS (outside this chapter) |

## Further reading

| Resource | URL |
|----------|-----|
| SDL2 wiki | [wiki.libsdl.org/SDL2/FrontPage](https://wiki.libsdl.org/SDL2/FrontPage) |
| Qt docs | [doc.qt.io](https://doc.qt.io/) |

## Try it now

### Exercise 1: Pick a library

Prompt: You want a settings dialog with checkboxes and file picker. SDL2 or Qt?

:::details Answer

**Qt** (or similar widget toolkit). SDL2 does not ship ready-made native dialogs; you draw everything yourself.

:::

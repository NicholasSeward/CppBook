# GUI Libraries and Portability

You rarely call macOS Cocoa, Windows Win32, or Linux X11/Wayland directly. You use a **library** as a middle layer.

## Two families

| Family | Examples | Good for |
|--------|----------|----------|
| **Game / multimedia** | SDL2, SFML, raylib, Allegro | 2D games, custom rendering, full-screen apps |
| **Windowing / widgets** | Qt, wxWidgets, GTK | Buttons, menus, dialogs, native-looking desktop apps |

**SDL2** is this chapter's focus: cross-platform, widely used, low-level enough to see how init, events, and drawing actually work.

## Why SDL2 for portability

Each OS has its own windowing API. Portable code without a library needs `#ifdef _WIN32` branches and separate backends.

SDL2 **wraps** those differences. The same `SDL_CreateWindow` and draw calls run on Windows, macOS, Linux, and (in TxtBook) the browser via Emscripten.

SDL2 can also use **hardware acceleration** for 2D rendering when a GPU is available, without you writing OpenGL, Vulkan, Metal, or Direct3D by hand.

## SDL2 feature snapshot

| Area | SDL2 provides |
|------|----------------|
| Window | Create, title, size, fullscreen flags |
| 2D draw | Renderer, rectangles, textures, copy/blit |
| Input | Keyboard, mouse, game controller basics |
| Events | Unified queue for quit, input, resize |
| Extensions | Image, font, audio, extra gfx (separate libs) |

> PREFERENCE: Pick **Qt** when you need native widgets and forms. Pick **SDL2** when you own the whole framebuffer (games, tools, visualizations).

## Program types (rough map)

| You are building | Often use |
|------------------|-----------|
| 2D game | SDL2, SFML, raylib |
| Desktop form app | Qt, wxWidgets |
| Terminal tool | No GUI library |
| Browser-only UI | HTML/JS (outside this chapter) |

## Try it now

### Exercise 1: Pick a library

Prompt: You want a settings dialog with checkboxes and file picker. SDL2 or Qt?

:::details Answer

**Qt** (or similar widget toolkit). SDL2 does not ship ready-made native dialogs; you draw everything yourself.

:::

# GUI Programming (SDL2) — outline

make sure to put a huge disclaimer

a lot of magic is being done to run sdl2 in the browser.  build times will be long.  all examples have been tested in chrome.  do play with the code but it is very posible to have perfectly fine code that may break in the browser.  you can even make the browser nonresponsive (by remove the sdl delay for example)

please use it but beware.  you may have to refresh tabs or even restart the browser.  save anything in other tabs if they matter.  

if you need assets in examples use the following

assets/dude.png
assets/font.ttf
assets/boing.wav
assets/music.ogg

Rough notes. One sentence per topic. Edit freely before fleshing into section files.

---

## What is GUI programming?

- GUI programming is writing software where the user interacts through windows, graphics, and input devices instead of only a text terminal.
- Contrast with console programs: output is visual, layout matters, and the program waits for user actions rather than running top-to-bottom once.

---

## Fundamental structure: the game loop

- Most interactive GUI and game programs revolve around a **game loop**: initialize once, then repeat update/draw/input until the user quits.
- Each trip through the loop is roughly one **frame** (one screen refresh cycle).
- The loop is why the program does not "finish" like `main` in a homework program; it keeps running until an exit condition.

---

## Event-driven programming

- GUI code is **event-driven**: the OS or library delivers events (key down, mouse move, window close) and your code reacts.
- You do not poll the keyboard in a tight `while` the way a console program might; you process an **event queue**. You get the events when you get them.  
- Tie events to game state: press left → move sprite; click button → run action.

---

## Libraries: games vs windowing toolkits

- You rarely talk to the OS window system directly; you use a **library** as a middle layer.
- **Game-oriented libraries** (examples to mention): SDL2, SFML, raylib, Allegro.
- **Windowing / GUI toolkits** (examples to mention): Qt, wxWidgets, GTK, Win32 API, Cocoa.
- Brief note on what each family is good for: games/rendering vs native widgets and dialogs.
- SDL2 is the focus of this chapter: cross-platform, low-level enough to learn how things work, widely used.

table of what types for programs and libraries for games/windowing
talk about the specific features of sdl2

---

## Why libraries help: portability and abstraction

- macOS, Windows, and Linux each have different native windowing APIs; portable code would otherwise need `#ifdef` branches everywhere.
- A library like SDL2 wraps those differences so the same init/create-window/draw code runs on multiple platforms.
- SDL2 can also route rendering through the GPU when available, without you writing OpenGL/Vulkan/Metal/DirectX calls by hand for basic 2D.

---

## SDL2 mindset: init everything, destroy in reverse

- SDL2 is a bit **old school**: you call explicit init functions for each subsystem you need (video, audio, fonts, images, etc.).
- On shutdown, destroy/cleanup in the **opposite order** from creation (renderer before window, window before `SDL_Quit`, etc.).
- Mention that later sections add **error checking** after each step with rollback if something fails.

---

## Double buffering

- Drawing directly to the visible screen while the user watches causes **flicker** and torn frames.
- **Double buffering**: draw to an off-screen buffer, then swap or present it to the screen in one step.
- SDL's renderer handles this pattern; you clear, draw, then `SDL_RenderPresent`.

---

## Basic SDL2 program structure (no error rollback yet)

Outline the skeleton; flesh each step into its own section:

1. **Init SDL** (and any extension libs: image, ttf, mixer).
2. **Create window** — the OS surface the user sees.
3. **Create renderer** — the object that draws into that window.
4. **Main game loop** — event loop + update + draw each frame.
5. **Cleanup** — destroy renderer, window, quit SDL (reverse order).

- First pass: minimal working program with no error checks.
- Later section: check return values, roll back and exit on failure.

---

## Sections to flesh out (init → loop → cleanup)

### Init SDL and extension libraries

- `SDL_Init` and flags for subsystems you need.
- Optional: `IMG_Init`, `TTF_Init`, `Mix_Init` when those chapters come in.
- Error checking pattern: if init fails, print `SDL_GetError`, exit (no partial state yet).

### Create window

- `SDL_CreateWindow` — title, position, size, flags.
- Rollback: if window fails, `SDL_Quit` and exit.

### Create renderer

- `SDL_CreateRenderer` — ties drawing to the window; hardware vs software acceleration flag.
- **Render as paintbrush metaphor**: you pass the renderer around; whoever holds it can draw, but typically one owner draws per frame.
- Rollback: destroy window, quit SDL.

### Main game loop

- `while (running)` — process events, update state, render, present.
- Inner **event loop**: `SDL_PollEvent` until queue empty.
- Drawing: clear, draw primitives/sprites, `SDL_RenderPresent`.

### Cleanup

- Destroy renderer, destroy window, quit mixer/image/ttf if used, `SDL_Quit`.
- Order matters: opposite of creation.

---

## Bouncing square example

- Simple demo: rectangle moves, bounces off window edges.
- Use `SDL_Delay(16)` (~60 FPS cap) to keep CPU from spinning.
- Note: fixed delay is fine when work per frame is light; serious games need to measure real frame time (see frame limiting section).
- Introduce `deltaTime` idea in passing for later engine section.

---

## Frame time and better limiting

- `SDL_Delay(16)` assumes every frame costs ~0 ms; real work varies.
- Snippet: target FPS, `SDL_GetTicks`, measure elapsed, delay only the remainder, optionally print FPS.
- Mention that knowing **frame duration** matters for smooth motion and physics.  you don't move a set distance per frame you might instead move your velocity * dt.

---

## Simple engine idea (optional capstone)

- Better structure: an **engine** holds objects to draw, pending events, and frame timing.
- `engine.step()` could process events, update, render in one call.
- Inside updates, use `engine.deltaTime` (seconds since last frame) for movement instead of "pixels per frame."

---

## SDL2 extension libraries — what each is for

- **SDL2** — core: window, input, events, 2D renderer basics.
- **SDL2_gfx** — extra primitives (lines, circles, polygons, rotozoom).
- **SDL2_image** — load PNG, JPG, etc. into textures.
- **SDL2_ttf** — TrueType fonts → text as texture or surface.
- **SDL2_mixer** — WAV/OGG playback, channels, music vs sound effects.

---

## Input: keyboard, mouse

- **Key press / release** — `SDL_KEYDOWN`, `SDL_KEYUP`, `event.key.keysym.sym`.
- **Mouse movement** — `SDL_MOUSEMOTION`, position in event.
- **Mouse clicks** — `SDL_MOUSEBUTTONDOWN` / `UP`, which button.
- **Getting mouse position** — from motion event or `SDL_GetMouseState`.
- Example: move object with keyboard; button that responds to mouse click.

---

## Drawing: primitives, colors, coordinates

- Basic renderer draws: rectangles, points, lines (gfx for circles).
- **Coordinate system**: origin top-left; **x** right positive, **y** **down** positive (unlike math class graphs).
[ascii drawing of coordinate system]
- **Color formats**:
  - Sometimes RGBA as separate values (0–255 per channel).
  - Sometimes one `Uint32`: SDL often **0xAABBGGRR** (ABGR in hex). Example: `0xFFFF0000` = full opaque blue.
  - `0xFF` = 255 = often "100%" of that channel; other APIs use 0–100 or 0.0–1.0 — read the docs.
- **SDL2_gfx circles** example: several colors, same API, different `Uint32` or RGBA.

---

## Images and textures

- Load image once with SDL2_image; store as **texture** on the renderer. explain what a texture is vs the image that was loaded.
- **Do not reload every frame** — disk I/O and decode are slow.
- Where to put files: `assets/` folder; paths relative to working directory or executable.
- Draw with `SDL_RenderCopy` (destination rect, optional source rect).


explain the concept of blit and how texture works into this.  

example
---

## Fonts and text

- SDL2_ttf: load `.ttf` once, render text to surface/texture.
- **Do not reload font every frame.**
- Small projects often redraw all text each frame; larger projects cache text textures and only re-render when the string changes.

example
---

## Audio

- SDL2_mixer: load sound effect and music files once.
- **Do not reload audio every frame.**
- Channels for SFX; `Mix_PlayMusic` for background loop.
- Volume, halt, fade (brief mention).

example sound fx
example background
---

## Assets and the build

- Source assets live in repo (`assets/images`, `assets/fonts`, `assets/audio`).
- **Build must copy** assets (and on Windows, **DLLs**) next to the executable or the program cannot find them at runtime.
- Contrast "works in IDE" vs "works from build folder."

---

## Asset organization

- Suggested layout: `assets/sprites/`, `assets/fonts/`, `assets/audio/`, `assets/ui/`.
- Naming conventions; one manifest or constants file for paths (optional).
- Keep paths in one place so moving files does not scatter string literals.

---

## Performance habits

- Move heavy work **out of the per-frame path** (load once, cache textures/fonts/audio).
- Error-check init; fail fast with clear messages.
- Rendering modes / blend modes (brief): alpha, additive — link to docs when needed.

---

## Cheat sheet (common functions / structs)

One subsection per library; bullet the names you use most in class:

### SDL2 (core)

- Structs: `SDL_Window`, `SDL_Renderer`, `SDL_Event`, `SDL_Rect`, `SDL_Texture`.
- Init/quit: `SDL_Init`, `SDL_Quit`, `SDL_GetError`.
- Window/renderer: `SDL_CreateWindow`, `SDL_DestroyWindow`, `SDL_CreateRenderer`, `SDL_DestroyRenderer`.
- Loop: `SDL_PollEvent`, `SDL_RenderClear`, `SDL_RenderPresent`, `SDL_SetRenderDrawColor`, `SDL_RenderFillRect`, `SDL_RenderDrawRect`.
- Time: `SDL_GetTicks`, `SDL_Delay`.
- [fill in more as you teach]

### SDL2_gfx

- `filledCircleRGBA`, `circleRGBA`, `lineRGBA`, `boxRGBA`, etc.
- [fill in]

### SDL2_image

- `IMG_Init`, `IMG_Quit`, `IMG_LoadTexture`, `IMG_Load`.
- [fill in]

### SDL2_ttf

- `TTF_Init`, `TTF_Quit`, `TTF_OpenFont`, `TTF_RenderText_Blended`, `TTF_CloseFont`.
- [fill in]

### SDL2_mixer

- `Mix_Init`, `Mix_Quit`, `Mix_OpenAudio`, `Mix_LoadWAV`, `Mix_LoadMUS`, `Mix_PlayChannel`, `Mix_PlayMusic`.
- [fill in]

---

## CMake and vcpkg (build tooling)

- **CMake** — cross-platform build generator; can copy `assets/` and DLLs to the output directory in one place.
- **vcpkg** — C++ package manager; SDL2 and extensions are not in the standard library, vcpkg makes adding/linking them easier.
- Brief "how this course project is laid out" if you have a template repo.

---

## Links and further reading

- SDL2 wiki
- SDL2 API reference (libsdl.org)
- Lazy Foo's SDL tutorials
- Twinklebeardev SDL2 tutorial
- [add course-specific links]

---

## Suggested section files (when fleshing out)

Rename/edit as needed:

1. what is gui programming.md
2. game loop and events.md
3. gui libraries and portability.md
4. sdl2 init and cleanup.md
5. window renderer and game loop.md
6. error checking and rollback.md
7. double buffering and coordinates.md
8. bouncing square and frame timing.md
9. keyboard and mouse input.md
10. colors and gfx primitives.md
11. images and textures.md
12. fonts and text.md
13. audio with mixer.md
14. assets and build copy.md
15. simple engine and delta time.md
16. sdl2 cheat sheet.md
17. cmake vcpkg and links.md

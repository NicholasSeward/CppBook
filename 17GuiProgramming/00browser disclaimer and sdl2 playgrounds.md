# Browser Disclaimer and SDL2 Playgrounds

> **WARNING — read this before running any `sdl2` example in TxtBook**
>
> A lot of machinery runs behind the scenes to compile SDL2 with **Emscripten** and draw to a **browser canvas** (typically **640×480**).
>
> - **Build times can be long.** The first compile of a playground may take a minute or more.
> - Examples are tested in **Chrome**. Valid desktop SDL2 code may behave slightly differently in the browser.
> - You can make a tab **unresponsive** — for example by removing **`SDL_Delay(16)`** inside the game loop so the loop spins as fast as possible.
> - If the canvas freezes or keyboard input stops working, **refresh the tab** or restart the browser. Save work in other tabs first.
>
> These playgrounds are for **learning**, not production deployment. When you build SDL2 on your own machine (see [CMake, vcpkg, and Further Reading](18cmake%20vcpkg%20and%20links.md)), you get a normal desktop executable without this browser layer.

## What `sdl2` fences are

Fenced code blocks tagged **`sdl2`** in this chapter compile in TxtBook with SDL2 and its common extensions already linked. You focus on the API, not on setting up a project from scratch on day one.

## Habits that keep playgrounds usable

| Habit | Why |
|-------|-----|
| **`SDL_Delay(16)`** once per frame | Caps frame rate near 60 FPS and keeps the browser tab responsive |
| Load assets **once** before the loop | Disk and decode are slow; do not reload every frame |
| **`// @asset: assets/...`** above includes | Tells TxtBook which chapter files to bundle |
| Click the **canvas** before arrow keys | Browser focus goes to the canvas, not the page |

## Chapter assets

Examples that need files use paths under this chapter's **`assets/`** folder:

| File | Use |
|------|-----|
| `assets/dude.png` | Sprite / texture demos |
| `assets/font.ttf` | Font / text demos |
| `assets/boing.wav` | Short sound effect |
| `assets/music.ogg` | Background music demo |

Reference them with `// @asset: assets/dude.png` (and similar) at the top of the fence.

## Further reading

| Resource | URL |
|----------|-----|
| SDL2 wiki | [wiki.libsdl.org/SDL2/FrontPage](https://wiki.libsdl.org/SDL2/FrontPage) |
| SDL2 API reference | [wiki.libsdl.org/SDL2/FrontPage](https://wiki.libsdl.org/SDL2/FrontPage) |
| Lazy Foo SDL tutorials | [lazyfoo.net/tutorials/SDL](https://lazyfoo.net/tutorials/SDL/) |

## Try it now

### Exercise 1: Why delay?

Prompt: What happens in the browser if you remove `SDL_Delay(16)` from every frame of a tight game loop?

:::details Answer

The loop may run as fast as the CPU allows, starving the browser and **freezing the tab**. The delay yields time so the page stays responsive.

:::

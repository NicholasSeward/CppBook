# What Is GUI Programming?

Until now, most of your programs talked through a **console**: text in, text out, then `main` ends.

**GUI programming** (graphical user interface) means the user interacts through **windows**, **graphics**, and **input devices** (keyboard, mouse, touch). Output is visual. Layout matters. The program often **keeps running** until the user closes the window instead of finishing in one straight line.

| Console program | GUI program |
|-----------------|-------------|
| `std::cout` for output | Draw shapes, images, text |
| `std::cin` for input | Keys, mouse, window events |
| Runs top to bottom, then exits | **Game loop** runs until quit |

## TxtBook SDL2 playgrounds

This chapter uses **`sdl2`** fenced playgrounds in TxtBook. They compile with Emscripten and draw to a browser canvas (typically **640×480**).

> NOTE: **Browser disclaimer.** A lot of machinery runs behind the scenes to make SDL2 work in the browser. **Build times can be long.** Examples are tested in Chrome. Perfectly valid desktop SDL2 code may behave differently in the browser. You can even make a tab unresponsive (for example by removing `SDL_Delay` inside the loop). Use the playgrounds, but be prepared to **refresh the tab** or restart the browser. Save work in other tabs first.

> PROTIP: Call **`SDL_Delay(16)`** once per frame so the browser stays responsive and you cap frame rate near 60 FPS.

## Chapter assets

Examples that need files use paths under this chapter's **`assets/`** folder:

| File | Use |
|------|-----|
| `assets/dude.png` | Sprite / texture demos |
| `assets/font.ttf` | Font / text demos |
| `assets/boing.wav` | Short sound effect |
| `assets/music.ogg` | Background music demo |

Reference them in playgrounds with `// @asset: assets/dude.png` (and similar) at the top of the fence.

## Try it now

### Exercise 1: Console vs GUI

Prompt: Name one thing a GUI program does that a one-shot console homework program usually does not.

:::details Answer

Keeps running in a **loop** until the user quits; and/or draws **graphics** instead of only printing text.

:::

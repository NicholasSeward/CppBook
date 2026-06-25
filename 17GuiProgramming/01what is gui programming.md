# What Is GUI Programming?

Until now, most of your programs talked through a **console**: text in, text out, then `main` ends.

**GUI programming** (graphical user interface) means the user interacts through **windows**, **graphics**, and **input devices** (keyboard, mouse, touch). Output is visual. Layout matters. The program often **keeps running** until the user closes the window instead of finishing in one straight line.

| Console program | GUI program |
|-----------------|-------------|
| `std::cout` for output | Draw shapes, images, text |
| `std::cin` for input | Keys, mouse, window events |
| Runs top to bottom, then exits | **Game loop** runs until quit |

## TxtBook SDL2 playgrounds

This chapter uses **`sdl2`** fenced playgrounds in TxtBook. Read **[Browser Disclaimer and SDL2 Playgrounds](00browser%20disclaimer%20and%20sdl2%20playgrounds.md)** first — build times, browser quirks, and the `SDL_Delay(16)` habit are explained there.

> PROTIP: Call **`SDL_Delay(16)`** once per frame so the browser stays responsive and you cap frame rate near 60 FPS.

## Game objects that draw themselves

As projects grow, you often wrap game state in a **class**. Connect Four, tic-tac-toe, a platformer level — each can expose a **`draw(SDL_Renderer* renderer)`** method. `main` (or a small engine) clears the screen, then asks each object to paint itself. Section [Window, Renderer, and Game Loop](05window%20renderer%20and%20game%20loop.md) shows passing the renderer around; the [Examples](19example%20tic%20tac%20toe.md) at the end of the chapter use this pattern.

## Chapter assets

Examples that need files use paths under this chapter's **`assets/`** folder — see section 00 for the file list and `@asset` syntax.

## Try it now

### Exercise 1: Console vs GUI

Prompt: Name one thing a GUI program does that a one-shot console homework program usually does not.

:::details Answer

Keeps running in a **loop** until the user quits; and/or draws **graphics** instead of only printing text.

:::

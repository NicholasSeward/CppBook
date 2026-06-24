# Assets and the Build

Source art lives in your repo. The **running program** looks for files on disk relative to the **working directory** or the **executable folder**.

## TxtBook playgrounds

Add assets at the top of an `sdl2` fence:

```sdl2
// @asset: assets/dude.png
// @asset: assets/font.ttf
```

Paths are relative to the lesson file (same as markdown images). TxtBook copies them into the wasm filesystem before **Run**.

## Desktop builds

When you compile locally, `assets/dude.png` is **not** magically next to your `.exe` unless you **copy** it there.

| Problem | Symptom |
|---------|---------|
| Asset not copied | `IMG_LoadTexture` fails, `IMG_GetError` "Couldn't open" |
| DLL not beside exe (Windows) | Program fails to start or load SDL |

**CMake** can copy `assets/` and required DLLs to the output directory (see section 18).

> NOTE: "It works in the IDE" often means the IDE's working directory is the project root. Running the `.exe` from Explorer uses a different folder.

## Suggested layout

```
17GuiProgramming/
  assets/
    sprites/     # dude.png, enemies...
    fonts/       # font.ttf
    audio/       # boing.wav, music.ogg
```

This chapter keeps a flat `assets/` for simplicity. Larger projects split by type.

## Path constants

Keep paths in one place:

```cpp
namespace Paths
{
    constexpr const char* playerSprite = "assets/dude.png";
    constexpr const char* uiFont = "assets/font.ttf";
}
```

## Performance

Move **load** work out of the frame loop:

- Textures, fonts, audio: **once** at init
- Heavy file I/O during gameplay causes stutter

## Try it now

### Exercise 1: Load failure

Prompt: Texture load fails after you moved `dude.png` but did not update the path string. Is that a compile error or runtime error?

:::details Answer

**Runtime** error (load returns null / logs `IMG_GetError`).

:::

# CMake, vcpkg, and Further Reading

SDL2 and its extensions are **not** part of the C++ standard library. You need a build system and (often) a package manager to link them on desktop.

## CMake

**CMake** generates project files (Visual Studio, Ninja, Makefiles) from a `CMakeLists.txt`. One place to:

- List `.cpp` sources
- Link `SDL2::SDL2`, `SDL2_image::SDL2_image`, etc.
- **Copy `assets/`** to the output directory next to the executable
- Copy **DLLs** on Windows so the program runs outside the IDE

Example ideas (not a full course template):

```cmake
add_executable(my_game main.cpp)
target_link_libraries(my_game PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)

add_custom_command(TARGET my_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:my_game>/assets)
```

## vcpkg

**[vcpkg](https://vcpkg.io/)** is a C++ package manager. Install SDL2 ports once, then CMake finds them:

```
vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer sdl2-gfx
```

Use a toolchain file: `cmake -DCMAKE_TOOLCHAIN_FILE=[vcpkg]/scripts/buildsystems/vcpkg.cmake ..`

> NOTE: TxtBook playgrounds already link SDL2 for `sdl2` fences. CMake and vcpkg matter for **local** desktop projects and homework submissions.

## Further reading

| Resource | URL |
|----------|-----|
| SDL2 wiki | [wiki.libsdl.org](https://wiki.libsdl.org/) |
| SDL2 API reference | [wiki.libsdl.org/SDL2/FrontPage](https://wiki.libsdl.org/SDL2/FrontPage) |
| Lazy Foo SDL tutorials | [lazyfoo.net/tutorials/SDL](https://lazyfoo.net/tutorials/SDL/) |
| TwinklebearDev SDL2 | [gist.github.com/Twinklebear](https://gist.github.com/Twinklebear) (SDL2 lesson series) |

## Full assets demo

Section 01 introduced chapter assets. A combined demo (sprite, font, gfx glow, click sound) lives in [test.md](test.md) for TxtBook testing. Use it as a reference when wiring all extensions together.

## Try it now

### Exercise 1: Why vcpkg?

Prompt: In one sentence, why might you use vcpkg for SDL2 on a desktop project?

:::details Answer

SDL2 is not built into the compiler; **vcpkg** downloads and builds the libraries so **CMake** can link them without manual SDK hunting.

:::

# Skippy

Skippy is a simple browser-based game built using C, SDL2, and compiled to WebAssembly using Emscripten. [Play it now in the browser!](https://ndugdale.github.io/skippy/)

<p align="center">
  <img src="/docs/images/skippy.png?raw=true" alt="Screenshot of Skippy" />
</p>

## Requirements

- **Emscripten**: [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) is required to compile the game for the web.
- **CMake**: [CMake](https://cmake.org/download/) is used for building the project.
- **_Python3_**: [Python3](https://www.python.org/downloads/) is required by Emscripten for various tools. If you install Emscripten via the SDK, or package managers such as Homebrew and Pacman, Python3 will be automatically installed as a dependency.
- **_SDL2_**: The game uses [SDL2](https://wiki.libsdl.org/SDL2/Installation) for handling graphics and input. Emscripten will automatically handle this via its ports, and so `SDL2`, `SDL2_image`, `SDL2_mixer`, and `SDL2_ttf` are only required as separate installations if you intend to build natively instead of for the web.

Install these requirements using your method of choice, e.g. on Arch Linux:

```sh
sudo pacman -S cmake emscripten
```

Or on macOS:

```sh
brew cmake emscripten
```

## Build & Run

The project uses CMake for building. You can use the `build.sh` script to compile the project with different build modes.

- Run the following to build the project:

```sh
./scripts/build.sh --debug
```

- By default, the build type is **debug**. To build with optimizations, use **release**:

```sh
./scripts/build.sh --release
```

### 2. **Running the Game in the Browser**

To run the game in a browser, use the `run.sh` script:

```sh
./scripts/run.sh
```

This will serve the game in a browser window.

## License

This project is licensed under the MIT License.

## Credits

- **Font**: "Monogram" font by [datagoblin](https://datagoblin.itch.io/monogram) (CC0 license)

# ChessEngine

A C++20 chess engine. Work in progress.

## Toolchain

- C++20 compiler (Clang 14+, GCC 11+, MSVC 19.30+)
- CMake ≥ 3.20

Install on macOS if missing:

```sh
brew install cmake
```

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Run the executable:

```sh
./build/bin/chess-engine
```

## Tests

Tests use GoogleTest, fetched on first configure (needs network):

```sh
cmake -B build -DBUILD_TESTING=ON -DCHESS_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Project layout

```
.
├── CMakeLists.txt          # Root build config (C++20, options, subdirs)
├── cmake/
│   └── Dependencies.cmake  # FetchContent-based dependency manager
├── include/chess/          # Public headers (engine façade, board, search…)
├── src/                    # Engine library + executable entry point
│   ├── CMakeLists.txt
│   ├── engine.cpp
│   └── main.cpp
└── tests/                  # GoogleTest unit tests (opt-in)
```

## Adding dependencies

Edit `cmake/Dependencies.cmake` and call `chess_add_dependency(...)`,
then link from a target:

```cmake
target_link_libraries(my_target PRIVATE fmt::fmt)
```

## Build options

| Option           | Default | Effect                              |
| ---------------- | ------- | ----------------------------------- |
| `CHESS_NATIVE`   | `ON`    | Tune binary for the host CPU (`-march=native`) |
| `CHESS_BUILD_TESTS` | `OFF` | Build the GoogleTest suite          |

# cpp-advent-of-code
My C++ advent of code submissions

## How to build

Built and run on Ubuntu 24.04 (WSL) using gcc14. gcc14 is required for std::print usage

Generate Generate projet:

```bash
# from the root of the project
cmake -B build --preset=gcc14
```

Build:

```bash
# from the root of the project
cmake --build build
```

Run:

```bash
# example run
build/2015/2015_1 "()()"
```

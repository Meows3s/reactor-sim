## Dependencies

### Build tools

- C++17 GCC or Clang
- CMake >= 3.16

### Libraries

| Library | Used for | Notes |
| --- | --- | --- |
| Qt6 Core, Gui, Widgets | Event loop, threads, signals/slots, UI | |
| Qt6 PrintSupport | Required by QCustomPlot | Needs CUPS on Linux |
| CUPS (dev headers) | Pulled in by Qt6 PrintSupport | `find_package(Cups)` fails without it |
| QCustomPlot | Real-time plots and colormaps | Bundled: `qcustomplot.h` / `qcustomplot.cpp` |
| OpenGL (dev headers) | Qt6 Gui dependency | Usually pulled in automatically |

### Install (Debian/Ubuntu)

```bash
sudo apt install build-essential cmake qt6-base-dev libcups2-dev libgl1-mesa-dev
```

```

### Build
```bash
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

- `clangd` with `build/compile_commands.json` for editor completion

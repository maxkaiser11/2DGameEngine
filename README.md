# vcpkg Setup & Build Guide — 2DGameEngine

This doc shows how to install **vcpkg**, install the SDL2 family, and build this project with CMake on Windows/macOS/Linux.

## Requirements
- Git
- CMake 3.20+
- C++ toolchain
    - Windows: Visual Studio 2022 (or Build Tools) + optional Ninja
    - macOS: Xcode command line tools
    - Linux: GCC or Clang + build essentials
- Optional: Ninja

## 1) Install vcpkg

### Windows (PowerShell)
```powershell
mkdir C:\GameDev
cd C:\GameDev
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install  # optional
```

### macOS / Linux (bash)
```bash
mkdir -p ~/Dev && cd ~/Dev
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install  # optional
```

> Assume vcpkg is at:
> - Windows: `C:\GameDev\vcpkg`
> - macOS/Linux: `~/Dev/vcpkg`

## 2) Install libraries
SDL2 + image/ttf/mixer

**Windows**
```powershell
C:\GameDev\vcpkg\vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet x64-windows
```

**macOS (Intel)**
```bash
~/Dev/vcpkg/vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet x64-osx
```

**macOS (Apple Silicon)**
```bash
~/Dev/vcpkg/vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet arm64-osx
```

**Linux (x64)**
```bash
~/Dev/vcpkg/vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet x64-linux
```

## 3) Configure & build with CMake

**Windows + Ninja**
```powershell
if (Test-Path build) { rmdir build -Recurse -Force }
cmake -S . -B build -G "Ninja" `
  -DCMAKE_TOOLCHAIN_FILE="C:/GameDev/vcpkg/scripts/buildsystems/vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build
```

**Windows + Visual Studio**
```powershell
if (Test-Path build) { rmdir build -Recurse -Force }
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE="C:/GameDev/vcpkg/scripts/buildsystems/vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build --config Debug
```

**macOS / Linux**
```bash
rm -rf build
cmake -S . -B build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$HOME/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake" \
  -DVCPKG_TARGET_TRIPLET=x64-osx   # or arm64-osx / x64-linux
cmake --build build
```

## 4) Run
Executable is in `build/bin`. CMake copies common asset folders next to it (assets/data/config/fonts/maps/textures). IDEs are set to run from that directory.

## 5) CLion / VSCode / VS
- **CLion**: Settings → CMake → CMake options:  
  `-DCMAKE_TOOLCHAIN_FILE=C:/GameDev/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows`
- **Visual Studio**: Use VS generator config above.
- **VSCode (CMake Tools)**: Set those cache variables in your `settings.json`/Configure options.

## 6) (Optional) CMakePresets.json
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "win-ninja-vcpkg",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": "C:/GameDev/vcpkg/scripts/buildsystems/vcpkg.cmake",
        "VCPKG_TARGET_TRIPLET": "x64-windows"
      }
    }
  ],
  "buildPresets": [
    { "name": "build", "configurePreset": "win-ninja-vcpkg" }
  ]
}
```

Use:
```powershell
cmake --preset win-ninja-vcpkg
cmake --build --preset build
```

## 7) Troubleshooting
- **Package not found** → Confirm triplet and reinstall packages for that triplet.
- **Toolchain path wrong** → Check the path to `scripts/buildsystems/vcpkg.cmake`.
- **Switching generators** → Delete `build/` and reconfigure.
- **Ninja: rules.ninja missing** → Clean build dir and reconfigure.
- **Black screen** → Run from `build/bin` where assets are copied.
- **Mac junk files** → Remove `.DS_Store` and `._*` and add to `.gitignore`.

## 8) One-liner
```powershell
git clone https://github.com/microsoft/vcpkg C:\GameDev\vcpkg
C:\GameDev\vcpkg\bootstrap-vcpkg.bat
C:\GameDev\vcpkg\vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet x64-windows
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="C:/GameDev/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build
```

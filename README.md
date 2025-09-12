# SDL2 Game Engine Setup

To run or build this project, follow the instructions below to correctly install all dependencies.

---

## ✅ Dependencies Required

You need to download and install the following libraries (specific versions):

- [SDL2 v2.0.12 (VC)](https://github.com/libsdl-org/SDL/releases/tag/release-2.0.12)
- [SDL2_image v2.0.5 (VC)](https://github.com/libsdl-org/SDL_image/releases/tag/release-2.0.5)
- [SDL2_ttf v2.0.15 (VC)](https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.0.15)
- [SDL2_mixer v2.0.4 (VC)](https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.0.4)
- [Lua 5.3.5 (Windows Binaries)](https://sourceforge.net/projects/luabinaries/files/5.3.5/)

---

## 📦 Step-by-Step Installation

### 1. Create the SDL2 Directory

On your **C:** drive, create a folder named `SDL2`:

```
C:\SDL2
```

### 2. Extract the Libraries

For each downloaded SDL2-related `.zip` file (the VC development libraries):

- Extract the `.zip` file.
- Open the folder and locate `include` and `lib` subfolders.
- Copy these `include` and `lib` folders into `C:\SDL2`.

You should end up with this structure:

```
C:\SDL2\include\SDL2\...
C:\SDL2\lib\x64\...
```

> You may merge the include and lib contents from each library.

---

### 3. Copy the DLLs

Copy the following DLLs (included in this project) into your **project root folder** — this is where your `.exe` file will be:

- SDL2.dll
- SDL2_image.dll
- SDL2_mixer.dll
- SDL2_ttf.dll
- lua53.dll
- zlib1.dll
- libpng16-16.dll
- libjpeg-9.dll
- libtiff-5.dll
- libwebp-7.dll

> ⚠️ If any of these are missing next to your executable, the application will not start.

---

## 🛠️ Build Configuration Notes

In your IDE (e.g., Visual Studio) or build system (e.g., CMake), ensure you:

- Add `C:\SDL2\include` to your include directories.
- Add `C:\SDL2\lib` to your library directories.

Link the following `.lib` files:

```
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_mixer.lib
SDL2_ttf.lib
lua53.lib
```

---

## ✅ You're Ready!

Once all the steps are complete, you should be able to build and run the project without errors.

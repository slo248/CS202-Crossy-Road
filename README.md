# CS202-Crossy-Road

[![cmake](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml/badge.svg)](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml) ![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0) 

## I. Overview

This is a 2D game clone version of <a href="https://www.google.com/search?q=crossy+road">Crossy Road</a>, which is developed as a group project in CS202 - Programming Systems in APCS-HCMUS.

![Game Preview](https://github.com/slo248/CS202-Crossy-Road/assets/116567243/3bb49d17-d257-4f49-b7c4-1f2d50f6d3e6)

Video demo: [Youtube](https://youtu.be/MwSDSFgAg_0)

## II. Minimum requirements

| **Operating System** |    **Compiler**   |
|:--------------------:|:-----------------:|
| Linux (Ubuntu)       | GNU 11.4          |
| Windows              | MSVC 19.37        |
| MacOS                | AppleClang 14.0   |

- CMake: v3.10
- SFML: [v2.6.1](https://github.com/SFML/SFML/releases/tag/2.6.1)

## III. How to run?

- Step 1: Install dependencies (**Linux users only**)
```console
sudo apt-get update
sudo apt-get install libfreetype6-dev libx11-dev libxcursor-dev libxrandr-dev libudev-dev libgl1-mesa-dev libflac-dev libogg-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libopenal-dev libpthread-stubs0-dev
```

- Step 2: Build
```console
git clone git@github.com:slo248/CS202-Crossy-Road.git
cd CS202-Crossy-Road
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

The executable file is located at `CS202-Crossy-Road/bin/<your operating system name>/CrossyRoad`.

## IV. Find a bug?

If you found some bugs or would like to improve the game, you can submit an issue using issues tab above.

If you would like to submit a pull request with a fix, reference the issue you created!

## V. Group members
| Student ID | Full name         |
|:----------:|-------------------|
|  22125010  | Phan Phúc Bảo     |
|  22125035  | Nguyễn Vĩnh Khang |
|  22125046  | Lê Thanh Lâm      |
|  22125076  | Nguyễn Hoàng Phúc |

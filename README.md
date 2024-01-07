# CS202-Crossy-Road

[![cmake](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml/badge.svg)](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml) ![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0) 

## I. Overview

This is a 2D game clone version of <a href="https://www.google.com/search?q=crossy+road">Crossy Road</a>, which is developed as a group project in CS202 - Programming Systems in APCS-HCMUS.

![Game Preview](https://github.com/slo248/CS202-Crossy-Road/assets/116567243/3bb49d17-d257-4f49-b7c4-1f2d50f6d3e6)

## II. Minimum requirements

| **Operating System** |    **Compiler**   |
|:--------------------:|:-----------------:|
| Linux (Ubuntu)       | GNU 11.4.0        |
| Windows              | Clang 16.0.6      |
| MacOS                | AppleClang 14.0.0 |

- CMake: v3.10
- SFML: [v2.6.1](https://github.com/SFML/SFML/releases/tag/2.6.1)

## III. How to run?

The executable file is located at `CS202-Crossy-Road/bin/<your operating system name>/CrossyRoad`.

### a. Linux (Ubuntu)

1. Install SFML (you would not have to do this if your machine already had SFML)
```console
sudo apt-get update
sudo apt-get install libfreetype-dev libx11-dev libxcursor-dev libxrandr-dev libudev-dev libgl1-mesa-dev libopenal-dev libflac-dev libvorbis-dev libvorbisenc2 libvorbisfile3 libogg-dev libpthread-stubs0-dev libxcb-image0-dev libjpeg-dev libudev-dev libx11-xcb-dev libxcb-randr0-dev libxcb1-dev libxcb1 libxcb-util0-dev libxcb-keysyms1-dev libxcb-icccm4-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xinerama0-dev libxcb-shm0-dev libxcb-xkb-dev libxcb-cursor-dev libxcb-render-util0-dev libxcb-render0-dev libxcb-xrm-dev libxcb-glx0-dev libxcb-xinput-dev libxcb-xrm-dev libxcb-xtest0-dev libxcb-xinerama0-dev libxcb-shape0-dev libxcb-shm0-dev libxcb-randr0-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-icccm4-dev libxcb-xfixes0-dev libxcb-sync-dev libxcb-xinerama0-dev libxcb-shape0-dev libxcb-shm0-dev libxcb-randr0-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-icccm4-dev libxcb-xfixes0-dev libxcb-sync-dev libxcb-xinerama0-dev libxcb-shape0-dev libxcb-shm0-dev libxcb-randr0-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-icccm4-dev libxcb-xfixes0-dev libxcb-sync-dev libxcb-xinerama0-dev libxcb-shape0-dev libxcb-shm0-dev libxcb-randr0-dev
git clone https://github.com/SFML/SFML.git
cd SFML
git checkout 2.6.x
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

2. Build code
```console
git clone https://github.com/slo248/CS202-Crossy-Road.git
cd CS202-Crossy-Road
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config Release
```

### b. Windows

1. Install SFML
```console
choco install mingw
git clone https://github.com/SFML/SFML.git
cd SFML
git checkout 2.6.x
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G"MinGW Makefiles" ..
cmake --build . --config Release
cmake --install . --config Release
```

2. Build code
```console
git clone https://github.com/slo248/CS202-Crossy-Road.git
cd CS202-Crossy-Road
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -G"MinGW Makefiles" ..
cmake --build . --config Release
```

### c. MacOS

1. Install SFML
```console
brew install sfml
```

2. Build code
```console
git clone https://github.com/slo248/CS202-Crossy-Road.git
cd CS202-Crossy-Road
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
cmake --build . --config Release
```

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

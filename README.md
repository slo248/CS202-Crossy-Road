# CS202-Crossy-Road

[![cmake](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml/badge.svg)](https://github.com/slo248/CS202-Crossy-Road/actions/workflows/build.yaml) ![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0) 

This is a 2D game clone version of <a href="https://www.google.com/search?q=crossy+road">Crossy Road</a>, which is developed as a group project in CS202 - Programming Systems in APCS-HCMUS.

![Game Preview](https://github.com/slo248/CS202-Crossy-Road/assets/116567243/3bb49d17-d257-4f49-b7c4-1f2d50f6d3e6)

## Minimum requirements

| **Operating System** |    **Compiler**   |
|:--------------------:|:-----------------:|
| Linux (Ubuntu)       | GNU 11.4.0        |
| Windows              | Clang 16.0.6      |
| MacOS                | AppleClang 14.0.0 |

- SFML: [v2.6.1](https://github.com/SFML/SFML/releases/tag/2.6.1)

## How to use

All instructions below have the directory in the root folder `CS202-Crossy-Road`.

### Linux (Ubuntu)

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
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build . --config Release
```

3. Run code
```console
./bin/Linux64/Release/CrossyRoad
```

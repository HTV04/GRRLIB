# GRRLIB-mod
## Table of Contents
* [Introduction](#introduction)
  * ...What is it?
* [Developing for the Wii/GameCube](#developing-for-the-wiigamecube)
  * ...How do I even start?
* [Downloading GRRLIB-mod](#downloading-grrlib-mod)
  * ...Where do I get it from?
* [Installing GRRLIB-mod](#installing-grrlib-mod)
  * ...How do I get it to a useable state?
* [Using GRRLIB-mod](#using-grrlib-mod)
  * ...What essentials do I need to know to get going?
* [GRRLIB Credits](#grrlib-credits)
  * ...Who do I thank for creating all this free stuff?
* [License](#license)
  * ...It's the MIT one!

## Introduction
GRRLIB-mod is a C/C++ 2D/3D graphics library based on [GRRLIB](https://github.com/GRRLIB/GRRLIB) for Wii/GameCube application developers. It is essentially a wrapper which presents a friendly interface to the Nintendo GX core.

GRRLIB-mod is supplied as a standard C/C++ library (aka. archive) called "libgrrlib-mod". Because GRRLIB-mod processes JPEG and PNG images, it requires the installation of the 'libjpeg' and 'libpngu' libraries. 'libpngu', in turn, requires 'libpng'. GRRLIB-mod has FileIO functions to allow real-time loading and saving of graphical data, and thus requires 'libfat'. GRRLIB-mod also has the possibility to use TrueType fonts, so 'libfreetype' is also required.

```
libgrrlib-mod      <- 2D/3D graphics library
├── libpngu-mod    <- Wrapper for libpng
│   └── libpng     <- PNG image processor
├── libjpeg        <- JPEG image processor
├── libfreetype    <- TrueType font processor
├── libogc-mod     <- Critical Wii/GameCube modules
└── libfat-mod     <- File I/O
```

## Developing for the Wii/GameCube
Do not progress until you have installed and configured devkitPro. Guides are and assistance are available at <https://devkitpro.org/index.php>

If you have just performed a clean (re)install, you should reboot before you continue.

## Downloading GRRLIB-mod
It is recommended to use the `mod` branch of the GRRLIB-mod repo. Simply clone this repository to your computer and switch to the `mod` branch.

This document will presume that you have clone this repository to a directory called  `C:\grr` for simplicity.

## Installing GRRLIB-mod
### Pacman
The quickest way to install GRRLIB-mod is by adding the `htv-dkp-libs` repository, allowing you to install GRRLIB-mod and its dependencies from pacman. Follow the instructions [here](https://github.com/HTV04/htv-dkp-libs).

After setting up the repository, install the `wii-grrlib-mod` and/or `gamecube-grrlib-mod` package(s) via pacman.

### Manual installation
This guide is for Windows. If you are using macOS, Linux, or another compatible operating system, you will need to convert these instructions.

```text
GRRLIB-mod  is supplied as source code
libpngu-mod is supplied as source code
libpng      is supplied via devkitPro pacman (ppc-libpng)
libjpeg     is supplied via devkitPro pacman (ppc-libjpeg-turbo)
libfreetype is supplied via devkitPro pacman (ppc-freetype)
libogc-mod  is supplied as source code
libfat-mod  is supplied as source code
```

libpngu-mod is available [here](https://github.com/HTV04/libpngu-mod), and should be installed.

libogc-mod is available [here](https://github.com/HTV04/libogc-mod). It is based off of libogc and contains various fixes. However, if you wish to compile GRRLIB-mod against the original libogc, append `GRRLIB_LIBOGC=libogc` to the arguments of `make`.

libfat-mod is available [here](https://github.com/HTV04/libfat-mod), and is required if compiling with libogc-mod. Otherwise, install `libfat-ogc` via devkitPro pacman.

The easy way is to install GRRLIB-mod and all the required libraries in a single command:
```bash
  c:
  cd \grr\src
  pacman -S ppc-libpng ppc-freetype ppc-libjpeg-turbo
  make clean all install
```

This process may take some time depending on the speed of your PC.

If you used the method above the following steps are not required, GRRLIB-mod is installed and you are ready to start developing Wii/GameCube homebrew games.

Each library could also be installed individually:

Install libfat, libpng, libfreetype and libjpeg with their dependencies:
```bash
  pacman -S ppc-libpng ppc-freetype ppc-libjpeg-turbo
```

To install libgrrlib-mod for Wii:
```bash
  c:
  cd \grr\src
  make clean all install
```

To install libgrrlib-mod for GameCube:
```bash
  c:
  cd \grr\src
  make GRRLIB_PLATFORM=cube clean all install
```

## Using GRRLIB-mod
After everything is installed, simply put
```c
#include <grrlib-mod.h>
```
at the top of your .c/.cpp file and use the functions as required

You will need to add:
```make
-lgrrlib-mod -lfreetype -lbz2 -ljpeg -lpngu-mod -lpng -lz
```
to the libs line in your Makefile.

Remember the order of the libraries is critical. You may (need to) insert other libraries in the middle of the list, you may need to add others to the start, or even the end, but do *not* change the order of the libraries shown here.

Also add `$(PORTLIBS)` to the `LIBDIRS` line in your makefile

You do NOT need to place anything in your application directory.

If you would like to see a working example of this, you can look at the example found in: C:\grr\examples\template\source

## GRRLIB Credits
### Project Leader
* NoNameNo

### Documentation
* Crayon
* BlueChip

### Lead Coder
* NoNameNo

### Support Coders
* Crayon
* Xane
* DragonMinded
* BlueChip
* elisherer

### Advisors
* RedShade
* Jespa

## License
GRRLIB-mod is released under the [MIT License](LICENSE).

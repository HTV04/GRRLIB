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

GRRLIB-mod is supplied as a standard C/C++ library (aka. archive) called "libgrrlib-mod". Because GRRLIB processes JPEG and PNG images, it requires the installation of the 'libjpeg' and 'libpngu' libraries. 'libpngu', in turn, requires 'libpng'. GRRLIB has FileIO functions to allow real-time loading and saving of graphical data, and thus requires 'libfat'. GRRLIB also has the possibility to use TrueType fonts, so 'libfreetype' is also required.

```
libgrrlib-mod      <- 2D/3D graphics library
├── libfat         <- File I/O
├── libjpeg        <- JPEG image processor
├── libpngu        <- Wii wrapper for libpng
│   └── libpng     <- PNG image processor
└── libfreetype    <- TrueType font processor
```

## Developing for the Wii/GameCube
Do not progress until you have installed and configured devkitPro. Guides are and assistance are available at <https://devkitpro.org/index.php>

If you have just performed a clean (re)install, you should reboot before you continue.

## Downloading GRRLIB-mod
It is recommended to use the `mod` branch of the GRRLIB-mod repo. Simply clone this repository to your computer and switch to the `mod` branch.

This document will presume that you have clone this repository to a directory called  `C:\grr` for simplicity.

## Installing GRRLIB-mod
This guide is for Windows. If you are using macOS, Linux, or another compatible operating system, you will need to convert these instructions.

```text
GRRLIB      is supplied as source code
libpngu     is available from the original GRRLIB repo
libpng      is supplied via devkitPro pacman (ppc-libpng)
libfreetype is supplied via devkitPro pacman (ppc-freetype)
libjpeg     is supplied via devkitPro pacman (ppc-libjpeg-turbo)
libfat      is supplied via devkitPro pacman (libfat-ogc)
```

libpngu can be compiled and installed using the [instructions from the original GRRLIB repo](https://github.com/GRRLIB/GRRLIB#installing-grrlib).

The easy way is to install GRRLIB and all the required libraries in a single command:
```bash
  c:
  cd \grr\src
  pacman -S libfat-ogc ppc-libpng ppc-freetype ppc-libjpeg-turbo
  make clean all install
```

This process may take some time depending on the speed of your PC.

If you used the method above the following steps are not required, GRRLIB-mod is installed and you are ready to start developing Wii/GameCube homebrew games.

Each library could also be installed individually:

Install libfat, libpng, libfreetype and libjpeg with their dependencies:
```bash
  pacman -S libfat-ogc ppc-libpng ppc-freetype ppc-libjpeg-turbo
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
  make PLATFORM=cube clean all install
```

## Using GRRLIB-mod
After everything is installed, simply put
```c
#include <grrlib-mod.h>
```
at the top of your .c/.cpp file and use the functions as required

You will need to add:
```make
-lgrrlib-mod -lfreetype -lbz2 -lfat -ljpeg -lpngu -lpng -lz
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

# img2hack [![Build Status](https://travis-ci.org/benvenutti/img2hack.svg?branch=master)](https://travis-ci.org/benvenutti/img2hack) [![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) [![Github Issues](https://img.shields.io/github/issues/benvenutti/img2hack.svg)](http://github.com/benvenutti/img2hack/issues) [![Github Releases](https://img.shields.io/github/release/benvenutti/img2hack.svg)](https://github.com/benvenutti/img2hack/releases)

*Convert images into HACK assembly code*

This project is a small desktop program that converts image files to HACK assembly files. The assembly file is to be run on a HACK simulator/computer, where the code will output the original image to its screen.

Since the HACK screen has only two possible values for each pixel, it can basically output binary images to it. So once you load an image to *img2hack*, the program will give you the possibility to fine-tune the conversion from non-binary to binary image over a graphical user interface (GUI).

Watch img2hack in action at [https://www.youtube.com/watch?v=i8HHfCDsWSE](https://www.youtube.com/watch?v=i8HHfCDsWSE).

If you don't know what HACK is, check it over [here](http://www.nand2tetris.org).

## Motivation

Well, that HACK screen was begging for it!

## Project setup

To build img2hack, you will need:

1. QtCreator 5.2 (or higher)
2. libmagick++5

Once you have this two dependencies installed, you will probably need to edit `img2hack.pro` so QtCreator can find the Magick++ lib in your system. These are the two lines that you must update:

```
INCLUDEPATH += . /usr/include/ImageMagick
LIBS += -L/usr/lib -lMagick++
```

## License

GPL v2 license (please see the file called LICENSE.md).

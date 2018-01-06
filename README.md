# img2hack [![Build Status](https://travis-ci.org/benvenutti/img2hack.svg?branch=master)](https://travis-ci.org/benvenutti/img2hack) [![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) [![Github Issues](https://img.shields.io/github/issues/benvenutti/img2hack.svg)](http://github.com/benvenutti/img2hack/issues) [![Github Releases](https://img.shields.io/github/release/benvenutti/img2hack.svg)](https://github.com/benvenutti/img2hack/releases)

This project is a small desktop program that converts image files to Hack assembly files. The assembly file is to be run on a Hack simulator/computer, where the code will output the original image to its screen. For more information on the Hack computer, take a look at [nand2tetris](http://nand2tetris.org/).

Since the Hack screen has only two possible values for each pixel, it can basically output binary images to it. So once you load an image to **img2hack**, the program will give you the possibility to fine-tune the conversion from non-binary to binary image over a graphical user interface.

Watch this [video](https://www.youtube.com/watch?v=i8HHfCDsWSE) to see **img2hack** in action! :tv:

...and if you want to assemble the generated code into a Hack binary you can also use my [assembler](https://github.com/benvenutti/hasm).

### Building **img2hack** from source

The following list enumerates the tools and dependencies' minimum requirements:

* C++11 compiler
* CMake 3.2
* Magick++ 7.0
* Qt5 Widgets

#### Configuring and Compiling

Run **cmake** to configure the native tools (preferably an *out of source* configuration) and then run the build. Here is an example in Linux:

```shh
img2hack$ mkdir build
img2hack$ cd build
img2hack/build$ cmake ..
img2hack/build$ cmake --build .
```

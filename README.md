# img2hack ![example workflow](https://github.com/benvenutti/img2hack/actions/workflows/ci.yaml/badge.svg)

This project is a small desktop program that converts image files to Hack assembly files. The assembly file is to be run on a Hack simulator/computer, where the code will output the original image to its screen. For more information on the Hack computer, take a look at [nand2tetris](http://nand2tetris.org/).

Since the Hack screen has only two possible values for each pixel, it can basically output binary images to it. So once you load an image to **img2hack**, the program will give you the possibility to fine-tune the conversion from non-binary to binary image over a graphical user interface.

Watch this [video](https://www.youtube.com/watch?v=i8HHfCDsWSE) to see **img2hack** in action! :tv:

...and if you want to assemble the generated code into a Hack binary you can also use my [assembler](https://github.com/benvenutti/hasm).

### Building **img2hack** from source

The following list enumerates the tools and dependencies' minimum requirements:

* C++17 compiler
* CMake 3.25 or higher
* Qt 6.5
* Catch 2 (this dependency is managed by the main CMake script)

#### Configuring and Compiling

Run **cmake** to configure the native tools (preferably an *out of source* configuration) and then run the build. Here is an example in Linux:

```shh
img2hack$ mkdir build
img2hack$ cd build
img2hack/build$ cmake ..
img2hack/build$ cmake --build .
```

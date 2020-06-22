# OpenGL
OpenGL exercises for practice, implementing examples and exercises from [LearnOpenGL](https://learnopengl.com) using **C++17** and trying to create clean and reusable code.

### Structure
The examples are divided in blocks according to my own criteria, each covering a different number of [LearnOpenGL](https://learnopengl.com) chapters. A brief description of the theory behind each block and the examples covered are included in the README files on each block. 

The blocks and a brief description of each of them are:
  1. [The Basics](01-basics) - shaders, buffers and basic elements of OpenGL
  2. [Textures](02-textures) - textures applied on objects
  3. [Space](03-space) - space transformations of OpenGL objects
  4. [Lighting](04-lighting) - different lights over OpenGL objects
  5. [Model Loading](05-models) - importing external models in OpenGL

For each block, an **_Utils_** library with my own implentation of helper classes and functions is used. The **_Utils_** library is incrementally extended and modified for each block, but the old versions remain on their blocks for documenting purposes and to allow me to make breaking changes without much hassle. Taking this into account, the **_Utils_** library of the last block is the most **complete and up-to-date** and includes every functionality of older versions.

### Compatibility
These examples can be built on different platforms as long as they support **C++17** and **OpenGL 4.10** and they have been tested on:
- Windows 10 - **_[TO BE COMPLETED]_**
- MacOS 10.15 (Catalina) - with Clang 11.0.3 
- _Ubuntu (pending)_

### How to build
It can be built with the help of **CMake**:
```
mkdir build
cd build
cmake ..
[compile the project as per your platform]
```

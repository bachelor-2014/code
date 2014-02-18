#Node module POC
This small POC is about testing the possibility of calling C++ functions from
NodeJS.

The code shows that it is possible to:

- Invoke C++ functions from Node with arguments and a return value
- Invoke JS callback functions in C++ given as arguments
- Wrap C++ classes in JS classes, hiding the implementation details of the C++
  classes
- Build and run the C++ Node modules with OpenCV (the code opens and displays
  and image)

For building the modules, node-gyp is used. The modules / build targets are
defined in the bindings.gyp file.

#How to build and run

- make
- node hello.js

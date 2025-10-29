# webviewtest

Template for a game using C, [webview](https://github.com/webview/webview/) and [PixiJS](https://pixijs.com/).

HTML, JS and CSS are embedded into the executable, while other resources are loaded using a function in C from binary files.

## Prerequisites

To build this, you need CMake, npm and node.js installed. You also need all the prerequisites for [webview](https://github.com/webview/webview/) installed on your system.

## Building

To have developer tools available inside of the webview, configure the CMake project with `CMAKE_BUILD_TYPE=Debug`.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild
```

To build resources, you can utilize the `resources` target:
```bash
cmake --build build -t resources
```

To build HTML, JS and CSS, you can utilize the `html` target:
```bash
cmake --build build -t html
```

Or to build everything:
```bash
cmake --build build
```

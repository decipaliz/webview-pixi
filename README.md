# webview + PixiJS

Proof of concept game using C, [webview](https://github.com/webview/webview/) and [PixiJS](https://pixijs.com/).

HTML, JS and CSS are embedded into the executable, while other resources are loaded using a function in C from binary files.

## Prerequisites

To build this, you need CMake, npm and node.js installed. You also need all the prerequisites for [webview](https://github.com/webview/webview/) installed on your system.

## Building

To have developer tools available inside of the webview, configure the CMake project with `CMAKE_BUILD_TYPE=Debug`.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild
```

Similarly, to build with optimizations, configure it with `CMAKE_BUILD_TYPE=Release`.

```bash
cmake -DCMAKE_BUILD_TYPE=Release -Bbuild
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

## Comment

This is a proof of concept to demonstrate that native webapps truly don't need Electron. Calling the OS's browser (or webkit in Linux's case) is way simpler and creates less space.

For example, my GNU/Linux build of this app only takes around ~670K. Compare that with 300M+ builds of electron apps and the difference is insane.

Webview has a bunch of [bindings](https://github.com/webview/webview?tab=readme-ov-file#bindings), so you can also use your favorite programming language instead of C and achieve pretty similar results.

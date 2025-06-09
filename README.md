# README.md

# Qt WASM Demo

This project is a Qt application that demonstrates building a C++ Qt application for WebAssembly with a dark theme interface.

## Project Structure

```
poc-c++-wasm/
├── src/
│   ├── main.cpp        # Application entry point
│   ├── mainwindow.cpp  # Main window implementation
│   └── mainwindow.h    # Main window header
├── CMakeLists.txt      # CMake configuration
└── README.md          # Project documentation
```

## Prerequisites

- Qt 6.x
- CMake 3.16 or higher
- Emscripten SDK (for WebAssembly build)

## Building the Project

### Native Build

1. Create a build directory:
```bash
mkdir build && cd build
```

2. Configure with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

### WebAssembly Build

1. First, activate Emscripten environment:
```bash
source /path/to/emsdk/emsdk_env.sh
```

2. Create a WASM build directory:
```bash
mkdir build-wasm && cd build-wasm
```

3. Configure with CMake for WASM:
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
```

4. Build the WASM target:
```bash
make
```

## Running the Application

### Native Build
```bash
./qtapp
```

### WebAssembly Build
The WASM build will generate HTML and JS files. You can serve them using any web server:
```bash
python3 -m http.server 8000
```

Then open your browser and navigate to `http://localhost:8000`

## Features

- Dark mode interface
- Responsive layout
- Click counter demonstration
- WebAssembly compatibility

## License

This project is open source and available under the MIT License.
# Makefile for building desktop and WASM versions
# Commands
CMAKE := /usr/local/bin/cmake
EMCMAKE := $(shell which emcmake)
QT_CMAKE_DESK := /opt/qt/6.6.3/gcc_64/bin/qt-cmake
QT_CMAKE_WASM := /opt/qt/6.6.3/wasm_singlethread/bin/qt-cmake
PYTHON3 := $(shell which python3)

# Check required commands
ifeq ($(CMAKE),)
$(error cmake not found. Please install cmake)
endif

ifeq ($(EMCMAKE),)
$(error emcmake not found. Please install emscripten)
endif

# Directories
BUILD_DESKTOP = build-desktop
BUILD_WASM = build-wasm

# Default target
all: desktop wasm

# Desktop build
.PHONY: desktop
desktop:
	@echo "Building desktop version..."
	$(QT_CMAKE_DESK) --preset desktop -B $(BUILD_DESKTOP)
	$(CMAKE) --build $(BUILD_DESKTOP)

# WASM build
# emcmake $(CMAKE) --preset wasm -B $(BUILD_WASM) --debug-find-pkg=Qt6Core
.PHONY: wasm
wasm:
	@echo "Building WASM version..."
	$(QT_CMAKE_WASM) --preset=wasm -B $(BUILD_WASM)
	$(CMAKE) --build $(BUILD_WASM)

# Clean builds
.PHONY: clean
clean:
	@echo "Cleaning build directories..."
	rm -rf $(BUILD_DESKTOP)
	rm -rf $(BUILD_WASM)

# Run desktop version
.PHONY: run-desktop
run-desktop: desktop
	@echo "Running desktop version..."
	./$(BUILD_DESKTOP)/helloworld

# Serve WASM version
.PHONY: serve-wasm
serve-wasm: wasm
	@echo "Serving WASM version on http://localhost:8123"
	python3 -m http.server 8123 --directory $(BUILD_WASM)
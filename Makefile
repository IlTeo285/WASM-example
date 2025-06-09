# Makefile for building desktop and WASM versions
# Commands
CMAKE := /usr/local/bin/cmake
EMCMAKE := $(shell which emcmake)
QT_CMAKE := $(shell which qt-cmake)
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
	$(CMAKE) --preset desktop -B $(BUILD_DESKTOP)
	$(CMAKE) --build $(BUILD_DESKTOP)

# WASM build
.PHONY: wasm
wasm:
	@echo "Building WASM version..."
	emcmake $(CMAKE) --preset wasm -B $(BUILD_WASM) --debug-find-pkg=Qt6Core
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
	@echo "Serving WASM version on http://localhost:8080"
	python3 -m http.server 8080 --directory $(BUILD_WASM)
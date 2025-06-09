cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cpp-project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable Qt debug output
#set(QT_DEBUG_FIND_PACKAGE ON)
#set(CMAKE_FIND_DEBUG_MODE ON)

# Check if we're building for WASM
if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
endif()

message(STATUS "Qt Path: ${QT_PATH}")
message(STATUS "Qt6_DIR: ${Qt6_DIR}")
message(STATUS "CMake Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")

# Configure Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(helloworld
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

target_link_libraries(helloworld PRIVATE Qt6::Widgets)

if(EMSCRIPTEN)
    # WASM specific flags
    set_target_properties(helloworld PROPERTIES
        LINK_FLAGS "-s WASM=1 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM_BIGINT=1 -s NO_EXIT_RUNTIME=0 -s \"EXPORTED_RUNTIME_METHODS=['ccall','cwrap']\" --bind"
    )

    # First try to locate wasm_shell.html
    find_file(WASM_SHELL
        NAMES wasm_shell.html
        PATHS 
            "${Qt6_DIR}/../../../plugins/platforms"
            "/opt/qt/6.6.3/wasm_singlethread/plugins/platforms"
            "${QT_PATH}/plugins/platforms"
        DOC "Path to Qt WASM shell template"
        NO_DEFAULT_PATH
    )

    if(NOT WASM_SHELL)
        message(FATAL_ERROR "Could not find wasm_shell.html. Please check your Qt WASM installation.")
    else()
        message(STATUS "Found WASM shell template at: ${WASM_SHELL}")
        configure_file(${WASM_SHELL} ${CMAKE_BINARY_DIR}/helloworld.html COPYONLY)
        
        # Rename to index.html after build
        add_custom_command(
            TARGET helloworld POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E rename 
                ${CMAKE_BINARY_DIR}/helloworld.html 
                ${CMAKE_BINARY_DIR}/index.html
            COMMENT "Renaming helloworld.html to index.html"
        )
    endif()
endif()

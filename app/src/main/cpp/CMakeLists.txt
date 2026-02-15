cmake_minimum_required(VERSION 3.22.1)

project("sdlc")

# Disable PkgConfig search on Android to avoid the "Could NOT find PkgConfig" error/warning
set(CMAKE_DISABLE_FIND_PACKAGE_PkgConfig ON)

# Set SDL options
set(SDL_SHARED ON CACHE BOOL "Build shared SDL library")
set(SDL_STATIC OFF CACHE BOOL "Build static SDL library")

# Ensure SDL2_image and SDL2_ttf use vendored dependencies for Android
set(SDL2IMAGE_VENDORED ON CACHE BOOL "Use vendored dependencies for SDL2_image")
set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored dependencies for SDL2_ttf")

# Disable SDL2_image formats that require missing external dependencies
set(SDL2IMAGE_AVIF OFF CACHE BOOL "Disable AVIF support")
set(SDL2IMAGE_WEBP OFF CACHE BOOL "Disable WEBP support")
set(SDL2IMAGE_TIF OFF CACHE BOOL "Disable TIFF support")
set(SDL2IMAGE_JXL OFF CACHE BOOL "Disable JXL support")

add_library(
        native-lib
        SHARED
        native-lib.cpp
        Sprite.cpp
)

# Find log library for Android
find_library(log-lib log)

# Add SDL
add_subdirectory(SDL)
add_subdirectory(SDL2_image)
add_subdirectory(SDL2_ttf)


# Include SDL headers
target_include_directories(native-lib PRIVATE SDL/include)

# Link libraries
target_link_libraries(
        native-lib
        SDL2
        SDL2_image
        SDL2_ttf
        android
        GLESv3
        log
)
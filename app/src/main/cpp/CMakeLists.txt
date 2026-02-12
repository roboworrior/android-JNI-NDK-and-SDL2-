cmake_minimum_required(VERSION 3.22.1)

project("sdlc")

# Set SDL options
set(SDL_SHARED ON CACHE BOOL "Build shared SDL library")
set(SDL_STATIC OFF CACHE BOOL "Build static SDL library")

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
# add_subdirectory(SDL2_image) # Commented out if it lacks CMakeLists.txt or fixed if name was wrong

# Include SDL headers
target_include_directories(native-lib PRIVATE SDL/include)

# Link libraries
target_link_libraries(
        native-lib
        SDL2
        SDL2_image
        android
        GLESv3
        log
)
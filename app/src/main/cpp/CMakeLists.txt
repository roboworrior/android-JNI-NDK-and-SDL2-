cmake_minimum_required(VERSION 3.22.1)

project("sdlc")

add_library(
        native-lib
        SHARED
        native-lib.cpp
)

# Find log library for Android
find_library(log-lib log)

# Add SDL
add_subdirectory(SDL)

# Include SDL headers
target_include_directories(native-lib PRIVATE SDL/include)

# Link libraries
target_link_libraries(
        native-lib
        SDL2
        android
        GLESv3
        log
)
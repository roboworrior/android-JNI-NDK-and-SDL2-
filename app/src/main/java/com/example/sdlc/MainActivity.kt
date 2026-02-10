package com.example.sdlc

import org.libsdl.app.SDLActivity

class MainActivity : SDLActivity() {

    override fun getLibraries(): Array<String> {
        return arrayOf(
            "SDL2",
            "native-lib"
        )
    }
}
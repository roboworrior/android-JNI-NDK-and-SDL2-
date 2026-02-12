#pragma once
#include <SDL.h>
#include <map>
#include <string>

// Structure to hold animation data
struct Animation {
    int row;        // Which row in sprite sheet
    int frames;     // Total frames in that row
    float speed;    // Time per frame (seconds)
};

class Sprite {
private:
    SDL_Texture* texture;     // Sprite sheet texture

    SDL_Rect srcRect;         // Portion of sprite sheet to render
    SDL_Rect destRect;        // Position & size on screen

    int frameWidth;           // Width of single frame
    int frameHeight;          // Height of single frame

    std::map<std::string, Animation> animations; // All animations
    std::string currentAnimation;                // Currently playing animation

    int currentFrame;         // Current frame index
    float frameTimer;         // Timer to switch frames

    SDL_RendererFlip flip;    // For left/right flipping

public:
    // Constructor
    Sprite(SDL_Texture* tex, int x, int y, int w, int h);

    // Add animation (name, row, frame count, speed)
    void addAnimation(std::string name, int row, int frames, float speed);

    // Switch animation
    void play(std::string name);

    // Update animation using delta time
    void update(float deltaTime);

    // Render sprite
    void render(SDL_Renderer* renderer);

    // Flip sprite (left/right)
    void setFlip(SDL_RendererFlip f);
};

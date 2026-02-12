#include "Sprite.h"

// Constructor
Sprite::Sprite(SDL_Texture* tex, int x, int y, int w, int h)
{
    texture = tex;

    frameWidth = w;
    frameHeight = h;

    // Initial source rectangle (first frame)
    srcRect = {0, 0, w, h};

    // Position on screen
    destRect = {x, y, w, h};

    currentFrame = 0;
    frameTimer = 0.0f;

    flip = SDL_FLIP_NONE; // Default no flip
}

// Add animation to map
void Sprite::addAnimation(std::string name, int row, int frames, float speed)
{
    animations[name] = {row, frames, speed};
}

// Play a specific animation
void Sprite::play(std::string name)
{
    // If animation already playing, don't reset
    if (currentAnimation != name)
    {
        currentAnimation = name;
        currentFrame = 0;     // Start from first frame
        frameTimer = 0.0f;    // Reset timer
    }
}

// Update animation frames
void Sprite::update(float deltaTime)
{
    if (currentAnimation.empty()) return;

    // Get current animation data
    Animation& anim = animations[currentAnimation];

    // Increase timer by delta time
    frameTimer += deltaTime;

    // If enough time passed, go to next frame
    if (frameTimer >= anim.speed)
    {
        frameTimer = 0.0f;
        currentFrame++;

        // Loop back if animation finished
        if (currentFrame >= anim.frames)
            currentFrame = 0;
    }

    // Update source rectangle position
    srcRect.x = currentFrame * frameWidth;
    srcRect.y = anim.row * frameHeight;
}

// Render sprite on screen
void Sprite::render(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect,
                     0, NULL, flip);
}

// Set sprite flip (left/right)
void Sprite::setFlip(SDL_RendererFlip f)
{
    flip = f;
}

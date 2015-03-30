#include "particle.h"

Particle::Particle(SDL_Texture* t, SDL_Rect* uv, SDL_Rect* b, int xVelocity, int yVelocity, int f, bool shouldFade) {
    texture = t;
    uvCoords = uv;
    bounds = b;
    xVel = xVelocity;
    yVel = yVelocity;
    maxFrames = f;
    fade = shouldFade;
    frames = 0;
}

Particle::~Particle() {
    delete texture;
}

void Particle::render(SDL_Renderer* renderer) {
    xPos += xVel;
    yPos += yVel;

    if(fade) {
        SDL_SetTextureAlphaMod(texture, 255 - 255 / (maxFrames - frames));
    }
    SDL_RenderCopy(renderer, texture, uvCoords, bounds);
    frame++;
}

bool Particle::doneAnimating() {
    return frame >= maxFrames;
}
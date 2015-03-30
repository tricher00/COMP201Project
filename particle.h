#ifndef _PARTICLE_H
#define _PARTICLE_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Particle {
public:
    Particle(SDL_Texture* t, int xpos, int ypos, int xVelocity, int yVelocity);
    ~Particle();
    void render(SDL_Renderer* renderer);
private:
    int xVel, yVel;
    int frame;
    int maxFrames;
    SDL_Texture* texture;
    SDL_Rect* uvCoords;
    SDL_Rect* bounds;
    bool fade;
};

#endif
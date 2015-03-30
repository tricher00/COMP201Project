#ifndef _BALL_H
#define _BALL_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>
#include "particle.h"

class Ball {
public:
    Ball(int x, int y, int w, int h);
    void step();
    void reverseY();
    void reverseX();
    void setPosition(int x, int y);
    void setStuck(bool s);
    int getYVel();
    int getXVel();
    bool shouldStick();
    bool isStuck();
    SDL_Rect getBounds();
    std::vector<Particle*> getParticles();
private:
    SDL_Rect bounds;
    int speed = 5;
    int xVel = 0;
    int yVel = 0;
    bool sticky = false;
    bool stuck = true;

    static const int MAX_PARTICLE = 30;
    std::vector<Particle*> particles;
};

#endif
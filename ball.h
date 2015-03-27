#ifndef _BALL_H
#define _BALL_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

class Ball {
public:
    Ball(int x, int y, int w, int h);
    void step();
    void reverseY();
    void reverseX();
    void setPosition(int x, int y);
    void setStuck(bool s);
    bool isStuck();
    SDL_Rect getBounds();
private:
    SDL_Rect bounds;
    int speed = 5;
    int xVel = 0;
    int yVel = 0;
    bool shouldStick = false;
    bool stuck = true;
};

#endif
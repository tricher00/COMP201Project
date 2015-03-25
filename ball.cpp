#include "ball.h"
#include <ctime>

Ball::Ball(int x, int y, int w, int h) {
    bounds.x = x;
    bounds.y = y;
    bounds.w = w;
    bounds.h = h;
    srand(time(0));
    yVel = rand() % 10;
    xVel = rand() % 10;
}

void Ball::step() {
    if(!stuck) {
        bounds.x += xVel;
        bounds.y += yVel;
    }
}

void Ball::reverseY() {
    yVel = -yVel;
}

void Ball::reverseX() {
    xVel = -xVel;
}

void Ball::setPosition(int x, int y) {
    bounds.x = x;
    bounds.y = y;
}

bool Ball::isStuck() {
    return stuck;
}

SDL_Rect Ball::getBounds() {
    return bounds;
}
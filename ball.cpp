#include "ball.h"
#include <ctime>
#include <iostream>

Ball::Ball(int x, int y, int w, int h) {
    bounds.x = x;
    bounds.y = y;
    bounds.w = w;
    bounds.h = h;
    srand(time(0));
    int posNeg[] = { -1, 1 };
    yVel = (4 + (rand() % 7)) * (-1);
    xVel = (2 + (rand() % 3)) * (posNeg[rand() % 2]);
    std::cout << "xVel: " << xVel << " yVel: " << yVel << std::endl;
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

int Ball::getYVel() {
    return yVel;
}

int Ball::getXVel() {
    return xVel;
}

void Ball::setPosition(int x, int y) {
    bounds.x = x;
    bounds.y = y;
}

bool Ball::shouldStick() {
    return sticky;
}

void Ball::setStuck(bool s) {
    stuck = s;
}

bool Ball::isStuck() {
    return stuck;
}

SDL_Rect Ball::getBounds() {
    return bounds;
}

std::vector<Particle*> Ball::getParticles() {
    return particles;
}
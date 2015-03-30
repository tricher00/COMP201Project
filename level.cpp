#include "level.h"
#include <iostream>

Level::Level(std::string path, int screenWidth, int screenHeight) {
    load(path, screenWidth, screenHeight);
    paddleBounds.w = screenWidth / 12;
    paddleBounds.h = screenHeight / 16;
    paddleBounds.x = screenWidth / 2 - paddleBounds.w / 2;
    paddleBounds.y = screenHeight - 10;
    screenBounds.x = 0;
    screenBounds.y = 0;
    screenBounds.w = screenWidth;
    screenBounds.h = screenHeight;
    balls.push_back(new Ball(paddleBounds.x + (paddleBounds.w / 2), paddleBounds.y - 16, 16, 16));
}

Level::~Level() {
    for(int i = 0; i < balls.size(); i++) {
        delete balls[i];
    }
}

void Level::update() {
    for(int i = 0; i < balls.size(); i++) {
        if(balls[i]->isStuck()) {
            balls[i]->setPosition(paddleBounds.x + (paddleBounds.w / 2) - (balls[i]->getBounds().w / 2), balls[i]->getBounds().y);
        } else {
            balls[i]->step();
            checkCollisions();
        }
    }

    if(moveLeft) {
        if(paddleBounds.x - BASE_PADDLE_SPEED >= 0) {
            paddleBounds.x -= BASE_PADDLE_SPEED;
        } else {
            paddleBounds.x = 0;
        }
    }

    if(moveRight) {
        if(paddleBounds.x + paddleBounds.w + BASE_PADDLE_SPEED <= screenBounds.w) {
            paddleBounds.x += BASE_PADDLE_SPEED;
        } else {
            paddleBounds.x = screenBounds.w - paddleBounds.w;
        }
    }
}

void Level::checkCollisions() {
    bool collided = false;
    SDL_Rect* intersect = new SDL_Rect();
    for(int i = 0; i < balls.size(); i++) {
        Ball* ball = balls[i];
        SDL_Rect ballBounds = ball->getBounds();
        for(int i = 0; i < bricks.size(); i++) {
            if(!bricks[i].broken && SDL_IntersectRect(&ballBounds, &bricks[i].bounds, intersect)) {
                if(intersect->w > intersect->h) {
                    // If its coming from below
                    if(ballBounds.y - ball->getYVel() > bricks[i].bounds.y + bricks[i].bounds.h) {
                        ballBounds.y = bricks[i].bounds.y + bricks[i].bounds.h;
                    } else {
                        ballBounds.y = bricks[i].bounds.y - ballBounds.h;
                    }
                    ball->reverseY();
                } else if(intersect->w < intersect->h) {
                    // If its coming from the left
                    if(ballBounds.x - ball->getXVel() > bricks[i].bounds.x + bricks[i].bounds.w) {
                        ballBounds.x = bricks[i].bounds.x + bricks[i].bounds.w;
                    } else {
                        ballBounds.x = bricks[i].bounds.x - ballBounds.w;
                    }
                    ball->reverseX();
                } else {
                    ball->reverseY();
                    ball->reverseX();
                }
                bricks[i].broken = true;
                collided = true;
                break;
            }
        }

        if(!collided && SDL_IntersectRect(&ballBounds, &paddleBounds, intersect)) {
            collided = true;
            if(ball->shouldStick()) {
                ball->setStuck(true);
            }
            if(intersect->w > intersect->h) {
                ball->reverseY();
            } else if(intersect->w < intersect->h) {
                ball->reverseX();
            } else {
                ball->reverseY();
                ball->reverseX();
            }
        }

        if(ballBounds.x <= 0 || ballBounds.x + ballBounds.w >= screenBounds.w) {
            ball->reverseX();
        } else if(ballBounds.y <= 0) {
            ball->reverseY();
        } else if(ballBounds.y >= screenBounds.h) {
            delete ball;
            ball = new Ball(paddleBounds.x + (paddleBounds.w / 2), paddleBounds.y - 16, 16, 16);
        
        }
    }
}

void Level::load(std::string path, int screenWidth, int screenHeight) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        return;
    }

    uint8_t r, g, b, a;
    for(int y = 0; y < loadedSurface->h; y++) {
        for(int x = 0; x < loadedSurface->w; x++) {
            uint32_t pixel = *((uint32_t*) loadedSurface->pixels + y * loadedSurface->w + x);
            SDL_GetRGBA(pixel, loadedSurface->format, &r, &g, &b, &a);
            if(a > 0) {
                Brick brick;
                SDL_Rect bounds;
                bounds.x = x * (screenWidth / loadedSurface->w);
                bounds.y = y * ((screenHeight - screenHeight / 4) / loadedSurface->h);
                bounds.w = screenWidth / loadedSurface->w;
                bounds.h = (screenHeight - screenHeight / 4) / loadedSurface->h;
                brick.bounds = bounds;
                SDL_Color color;
                color.r = r;
                color.g = g;
                color.b = b;
                color.a = a;
                brick.color = color;
                bricks.push_back(brick);
            }
        }
    }
    SDL_FreeSurface(loadedSurface);
}

void Level::movePaddle(Direction dir, bool down) {
    if(dir == LEFT) {
        moveLeft = down;
    } else {
        moveRight = down;
    }
}

void Level::releaseBall() {
    for(int i = 0; i < balls.size(); i++) {
        balls[i]->setStuck(false);
    }
}

bool Level::isOver() {
    for(int i = 0; i < bricks.size(); i++) {
        if(!bricks[i].broken) {
            return false;
        }
    }
    return true;
}

std::vector<Ball*> Level::getBalls() {
    return balls;
}

SDL_Rect Level::getPaddleBounds() {
    return paddleBounds;
}

std::vector<Brick> Level::getBricks() {
    return bricks;
}

std::vector<Particle*> Level::getParticles() {
    return particles;
}
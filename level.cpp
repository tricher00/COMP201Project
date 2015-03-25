#include "level.h"
#include "ball.h"
#include <iostream>

Level::Level(std::string path, int screenWidth, int screenHeight) {
    load(path, screenWidth, screenHeight);
    paddleBounds.x = screenWidth / 2;
    paddleBounds.y = screenHeight - 10;
    paddleBounds.w = screenWidth / 12;
    paddleBounds.h = screenHeight / 16;
    ball = new Ball(paddleBounds.x + (paddleBounds.w / 2), paddleBounds.y + 5, 5, 5);
}

Level::~Level() {
    delete ball;
}

void Level::update() {
    if(!ball->isStuck()) {
        ball->step();
    } else {
        ball->setPosition(paddleBounds.x + (paddleBounds.w / 2) - (ball->getBounds().w / 2), paddleBounds.y + ball->getBounds().h);
    }
}

void Level::checkCollisions() {
    bool collided = false;
    SDL_Rect *intersect;
    SDL_Rect ballBounds = ball->getBounds();
    for(int i = 0; i < bricks.size(); i++) {
        if(SDL_IntersectRect(&ballBounds, &bricks[i].bounds, intersect)) {
            collided = true;
            break;
        }
    }

    if(!collided && SDL_IntersectRect(&ballBounds, &paddleBounds, intersect)) {
        collided = true;
    }

    if(collided) {
        if(intersect->w > intersect->h) {
            ball->reverseY();
        } else if(intersect->w < intersect->h) {
            ball->reverseX();
        } else {
            ball->reverseY();
            ball->reverseX();
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
                bounds.y = y * (screenWidth / 24);
                bounds.w = screenWidth / loadedSurface->w;
                bounds.h = screenHeight / 24;
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

void Level::movePaddle(Direction dir) {
    dir == LEFT ? paddleBounds.x -= BASE_PADDLE_SPEED : paddleBounds.x += BASE_PADDLE_SPEED;
}

bool Level::isOver() {
    for(int i = 0; i < bricks.size(); i++) {
        if(!bricks[i].broken) {
            return false;
        }
    }
    return true;
}

SDL_Rect Level::getPaddleBounds() {
    return paddleBounds;
}

std::vector<Brick> Level::getBricks() {
    return bricks;
}
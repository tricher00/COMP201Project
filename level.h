#ifndef _LEVEL_H
#define _LEVEL_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Ball;

enum Direction { LEFT, RIGHT };

typedef struct {
    SDL_Rect bounds;
    SDL_Color color;
    bool broken = false;
} Brick;

class Level {
public:
    Level(std::string path, int screenWidth, int screenHeight);
    ~Level();
    void update();
    void checkCollisions();
    void load(std::string path, int screenWidth, int screenHeight);
    void movePaddle(Direction dir, bool down);
    bool isOver();
    SDL_Rect getPaddleBounds();
    SDL_Rect getBallBounds();
    std::vector<Brick> getBricks();
private:
    static const int BASE_PADDLE_SPEED = 10;
    Ball *ball;
    SDL_Rect paddleBounds;
    SDL_Rect screenBounds;
    std::vector<Brick> bricks;
    bool moveLeft = false, moveRight = false;
};

#endif
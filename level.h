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
    void movePaddle(Direction dir);
    bool isOver();
    SDL_Rect getPaddleBounds();
    std::vector<Brick> getBricks();
private:
    static const int BASE_PADDLE_SPEED = 7;
    Ball *ball;
    SDL_Rect paddleBounds;
    std::vector<Brick> bricks;
};

#endif
#ifndef _LEVEL_H
#define _LEVEL_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "particle.h"
#include "ball.h"

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
    void releaseBall();
    bool isOver();
    SDL_Rect getPaddleBounds();
    std::vector<Ball*> getBalls();
    std::vector<Brick> getBricks();
    std::vector<Particle*> getParticles();
private:
    static const int BASE_PADDLE_SPEED = 10;
    std::vector<Ball*> balls;
    SDL_Rect paddleBounds;
    SDL_Rect screenBounds;
    std::vector<Brick> bricks;
    bool moveLeft = false, moveRight = false;
    static const int MAX_PARTICLES = 20;
    std::vector<Particle*> particles;
};

#endif
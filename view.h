#ifndef _VIEW_H
#define _VIEW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "model.h"
#include <map>
#include <string>

// Show (output) the state of the model
class View {
public:
    View(std::string title, int width, int height);
    ~View();
    // Print out the visible stuff in the grid
    void show(Model * model);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screen;
    bool fail;
    SDL_Texture* load(char * path);
    TTF_Font* font;
    SDL_Texture* levelTextures;
    SDL_Texture* brickTextures;
    SDL_Texture* bgTexture;
    SDL_Texture* bubbleTexture;
    SDL_Rect paddleUV = { 0, 0, 256, 45 };
    SDL_Rect brickUV = { 0, 0, 128, 128 };
    SDL_Rect ballUV = { 0, 45, 32, 32 };
};
#endif
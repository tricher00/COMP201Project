#include "view.h"

using namespace std;

// Initialize SDL
View::View(string title, int width, int height) {
    fail = false;
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        fail = true;
        return;
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fail = true;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x01);

    // Get the screen
    screen = SDL_GetWindowSurface(window);
    //Initialize JPEG and PNG loading
    if( !( IMG_Init( IMG_INIT_JPG|IMG_INIT_PNG ) & (IMG_INIT_JPG|IMG_INIT_PNG) ) ) {
        fail = true;
        return;
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        fail = true;
        return;
    }

    // Initialize True type fonts
    if( TTF_Init() == -1 ) {
        return;
    }
    // Load assets
    font = TTF_OpenFont("assets/LiberationSans-Regular.ttf", 28);
    levelTextures = load("assets/textures/leveltextures.png");
    brickTextures = load("assets/textures/bricks.png");
    bgTexture = load("assets/textures/bg.png");
    bubbleTexture = load("assets/textures/bubble.png");

    SDL_SetTextureBlendMode(levelTextures, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(brickTextures, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(bubbleTexture, SDL_BLENDMODE_BLEND);
}

View::~View() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

/**
 *  Load an image from a file to a SDL_Texture
 */
SDL_Texture* View::load(char * path) {
    // Load image
    //SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL) {
        return NULL;
    }
    // Convert surface to screen format
    //optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
    
    // Get rid of old loaded surface
    
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    //SDL_FreeSurface(optimizedSurface);
    return tex;
}

void View::show(Model* model) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

    for(int i = 0; i < model->getCurrentLevel()->getBricks().size(); i++) {
        if(!model->getCurrentLevel()->getBricks()[i].broken) {
            SDL_Color color = model->getCurrentLevel()->getBricks()[i].color;
            SDL_SetTextureColorMod(brickTextures, color.r, color.g, color.b);
            SDL_SetTextureAlphaMod(brickTextures, color.a);
            SDL_RenderCopy(renderer, brickTextures, &brickUV, &model->getCurrentLevel()->getBricks()[i].bounds);
        }
    }

    SDL_Rect paddleBounds = model->getCurrentLevel()->getPaddleBounds();
    SDL_RenderCopy(renderer, levelTextures, &paddleUV, &paddleBounds);

    for(int i = 0; i < model->getCurrentLevel()->getBalls().size(); i++) {
        SDL_Rect ballBounds = model->getCurrentLevel()->getBalls()[i]->getBounds();
        SDL_RenderCopy(renderer, levelTextures, &ballUV, &ballBounds);
    }

    for(int i = 0; i < model->getCurrentLevel()->getParticles().size(); i++) {
        //model->getCurrentLevel()->getParticles()[i]->render(renderer);
    }

    for(int i = 0; i < model->getCurrentLevel()->getBalls().size(); i++) {
        for(int j = 0; j < model->getCurrentLevel()->getBalls()[i]->getParticles().size(); j++) {
            //model->getCurrentLevel()->getBalls()[i]->getParticles()[j]->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}

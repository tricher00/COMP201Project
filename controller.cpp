#include "controller.h"
#include <map>

using namespace std;

Controller::Controller() {
    view = new View("Game", 1024, 768);
    model = new Model(1024, 768);
}

Controller::~Controller() {
    delete model;
    delete view;
}

void Controller::loop() {
    SDL_Event e;
    unsigned int lastTime = 0, currentTime;
    unsigned int frameDelay = 1000 / 60;
    std::map<SDL_Keycode, Direction> direction;
    direction[SDLK_LEFT] = LEFT;
    direction[SDLK_RIGHT] = RIGHT;

    while(!model->gameOver()) {
        currentTime = SDL_GetTicks();
        // Do stuff here to animate as necessary
        if(currentTime > lastTime + frameDelay) {
            while(SDL_PollEvent(&e)) {
                switch (e.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        model->getCurrentLevel()->movePaddle(direction[e.key.keysym.sym], true);
                        break;
                    default:
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym) {
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        model->getCurrentLevel()->movePaddle(direction[e.key.keysym.sym], false);
                        break;
                    default:
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                }
            }
            model->update();
            view->show(model);
            lastTime = currentTime;
        }
    }
    // TODO: show something nice?
    view->show(model);
    SDL_Delay(3000);
}

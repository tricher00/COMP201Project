#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.h"
#include "view.h"
#include "level.h"

// Handle input
class Controller {
public:
    Controller();
    ~Controller();
    // Event loop
    void loop();
private:
    Model * model;
    View * view;
};
#endif
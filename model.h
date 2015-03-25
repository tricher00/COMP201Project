#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include "level.h"

// The model manages the state of the game
class Model {
public:
    // Constructor (instantiates object)
    Model(int screenWidth, int screenHeight);
    // Destructor deletes all dynamically allocated stuff
    ~Model();
    // Is the game over?
    bool gameOver();
    void update();
    void addLevel(Level *level);
    Level* getCurrentLevel();
private:
    int currentLevel = 0;
    std::vector<Level*> levels;
};

#endif
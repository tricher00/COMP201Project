#include "model.h"
#include <iostream>

Model::Model(int screenWidth, int screenHeight) {
    addLevel(new Level("assets/level1.png", screenWidth, screenHeight));
}

Model::~Model() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
}

bool Model::gameOver() {
    return currentLevel == levels.size() - 1 && getCurrentLevel()->isOver();
}

void Model::update() {
    getCurrentLevel()->update();
}

void Model::addLevel(Level *level) {
    levels.push_back(level);
}

Level* Model::getCurrentLevel() {
    return levels[currentLevel];
}
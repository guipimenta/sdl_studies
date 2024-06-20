#pragma once
#include <string>
#include "canvas.h"
#include <signal.h>

namespace Blocks {

volatile sig_atomic_t quit = 0;

void signalHandler(int signal) {
    quit = 1;
}

class GameEngine {
public:
    GameEngine() {};
    
    virtual void run() = 0;
    
    virtual void update() = 0;
    
    virtual void render() = 0;
    
    virtual void handleEvents() = 0;
    
    virtual void clean() = 0;

    virtual void keydown(SDL_Event e) = 0;
    
    bool running() { 
        return isRunning && !quit; 
    }

protected:
    bool isRunning;
};


class SimpleGameEngine : public GameEngine {

public:

    SimpleGameEngine(
        std::string title,
        int width,
        int height
    ) : title(title), width(width), height(height), gameCanvas(title) {};

    virtual void run() override;

    virtual void update() override;

    virtual void render() override;

    virtual void handleEvents() override;

    virtual void clean() override;

    virtual void keydown(SDL_Event e) override;

    

protected:
    Blocks::Canvas gameCanvas;
        const int width;
    const int height;

private:

    const std::string title;

    
};


void SimpleGameEngine::run() {
    gameCanvas.init();
    isRunning = true;
    signal(SIGINT, signalHandler);
    SDL_Event e;
    while (running()) {
        if (SDL_PollEvent( & e)) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            } else if (e.type == SDL_KEYDOWN) {
                keydown(e);
            }
        }
        handleEvents();
        update();
        render();

    }
    clean();
};

void SimpleGameEngine::update() {
    // Update game state
}

void SimpleGameEngine::render() {
    // Render game state
}

void SimpleGameEngine::handleEvents() {
    // Handle game events
}

void SimpleGameEngine::clean() {
    // clean up
}

void SimpleGameEngine::keydown(SDL_Event e) {
    // Handle keydown events
}

};


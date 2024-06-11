#pragma once
#include <iostream>
#include <string>
#include "geometry.h"



class Canvas {
public:
    Canvas(std::string title) : title(title) {};
    ~Canvas() {
        SDL_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    };
    void init();

    void draw(Shape* shape) {
        shape->draw(renderer);
    }

    void render() {
        SDL_RenderPresent(renderer);
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

private:
    std::string title;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

void Canvas::init() {
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow(title.c_str(),
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            680, 480,
                                            0);
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

#pragma once
#include <iostream>
#include <string>
#include "geometry.h"

namespace Blocks {

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
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
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

    SDL_RendererInfo info;
    SDL_GetRendererInfo(renderer, &info);
    if (info.flags & SDL_RENDERER_SOFTWARE) {
        std::cout << "Software renderer" << std::endl;
    }
    SDL_Log("Renderer: %s", info.name);
}


};
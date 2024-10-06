#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "game.h"
#include "geometry.h"
#include "font.h"

void renderText(SDL_Renderer* renderer, const std::string& text, int x, int y, TTF_Font* font, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cout << "Failed to create surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

class Dots : public Blocks::SimpleGameEngine  {
public:
    Dots(const std::string& title, int width, int height) 
    : SimpleGameEngine(title, width, height)  {}

    void update() override {
        gameCanvas.clear();
        Blocks::Font f("a.txt", 5, 5);
        gameCanvas.draw(&f);
        Blocks::Circle c(circleX, circleY, 50);
        gameCanvas.draw(&c);
        gameCanvas.draw(&c);
        renderText(this->gameCanvas.getRenderer(), "My First CPP Engine", 50, 50, TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24), { 255, 255, 255, 255 });

    }

    void render() override {
        gameCanvas.render();
    }

    void keydown(SDL_Event e) override {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                SDL_Log("UP");
                circleY -= 5;
                break;
            case SDLK_DOWN:
                SDL_Log("DOWN");
                circleY += 5;
                // Handle down arrow key
                break;
            case SDLK_LEFT:
                SDL_Log("LEFT");
                circleX -= 5;
                // Handle left arrow key
                break;
            case SDLK_RIGHT:
                SDL_Log("RIGHT");
                circleX += 5;
                // Handle right arrow key
                break;
            // Add more keys as needed...
        }
    }
private:
    int dotx=0, doty=10;
    int circleX = 150, circleY = 150;
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
};

int main()
{
    
    Dots game("Simple Game", 680, 480);
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

     if (TTF_Init() == -1) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    game.run();
    return 0;
}
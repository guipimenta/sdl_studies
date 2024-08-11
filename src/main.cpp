#include <SDL.h>
#include <iostream>
#include "game.h"
#include "geometry.h"
#include "font.h"

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

};

int main()
{
    Dots game("Simple Game", 680, 480);
    game.run();
    return 0;
}
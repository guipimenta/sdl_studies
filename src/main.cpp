#include <SDL.h>
#include <iostream>
#include "game.h"
#include "geometry.h"

class Dots : public SimpleGameEngine  {
public:
    Dots(const std::string& title, int width, int height) 
    : SimpleGameEngine(title, width, height)  {}

    void update() override {        
        Point dot(dotx, doty);
        gameCanvas.draw(&dot);

        Point dot2(dotx, doty + 1);
        gameCanvas.draw(&dot2);

        Point dot3(dotx, doty + 1);
        gameCanvas.draw(&dot3);

        Circle c(circleX, circleY, 50);
        gameCanvas.draw(&c);
        
        dotx += 5;
        circleX += 5;
        if (dotx > width) {
            dotx = 0;
            circleX = 150;
            gameCanvas.clear();
        }
    }

    void render() override {
        gameCanvas.render();
        SDL_Delay(50);
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
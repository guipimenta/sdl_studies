#pragma once
#include <string>
#include <SDL.h>
#include "assets.h"

namespace Blocks {

class Font {
public:

    Font(std::string asset, int x, int y) : font(Assets::readAsset(asset)), x(x), y(y) {};
    virtual ~Font() {};
    void draw(SDL_Renderer* renderer);

private:

    const Assets::Font font;
    const int x;
    const int y;

};

void Font::draw(SDL_Renderer* renderer) {
    int x0 = this->x;
    int y0 = this->y;
    for (int i = 0; i < Assets::FONT_X; ++i) {
        for (int j = 0; j < Assets::FONT_Y; ++j) {
            if(font[i][j] == 1) {
                Circle circle(x0, y0, 2);
                circle.draw(renderer);
            }
            x0++;
        }
        y0++;
    }
};

};
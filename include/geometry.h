#pragma once

#include <SDL.h>


class Shape {
public:
    Shape() {};
    virtual ~Shape() {};
    virtual void draw(SDL_Renderer* renderer) = 0;
};


class Point : public Shape {
public:
    Point(int x, int y) : x(x), y(y) {};
    virtual ~Point() {};
    void draw(SDL_Renderer* renderer) override;
private: 
    int x;
    int y;
};

void Point::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if (SDL_RenderDrawPoint(renderer, x, y) == -1) {
        std::cout << "Could not draw point: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Point drawn at (" << x << ", " << y << ")" << std::endl;
    }
    SDL_RenderPresent(renderer);    
}

class Circle : public Shape {
public:
    Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {};
    virtual ~Circle() {};
    void draw(SDL_Renderer* renderer) override;
private:
    int x;
    int y;
    int radius;
};




void Circle::draw(SDL_Renderer* renderer)  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int32_t dx = 0, dy = radius, err = 3 - 2 * radius;

    while (dy >= dx) {
        SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        SDL_RenderDrawPoint(renderer, x + dy, y + dx);
        SDL_RenderDrawPoint(renderer, x - dx, y + dy);
        SDL_RenderDrawPoint(renderer, x - dy, y + dx);
        SDL_RenderDrawPoint(renderer, x + dx, y - dy);
        SDL_RenderDrawPoint(renderer, x + dy, y - dx);
        SDL_RenderDrawPoint(renderer, x - dx, y - dy);
        SDL_RenderDrawPoint(renderer, x - dy, y - dx);

        if (err < 0) {
            err += 4 * dx + 6;
        } else {
            err += 4 * (dx - dy) + 10;
            dy -= 1;
        }
        dx += 1;
    }
    SDL_RenderPresent(renderer);
};
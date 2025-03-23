#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include "vector2.h"

class Ball{
public:
    Ball(Vector2 position, Vector2 velocity, double mass, int radius, SDL_Color color);
    void update(int screenWidth, int screenHeight, std::vector<Ball>& balls);
    void draw(SDL_Renderer* renderer);

private:
    Vector2 position;
    Vector2 velocity;
    double mass;
    int radius;
    SDL_Color color;

    void handleWallCollision(int screenWidth, int screenHeight);
    void checkCollision(Ball& other);
    double calcVel(double v1, double v2, double mass1, double mass2);
};
#endif
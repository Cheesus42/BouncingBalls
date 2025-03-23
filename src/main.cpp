#include "Ball.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_COUNT = 25;

void addBall(double x, double y, double vx, double vy, int mass, SDL_Color color, std::vector<Ball>& balls){
    Vector2 pos = {x, y};
    Vector2 vel = {vx, vy};
    balls.emplace_back(pos, vel, mass, mass, color);
}

int main(int argc, char* argv[]){

    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO) != 0)){
        std::cerr << "SDL konnte nicht initialisiert werden: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(  "Ball Beispiel", 
                                            SDL_WINDOWPOS_CENTERED, 
                                            SDL_WINDOWPOS_CENTERED, 
                                            SCREEN_WIDTH, SCREEN_HEIGHT, 
                                            SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Fenster konnte nicht erstellt werden: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 2;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer konnte nicht erstellt werden: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    std::vector<Ball> balls;
    // for (int i = 0; i < BALL_COUNT; i++){
    //     addBall(std::rand() % (SCREEN_WIDTH - 40) + 20, std::rand() % (SCREEN_HEIGHT - 40) + 20, (std::rand() % 5) + 1, (std::rand() % 5) + 1, (std::rand() % 15) + 5, {static_cast<Uint8>(std::rand() % 256), static_cast<Uint8>(std::rand() % 256), static_cast<Uint8>(std::rand() % 256), 255}, balls);
    // }

    addBall(200, 400, 1, 0, 10, {255, 0, 0, 255}, balls);
    addBall(400, 400, 1, 0, 10, {0, 255, 0, 255}, balls);
    
    
    bool running = true;
    SDL_Event event;

    while(running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
        }
        
        for(auto& ball : balls){
            ball.update(SCREEN_WIDTH, SCREEN_HEIGHT, balls);
        }
        
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& ball : balls){
            ball.draw(renderer);
        }
        

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
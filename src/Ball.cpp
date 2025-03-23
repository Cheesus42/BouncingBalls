#include "Ball.h"
#include <cmath>

Ball::Ball(Vector2 position, Vector2 velocity, double mass, int radius, SDL_Color color) 
    : position(position), velocity(velocity), mass(mass), radius(radius), color(color) {}

void Ball::update(int screenWidth, int screenHeight, std::vector<Ball>& balls){
    position += velocity;

    handleWallCollision(screenWidth, screenHeight);
    for (Ball& other : balls){
        if (&other != this){
            checkCollision(other);
        }
    }
}

void Ball::draw(SDL_Renderer* renderer) {

    // Setze die Zeichenfarbe auf die Ballfarbe
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Algorithmus zum Zeichnen eines Kreises (Midpoint Circle Algorithm)
    double r = radius;
    int d;
    Vector2 offset = {0, r};
    d = 3 - 2 * r;

    while (offset.x <= offset.y) {
        SDL_RenderDrawPoint(renderer, position.x + offset.x, position.y + offset.y);
        SDL_RenderDrawPoint(renderer, position.x - offset.x, position.y + offset.y);
        SDL_RenderDrawPoint(renderer, position.x + offset.x, position.y - offset.y);
        SDL_RenderDrawPoint(renderer, position.x - offset.x, position.y - offset.y);
        SDL_RenderDrawPoint(renderer, position.x + offset.y, position.y + offset.x);
        SDL_RenderDrawPoint(renderer, position.x - offset.y, position.y + offset.x);
        SDL_RenderDrawPoint(renderer, position.x + offset.y, position.y - offset.x);
        SDL_RenderDrawPoint(renderer, position.x - offset.y, position.y - offset.x);

        if (d < 0) {
            d += 4 * offset.x + 6;
        } else {
            d += 4 * (offset.x - offset.y) + 10;
            (offset.y)--;
        }
        (offset.x)++;
    }
}

void Ball::handleWallCollision(int screenWidth, int screenHeight){
    if (position.x - radius <= 0 || position.x + radius >= screenWidth){
        velocity.x = -(velocity.x);
    }
    if (position.y - radius <= 0 || position.y + radius >= screenHeight){
        velocity.y = -(velocity.y);
    }
}

void Ball::checkCollision(Ball& other){
    Vector2 delta = other.position - this->position;
    double distance = std::sqrt((delta.x*delta.x) + (delta.y*delta.y));
    double minDistance = this->radius + other.radius;

    //kollisionsüberprüfung
    bool coll = distance <= this->radius + other.radius ? true : false;

    if (coll){
        Vector2 normal = delta / distance;
        Vector2 tang = Vector2(-(normal.y), normal.x);

        double v1n = this->velocity.dot(normal);
        double v2n = other.velocity.dot(normal);

        double v1t = this->velocity.dot(tang);
        double v2t = other.velocity.dot(tang);

        //Funktion
        double v1nnew = calcVel(v1n, v2n, this->mass, other.mass);
        double v2nnew = calcVel(v2n, v1n, this->mass, other.mass);

        Vector2 v1new = normal * v1nnew + tang * v1t;
        Vector2 v2new = normal * v2nnew + tang * v2t;

        this->velocity = v1new;
        other.velocity = v2new;

        double overlap = minDistance - distance;
        Vector2 correction = normal * (overlap / 2);

        this->position -= correction;
        other.position += correction;
    }
}
double Ball::calcVel(double v1, double v2, double mass1, double mass2){
    return ((mass1 - mass2) * v1 + 2 * mass2 * v2) / (mass1 + mass2);
}
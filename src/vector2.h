#include <cmath>
#include <iostream>
class Vector2{
    public:

        double x;
        double y;

        Vector2() : x(0.0), y(0.0) {}
        Vector2(double x, double y) : x(x), y(y) {}

        Vector2 operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }
        
        // Vektorsubtraktion
        Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }
        
        Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        // Skalare Multiplikation
        Vector2 operator*(double scalar) const {
            return Vector2(x * scalar, y * scalar);
        }
        
        Vector2 operator/(double scalar) const {
            if (scalar == 0.0) {
                throw std::invalid_argument("Division by zero");
            }
            return Vector2(x / scalar, y / scalar);
        }
        
        // Dot-Produkt
        double dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }
        
        // Länge (Magnitude) des Vektors
        double magnitude() const {
            return std::sqrt(x * x + y * y);
        }
        
        // Normalisierung des Vektors
        Vector2 normalize() const {
            double mag = magnitude();
            if (mag == 0.0) {
                throw std::invalid_argument("Cannot normalize zero vector");
            }
            return Vector2(x / mag, y / mag);
        }
    
};
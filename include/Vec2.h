// ========================================
// include/Vec2.h
// ========================================
#pragma once
#include <cmath>


struct Vec2 {
float x{0.f}, y{0.f};
Vec2() = default;
Vec2(float x_, float y_) : x(x_), y(y_) {}


// operações básicas
Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
Vec2 operator*(float s) const { return {x * s, y * s}; }
Vec2& operator+=(const Vec2& o){ x+=o.x; y+=o.y; return *this; }
Vec2& operator-=(const Vec2& o){ x-=o.x; y-=o.y; return *this; }


float length() const { return std::sqrt(x*x + y*y); }
Vec2 normalized() const { float m = length(); return m>0? Vec2{x/m, y/m} : Vec2{}; }


// rotação (eixo y positivo para baixo)
Vec2 rotated(float rad) const {
float cs = std::cos(rad), sn = std::sin(rad);
return { x*cs - y*sn, y*cs + x*sn };
}
};
// ========================================
// include/Rect.h
// ========================================
#pragma once
#include "Vec2.h"


struct Rect {
float x{0.f}, y{0.f}, w{0.f}, h{0.f};
Rect() = default;
Rect(float x_, float y_, float w_, float h_) : x(x_), y(y_), w(w_), h(h_) {}


Vec2 center() const { return {x + w*0.5f, y + h*0.5f}; }
bool contains(const Vec2& p) const { return p.x>=x && p.x<=x+w && p.y>=y && p.y<=y+h; }
Rect operator+(const Vec2& v) const { return {x+v.x, y+v.y, w, h}; }
};
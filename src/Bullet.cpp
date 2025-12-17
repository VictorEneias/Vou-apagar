#include "Bullet.h"
#include "GameObject.h"
#include <cmath>

Bullet::Bullet(GameObject& go, const Vec2& vel, float maxDistance, int damage)
: Component(go), velocity(vel), distanceLeft(maxDistance), bulletDamage(damage) {}

void Bullet::Update(float dt){
    Vec2 step = velocity * dt;
    associated.box.x += step.x;
    associated.box.y += step.y;
    distanceLeft -= step.length();
    if (distanceLeft <= 0.f) associated.RequestDelete();
}

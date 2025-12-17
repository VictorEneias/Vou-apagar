#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject& go, const Vec2& velocity, float maxDistance, int damage);

    void Update(float dt) override;
    void Render() override {}

    int GetDamage() const { return bulletDamage; }

private:
    Vec2 velocity;
    float distanceLeft{0.f};
    int bulletDamage{0};
};

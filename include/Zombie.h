#pragma once
#include "Component.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
public:
    explicit Zombie(GameObject& go);
    void Update(float dt) override;
    void Render() override {}
    void Damage(int damage);
private:
    int hitpoints{100};
    bool dead{false};
    bool hit{false};
    Timer deathTimer;
    Timer hitTimer;
    Sound deathSound;
};
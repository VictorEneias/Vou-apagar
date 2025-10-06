#pragma once
#include "Component.h"

class Zombie : public Component {
public:
    explicit Zombie(GameObject& go);
    void Update(float dt) override;
    void Render() override {}
    void Damage(int damage);
private:
    int hitpoints{100};
};

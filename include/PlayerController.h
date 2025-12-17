#pragma once
#include <memory>
#include "Component.h"
#include "Vec2.h"

class Character;

class PlayerController : public Component {
public:
    PlayerController(GameObject& go, std::weak_ptr<Character> character);
    void Update(float dt) override;
    void Render() override {}

private:
    std::weak_ptr<Character> character;
};

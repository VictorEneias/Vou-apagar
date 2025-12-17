#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class Gun;

class Character : public Component {
public:
    explicit Character(GameObject& go);

    void Start() override;
    void Update(float dt) override;
    void Render() override {}

    void EnqueueCommand(const std::function<void(Character&, float)>& cmd);
    void Move(const Vec2& dir);
    void AimAt(const Vec2& target);
    void Shoot(const Vec2& target);
    void Reload();

    void SetGun(std::weak_ptr<Gun> gunPtr);
    GameObject& GetGameObject() { return associated; }
    const GameObject& GetGameObject() const { return associated; }

    bool IsDead() const { return dead; }

private:
    void UpdateAnimation();

    int hp{100};
    float speed{220.f};
    float linearSpeed{0.f};
    Vec2 direction{0.f, 0.f};
    Vec2 lookDir{1.f, 0.f};
    bool dead{false};
    Timer deathTimer;
    std::vector<std::function<void(Character&, float)>> taskQueue;
    std::weak_ptr<Gun> gun;
};

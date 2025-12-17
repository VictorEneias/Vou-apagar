#pragma once
#include <memory>
#include "Component.h"
#include "Timer.h"
#include "Sound.h"
#include "Vec2.h"

class Character;
class Gun : public Component {
public:
    explicit Gun(GameObject& go);

    void Start() override;
    void Update(float dt) override;
    void Render() override {}

    void SetOwner(std::weak_ptr<Character> ownerPtr);
    void Shoot(const Vec2& target);
    void Reload();
    void SetAim(const Vec2& dir);

    int GetCooldownState() const { return cooldownState; }

private:
    void SetState(int state);
    void SpawnBullet(const Vec2& direction);

    std::weak_ptr<Character> owner;
    Timer cooldownTimer;
    int cooldownState{0}; // 0=idle,1=shot cooldown,2=reloading,3=disabled
    float shotCooldown{0.35f};
    float reloadTime{1.0f};
    Sound shotSound;
    Sound reloadSound;
};

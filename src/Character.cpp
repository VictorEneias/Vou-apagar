#include "Character.h"
#include "GameObject.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Gun.h"
#include <cmath>

namespace {
constexpr float kDeg = 180.0f / 3.14159265358979323846f;
}

Character::Character(GameObject& go) : Component(go) {}

void Character::Start(){
    UpdateAnimation();
    Component::Start();
}

void Character::EnqueueCommand(const std::function<void(Character&, float)>& cmd){
    taskQueue.push_back(cmd);
}

void Character::Move(const Vec2& dir){
    direction = dir;
}

void Character::AimAt(const Vec2& target){
    Vec2 center = associated.box.center();
    lookDir = (target - center).normalized();
    if (lookDir.length() == 0.f) lookDir = {1.f, 0.f};
    associated.angleDeg = std::atan2(lookDir.y, lookDir.x) * kDeg;
    if (auto g = gun.lock()) g->SetAim(lookDir);
}

void Character::Shoot(const Vec2& target){
    if (dead) return;
    AimAt(target);
    if (auto g = gun.lock()) g->Shoot(target);
}

void Character::Reload(){
    if (auto g = gun.lock()) g->Reload();
}

void Character::Update(float dt){
    if (!Started()) Start();

    if (dead){
        deathTimer.Update(dt);
        if (deathTimer.Get() > 1.5f) associated.RequestDelete();
        return;
    }

    for (auto& cmd : taskQueue) cmd(*this, dt);
    taskQueue.clear();

    Vec2 dir = direction.normalized();
    linearSpeed = (direction.length() > 0.f ? speed : 0.f);
    associated.box.x += dir.x * linearSpeed * dt;
    associated.box.y += dir.y * linearSpeed * dt;

    UpdateAnimation();
}

void Character::UpdateAnimation(){
    auto anim = associated.GetComponent<Animator>();
    if (!anim) return;

    if (dead){
        anim->SetAnimation("dead");
        return;
    }

    if (direction.length() > 0.f) anim->SetAnimation("walking");
    else anim->SetAnimation("idle");
}

void Character::SetGun(std::weak_ptr<Gun> gunPtr){
    gun = std::move(gunPtr);
}

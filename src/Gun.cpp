#include "Gun.h"
#include "GameObject.h"
#include "Character.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Bullet.h"
#include "Game.h"
#include "State.h"
#include <cmath>
#include <memory>

namespace {
constexpr double kDeg = 180.0 / 3.14159265358979323846;
}

Gun::Gun(GameObject& go)
: Component(go), shotSound("Recursos/audio/Range.wav"), reloadSound("Recursos/audio/PumpAction.mp3") {}

void Gun::Start(){
    SetState(0);
    Component::Start();
}

void Gun::SetOwner(std::weak_ptr<Character> ownerPtr){
    owner = std::move(ownerPtr);
}

void Gun::SetState(int state){
    cooldownState = state;
    if (auto anim = associated.GetComponent<Animator>()){
        if (cooldownState == 2) anim->SetAnimation("reloading");
        else anim->SetAnimation("idle");
    }
    cooldownTimer.Restart();
}

void Gun::SetAim(const Vec2& dir){
    Vec2 n = dir.length() > 0.f ? dir.normalized() : Vec2{1.f, 0.f};
    double angle = std::atan2(n.y, n.x) * kDeg;
    associated.angleDeg = angle;
    if (auto sr = associated.GetComponent<SpriteRenderer>()){
        bool flipVertical = (angle > 90.0 || angle < -90.0);
        sr->SetFlip(false, flipVertical);
    }
}

void Gun::SpawnBullet(const Vec2& direction){
    auto& state = Game::GetInstance().GetState();
    if (auto bulletWeak = state.AddObject(new GameObject()); auto bullet = bulletWeak.lock()){
        auto center = associated.box.center();
        bullet->AddComponent(std::make_shared<SpriteRenderer>(*bullet, "Recursos/img/Bullet.png", 1, 1));
        bullet->AddComponent(std::make_shared<Bullet>(*bullet, direction * 700.f, 600.f, 15));
        bullet->box.setCenter(center + direction * 20.f);
        bullet->angleDeg = std::atan2(direction.y, direction.x) * kDeg;
    }
}

void Gun::Shoot(const Vec2& target){
    if (cooldownState == 1 || cooldownState == 2 || cooldownState == 3) return;
    auto o = owner.lock();
    if (!o) return;

    Vec2 center = o->GetGameObject().box.center();
    Vec2 dir = (target - center).normalized();
    if (dir.length() == 0.f) dir = {1.f, 0.f};

    SetAim(dir);
    SpawnBullet(dir);
    shotSound.Play(1);
    SetState(1);
}

void Gun::Reload(){
    if (cooldownState == 2 || cooldownState == 3) return;
    reloadSound.Play(1);
    SetState(2);
}

void Gun::Update(float dt){
    if (auto o = owner.lock()){
        associated.box.setCenter(o->GetGameObject().box.center());
    } else {
        cooldownState = 3;
        associated.RequestDelete();
        return;
    }

    cooldownTimer.Update(dt);
    if (cooldownState == 1 && cooldownTimer.Get() >= shotCooldown) SetState(0);
    else if (cooldownState == 2 && cooldownTimer.Get() >= reloadTime) SetState(0);
}

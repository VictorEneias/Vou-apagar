#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include <memory>

Zombie::Zombie(GameObject& go)
: Component(go), deathSound("Recursos/audio/Dead.wav") {
    auto sr = std::make_shared<SpriteRenderer>(associated, "Recursos/img/Enemy.png", 6, 4);
    associated.AddComponent(sr);

    auto anim = std::make_shared<Animator>(associated);
    associated.AddComponent(anim);
    anim->AddAnimation("walking", {0, 5, 0.12f});
    anim->AddAnimation("hit",     {6, 11, 0.05f});
    anim->AddAnimation("dead",    {12, 17, 0.1f});
    anim->SetAnimation("walking");
}

void Zombie::Damage(int damage){
    if (dead || damage <= 0) return;

    hit = true;
    hitTimer.Restart();
    hitpoints -= damage;
    if (auto anim = associated.GetComponent<Animator>()) anim->SetAnimation("hit");

    if (hitpoints <= 0){
        dead = true;
        deathTimer.Restart();
        if (auto anim = associated.GetComponent<Animator>())
            anim->SetAnimation("dead");
        else if (auto sr = associated.GetComponent<SpriteRenderer>())
            sr->SetFrame(12);
        deathSound.Play(1);
    }
}

void Zombie::Update(float dt){
    if (dead){
        deathTimer.Update(dt);
        if (deathTimer.Get() > 1.0f) associated.RequestDelete();
        return;
    }

    if (hit){
        hitTimer.Update(dt);
        if (hitTimer.Get() > 0.2f){
            hit = false;
            if (auto anim = associated.GetComponent<Animator>()) anim->SetAnimation("walking");
        }
    }
}
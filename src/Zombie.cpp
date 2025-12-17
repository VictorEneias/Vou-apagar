#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"

Zombie::Zombie(GameObject& go)
: Component(go), deathSound("Recursos/audio/Dead.wav") {
    auto* sr = new SpriteRenderer(associated, "Recursos/img/Enemy.png", 3, 2);
    associated.AddComponent(sr);

    auto* anim = new Animator(associated);
    associated.AddComponent(anim);
    anim->AddAnimation("walking", {0,3,10});
    anim->AddAnimation("dead",    {5,5,0});
    anim->SetAnimation("walking");
}

void Zombie::Damage(int damage){
    if (dead) return;

    hitpoints -= damage;
    if (hitpoints <= 0){
        dead = true;
        if (auto* anim = associated.GetComponent<Animator>())
            anim->SetAnimation("dead");
        else if (auto* sr = associated.GetComponent<SpriteRenderer>())
            sr->SetFrame(5);
        deathSound.Play(1);
    }
}

void Zombie::Update(float /*dt*/){
    Damage(1);
}
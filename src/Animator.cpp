// ========================================
// src/Animator.cpp
// ========================================
#include "Animator.h"
#include "GameObject.h"
#include "SpriteRenderer.h"


Animator::Animator(GameObject& go) : Component(go) {}


void Animator::AddAnimation(const std::string& name, const Animation& a){
animations.emplace(name, a);
}


void Animator::SetAnimation(const std::string& name){
auto it = animations.find(name);
if (it == animations.end()) return;
frameStart = it->second.frameStart;
frameEnd = it->second.frameEnd;
frameTime = it->second.frameTime;
currentFrame = frameStart;
timeElapsed = 0.f;
if (auto* sr = associated.GetComponent<SpriteRenderer>()) {
sr->SetFrame(currentFrame);
}
}


void Animator::Update(float dt){
if (frameTime <= 0.f) return; // sem animação
timeElapsed += dt;
if (timeElapsed >= frameTime){
    timeElapsed -= frameTime;
    currentFrame++;
    if (currentFrame > frameEnd) currentFrame = frameStart;
    if (auto* sr = associated.GetComponent<SpriteRenderer>()) {
        sr->SetFrame(currentFrame);
    }
}
}
// ========================================
// include/Animator.h
// ========================================
#pragma once
#include <unordered_map>
#include <string>
#include "Component.h"
#include "Animation.h"


class Animator : public Component {
public:
explicit Animator(GameObject& go);
void Update(float dt) override;
void Render() override {}


void SetAnimation(const std::string& name);
void AddAnimation(const std::string& name, const Animation& anim);


private:
std::unordered_map<std::string, Animation> animations;
int frameStart{0};
int frameEnd{0};
float frameTime{0.f};
int currentFrame{0};
float timeElapsed{0.f};
};
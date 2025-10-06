// ========================================
// include/State.h
// ========================================
#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Music.h"


class State {
public:
State();
~State();


void LoadAssets();
void Update(float dt);
void Render();


void AddObject(GameObject* go);


bool QuitRequested() const { return quitRequested; }


private:
std::vector<std::unique_ptr<GameObject>> objectArray;
Music music;
bool quitRequested{false};
};
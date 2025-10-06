// ========================================
// src/State.cpp
// ========================================
#include "State.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include <SDL2/SDL.h>


State::State(){
LoadAssets();
}


State::~State(){
objectArray.clear();
}


void State::LoadAssets(){
// Música de fundo
music.Open("Recursos/audio/BGM.wav");
music.Play(-1);


// Background como GameObject + SpriteRenderer
auto* bg = new GameObject();
auto* bgSR = new SpriteRenderer(*bg, "Recursos/img/Background.png", 1, 1);
bg->AddComponent(bgSR);
bg->box.x = 0; bg->box.y = 0;
AddObject(bg);


// Zombie no meio
auto* z = new GameObject();
z->box.x = 600; z->box.y = 450;
z->AddComponent(new Zombie(*z));
AddObject(z);
}


void State::AddObject(GameObject* go){
objectArray.emplace_back(go);
}


void State::Update(float /*dt*/){
if (SDL_QuitRequested()) { quitRequested = true; return; }


// Atualiza todos
for (auto& obj : objectArray) obj->Update(0.f);


// Remove mortos
for (size_t i=0; i<objectArray.size(); ){
if (objectArray[i]->IsDead()) {
objectArray.erase(objectArray.begin() + (long)i);
} else {
++i;
}
}
}


void State::Render(){
for (auto& obj : objectArray) obj->Render();
}
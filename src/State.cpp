// ========================================
// src/State.cpp
// ========================================
#include "State.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "InputManager.h"
#include "CameraFollower.h"
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
bg->AddComponent(new CameraFollower(*bg));
AddObject(bg);


// TileMap
auto* map = new GameObject();
map->box.x = 0; map->box.y = 0;
map->AddComponent(new TileMap(*map, "Recursos/map/map.txt", new TileSet(64, 64, "Recursos/img/Tileset.png")));
AddObject(map);


// Zombie no meio
auto* z = new GameObject();
z->box.x = 600; z->box.y = 450;
z->AddComponent(new Zombie(*z));
AddObject(z);
}


void State::AddObject(GameObject* go){
objectArray.emplace_back(go);
}


void State::Update(float dt){
    auto& in = InputManager::GetInstance();
    if (SDL_QuitRequested() || in.KeyPress(SDL_SCANCODE_ESCAPE)) {
        quitRequested = true; return;
    }

    for (auto& obj : objectArray) obj->Update(dt);

    for (size_t i=0; i<objectArray.size();) {
        if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin() + (long)i);
        else ++i;
    }
}


void State::Render(){
for (auto& obj : objectArray) obj->Render();
}
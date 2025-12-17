// ========================================
// src/State.cpp
// ========================================
#include "State.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Zombie.h"
#include "Bullet.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include "Character.h"
#include "Gun.h"
#include "PlayerController.h"
#include "Camera.h"
#include <SDL2/SDL.h>
#include <memory>

State::State(){
    LoadAssets();
}

State::~State(){
    objectArray.clear();
}

void State::Start(){
    if (started) return;
    for (auto& obj : objectArray){
        if (obj) obj->Start();
    }
    started = true;
}

void State::LoadAssets(){
    // Música de fundo
    music.Open("Recursos/audio/BGM.wav");
    music.Play(-1);

    // Background
    if (auto bgWeak = AddObject(new GameObject()); auto bg = bgWeak.lock()){
        bg->box.x = 0; bg->box.y = 0;
        bg->AddComponent(std::make_shared<SpriteRenderer>(*bg, "Recursos/img/Background.png", 1, 1));
        bg->AddComponent(std::make_shared<CameraFollower>(*bg));
    }

    // TileMap
    if (auto mapWeak = AddObject(new GameObject()); auto map = mapWeak.lock()){
        map->box.x = 0; map->box.y = 0;
        map->AddComponent(std::make_shared<TileMap>(*map, "Recursos/map/map.txt", new TileSet(64, 64, "Recursos/img/Tileset.png")));
    }

    // Player
    std::shared_ptr<Character> playerChar;
    if (auto playerWeak = AddObject(new GameObject()); auto player = playerWeak.lock()){
        player->box.x = 600; player->box.y = 450;
        auto sr = std::make_shared<SpriteRenderer>(*player, "Recursos/img/Player.png", 6, 4);
        player->AddComponent(sr);
        auto anim = std::make_shared<Animator>(*player);
        anim->AddAnimation("idle",    {0, 5, 0.1f});
        anim->AddAnimation("walking", {6, 11, 0.08f});
        anim->AddAnimation("dead",    {12, 17, 0.15f});
        anim->SetAnimation("idle");
        player->AddComponent(anim);
        playerChar = std::make_shared<Character>(*player);
        player->AddComponent(playerChar);
        player->AddComponent(std::make_shared<PlayerController>(*player, playerChar));
        Camera::Follow(player.get());
    }

    // Gun
    if (auto gunWeak = AddObject(new GameObject()); auto gunGO = gunWeak.lock()){
        gunGO->box.x = 600; gunGO->box.y = 450;
        auto sr = std::make_shared<SpriteRenderer>(*gunGO, "Recursos/img/Gun.png", 6, 2);
        gunGO->AddComponent(sr);
        auto anim = std::make_shared<Animator>(*gunGO);
        anim->AddAnimation("idle",      {0, 5, 0.08f});
        anim->AddAnimation("reloading", {6, 11, 0.1f});
        anim->SetAnimation("idle");
        gunGO->AddComponent(anim);
        auto gun = std::make_shared<Gun>(*gunGO);
        gunGO->AddComponent(gun);
        if (playerChar){
            playerChar->SetGun(gun);
            gun->SetOwner(playerChar);
        }
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);
    if (started) ptr->Start();
    return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
    for (auto& obj : objectArray){
        if (obj.get() == go) return obj;
    }
    return std::weak_ptr<GameObject>();
}

void State::Update(float dt){
    if (!started) Start();

    auto& in = InputManager::GetInstance();
    if (in.QuitRequested() || in.KeyPress(SDL_SCANCODE_ESCAPE)) {
        quitRequested = true; return;
    }

    if (in.KeyPress(SDL_SCANCODE_SPACE)){
        Vec2 pos{ Camera::posX + (float)in.GetMouseX(), Camera::posY + (float)in.GetMouseY() };
        if (auto zWeak = AddObject(new GameObject()); auto z = zWeak.lock()){
            z->box.x = pos.x; z->box.y = pos.y;
            z->AddComponent(std::make_shared<Zombie>(*z));
        }
    }

    if (in.MousePress(SDL_BUTTON_LEFT)){
        Vec2 mouseWorld{ Camera::posX + (float)in.GetMouseX(), Camera::posY + (float)in.GetMouseY() };
        for (auto& obj : objectArray){
            if (auto zombie = obj->GetComponent<Zombie>()){
                if (obj->box.contains(mouseWorld)) zombie->Damage(10);
            }
        }
    }

    for (auto& obj : objectArray) obj->Update(dt);

    for (auto& obj : objectArray){
        if (auto bullet = obj->GetComponent<Bullet>()){
            for (auto& target : objectArray){
                if (target.get() == obj.get()) continue;
                if (auto zombie = target->GetComponent<Zombie>()){
                    if (obj->box.overlaps(target->box)){
                        zombie->Damage(bullet->GetDamage());
                        obj->RequestDelete();
                        break;
                    }
                }
            }
        }
    }

    for (size_t i=0; i<objectArray.size();){
        if (objectArray[i]->IsDead()){
            if (objectArray[i].get() == Camera::GetFocus()) Camera::Unfollow();
            objectArray.erase(objectArray.begin() + (long)i);
        } else ++i;
    }
}

void State::Render(){
    for (auto& obj : objectArray) obj->Render();
}

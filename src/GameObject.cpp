// ========================================
// src/GameObject.cpp
// ========================================
#include "GameObject.h"
#include <algorithm>
#include <utility>


GameObject::GameObject() = default;


GameObject::~GameObject() = default;


void GameObject::AddComponent(std::shared_ptr<Component> cpt){
    components.push_back(std::move(cpt));
    if (started && components.back() && !components.back()->Started()) {
        components.back()->Start();
    }
}

void GameObject::AddComponent(Component* cpt){
    AddComponent(std::shared_ptr<Component>(cpt));
}


void GameObject::RemoveComponent(Component* cpt){
    auto it = std::remove_if(components.begin(), components.end(),
        [cpt](const std::shared_ptr<Component>& c){ return c.get() == cpt; });
    components.erase(it, components.end());
}


void GameObject::Start(){
    if (started) return;
    for (auto& c : components){
        if (c && !c->Started()) c->Start();
    }
    started = true;
}


void GameObject::Update(float dt){
    if (!started) Start();
    for (auto& c : components) {
        if (c) c->Update(dt);
    }
}


void GameObject::Render(){
    for (auto& c : components) {
        if (c) c->Render();
    }
}
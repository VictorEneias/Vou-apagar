// ========================================
// src/GameObject.cpp
// ========================================
#include "GameObject.h"
#include <algorithm>


GameObject::GameObject() = default;


GameObject::~GameObject(){
for (int i=(int)components.size()-1; i>=0; --i) {
delete components[(size_t)i];
}
components.clear();
}


void GameObject::AddComponent(Component* cpt){
components.push_back(cpt);
}


void GameObject::RemoveComponent(Component* cpt){
auto it = std::find(components.begin(), components.end(), cpt);
if (it != components.end()) components.erase(it);
}


void GameObject::Update(float dt){
for (auto* c : components) c->Update(dt);
}


void GameObject::Render(){
for (auto* c : components) c->Render();
}
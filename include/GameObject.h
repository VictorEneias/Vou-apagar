// ========================================
// include/GameObject.h
// ========================================
#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include "Rect.h"
#include "Component.h"


class GameObject {
public:
GameObject();
~GameObject();


void Update(float dt);
void Render();


bool IsDead() const { return isDead; }
void RequestDelete() { isDead = true; }


void AddComponent(Component* cpt);
void RemoveComponent(Component* cpt);


template <class T>
T* GetComponent();


Rect box; // posição/tamanho


private:
std::vector<Component*> components;
bool isDead{false};
};


// Template no header
template <class T>
T* GameObject::GetComponent() {
for (auto* c : components) {
if (auto* casted = dynamic_cast<T*>(c)) return casted;
}
return nullptr;
}
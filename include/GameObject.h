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
#include "Vec2.h"


class GameObject {
public:
    GameObject();
    ~GameObject();

    void Start();
    void Update(float dt);
    void Render();

    bool IsDead() const { return isDead; }
    void RequestDelete() { isDead = true; }

    void AddComponent(std::shared_ptr<Component> cpt);
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    template <class T>
    std::shared_ptr<T> GetComponent();

    Rect box; // posição/tamanho
    float angleDeg{0.f};
    Vec2 scale{1.f, 1.f};

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead{false};
    bool started{false};
};


// Template no header
template <class T>
std::shared_ptr<T> GameObject::GetComponent() {
    for (auto& c : components) {
        if (auto casted = std::dynamic_pointer_cast<T>(c)) return casted;
    }
    return nullptr;
}
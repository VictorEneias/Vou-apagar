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

    void Start();
    void LoadAssets();
    void Update(float dt);
    void Render();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    bool QuitRequested() const { return quitRequested; }

private:
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested{false};
    bool started{false};
};
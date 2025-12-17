// ========================================
// include/Component.h
// ========================================
#pragma once
class GameObject;


class Component {
public:
    explicit Component(GameObject& associated) : associated(associated) {}
    virtual ~Component() = default;

    virtual void Start();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    bool Started() const { return started; }

protected:
    GameObject& associated;
    bool started{false};
};

// inline default Start
inline void Component::Start() { started = true; }
#pragma once
#include "Component.h"
#include "Camera.h"

class CameraFollower : public Component{
public:
  explicit CameraFollower(GameObject& go):Component(go){}
  void Update(float) override {
    associated.box.x = Camera::posX;
    associated.box.y = Camera::posY;
  }
  void Render() override {}
};

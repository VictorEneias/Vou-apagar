#pragma once
class GameObject;

class Camera{
public:
  static void Follow(GameObject* go);
  static void Unfollow();
  static GameObject* GetFocus();
  static void Update(float dt);
  static float posX, posY;
private:
  static GameObject* focus;
};

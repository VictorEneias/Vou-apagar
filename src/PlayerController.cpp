#include "PlayerController.h"
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"
#include <SDL2/SDL.h>

PlayerController::PlayerController(GameObject& go, std::weak_ptr<Character> c)
: Component(go), character(std::move(c)) {}

void PlayerController::Update(float dt){
    (void)dt;
    auto ch = character.lock();
    if (!ch) { associated.RequestDelete(); return; }

    auto& input = InputManager::GetInstance();
    Vec2 dir{0.f, 0.f};
    if (input.IsKeyDown(SDL_SCANCODE_W)) dir.y -= 1.f;
    if (input.IsKeyDown(SDL_SCANCODE_S)) dir.y += 1.f;
    if (input.IsKeyDown(SDL_SCANCODE_A)) dir.x -= 1.f;
    if (input.IsKeyDown(SDL_SCANCODE_D)) dir.x += 1.f;

    ch->EnqueueCommand([dir](Character& c, float){ c.Move(dir); });

    Vec2 mouseWorld{ Camera::posX + (float)input.GetMouseX(), Camera::posY + (float)input.GetMouseY() };
    ch->EnqueueCommand([mouseWorld](Character& c, float){ c.AimAt(mouseWorld); });

    if (input.MousePress(SDL_BUTTON_LEFT)){
        ch->EnqueueCommand([mouseWorld](Character& c, float){ c.Shoot(mouseWorld); });
    }
    if (input.MousePress(SDL_BUTTON_RIGHT)){
        ch->EnqueueCommand([](Character& c, float){ c.Reload(); });
    }
}

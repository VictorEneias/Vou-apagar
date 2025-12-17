#pragma once
#include <SDL2/SDL.h>
#include <array>

class InputManager {
public:
  static InputManager& GetInstance(){ static InputManager i; return i; }

  void Update(){
    keyDown.fill(false); keyUp.fill(false);
    mouseDown.fill(false); mouseUp.fill(false);
    SDL_Event e;
    while (SDL_PollEvent(&e)){
      switch(e.type){
        case SDL_QUIT: quitReq = true; break;
        case SDL_KEYDOWN:
          if(!e.key.repeat){
            keyState[e.key.keysym.scancode]=true;
            keyDown[e.key.keysym.scancode]=true;
          }
          break;
        case SDL_KEYUP:
          keyState[e.key.keysym.scancode]=false;
          keyUp[e.key.keysym.scancode]=true;
          break;
        case SDL_MOUSEMOTION:
          mouseX=e.motion.x; mouseY=e.motion.y; break;
        case SDL_MOUSEBUTTONDOWN:{
          int b=e.button.button;
          if(b>=0 && b<(int)mouseState.size()){
            mouseState[b]=true; mouseDown[b]=true;
          }
          break;
        }
        case SDL_MOUSEBUTTONUP:{
          int b=e.button.button;
          if(b>=0 && b<(int)mouseState.size()){
            mouseState[b]=false; mouseUp[b]=true;
          }
          break;
        }
      }
    }
  }

  bool QuitRequested() const { return quitReq; }
  bool KeyPress   (SDL_Scancode sc) const { return keyDown[sc]; }
  bool KeyRelease (SDL_Scancode sc) const { return keyUp[sc]; }
  bool IsKeyDown  (SDL_Scancode sc) const { return keyState[sc]; }

  bool MousePress (int b) const { return b>=0 && b<(int)mouseDown.size() && mouseDown[b]; }
  bool MouseRelease(int b) const{ return b>=0 && b<(int)mouseUp.size() && mouseUp[b]; }
  bool IsMouseDown(int b) const { return b>=0 && b<(int)mouseState.size() && mouseState[b]; }

  int GetMouseX() const { return mouseX; }
  int GetMouseY() const { return mouseY; }

private:
  InputManager() = default;

  std::array<bool, SDL_NUM_SCANCODES> keyDown{}, keyUp{}, keyState{};
  std::array<bool, 8> mouseDown{}, mouseUp{}, mouseState{};
  int mouseX{0}, mouseY{0};
  bool quitReq{false};
};

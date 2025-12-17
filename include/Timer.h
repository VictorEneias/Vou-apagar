#pragma once
class Timer{
public:
  void Update(float dt){ t+=dt; }
  void Restart(){ t=0.f; }
  float Get() const { return t; }
  bool TimeOut(float lim) const { return t>=lim; }
private:
  float t{0.f};
};

#pragma once

#include "Constants.h"
#include "../lib/glm/glm.hpp"

class Player
{
private:
public:
  glm::vec2 target;
  glm::vec2 position;
  glm::vec2 velocity;
  int size;
  bool isActive;

  Player();
  void SetVelocity(int x, int y);
  void UpdatePosition(int x, int y);
  void Update(float deltaTime);
  void Kill();
  bool IsActive() const;
};

#pragma once

#include "../lib/glm/glm.hpp"


class Bullet
{
private:
public:
  glm::vec2 target;
  glm::vec2 position;
  glm::vec2 velocity;
  int size;
  bool isActive;

  Bullet(float x, float y, float posX, float posY, int size);
  void Update(float deltaTime);
  void Kill();
  bool IsActive() const;
};

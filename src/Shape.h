#pragma once

#include "Random.h"

#include "../lib/glm/glm.hpp"

class Shape
{
private:
  bool isActive;

public:
  glm::vec2 position;
  glm::vec2 velocity;
  int height;
  int width;
  int red;
  int green;
  int blue;
  Shape(Random* random, float prevPosX, float prevPosY, glm::vec2& playerPos);
  void Update(float deltaTime);
  void Kill();
};

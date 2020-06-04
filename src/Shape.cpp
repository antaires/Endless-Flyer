#include "Shape.h"
#include "Constants.h"
#include <cmath>

Shape::Shape(Random* random, float prevPos)
{
  // prevent shapes spawning over other shapes
  float xOrigin = prevPos;
  while (std::abs(xOrigin - prevPos) < BRICK_SIZE * 5)
  {
    xOrigin = random->GetRand(0, WINDOW_WIDTH - BRICK_SIZE);
  }

  red   = (int) random->GetRand(0, 255);
  green = (int) random->GetRand(0, 255);
  blue  = (int) random->GetRand(0, 255);

  isActive = true;
  // todo use these ?
  //bool rotate    = (int) random->GetRand(0, 1);
  //bool mirror    = (int) random->GetRand(0, 1);
}

void Shape::Kill()
{
  isActive = false;
}

void Shape::Update(float deltaTime)
{
  // update shape bounding box
  float tempX = position.x + velocity.x * deltaTime;
  float tempY = position.y + velocity.y * deltaTime;

  // TODO update for horizontal movement
  if (tempY >= WINDOW_HEIGHT + height)
  {
    tempY = WINDOW_HEIGHT + height;
  }
  position.x = tempX;
  position.y = tempY;
}

#include "Shape.h"
#include "Constants.h"
#include <cmath>

#include <iostream>

Shape::Shape(Random* random, float prevPos)
{
  // prevent shapes spawning over other shapes
  float yOrigin = prevPos;


  height = random->GetRand(30, 70);
  width  = height;

  while (std::abs(yOrigin - prevPos) < height * 5)
  {
    yOrigin = random->GetRand(0, WINDOW_HEIGHT - height);
  }

  red   = (int) random->GetRand(0, 255);
  green = (int) random->GetRand(0, 255);
  blue  = (int) random->GetRand(0, 255);

  isActive = true;
  // todo use these ?
  //bool rotate    = (int) random->GetRand(0, 1);
  //bool mirror    = (int) random->GetRand(0, 1);
  position.x = WINDOW_WIDTH - width;
  position.y = yOrigin;

  velocity.x = (int) random->GetRand(10, 100) * -1;
  velocity.y = 0;
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

  if (tempX <= 0 + height)
  {
    isActive = false;
  }

  position.x = tempX;
  position.y = tempY;
}

#include "Shape.h"
#include "Constants.h"
#include <cmath>

#include <iostream>

Shape::Shape(Random* random, float prevPosX, float prevPosY, glm::vec2& playerPos)
{
  // prevent shapes spawning over other shapes
  float xOrigin = prevPosX;
  float yOrigin = prevPosY;

  height = random->GetRand(30, 100);
  width  = height;

  red   = (int) random->GetRand(0, 255);
  green = (int) random->GetRand(0, 255);
  blue  = (int) random->GetRand(0, 255);

  isActive = true;
  // todo use these ?
  //bool rotate    = (int) random->GetRand(0, 1);
  //bool mirror    = (int) random->GetRand(0, 1);

  // TODO put in functions
  /*
  while (std::abs(yOrigin - prevPosY) < height * 5)
  {
    yOrigin = random->GetRand(0, WINDOW_HEIGHT - height);
  }

  while (std::abs(xOrigin - prevPosX) < width * 5)
  {
    xOrigin = random->GetRand(0, WINDOW_WIDTH - width);
  }*/

  // TODO randomly, either x or y == 0 or height/width
  bool side = (int) random->GetRand(0, 4);
  if (side == 0)
  {
    position.x = WINDOW_WIDTH - width;
    position.y = random->GetRand(0, WINDOW_HEIGHT - height);
  } else if (side == 1){
    position.x = 0;
    position.y = random->GetRand(0, WINDOW_HEIGHT - height);
  } else if (side == 2){
    position.x = random->GetRand(0, WINDOW_WIDTH - width);
    position.y = WINDOW_HEIGHT - height;
  } else {
    position.x = random->GetRand(0, WINDOW_WIDTH - width);
    position.y = 0;
  }

  velocity = playerPos - position;
  //velocity.x = (int) random->GetRand(10, 100) * -1;
  //velocity.y = 0;
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

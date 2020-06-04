#include "Bullet.h"
#include "Constants.h"

#include <iostream>

Bullet::Bullet(float x, float y, int size): size(size)
{
  isActive = true;

  target.x = x;
  target.y = y;

  position.x = (float) (WINDOW_WIDTH / 2);
  position.y = (float) WINDOW_HEIGHT;

  velocity = glm::normalize(target-position);
}

void Bullet::Update(float deltaTime)
{
  position.x = (position.x + (velocity.x * BULLET_SPEED) * deltaTime);
  position.y = (position.y + (velocity.y * BULLET_SPEED) * deltaTime);

  // if position x or y offscreen, turn off bullet
  if (position.x > WINDOW_WIDTH
    || position.x < 0
    || position.y > WINDOW_HEIGHT
    || position.y < 0)
    {
      isActive = false;
    }
}

void Bullet::Kill()
{
  isActive = false;
}

bool Bullet::IsActive() const
{
  return isActive;
}

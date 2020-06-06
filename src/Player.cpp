#include "Player.h"

Player::Player()
{
  position.x = WINDOW_WIDTH / 2;
  position.y = WINDOW_HEIGHT / 2;
  velocity.x = 0; velocity.y = 0;
  size = PLAYER_SIZE;
}

void Player::SetVelocity(int x, int y)
{
  velocity.x = x;
  velocity.y = y;
}

void Player::Update(float deltaTime)
{
  position.x = (position.x + (velocity.x * SHIP_SPEED) * deltaTime);
  position.y = (position.y + (velocity.y * SHIP_SPEED) * deltaTime);
}

void Player::Kill()
{
    isActive = false;
}

bool Player::IsActive() const
{
  return isActive;
}

#pragma once

#include "Constants.h"
#include "Bullet.h"
#include "Shape.h"
#include "Player.h"
#include "Random.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Board {
private:
  Player* player;
  Random* random;
  float lastShapeSpawnPositionX;
  float lastShapeSpawnPositionY;
  // TODO: make smart pointers
  std::unordered_map<Shape*, Shape*> shapes;
  std::unordered_map<Bullet*, Bullet*> bullets;
  std::unordered_map<Bullet*, Bullet*> bulletsToRemove;
  std::unordered_map<Shape*, Shape*> shapesToRemove;

  bool CollisionShape(Shape* shape, Bullet* bullet) const;
  void RemoveDeadBullets();
  void RemoveDeadShapes();
public:
  Board(Random* random);
  ~Board();
  void Update(float deltaTime);
  Shape* SpawnShape();
  Shape* SpawnShapeExplosion(int size, glm::vec2& pos, glm::vec2& target);
  void FireBullet(int x, int y);
  void MoveShip(int x, int y);
  void CheckCollisions();

  std::unordered_map<Shape*, Shape*> GetShapes() const;
  std::unordered_map<Bullet*, Bullet*> GetBullets() const;
  Player* GetPlayer() const;
};

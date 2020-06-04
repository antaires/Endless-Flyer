#pragma once

#include "Constants.h"
#include "Bullet.h"
#include "Shape.h"
#include "Random.h"

#include <iostream>
#include <vector>
#include <unordered_map>

class Board {
private:
  float lastShapeSpawnPosition;
  // TODO: make smart pointers
  std::unordered_map<Shape*, Shape*> shapes;
  std::unordered_map<Bullet*, Bullet*> bullets;
  std::unordered_map<Bullet*, Bullet*> bulletsToRemove;
  std::unordered_map<Shape*, Shape*> shapesToRemove;

  bool CollisionShape(Shape* shape, Bullet* bullet) const;
  void RemoveDeadBullets();
  void RemoveDeadShapes();
public:
  Board();
  ~Board();
  void Update(float deltaTime);
  Shape* SpawnShape(Random* random);
  void FireBullet(int x, int y);
  void CheckCollisions();

  std::unordered_map<Shape*, Shape*> GetShapes() const;
  std::unordered_map<Bullet*, Bullet*> GetBullets() const;
};

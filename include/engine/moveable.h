#pragma once
#include "engine/node.h"
#include "game/utils.h"

namespace engine
{
class Moveable : public Node
{
public:
  Vector2 startPosition;
  Vector2 targetPosition;

  float moveTime = 0;
  float moveDuration = 0;

  bool following = false;
  Vector2 followTarget;
  float followSpeed = 20.f;

  Moveable(Transform transform): Node(transform){};
  
  void Move(Vector2 target);
  void Follow(Vector2 target);
  virtual void Update(float dt) override;
};
}
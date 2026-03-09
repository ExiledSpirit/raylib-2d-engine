#pragma once
#include "engine/node.h"
#include "game/utils.h"

namespace engine
{
class Moveable : public Node
{
public:
  bool dragging = false;
  float dragFollowSpeed = 15.f;
  Vector2 clickOffset;
  Vector2 originalPosition;
  Node* originalContainer = nullptr;

  Vector2 startPosition;
  Vector2 targetPosition;

  float moveTime = 0;
  float moveDuration = 0;

  bool following = false;
  Vector2 followTarget;
  float followSpeed = 20.f;

  Moveable(Transform transform, engine::RenderResources renderResources): Node(transform, renderResources){};
  
  void Move(Vector2 target);
  void EndMove();
  void Follow(Vector2 target);
  void StartDrag(Vector2 mouse);
  void StopDrag();
  virtual void Update(float dt) override;
};
}
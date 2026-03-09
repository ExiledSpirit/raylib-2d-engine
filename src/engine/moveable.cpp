#include "engine/moveable.h"
#include "game/utils.h"
#include "external/reasings.h"
#include <algorithm>
#include <iostream>

namespace engine
{

void Moveable::Move(Vector2 target)
{
  layer = 1;
  following = false;
  dragging = false;
  // if (target.x == this->targetPosition.x && target.y == this->targetPosition.y) return;
  
  this->startPosition = transform.position;
  this->targetPosition = target;

  this->moveTime = 0.0f;
}

void Moveable::EndMove()
{
  this->layer = 0;
}

void Moveable::Update(float dt)
{
  if (dragging)
  {
    Vector2 mouse = GetMousePosition();

    Vector2 target = {
      mouse.x - clickOffset.x,
      mouse.y - clickOffset.y
    };

    transform.position = Vector2Lerp(
      transform.position,
      target,
      dt * dragFollowSpeed
    );

    return;
  }
  if (following)
  {
    transform.position = Vector2Lerp(
      transform.position,
      followTarget,
      dt * followSpeed
    );
    return;
  }
  this->moveTime = std::min<float>(this->moveTime + dt, 1.0f);

  if (this->moveTime == 1.0f) {
    this->EndMove();
    return;
  }

  float x = EaseCubicOut(
    this->moveTime,
    this->startPosition.x,
    this->targetPosition.x - this->startPosition.x,
    1
  );
  float y = EaseCubicOut(
    this->moveTime,
    this->startPosition.y,
    this->targetPosition.y - this->startPosition.y,
    1
  );
  this->transform.position = {x, y};
}

void Moveable::Follow(Vector2 target) {
  this->followTarget = target;
  this->following = true;
}

void Moveable::StartDrag(Vector2 mouse)
{
  std::cout << "Drag started\n";
  layer = 1;
  dragging = true;

  clickOffset = {
    mouse.x - transform.position.x,
    mouse.y - transform.position.y
  };

  originalPosition = targetPosition;
  originalContainer = container;

  moveTime = 1.0f;
}

void Moveable::StopDrag()
{
  layer = 0;
  dragging = false;
  std::cout << "Drag stopped\n" << "original.x=" << originalPosition.x << "original.y=" << originalPosition.y << "\n";
  Move(originalPosition);
}

}
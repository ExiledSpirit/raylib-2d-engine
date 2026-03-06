#include "engine/moveable.h"
#include "game/utils.h"
#include "external/reasings.h"
#include <algorithm>

namespace engine
{

void Moveable::Move(Vector2 target)
{
  following = false;
  if (target.x == this->targetPosition.x && target.y == this->targetPosition.y) return;
  
  this->startPosition = transform.position;
  this->targetPosition = target;

  this->moveTime = 0.0f;
}

void Moveable::Update(float dt)
{
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

  float x = EaseCubicInOut(
    this->moveTime,
    this->startPosition.x,
    this->targetPosition.x - this->startPosition.x,
    1
  );
  float y = EaseCubicInOut(
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

}
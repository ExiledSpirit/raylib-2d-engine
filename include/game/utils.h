#include "game/card.h"
#include "raymath.h"

namespace game
{

class Utils
{
public:
  static float SmoothLerp(float current, float target, float dt, float speed)
  {
      float value = Lerp(current, target, dt * speed);

      if (fabs(value - target) < 0.01f)
          value = target;

      return value;
  }
};

}
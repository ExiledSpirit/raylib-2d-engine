#include "engine/shader_instance.h"
#include "engine/node.h"
#include "raymath.h"
#include "iostream"

namespace engine
{

void ShaderInstance::Update(Node* node)
{
  float hovering = node->hover.is ? 1.0f : 0.0f;

  if (hoverLoc != -1)
    SetShaderValue(shader, hoverLoc, &hovering, SHADER_UNIFORM_FLOAT);

  float tiltValues[2] = {0.0f, 0.0f};

  if (node->hover.is)
  {
    Vector2 mouse = GetMousePosition();
    Vector2 center = node->transform.position;

    Vector2 delta = {
      mouse.x - center.x,
      mouse.y - center.y
    };

    tiltValues[0] = Clamp(delta.x / (node->transform.size.x * 0.5f), -1.0f, 1.0f);
    tiltValues[1] = Clamp(delta.y / (node->transform.size.y * 0.5f), -1.0f, 1.0f);
  }

  if (tiltLoc != -1)
    SetShaderValue(shader, tiltLoc, tiltValues, SHADER_UNIFORM_VEC2);
}
}
#pragma once
#include "raylib.h"

namespace engine
{

class Node;

class ShaderInstance
{
public:

  Shader shader;

  int tiltLoc = -1;
  int hoverLoc = -1;
  int cardSizeLoc = -1;

  void Init(const char* vs, const char* fs)
  {
      shader = LoadShader(vs, fs);

      tiltLoc = GetShaderLocation(shader, "tilt");
      hoverLoc = GetShaderLocation(shader, "hover");
  }

  void Update(Node* node);
};

}

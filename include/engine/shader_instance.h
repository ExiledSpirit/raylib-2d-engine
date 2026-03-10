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
  int timeLoc = -1;
  int resolutionLoc = -1;

  void Init(const char* vs, const char* fs)
  {
      shader = LoadShader(vs, fs);

      timeLoc = GetShaderLocation(shader, "iTime");
      resolutionLoc = GetShaderLocation(shader, "iResolution");
      tiltLoc = GetShaderLocation(shader, "tilt");
      hoverLoc = GetShaderLocation(shader, "hover");
  }

  void Update(Node* node);
};

}

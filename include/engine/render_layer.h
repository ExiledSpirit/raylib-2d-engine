#pragma once

namespace engine
{

enum class RenderLayer {
  BACKGROUND = 0,
  ZONE = 10,
  CARD = 20,
  MOVING = 30,
  HOVERING = 40,
  DRAGGING = 40
};

}
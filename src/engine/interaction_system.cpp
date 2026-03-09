#include "engine/interaction_system.h"
#include "engine/moveable.h"

namespace engine
{
void InteractionSystem::Update(std::vector<Node*>& nodes)
{
  Vector2 mouse = GetMousePosition();

  Node* hovered = nullptr;

  // iterate in reverse draw order
  for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
  {
    Node* node = *it;

    if (node->CollidesWithPoint(mouse))
    {
      hovered = node;
      break;
    }
  }

  for (Node* node : nodes) {
    node->hover.is = false;
  }

  if (hovered)
    hovered->hover.is = true;

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    if (hovered)
    {
      auto* moveable = dynamic_cast<Moveable*>(hovered);

      if (moveable) {
        moveable->StartDrag(GetMousePosition());
        this->draggingNode = moveable;
      }
    }
  }
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
  {
    if (this->draggingNode) {
      this->draggingNode->StopDrag();
      this->draggingNode = nullptr;
    }
  }
}
}
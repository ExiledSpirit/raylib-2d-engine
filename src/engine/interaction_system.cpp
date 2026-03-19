#include "engine/interaction_system.h"
#include "engine/moveable.h"
#include <algorithm>

namespace engine
{

static void CollectNodes(Node* node, std::vector<Node*>& out)
{
  out.push_back(node);

  for (auto* child : node->children)
    CollectNodes(child, out);
}

void InteractionSystem::Update(std::vector<Node*>& roots)
{
  Vector2 mouse = GetMousePosition();

  std::vector<Node*> nodes;

  for (auto* root : roots)
    CollectNodes(root, nodes);

  std::stable_sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
    return a->layer < b->layer;
  });

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

  if (hovered) {
    TraceLog(LOG_INFO, "%d", hovered->layer);
    hovered->hover.is = true;
  }

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

      // Notify drop targets
      // for (Node* node : nodes)
      //   if (node->CollidesWithPoint(mouse))
      //     node->OnRelease(draggingNode);
      this->draggingNode = nullptr;
    }
  }
}
}
#include "engine/interaction_system.h"

namespace engine
{

void InteractionSystem::Update(std::vector<Node*>& nodes)
{
    Vector2 mouse = GetMousePosition();

    TraceLog(LOG_INFO, "Mouse: (%.2f, %.2f)", mouse.x, mouse.y);
    Node* newHovered = nullptr;

    // iterate in reverse render order (top first)
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it)
    {
        Node* node = *it;

        if (!node->hover.can)
            continue;

        if (node->CollidesWithPoint(mouse))
        {
            TraceLog(LOG_INFO, "Collides!");
            newHovered = node;
            break;
        }
    }

    if (hovered != newHovered)
    {
        if (hovered)
            hovered->hover.is = false;

        hovered = newHovered;

        if (hovered)
            hovered->hover.is = true;
    }
}

}
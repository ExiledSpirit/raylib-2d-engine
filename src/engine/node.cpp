#include "engine/node.h"
#include <cmath>

namespace engine
{

void Node::Update(float dt)
{

}

void Node::Draw(RenderQueue& queue)
{
  queue.Submit(this, this->layer);
  for (size_t i = 0; i < this->children.size(); i++)
  {
    children.at(i)->Draw(queue);
  }
}

void Node::SetContainer(Node* newContainer)
{
    container = newContainer;
    newContainer->children.push_back(this);
}

bool Node::CollidesWithPoint(Vector2 point)
{
    Vector2 renderPos = {
        transform.position.x,
        transform.position.y - lift
    };

    Vector2 center = {
        renderPos.x,
        renderPos.y
    };

    Vector2 local = {
        point.x - center.x,
        point.y - center.y
    };

    float cosR = cosf(-transform.rotation * DEG2RAD);
    float sinR = sinf(-transform.rotation * DEG2RAD);

    Vector2 rotated = {
        local.x * cosR - local.y * sinR,
        local.x * sinR + local.y * cosR
    };

    float halfW = transform.size.x * 0.5f;
    float halfH = transform.size.y * 0.5f;

    return rotated.x >= -halfW &&
           rotated.x <=  halfW &&
           rotated.y >= -halfH &&
           rotated.y <=  halfH;
}

void Node::Release(bool dragged)
{

}
void Node::Click()
{

}
void Node::Animate()
{

}
void Node::Remove()
{

}
void Node::Hover()
{

}
void Node::StopHover()
{

}
void Node::StopDrag()
{

}
bool CanDrag()
{

}
void Node::Drag()
{

}
}
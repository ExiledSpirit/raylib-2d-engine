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

bool Node::CollidesWithPoint(Vector2 point)
{
    // 1️⃣ Get actual rendered position (including lift)
    Vector2 renderPos = {
        transform.position.x,
        transform.position.y - lift   // IMPORTANT
    };

    // 2️⃣ Compute center (origin used in DrawTexturePro)
    Vector2 center = {
        renderPos.x,
        renderPos.y
    };

    // 3️⃣ Move mouse into local space
    Vector2 local = {
        point.x - center.x,
        point.y - center.y
    };

    // 4️⃣ Apply inverse rotation
    float cosR = cosf(-transform.rotation * DEG2RAD);
    float sinR = sinf(-transform.rotation * DEG2RAD);

    Vector2 rotated = {
        local.x * cosR - local.y * sinR,
        local.x * sinR + local.y * cosR
    };

    // 5️⃣ Check inside unrotated bounds
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
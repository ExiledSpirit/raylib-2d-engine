#pragma once
#include "engine/object.h"
#include "engine/render_queue.h"
#include <vector>
#include "raylib.h"

namespace engine
{

struct HoverState {
  bool can = true;
  bool is = false;
};

struct Transform {
    Vector2 position {0, 0};
    Vector2 size {0, 0};
    float rotation = 0.0f;
    float scale = 1.0f;
};

class Node : public Object
{
public:
  virtual ~Node() = default;
  Node(Transform transform): transform(transform), scale(transform.scale) {}
  void Draw(RenderQueue& queue);
  virtual void Render() = 0;

  Transform transform;
  int layer = 0;
  bool visible = true;
  float lift = 0.f;
  float targetLift = 0.f;

  float tilt = 0.f;
  float targetTilt = 0.f;

  float scale = 1.f;
  float targetScale = 1.f;

  std::vector<Node*> children;

  virtual void Update(float dt);
  void Release(bool dragged);
  void Click();
  void Animate();
  void Remove();
  void Hover();
  void StopHover();
  void StopDrag();
  bool CanDrag();
  void Drag();
  HoverState hover;
  virtual bool CollidesWithPoint(Vector2 point);
};

}
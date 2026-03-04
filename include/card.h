#pragma once
#include "engine/node.h"

class Card : public engine::Node
{
public:
  Card(Texture2D texture, engine::Transform transform): texture(texture), engine::Node(transform) {}

  void Render() override;
  void Update(float dt) override;
  bool CollidesWithPoint(Vector2 point) override;
private:
  Texture2D texture;
  float targetLift;
};
#pragma once
#include "engine/node.h"
#include "engine/render_resources.h"
#include "engine/render_layer.h"

namespace game
{

class Background : public engine::Node
{

public:
  Texture2D texture;
  Background(engine::Transform transform, Texture2D texture, engine::RenderResources renderResources)
    : texture(texture), Node(transform, renderResources)
  {
    hover.can = false;
    layer = engine::RenderLayer::BACKGROUND;
  }

  void Render() override
  {
    DrawTextureRec(texture, 
      (Rectangle){ 0, 0, (float)texture.width, (float)-texture.height }, 
      (Vector2){ 0, 0 }, WHITE);
  }

  void Update(float dt) override
  {

  }
};

}
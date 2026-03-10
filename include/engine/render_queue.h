#pragma once
#include "engine/render_layer.h"
#include <map>
#include <vector>

namespace engine
{

class Node;

class RenderQueue
{
public:
  void Submit(Node* node, RenderLayer layer);
  void Flush();
  void Clear();

private:
  std::map<RenderLayer, std::vector<Node*>> layers = std::map<RenderLayer, std::vector<Node*>>();
};

}
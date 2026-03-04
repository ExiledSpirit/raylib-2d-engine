#include "engine/render_queue.h"
#include "engine/node.h"
#include "iostream"

namespace engine
{

void RenderQueue::Submit(Node* node, int layer)
{
  std::cout << "renderqueue: submit" << std::endl;
  layers[layer].push_back(node);
}

void RenderQueue::Flush()
{
  for (auto& [layer, nodes]: layers)
  {
  std::cout << "renderqueue: rendering" << std::endl;
    for (Node* node : nodes)
    {
      std::cout << "renderqueue: rendering" << std::endl;
      node->Render();
    }
  }
}

void RenderQueue::Clear()
{
  layers.clear();
}
 
}
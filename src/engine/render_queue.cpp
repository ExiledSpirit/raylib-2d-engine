#include "engine/render_queue.h"
#include "engine/node.h"
#include "engine/moveable.h"
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
  Node* draggingNode = nullptr;
  for (auto& [layer, nodes]: layers)
  {
  std::cout << "renderqueue: rendering" << std::endl;
    for (Node* node : nodes)
    {
      engine::Moveable* moveable = (engine::Moveable*)node;
      if (moveable->following) 
      {
        draggingNode = moveable;
        continue;
      }
      std::cout << "renderqueue: rendering" << std::endl;
      node->Render();
    }
  }

  if (draggingNode)
  {
    draggingNode->Render();
  }
}

void RenderQueue::Clear()
{
  layers.clear();
}
 
}
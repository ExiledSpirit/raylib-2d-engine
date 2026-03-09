#include "engine/render_queue.h"
#include "engine/shader_instance.h"
#include "engine/node.h"
#include "engine/moveable.h"
#include "iostream"

namespace engine
{

void RenderQueue::Submit(Node* node, int layer)
{
  layers[layer].push_back(node);
}

void RenderQueue::Flush()
{
  ShaderInstance* currentShader = nullptr;
  Node* draggingNode = nullptr;

  for (auto& [layer, nodes] : layers)
  {
    for (Node* node : nodes)
    {
      Moveable* moveable = dynamic_cast<Moveable*>(node);

      ShaderInstance* shader = node->renderResources.shaderInstance;

      if (shader != currentShader)
      {
        // if (currentShader)
        //   EndShaderMode();

        currentShader = shader;

        // if (currentShader)
        //   BeginShaderMode(currentShader->shader);
      }

      if (currentShader)
        currentShader->Update(node);

      node->Render();
    }
  }

  // if (currentShader)
  //   EndShaderMode();
}

void RenderQueue::Clear()
{
  layers.clear();
}
 
}
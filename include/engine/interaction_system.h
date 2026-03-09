#include "engine/node.h"
#include <vector>

namespace engine
{

class Moveable;

class InteractionSystem
{
public:
  Moveable* draggingNode = nullptr;
  void Update(std::vector<Node*>& nodes);
private:
  Node* hovered = nullptr;
};

}
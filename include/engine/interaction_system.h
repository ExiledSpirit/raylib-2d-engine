#include "engine/node.h"
#include <vector>

namespace engine
{

class InteractionSystem
{
public:
  void Update(std::vector<Node*>& nodes);
private:
  Node* hovered = nullptr;
};

}
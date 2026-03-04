#pragma once
#include <map>
#include <vector>

namespace engine
{

class Node;

class RenderQueue
{
public:
  void Submit(Node* node, int layer);
  void Flush();
  void Clear();

private:
  std::map<int, std::vector<Node*>> layers = std::map<int, std::vector<Node*>>();
};

}
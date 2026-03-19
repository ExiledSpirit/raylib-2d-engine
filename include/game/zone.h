#pragma once
#include "engine/node.h"
#include <vector>

namespace game
{

class Card;

class Zone : public engine::Node
{
public:
  std::vector<Card*> cards;

  Zone(engine::Transform transform);

  virtual void AddCard(Card* card);
  virtual void RemoveCard(Card* card);
  void Update(float dt) override;
  void Render() override {}

  virtual void Layout(); // Flex layout, should be called whenever cards are added/ rmeoved
  virtual bool AcceptCard(Card* card); // Should be overriten by zones that should accept only specific types of cards (like weapon zone)

};

}
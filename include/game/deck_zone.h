#pragma once
#include "game/zone.h"

namespace game
{

class DeckZone : public Zone
{
public:
  DeckZone(engine::Transform transform);

  void AddCard(Card* card) override;
  void Layout() override;
};

}
#pragma once
#include "game/zone.h"

namespace game
{

class DeckZone : public Zone
{
public:
  DeckZone(engine::Transform transform);

  void Layout() override;
};

}
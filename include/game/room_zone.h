#pragma once
#include "game/zone.h"

namespace game
{

class RoomZone : public Zone
{
public:
  RoomZone(engine::Transform transform);

  void Layout() override;
};

}
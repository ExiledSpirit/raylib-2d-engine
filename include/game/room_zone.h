#pragma once
#include "game/zone.h"

namespace game
{

class RoomZone : public Zone
{
public:
  RoomZone(engine::Transform transform);

  void AddCard(Card* card) override;
  bool AcceptCard(Card* card) override;
  void Render() override;
  void Layout() override;
};

}
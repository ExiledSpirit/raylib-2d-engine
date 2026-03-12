#include "game/room_zone.h"
#include "game/card.h"

namespace game
{

RoomZone::RoomZone(engine::Transform transform)
  : Zone(transform)
{
}

void RoomZone::Layout() // should align horizontally with equal spacing
{
  float spacing = 240; // for now

  for (size_t i = 0; i < cards.size(); i++)
  {
    auto* card = cards[i];

    Vector2 pos = {
      transform.position.x + i * spacing,
      transform.position.y
    };

    card->Move(pos);
  }
}

}
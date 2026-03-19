#include "game/room_zone.h"
#include "game/card.h"
#include "raylib.h"

namespace game
{

RoomZone::RoomZone(engine::Transform transform)
  : Zone(transform)
{
}

void RoomZone::Layout() // should align horizontally with equal spacing
{
  float spacing = 80 * scale;

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

void RoomZone::AddCard(Card* card)
{
  card->Unflip();
  cards.push_back(card);
  card->container = this;
  this->children.push_back(card);

  Layout();
}

bool RoomZone::AcceptCard(Card* card)
{
  if (card == nullptr) return false;
  if (this->cards.size() >= 4) return false;

  return true;
}

void RoomZone::Render()
{
  float x = transform.position.x;
  float y = transform.position.y;
  float w = transform.size.x;
  float h = transform.size.y;
  DrawRectangleLines(x, y, w, h, WHITE);
}

}
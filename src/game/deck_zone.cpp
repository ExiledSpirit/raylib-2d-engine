#include "game/deck_zone.h"
#include "game/card.h"

namespace game
{

DeckZone::DeckZone(engine::Transform transform)
  : Zone(transform)
{
}

void DeckZone::Layout() // should stack vertically
{
  float spacing = -1; // Card stacking

  for (size_t i = 0; i < cards.size(); i++)
  {
    auto* card = cards[i];

    Vector2 pos = {
      transform.position.x,
      transform.position.y + i * spacing
    };

    card->Move(pos);
  }
}

void DeckZone::AddCard(Card* card)
{
  card->Flip();
  cards.push_back(card);
  card->container = this;

  Layout();
}

}
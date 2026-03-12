#include "game/zone.h"
#include "game/card.h"
#include <vector>
#include <bits/algorithmfwd.h>

namespace game
{

Zone::Zone(engine::Transform transform)
  : Node(transform)
{
  hover.can = false;
}

void Zone::AddCard(Card* card)
{
  cards.push_back(card);
  card->container = this;

  Layout();
}

void Zone::RemoveCard(Card* card)
{
  // cards.erase(
  //   std::remove(cards.begin(), cards.end(), card),
  //   cards.end()
  // );
}

bool Zone::AcceptCard(Card* card)
{
  return true;
}

void Zone::Layout()
{
  // Flex layout implementation
}

}

#pragma once
#include "engine/node.h"
#include "engine/moveable.h"

namespace game
{

enum struct CardEnhancement
{
    E_BACK=0,
    E_BLANK = 1,
    E_GOLD = 6
};

enum struct CardSuit
{
    HEARTH,
    CLUB,
    DIAMOND,
    SPADE
};

enum struct CardRank
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    J,
    Q,
    K,
    ACE
};

class Card : public engine::Moveable
{
public:
    Card(
        Texture2D& deckAtlas,
        Texture2D& enhancerAtlas,
        CardSuit suit,CardRank rank, CardEnhancement enhancement,
        engine::Transform transform,
        engine::RenderResources renderResources
    );

    void Render() override;
    void Update(float dt) override;
    bool CollidesWithPoint(Vector2 point) override;

    CardSuit suit;
    CardRank rank;
    CardEnhancement enhancement;

    bool isFlipped = false;
    void Flip();
    void Unflip();
private:
    Texture2D* deckAtlas;
    Texture2D* enhancerAtlas;
};

}

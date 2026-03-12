#include "game/card.h"
#include "game/utils.h"
#include "iostream"
#include <raymath.h>

namespace game
{
Card::Card(
    Texture2D& deckAtlas, 
    Texture2D& enhancerAtlas,
    CardSuit suit, CardRank rank, CardEnhancement enhancement,
    engine::Transform transform,
    engine::RenderResources renderResources
)
    : deckAtlas(&deckAtlas), enhancerAtlas(&enhancerAtlas), suit(suit), rank(rank), enhancement(enhancement), engine::Moveable(transform, renderResources) {}

void Card::Render()
{
    const int CARD_W = 71;
    const int CARD_H = 95;

    Rectangle dest = {
        transform.position.x,
        transform.position.y - lift,
        transform.size.x * scale,
        transform.size.y * scale
    };

    Vector2 origin = {
        dest.width * 0.5f,
        dest.height * 0.5f
    };

    float enhancement_w = (float)((isFlipped ? (int)CardEnhancement::E_BACK : (int)enhancement) * CARD_W);

    Rectangle enhancerSource = {
        enhancement_w,
        0,
        (float)CARD_W,
        (float)CARD_H
    };

    DrawTexturePro(
        *enhancerAtlas,
        enhancerSource,
        dest,
        origin,
        tilt,
        WHITE
    );

    if (isFlipped) return;

    Rectangle cardSource = {
        (float)((int)rank * CARD_W),
        (float)((int)suit * CARD_H),
        (float)CARD_W,
        (float)CARD_H
    };

    DrawTexturePro(
        *deckAtlas,
        cardSource,
        dest,
        origin,
        tilt,
        WHITE
    );
}

void Card::Update(float dt)
{
    this->engine::Moveable::Update(dt);
    Vector2 mouse = GetMousePosition();

    Vector2 center = {
        transform.position.x,
        transform.position.y
    };

    if (hover.is)
    {
        // Lift
        targetLift = 25.f;

        // Slight scale boost
        targetScale = transform.scale * 1.05f;

        // Calculate tilt based on mouse offset
        Vector2 delta = {
            mouse.x - center.x,
            mouse.y - center.y
        };

        float normalized = delta.x / (transform.size.x * 0.5f);
        normalized = Clamp(normalized, -1.f, 1.f);

        targetTilt = normalized * 12.f; // max 12 degrees
    }
    else
    {
        targetLift = 0.f;
        targetScale = transform.scale;
        targetTilt = 0.f;
    }

    // Smooth interpolation
    float speed = 10.f;

    lift  = Utils::SmoothLerp(lift, targetLift, dt, speed);
    tilt  = Utils::SmoothLerp(tilt, targetTilt, dt, speed);
    scale = Utils::SmoothLerp(scale, targetScale, dt, speed);
}

bool Card::CollidesWithPoint(Vector2 point)
{
    float buffer = hover.is ? 32.f : 0.f;

    Vector2 renderPos = {
        transform.position.x,
        transform.position.y - lift
    };

    Vector2 center = renderPos;

    Vector2 local = {
        point.x - center.x,
        point.y - center.y
    };

    float cosR = cosf(-tilt * DEG2RAD);
    float sinR = sinf(-tilt * DEG2RAD);

    Vector2 rotated = {
        local.x * cosR - local.y * sinR,
        local.x * sinR + local.y * cosR
    };

    float halfW = (transform.size.x * scale) * 0.5f + buffer;
    float halfH = (transform.size.y * scale) * 0.5f + buffer;

    return rotated.x >= -halfW &&
           rotated.x <=  halfW &&
           rotated.y >= -halfH &&
           rotated.y <=  halfH;
}

void Card::Flip()
{
    isFlipped = true;
}

void Card::Unflip()
{
    isFlipped = false;
}

}


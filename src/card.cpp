#include "card.h"
#include "iostream"
#include <raymath.h>
void Card::Render()
{
    Rectangle source = {
        0, 0,
        (float)texture.width,
        -(float)texture.height  // flip Y once
    };

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

    DrawTexturePro(
        texture,
        source,
        dest,
        origin,
        tilt,     // use animated tilt
        WHITE
    );
}
void Card::Update(float dt)
{
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
        targetScale = 1.05f;

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
        targetScale = 1.f;
        targetTilt = 0.f;
    }

    // Smooth interpolation
    float speed = 10.f;

    lift  = Lerp(lift,  targetLift,  dt * speed);
    tilt  = Lerp(tilt,  targetTilt,  dt * speed);
    scale = Lerp(scale, targetScale, dt * speed);
}

bool Card::CollidesWithPoint(Vector2 point)
{
    float buffer = hover.is ? 32.f : 0.f;   // 👈 padding

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
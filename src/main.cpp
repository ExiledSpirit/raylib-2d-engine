#include "game/card.h"
#include "engine/render_queue.h"
#include "engine/interaction_system.h"
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Balatro Prototype");
    SetTargetFPS(60);

    engine::RenderQueue queue = engine::RenderQueue();

    Shader balatroShader = LoadShader(0, "resources/shaders/menu_background.fs");
    float resolution[2] = { (float)160, (float)240 };

    Texture2D deckAtlas = LoadTexture("resources/textures/1x/8BitDeck.png");
    Texture2D enhancerAtlas = LoadTexture("resources/textures/1x/Enhancers.png");
    Vector2 position {100, 300};
    Vector2 size {71, 95};
    float rotation = 0.0f;
    float scale = 3.0f;


    game::Card card(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::HEARTH, game::CardRank::TWO,   // atlasX, atlasY
        game::CardEnhancement::E_BLANK,
        {.position = position, .size = size, .rotation = rotation, .scale = scale}
    );

    game::Card card2(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::DIAMOND, game::CardRank::J,    // another card sprite
        game::CardEnhancement::E_GOLD,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale}
    );

    game::Card card3(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::CLUB, game::CardRank::ACE,   // another card sprite
        game::CardEnhancement::E_BLANK,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale}
    );

    game::Card card4(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::SPADE, game::CardRank::K,   // another card sprite
        game::CardEnhancement::E_BLANK,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale}
    );

    engine::InteractionSystem interaction;
    std::vector<engine::Node*> nodes;
    nodes.push_back(&card);
    nodes.push_back(&card2);
    nodes.push_back(&card3);
    nodes.push_back(&card4);
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float time = (float)GetTime();

        queue.Clear();
        Vector2 mouse = GetMousePosition();
        interaction.Update(nodes);

        for (size_t i = 0; i < nodes.size(); i++)
        {
            auto* card = (game::Card*)nodes.at(i);
            card->Move({float(100 + i*250), 300});
            if (i==0) card->Follow(mouse);
            card->Update(dt);
            card->Draw(queue);
        }

        BeginDrawing();
            ClearBackground(DARKGREEN);

            queue.Flush();
        EndDrawing();
    }

    CloseWindow();
}
#include "game/card.h"
#include "game/background.h"
#include "engine/render_queue.h"
#include "engine/shader_instance.h"
#include "engine/interaction_system.h"
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Balatro Prototype");
    SetTargetFPS(60);

    engine::RenderQueue queue = engine::RenderQueue();

    Texture2D deckAtlas = LoadTexture("resources/textures/1x/8BitDeck.png");
    Texture2D enhancerAtlas = LoadTexture("resources/textures/1x/Enhancers.png");
    Vector2 position {100, 300};
    Vector2 size {71, 95};
    float rotation = 0.0f;
    float scale = 3.0f;

    engine::ShaderInstance *skewShaderInstance = new engine::ShaderInstance();
    engine::ShaderInstance *backgroundShaderInstance = new engine::ShaderInstance();

    skewShaderInstance->Init("resources/shaders/skew.vs", "resources/shaders/skew.fs");
    backgroundShaderInstance->Init(0, "resources/shaders/menu_background.fs");

    engine::RenderResources cardRenderResources = {
        .shaderInstance=nullptr
    };
    engine::RenderResources backgroundRenderResources = {
        .shaderInstance=backgroundShaderInstance
    };

    RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    game::Background background(
        {.position = position, .size = size, .rotation = rotation, .scale = scale}, target.texture, backgroundRenderResources
    );

    game::Card card(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::HEARTH, game::CardRank::TWO,   // atlasX, atlasY
        game::CardEnhancement::E_BLANK,
        {.position = position, .size = size, .rotation = rotation, .scale = scale},
        cardRenderResources
    );

    game::Card card2(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::DIAMOND, game::CardRank::J,    // another card sprite
        game::CardEnhancement::E_GOLD,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale},
        cardRenderResources
    );

    game::Card card3(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::CLUB, game::CardRank::ACE,   // another card sprite
        game::CardEnhancement::E_BLANK,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale},
        cardRenderResources
    );

    game::Card card4(
        deckAtlas,
        enhancerAtlas,
        game::CardSuit::SPADE, game::CardRank::K,   // another card sprite
        game::CardEnhancement::E_BLANK,
        {.position = {.x=position.x, .y=position.y}, .size = size, .rotation = rotation, .scale = scale},
        cardRenderResources
    );

    std::vector<engine::Node*> nodes;
    nodes.push_back(&background);
    nodes.push_back(&card);
    nodes.push_back(&card2);
    nodes.push_back(&card3);
    nodes.push_back(&card4);

    for (size_t i = 0; i < nodes.size(); i++)
    {
      game::Card* card =  dynamic_cast<game::Card*>(nodes.at(i));
      if (card)
        card->Move({float(100 + i*250), 300});
    }

    engine::InteractionSystem interaction;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        queue.Clear();
        interaction.Update(nodes);

        for (size_t i = 0; i < nodes.size(); i++)
        {
            game::Card* card =  dynamic_cast<game::Card*>(nodes.at(i));
            if (card) {
                card->Update(dt);
                card->Draw(queue);
                continue;
            }
            game::Background* background = dynamic_cast<game::Background*>(nodes.at(i));
            if (background) {
                background->Update(dt);
                background->Draw(queue);
            }
        }

        BeginDrawing();
            ClearBackground(DARKGREEN);

            queue.Flush();
        EndDrawing();
    }

    CloseWindow();
}
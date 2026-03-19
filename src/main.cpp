#include "game/card.h"
#include "game/deck_zone.h"
#include "game/room_zone.h"
#include "game/background.h"
#include "engine/render_queue.h"
#include "engine/shader_instance.h"
#include "engine/interaction_system.h"
#include "raylib.h"
#include <memory>
#include <algorithm>
#include <random>

void DrawRoomCard(game::DeckZone &deck, game::RoomZone &room)
{
  if (!room.AcceptCard(deck.GetNextCard())) return;

  room.AddCard(deck.DrawCard());
}

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
  float scale = 2.0f;

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

  std::vector<std::unique_ptr<game::Card>> cards;
  std::vector<engine::Node*> nodes;

  for (int suit = 0; suit < 4; suit++)
  {
    for (int rank = 0; rank < 13; rank++)
    {
      auto card = std::make_unique<game::Card>(
        deckAtlas,
        enhancerAtlas,
        (game::CardSuit)suit,
        (game::CardRank)rank,
        game::CardEnhancement::E_BLANK,
        engine::Transform{
          .position = {.x=position.x, .y=position.y},
          .size = size,
          .rotation = rotation,
          .scale = scale
        },
        cardRenderResources
      );

      cards.push_back(std::move(card));
    }
  }

  std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device{}()));

  game::DeckZone deckZone(
    engine::Transform{
      .position = {.x=150, .y=300},
      .size = size,
      .rotation = rotation,
      .scale = scale
    }
  );

  game::RoomZone roomZone(
    engine::Transform{
      .position = {.x=300, .y=200},
      .size = {
        .x = 700,
        .y = 400
      },
      .rotation = rotation,
      .scale = scale
    }
  );

  for (std::unique_ptr<game::Card>& card : cards)
  {
    // nodes.push_back(card.get());
  }


  for (size_t i = 0; i < cards.size(); i++)
  {
    game::Card* card = cards.at(i).get();
    if (card) {
      deckZone.AddCard(card);
    }
  }

  nodes.push_back(&background);
  nodes.push_back(&roomZone);
  nodes.push_back(&deckZone);
  engine::InteractionSystem interaction;
  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();

    queue.Clear();
    interaction.Update(nodes);
    if (IsKeyPressed(KEY_SPACE))
      DrawRoomCard(deckZone, roomZone);

    for (auto* node : nodes)
    {
      node->Update(dt);
      node->Draw(queue);
    }
  
    BeginDrawing();
      ClearBackground(DARKGREEN);

      queue.Flush();
    EndDrawing();
  }

  CloseWindow();
}
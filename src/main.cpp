#include "card.h"
#include "engine/render_queue.h"
#include "engine/interaction_system.h"
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Balatro Prototype");
    SetTargetFPS(60);

    engine::RenderQueue queue = engine::RenderQueue();

    Shader balatroShader = LoadShader(0, "resources/shaders/menu_background.fs");
    RenderTexture2D target = LoadRenderTexture(160, 240);
    int iResolutionLoc = GetShaderLocation(balatroShader, "iResolution");
    int iTimeLoc = GetShaderLocation(balatroShader, "iTime");
    float resolution[2] = { (float)160, (float)240 };
    SetShaderValue(balatroShader, iResolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    Vector2 position {333, 333};
    Vector2 size {160, 240};
    float rotation = 0.0f;
    float scale = 1.0f;

    Card card = Card(target.texture, {.position = position, .size = size, .rotation = rotation, .scale = scale});
    Card card2 = Card(target.texture, {.position = {.x=position.x + 50, .y=position.y}, .size = size, .rotation = rotation, .scale = scale});
    
    engine::InteractionSystem interaction;
    std::vector<engine::Node*> nodes;
    nodes.push_back(&card);
    nodes.push_back(&card2);
    while (!WindowShouldClose())
    {
    float dt = GetFrameTime();
    float time = (float)GetTime();
    SetShaderValue(balatroShader, iTimeLoc, &time, SHADER_UNIFORM_FLOAT);

    queue.Clear();                        // 1️⃣ clear first

    // 2️⃣ resolve hover
    interaction.Update(nodes);

    // 3️⃣ update + submit
    for (auto* node : nodes)
    {
        node->Update(dt);
        node->Draw(queue);
    }

    // 4️⃣ render
    BeginDrawing();
        ClearBackground(DARKGREEN);

        BeginShaderMode(balatroShader);
            queue.Flush();
        EndShaderMode();

    EndDrawing();
}

    CloseWindow();
}
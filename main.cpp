#include "raylib.h"
#include "raymath.h"

int main()
{
    // Drawing window
    int windowDimention[2];
    windowDimention[0] = 500;
    windowDimention[1] = 500;
    InitWindow(windowDimention[0], windowDimention[1], "Project 4");

    // Load map texture & determen map position
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    // variable for camera movement
    float speed = 4.0;

    // Load hero texture & determen the position and dimentions of the hero
    Texture2D hero_idle = LoadTexture("characters/hero_idle_sprite.png");
    Texture2D hero_run = LoadTexture("characters/hero_run_sprite.png");
    Texture2D hero = LoadTexture("characters/hero_idle_sprite.png");
    Vector2 heroPos{
        (float)windowDimention[0]/2.0f - 4.0f * (0.5f * (float)hero.width/6.0f),
        (float)windowDimention[1]/2.0f - 4.0f * (0.5f * (float)hero.height)
    };

    // If the value is 1 the hero is facing right but if it is -1 he is facing left
    float rightLeft = 1.f;

    // Animation variables
    float runningTime = 0;
    int frame = 0;
    const int maxFrame = 6;
    const float updateTime = 1.f/8.f;

    SetTargetFPS(60);
    // Keeping window open and adding peramiters
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Defining what happens if a key is pressed
        Vector2 direction{};
        if (IsKeyDown(KEY_A))   direction.x -= 1.0;
        if (IsKeyDown(KEY_S))   direction.y += 1.0;
        if (IsKeyDown(KEY_D))   direction.x += 1.0;
        if (IsKeyDown(KEY_W))   direction.y -= 1.0;
        if (Vector2Length(direction) != 0.0)
        {   
            // set mapPos = mapPos - direction ---- Vector2Normalize is used for diagonal movement so that it is not faster than normal
            //                                 ---- Vector2Scale is used for multiplying the given direction with a desired vector
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

            // Check if hero is facing right or left
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

            hero = hero_run;
        }
        else
        {
            hero = hero_idle;
        }
        

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame) frame = 0;
        }
        

        // Draw the hero
        Rectangle source{frame * (float)hero.width/6.f, 0.f, rightLeft * (float)hero.width/6.f, (float)hero.height};
        Rectangle dest{heroPos.x, heroPos.y, 4.0f * (float)hero.width/6.0f, 4.0f * (float)hero.height};
        DrawTexturePro(hero, source, dest, Vector2{}, 0.f, WHITE);

        // End drawing
        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(hero);
    CloseWindow();
}
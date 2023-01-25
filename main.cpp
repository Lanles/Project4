#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    // Drawing window
    int windowDimention[2];
    windowDimention[0] = 500;
    windowDimention[1] = 500;
    InitWindow(windowDimention[0], windowDimention[1], "Project 4");

    // Load map texture, determen map position & map size
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapSize = 4.0f;

    // Getting the Character class
    Character hero(windowDimention[0], windowDimention[1]);

    // Getting the Enemy class
    Enemy goblin(Vector2{}, LoadTexture("characters/goblin_idle_sprite.png"), LoadTexture("characters/goblin_Run_sprite.png"));
    goblin.setTarger(&hero);

    // props array for position and texture
    Prop props [2]{
        Prop{Vector2{700.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 700.f}, LoadTexture("nature_tileset/Log.png")}
    };

    SetTargetFPS(60);
    // Keeping window open and adding peramiters
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(hero.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapSize, WHITE);

        // Draw props
        for (auto prop : props)
        {
            prop.Render(hero.getWorldPos());
        }

        hero.tick(GetFrameTime());
        goblin.tick(GetFrameTime());

        // Check if player is near edges of map
        if (hero.getWorldPos().x < 0.f || 
            hero.getWorldPos().y < 0.f || 
            hero.getWorldPos().x + windowDimention[0] > map.width * mapSize ||
            hero.getWorldPos().y + windowDimention[1] > map.height * mapSize)
        {
            hero.undoMovement();
        }
        
        // Check if player is coliding with prop
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(hero.getWorldPos()), hero.GetCollisionRec()))
            {
                hero.undoMovement();
            }
        }

        // Check if sword hit enemy
        if (IsKeyPressed(KEY_SPACE))
        {
            if(CheckCollisionRecs(goblin.GetCollisionRec(), hero.getWeaponCollision()))
            {
                goblin.setAlive(false);
            }
        }
        
        // End drawing
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
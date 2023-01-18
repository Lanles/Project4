#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

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

    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset/Rock.png")};

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

        rock.Render(hero.getWorldPos());

        hero.tick(GetFrameTime());

        // Check if player is near edges of map
        if (hero.getWorldPos().x < 0.f || 
            hero.getWorldPos().y < 0.f || 
            hero.getWorldPos().x + windowDimention[0] > map.width * mapSize ||
            hero.getWorldPos().y + windowDimention[1] > map.height * mapSize)
        {
            hero.undoMovement();
        }
        

        // End drawing
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
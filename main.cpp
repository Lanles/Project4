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
        }

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // End drawing
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
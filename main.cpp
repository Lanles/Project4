#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

    // Getting the Enemy class for goblin and slime
    Enemy goblin{
        Vector2{800.f, 300.f}, 
        LoadTexture("characters/goblin_idle_sprite.png"), 
        LoadTexture("characters/goblin_Run_sprite.png")
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_sprite.png"), 
        LoadTexture("characters/slime_run_sprite.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for (auto enemy : enemies)
    {
        enemy->setTarger(&hero);
    }

    // props array for position and texture
    Prop props [6]{
        Prop{Vector2{700.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 700.f}, LoadTexture("nature_tileset/Log.png")},
        Prop{Vector2{1000.f, 500.f}, LoadTexture("nature_tileset/Bush.png")},
        Prop{Vector2{800.f, 1000.f}, LoadTexture("nature_tileset/Sign.png")},
        Prop{Vector2{500.f, 1200.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{900.f, 900.f}, LoadTexture("nature_tileset/Bush.png")}
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


        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        };
        
        hero.tick(GetFrameTime());

        // Draw health of game over
        if (!hero.getAlive())
        {
            DrawText("Game Over!", windowDimention[0]/4, windowDimention[1]/2, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string heroHealth = "Health: ";
            heroHealth.append(std::to_string(hero.getHeroHP()), 0, 3); // The zero makes it so that we start from the first number (0 means from the beginning)
                                                                       // And the second number decides how many numbers we will show (2 in this case)
            DrawText(heroHealth.c_str(), 10.f, 10.f, 25, RED);
        }

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
            for (auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->GetCollisionRec(), hero.getWeaponCollision()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        
        // End drawing
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}
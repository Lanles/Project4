#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;

    screenPos = {
        static_cast<float>(winWidth)/2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight)/2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // Defining what happens if a key is pressed
    Vector2 direction{};
    if (IsKeyDown(KEY_A))   direction.x -= 1.0;
    if (IsKeyDown(KEY_S))   direction.y += 1.0;
    if (IsKeyDown(KEY_D))   direction.x += 1.0;
    if (IsKeyDown(KEY_W))   direction.y -= 1.0;
    if (Vector2Length(direction) != 0.0)
    {   
        // set worldPos = worldPos + direction ---- Vector2Normalize is used for diagonal movement so that it is not faster than normal
        //                                     ---- Vector2Scale is used for multiplying the given direction with a desired vector
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        // Check if hero is facing right or left
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }
    else
    {
        texture = idle;
    }

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame) frame = 0;
    }

    // Draw the hero
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Character::GetCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}
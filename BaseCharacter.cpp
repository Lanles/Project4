#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame) frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {   
        // set worldPos = worldPos + velocity ---- Vector2Normalize is used for diagonal movement so that it is not faster than normal
        //                                     ---- Vector2Scale is used for multiplying the given velocity with a desired vector
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // Check if hero is facing right or left
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw the hero
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
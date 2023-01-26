#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrame;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2
    {
        static_cast<float>(windowWidth)/2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight)/2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if (!getAlive()) return;
    
    // Defining what happens if a key is pressed
    if (IsKeyDown(KEY_A))   velocity.x -= 1.0;
    if (IsKeyDown(KEY_S))   velocity.y += 1.0;
    if (IsKeyDown(KEY_D))   velocity.x += 1.0;
    if (IsKeyDown(KEY_W))   velocity.y -= 1.0;
    
    BaseCharacter::tick(deltaTime);

    // determen sword position and rotation
    Vector2 origin{};
    Vector2 offset{};
    float rotation = 0.f;
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {45.f, 50.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, weapon.height * scale
        };
        if (IsKeyDown(KEY_SPACE))   rotation = 35.f;
        
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {20.f, 50.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale, 
            getScreenPos().y + offset.y - weapon.height * scale, 
            weapon.width * scale, weapon.height * scale
        };
        if (IsKeyDown(KEY_SPACE))   rotation = -35.f;
    }
    

    // Draw sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);
}

void Character::takeDMG(float damage)
{
    heroHP -= damage;
    if (heroHP <= 0.f)
    {
        setAlive(false);
    }
    
}
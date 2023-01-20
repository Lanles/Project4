#include "raylib.h"
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void undoMovement();
        Rectangle GetCollisionRec();
    protected:
        Texture2D texture{LoadTexture("characters/hero_idle_sprite.png")};
        Texture2D idle{LoadTexture("characters/hero_idle_sprite.png")};
        Texture2D run{LoadTexture("characters/hero_run_sprite.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};

        // If the value is 1 the hero is facing right but if it is -1 he is facing left
        float rightLeft = 1.f;

        // Animation variables
        float runningTime = 0;
        int frame = 0;
        int maxFrame = 6;
        float updateTime = 1.f/10.f;
        // Variable for camera movement
        float speed = 4.f;
        float width = 0;
        float height = 0;
        // Player scale number
        float scale = 4.0f;
    private:
    
};

#endif
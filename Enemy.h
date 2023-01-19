#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle GetCollisionRec();
private:
    Texture2D texture{LoadTexture("characters/goblin_idle_sprite.png")};
    Texture2D idle{LoadTexture("characters/goblin_idle_sprite.png")};
    Texture2D run{LoadTexture("characters/goblin_run_sprite.png")};
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
    // Enemy scale number
    float scale = 4.0f;
};
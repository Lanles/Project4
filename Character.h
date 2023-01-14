#include "raylib.h"

class Character
{
public:
    Character();
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void undoMovement();
private:
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
    float updateTime = 1.f/8.f;
    // variable for camera movement
    float speed = 4.f;
    float width = 0;
    float height = 0;
};
#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 heroPosition);
    Rectangle GetCollisionRec(Vector2 heroPosition);
private:
    Vector2 worldPosition{};
    Texture2D texture{};
    float scale = 3.0f;
};
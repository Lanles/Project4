#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPosition(pos),
    texture(tex)
{

}

void Prop::Render(Vector2 heroPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, heroPosition) };
    DrawTextureEx(texture, screenPosition, 0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 heroPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, heroPosition) };
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        texture.width * scale,
        texture.height * scale
    };
}
#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPosition(pos),
    texture(tex)
{

}

void Prop::Render(Vector2 knightPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, knightPosition) };
    DrawTextureEx(texture, screenPosition, 0.f, scale, WHITE);
}
#include "raylib.h"
#include "BaseCharacter.h"

class Prop : public BaseCharacter
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 heroPosition);
    Rectangle GetCollisionRec(Vector2 heroPosition);
private:
    Texture2D texture{};
    Vector2 worldPosition{};
    float scale = 3.0f;
};
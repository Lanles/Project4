#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarger(Character* character) { target = character; };
    virtual Vector2 getScreenPos() override;
private:
    Character* target;
    float enemyDMG = 10.f;
};
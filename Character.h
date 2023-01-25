#include "raylib.h"
#include "BaseCharacter.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollision() { return weaponCollisionRec; }
    float getHeroHP() const { return heroHP; }
    void takeDMG(float damage);
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/sword.png")};
    Rectangle weaponCollisionRec{};
    float heroHP = 100.f;
};

#endif
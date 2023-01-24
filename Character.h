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
private:
    int windowWidth{};
    int windowHeight{};
};

#endif
#ifndef SPIDERGAME_PLAYER_H
#define SPIDERGAME_PLAYER_H

#include <vector>
#include "Projectile.h"

class Player
{
public:
    Player();
    void Reset();
    void SetMovingLeft(bool moving);
    void SetMovingRight(bool moving);
    void SetFiring(bool firing);
    void Update(float elapsedSeconds);
    void Draw() const;
    std::vector<Projectile>& GetProjectiles();
    float GetX() const;
    float GetY() const;
    float GetHalfWidth() const;
    float GetHalfHeight() const;

private:
    float x_;
    float y_;
    float fireTimer_;
    float animationTime_;
    bool movingLeft_;
    bool movingRight_;
    bool firing_;
    std::vector<Projectile> projectiles_;
};

#endif

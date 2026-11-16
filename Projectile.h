#ifndef SPIDERGAME_PROJECTILE_H
#define SPIDERGAME_PROJECTILE_H

class Projectile
{
public:
    Projectile(float x, float y, float velocityY);
    void Update(float elapsedSeconds);
    void Draw() const;
    bool IsActive() const;
    void Deactivate();
    float GetX() const;
    float GetY() const;
    float GetHalfWidth() const;
    float GetHalfHeight() const;

private:
    float x_;
    float y_;
    float velocityY_;
    bool active_;
};

#endif

#ifndef SPIDERGAME_ENEMY_H
#define SPIDERGAME_ENEMY_H

class Enemy
{
public:
    Enemy(float x, float y, float speed);
    void Update(float elapsedSeconds);
    void Draw() const;
    bool IsActive() const;
    void Deactivate();
    float GetX() const;
    float GetY() const;
    float GetRadius() const;

private:
    float x_;
    float y_;
    float speed_;
    float animationTime_;
    float velocityX_;
    float velocityY_;
    float turnTimer_;
    bool active_;
};

#endif

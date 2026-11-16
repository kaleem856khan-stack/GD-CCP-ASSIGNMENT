#include "Projectile.h"
#include "Config.h"
#include <GL/glut.h>

Projectile::Projectile(float x, float y, float velocityY)
    : x_(x), y_(y), velocityY_(velocityY), active_(true)
{
}

void Projectile::Update(float elapsedSeconds)
{
    if (!active_) return;
    y_ += velocityY_ * elapsedSeconds;
    if (y_ > Config::WORLD_TOP + GetHalfHeight()) active_ = false;
}

void Projectile::Draw() const
{
    if (!active_) return;
    glColor3f(0.25f, 0.72f, 0.92f);
    glBegin(GL_QUADS);
    glVertex2f(x_ - GetHalfWidth(), y_ - GetHalfHeight());
    glVertex2f(x_ + GetHalfWidth(), y_ - GetHalfHeight());
    glVertex2f(x_ + GetHalfWidth(), y_ + GetHalfHeight());
    glVertex2f(x_ - GetHalfWidth(), y_ + GetHalfHeight());
    glEnd();
    glColor3f(0.78f, 0.93f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(x_, y_ - GetHalfHeight());
    glVertex2f(x_, y_ + GetHalfHeight());
    glEnd();
}

bool Projectile::IsActive() const { return active_; }
void Projectile::Deactivate() { active_ = false; }
float Projectile::GetX() const { return x_; }
float Projectile::GetY() const { return y_; }
float Projectile::GetHalfWidth() const { return Config::PROJECTILE_WIDTH * 0.5f; }
float Projectile::GetHalfHeight() const { return Config::PROJECTILE_HEIGHT * 0.5f; }

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
    glColor3f(1.0f, 0.58f, 0.08f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x_, y_ + GetHalfHeight());
    glVertex2f(x_ - GetHalfWidth(), y_);
    glVertex2f(x_ + GetHalfWidth(), y_);
    glEnd();
    glColor3f(0.96f, 0.78f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(x_ - GetHalfWidth(), y_);
    glVertex2f(x_ + GetHalfWidth(), y_);
    glVertex2f(x_ + GetHalfWidth() * 0.7f, y_ - GetHalfHeight());
    glVertex2f(x_ - GetHalfWidth() * 0.7f, y_ - GetHalfHeight());
    glEnd();
}

bool Projectile::IsActive() const { return active_; }
void Projectile::Deactivate() { active_ = false; }
float Projectile::GetX() const { return x_; }
float Projectile::GetY() const { return y_; }
float Projectile::GetHalfWidth() const { return Config::PROJECTILE_WIDTH * 0.5f; }
float Projectile::GetHalfHeight() const { return Config::PROJECTILE_HEIGHT * 0.5f; }

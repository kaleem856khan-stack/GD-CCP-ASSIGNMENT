#include "Projectile.h"
#include "Config.h"
#include <GL/glut.h>
#include <cmath>

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
    glColor3f(0.48f, 0.78f, 0.9f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; ++i)
    {
        float angle = (float)i * 6.2831853f / 8.0f;
        glVertex2f(x_, y_);
        glVertex2f(x_ + (float)std::cos(angle) * GetHalfWidth(),
                   y_ + (float)std::sin(angle) * GetHalfHeight());
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 8; ++i)
    {
        float angle = (float)i * 6.2831853f / 8.0f;
        glVertex2f(x_ + (float)std::cos(angle) * GetHalfWidth(),
                   y_ + (float)std::sin(angle) * GetHalfHeight());
    }
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x_ - GetHalfWidth() * 0.5f, y_ - GetHalfHeight() * 0.5f);
    glVertex2f(x_ + GetHalfWidth() * 0.5f, y_ + GetHalfHeight() * 0.5f);
    glVertex2f(x_ + GetHalfWidth() * 0.5f, y_ - GetHalfHeight() * 0.5f);
    glVertex2f(x_ - GetHalfWidth() * 0.5f, y_ + GetHalfHeight() * 0.5f);
    glEnd();
}

bool Projectile::IsActive() const { return active_; }
void Projectile::Deactivate() { active_ = false; }
float Projectile::GetX() const { return x_; }
float Projectile::GetY() const { return y_; }
float Projectile::GetHalfWidth() const { return Config::PROJECTILE_WIDTH * 0.5f; }
float Projectile::GetHalfHeight() const { return Config::PROJECTILE_HEIGHT * 0.5f; }

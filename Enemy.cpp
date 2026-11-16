#include "Enemy.h"
#include "Config.h"
#include <GL/glut.h>
#include <cmath>

Enemy::Enemy(float x, float y, float speed)
    : x_(x), y_(y), speed_(speed), animationTime_(0.0f), active_(true)
{
}

void Enemy::Update(float elapsedSeconds, float targetX, float targetY)
{
    if (!active_) return;
    float dx = targetX - x_;
    float dy = targetY - y_;
    float length = (float)std::sqrt(dx * dx + dy * dy);
    if (length > 0.001f)
    {
        x_ += dx / length * speed_ * elapsedSeconds;
        y_ += dy / length * speed_ * elapsedSeconds;
    }
    animationTime_ += elapsedSeconds;
}

void Enemy::Draw() const
{
    if (!active_) return;
    float wiggle = 2.0f * (float)std::sin(animationTime_ * 11.0f);
    glPushMatrix();
    glTranslatef(x_, y_, 0.0f);
    glColor3f(0.15f, 0.48f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(-5.0f, 3.0f); glVertex2f(-12.0f, 8.0f + wiggle);
    glVertex2f(-5.0f, -2.0f); glVertex2f(-12.0f, -7.0f - wiggle);
    glVertex2f(5.0f, 3.0f); glVertex2f(12.0f, 8.0f - wiggle);
    glVertex2f(5.0f, -2.0f); glVertex2f(12.0f, -7.0f + wiggle);
    glEnd();
    glColor3f(0.28f, 0.68f, 0.27f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 16; ++i)
    {
        float angle = (float)i * 6.2831853f / 16.0f;
        glVertex2f((float)std::cos(angle) * GetRadius(), (float)std::sin(angle) * GetRadius());
    }
    glEnd();
    glColor3f(0.92f, 0.95f, 0.7f);
    glPointSize(3.0f);
    glBegin(GL_POINTS); glVertex2f(-3.5f, 2.0f); glVertex2f(3.5f, 2.0f); glEnd();
    glPopMatrix();
}

bool Enemy::IsActive() const { return active_; }
void Enemy::Deactivate() { active_ = false; }
float Enemy::GetX() const { return x_; }
float Enemy::GetY() const { return y_; }
float Enemy::GetRadius() const { return (float)Config::ENEMY_RADIUS; }

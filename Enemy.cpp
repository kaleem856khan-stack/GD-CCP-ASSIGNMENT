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
    float wingBeat = 4.0f * (float)std::sin(animationTime_ * 20.0f);
    float legSwing = 2.0f * (float)std::sin(animationTime_ * 12.0f);
    glPushMatrix();
    glTranslatef(x_, y_, 0.0f);
    glColor3f(0.73f, 0.88f, 0.97f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-6.0f, 5.0f);
    for (int i = 0; i <= 16; ++i)
    {
        float angle = (float)i * 6.2831853f / 16.0f;
        glVertex2f(-6.0f + (float)std::cos(angle) * 5.0f,
                   5.0f + wingBeat * 0.3f + (float)std::sin(angle) * 8.0f);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(6.0f, 5.0f);
    for (int i = 0; i <= 16; ++i)
    {
        float angle = (float)i * 6.2831853f / 16.0f;
        glVertex2f(6.0f + (float)std::cos(angle) * 5.0f,
                   5.0f - wingBeat * 0.3f + (float)std::sin(angle) * 8.0f);
    }
    glEnd();
    glColor3f(0.12f, 0.1f, 0.07f);
    glBegin(GL_LINES);
    glVertex2f(-4.0f, -2.0f); glVertex2f(-11.0f, -5.0f - legSwing);
    glVertex2f(-4.0f, 2.0f); glVertex2f(-12.0f, 2.0f + legSwing);
    glVertex2f(-3.0f, 6.0f); glVertex2f(-10.0f, 10.0f - legSwing);
    glVertex2f(4.0f, -2.0f); glVertex2f(11.0f, -5.0f + legSwing);
    glVertex2f(4.0f, 2.0f); glVertex2f(12.0f, 2.0f - legSwing);
    glVertex2f(3.0f, 6.0f); glVertex2f(10.0f, 10.0f + legSwing);
    glEnd();
    glColor3f(0.94f, 0.68f, 0.08f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 1.0f);
    for (int i = 0; i <= 16; ++i)
    {
        float angle = (float)i * 6.2831853f / 16.0f;
        glVertex2f((float)std::cos(angle) * 6.0f,
                   1.0f + (float)std::sin(angle) * 10.0f);
    }
    glEnd();
    glColor3f(0.12f, 0.1f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(-5.0f, 5.0f); glVertex2f(5.0f, 5.0f);
    glVertex2f(4.0f, 2.0f); glVertex2f(-4.0f, 2.0f);
    glVertex2f(-4.0f, 0.0f); glVertex2f(4.0f, 0.0f);
    glVertex2f(3.0f, -3.0f); glVertex2f(-3.0f, -3.0f);
    glVertex2f(-3.0f, -5.0f); glVertex2f(3.0f, -5.0f);
    glVertex2f(2.0f, -7.0f); glVertex2f(-2.0f, -7.0f);
    glEnd();
    glColor3f(0.17f, 0.12f, 0.08f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, -8.0f);
    for (int i = 0; i <= 12; ++i)
    {
        float angle = (float)i * 6.2831853f / 12.0f;
        glVertex2f((float)std::cos(angle) * 4.0f,
                   -8.0f + (float)std::sin(angle) * 4.0f);
    }
    glEnd();
    glColor3f(0.95f, 0.82f, 0.25f);
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    glVertex2f(-1.5f, -7.5f); glVertex2f(1.5f, -7.5f);
    glEnd();
    glColor3f(0.17f, 0.12f, 0.08f);
    glBegin(GL_LINES);
    glVertex2f(-2.5f, -10.0f); glVertex2f(-4.0f, -14.0f);
    glVertex2f(2.5f, -10.0f); glVertex2f(4.0f, -14.0f);
    glVertex2f(-2.0f, 11.0f); glVertex2f(-4.0f, 15.0f);
    glVertex2f(2.0f, 11.0f); glVertex2f(4.0f, 15.0f);
    glEnd();
    glColor3f(0.1f, 0.08f, 0.05f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-3.0f, 9.0f); glVertex2f(3.0f, 9.0f); glVertex2f(0.0f, 15.0f);
    glEnd();
    glPopMatrix();
}

bool Enemy::IsActive() const { return active_; }
void Enemy::Deactivate() { active_ = false; }
float Enemy::GetX() const { return x_; }
float Enemy::GetY() const { return y_; }
float Enemy::GetRadius() const { return (float)Config::ENEMY_RADIUS; }

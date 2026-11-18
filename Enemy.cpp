#include "Enemy.h"
#include "Config.h"
#include <GL/glut.h>
#include <cmath>

static float RandomUnit()
{
    static unsigned int state = 2463534242u;
    state = state * 1664525u + 1013904223u;
    return (float)(state >> 8) / 16777215.0f;
}

Enemy::Enemy(float x, float y, float speed)
    : x_(x), y_(y), speed_(speed), animationTime_(0.0f),
      velocityX_(0.0f), velocityY_(0.0f), turnTimer_(0.0f), active_(true)
{
    float angle = RandomUnit() * 6.2831853f;
    velocityX_ = (float)std::cos(angle) * speed_;
    velocityY_ = (float)std::sin(angle) * speed_;
    turnTimer_ = 0.35f + RandomUnit() * 1.1f;
}

void Enemy::Update(float elapsedSeconds)
{
    if (!active_) return;
    turnTimer_ -= elapsedSeconds;
    if (turnTimer_ <= 0.0f)
    {
        float angle = RandomUnit() * 2.0943951f - 1.0471976f;
        float oldX = velocityX_;
        float oldY = velocityY_;
        velocityX_ = (oldX * (float)std::cos(angle) - oldY * (float)std::sin(angle));
        velocityY_ = (oldX * (float)std::sin(angle) + oldY * (float)std::cos(angle));
        turnTimer_ = 0.35f + RandomUnit() * 1.1f;
    }
    x_ += velocityX_ * elapsedSeconds;
    y_ += velocityY_ * elapsedSeconds;
    if (x_ < Config::WORLD_LEFT + GetRadius())
    {
        x_ = Config::WORLD_LEFT + GetRadius();
        velocityX_ = (float)std::fabs(velocityX_);
    }
    else if (x_ > Config::WORLD_RIGHT - GetRadius())
    {
        x_ = Config::WORLD_RIGHT - GetRadius();
        velocityX_ = -(float)std::fabs(velocityX_);
    }
    if (y_ > Config::WORLD_TOP - GetRadius())
    {
        y_ = Config::WORLD_TOP - GetRadius();
        velocityY_ = -(float)std::fabs(velocityY_);
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

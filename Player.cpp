#include "Player.h"
#include "Config.h"
#include <GL/glut.h>
#include <cmath>

Player::Player()
    : x_(0.0f), y_(Config::WORLD_BOTTOM + 36.0f), fireTimer_(0.0f),
      animationTime_(0.0f), movingLeft_(false), movingRight_(false), firing_(false)
{
}

void Player::Reset()
{
    x_ = 0.0f;
    y_ = Config::WORLD_BOTTOM + 36.0f;
    fireTimer_ = 0.0f;
    animationTime_ = 0.0f;
    movingLeft_ = false;
    movingRight_ = false;
    firing_ = false;
    projectiles_.clear();
}

void Player::SetMovingLeft(bool moving) { movingLeft_ = moving; }
void Player::SetMovingRight(bool moving) { movingRight_ = moving; }
void Player::SetFiring(bool firing) { firing_ = firing; }

void Player::Update(float elapsedSeconds)
{
    float direction = 0.0f;
    if (movingLeft_) direction -= 1.0f;
    if (movingRight_) direction += 1.0f;
    x_ += direction * Config::PLAYER_SPEED * elapsedSeconds;
    if (x_ < Config::WORLD_LEFT + GetHalfWidth()) x_ = Config::WORLD_LEFT + GetHalfWidth();
    if (x_ > Config::WORLD_RIGHT - GetHalfWidth()) x_ = Config::WORLD_RIGHT - GetHalfWidth();
    animationTime_ += elapsedSeconds;
    fireTimer_ -= elapsedSeconds;

    if (firing_ && fireTimer_ <= 0.0f)
    {
        projectiles_.push_back(Projectile(x_, y_ + GetHalfHeight(), Config::PROJECTILE_SPEED));
        fireTimer_ = Config::PROJECTILE_COOLDOWN;
    }
    for (std::vector<Projectile>::iterator it = projectiles_.begin(); it != projectiles_.end(); ++it)
        it->Update(elapsedSeconds);
}

void Player::Draw() const
{
    const float phase = animationTime_ * 13.0f;
    const float swing = (movingLeft_ || movingRight_) ? 5.0f : 2.0f;
    glPushMatrix();
    glTranslatef(x_, y_, 0.0f);
    glColor3f(0.63f, 0.48f, 0.82f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-7.0f, 7.0f); glVertex2f(-18.0f, 15.0f + swing * (float)std::sin(phase));
    glVertex2f(-10.0f, 3.0f); glVertex2f(-20.0f, 5.0f - swing * (float)std::sin(phase));
    glVertex2f(-10.0f, -3.0f); glVertex2f(-19.0f, -8.0f + swing * (float)std::sin(phase));
    glVertex2f(-6.0f, -8.0f); glVertex2f(-13.0f, -17.0f - swing * (float)std::sin(phase));
    glVertex2f(7.0f, 7.0f); glVertex2f(18.0f, 15.0f - swing * (float)std::sin(phase));
    glVertex2f(10.0f, 3.0f); glVertex2f(20.0f, 5.0f + swing * (float)std::sin(phase));
    glVertex2f(10.0f, -3.0f); glVertex2f(19.0f, -8.0f - swing * (float)std::sin(phase));
    glVertex2f(6.0f, -8.0f); glVertex2f(13.0f, -17.0f + swing * (float)std::sin(phase));
    glEnd();
    glColor3f(0.28f, 0.16f, 0.42f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, -4.0f);
    for (int i = 0; i <= 24; ++i)
    {
        float angle = (float)i * 6.2831853f / 24.0f;
        glVertex2f((float)std::cos(angle) * 9.0f, -4.0f + (float)std::sin(angle) * 12.0f);
    }
    glEnd();
    glColor3f(0.48f, 0.34f, 0.64f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 5.0f);
    for (int i = 0; i <= 20; ++i)
    {
        float angle = (float)i * 6.2831853f / 20.0f;
        glVertex2f((float)std::cos(angle) * 6.0f, 5.0f + (float)std::sin(angle) * 7.0f);
    }
    glEnd();
    glColor3f(0.42f, 0.28f, 0.58f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 15.0f);
    for (int i = 0; i <= 20; ++i)
    {
        float angle = (float)i * 6.2831853f / 20.0f;
        glVertex2f((float)std::cos(angle) * 5.0f, 15.0f + (float)std::sin(angle) * 5.0f);
    }
    glEnd();
    glColor3f(0.94f, 0.22f, 0.2f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glVertex2f(-2.0f, 16.0f); glVertex2f(2.0f, 16.0f);
    glEnd();
    glColor3f(0.74f, 0.77f, 0.82f);
    glBegin(GL_LINES);
    glVertex2f(-4.0f, -2.0f); glVertex2f(4.0f, -2.0f);
    glVertex2f(-3.0f, -7.0f); glVertex2f(3.0f, -7.0f);
    glEnd();
    glPopMatrix();
}

std::vector<Projectile>& Player::GetProjectiles() { return projectiles_; }
float Player::GetX() const { return x_; }
float Player::GetY() const { return y_; }
float Player::GetHalfWidth() const { return Config::PLAYER_WIDTH * 0.5f; }
float Player::GetHalfHeight() const { return Config::PLAYER_HEIGHT * 0.5f; }

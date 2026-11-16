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
    const float phase = animationTime_ * 16.0f;
    const float flameLength = 7.0f + 3.0f * (float)std::sin(phase);
    glPushMatrix();
    glTranslatef(x_, y_, 0.0f);
    glColor3f(1.0f, 0.42f, 0.08f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-3.0f, -16.0f); glVertex2f(-1.0f, -16.0f); glVertex2f(-2.0f, -16.0f - flameLength);
    glVertex2f(1.0f, -16.0f); glVertex2f(3.0f, -16.0f); glVertex2f(2.0f, -16.0f - flameLength);
    glEnd();
    glColor3f(0.22f, 0.31f, 0.42f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 10.0f); glVertex2f(-5.0f, 12.0f); glVertex2f(-23.0f, 0.0f);
    glVertex2f(-25.0f, -7.0f); glVertex2f(-7.0f, -3.0f); glVertex2f(-4.0f, -15.0f);
    glVertex2f(0.0f, -18.0f); glVertex2f(4.0f, -15.0f); glVertex2f(7.0f, -3.0f);
    glVertex2f(25.0f, -7.0f); glVertex2f(23.0f, 0.0f); glVertex2f(5.0f, 12.0f);
    glEnd();
    glColor3f(0.34f, 0.45f, 0.57f);
    glBegin(GL_POLYGON);
    glVertex2f(-4.0f, -12.0f); glVertex2f(-14.0f, -20.0f); glVertex2f(-3.0f, -17.0f);
    glVertex2f(0.0f, -14.0f); glVertex2f(3.0f, -17.0f); glVertex2f(14.0f, -20.0f);
    glVertex2f(4.0f, -12.0f); glEnd();
    glColor3f(0.39f, 0.52f, 0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 29.0f); glVertex2f(-5.0f, 13.0f); glVertex2f(-4.0f, -16.0f);
    glVertex2f(0.0f, -20.0f); glVertex2f(4.0f, -16.0f); glVertex2f(5.0f, 13.0f);
    glEnd();
    glColor3f(0.24f, 0.77f, 0.94f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 17.0f); glVertex2f(-2.6f, 10.0f); glVertex2f(-2.0f, 5.0f);
    glVertex2f(2.0f, 5.0f); glVertex2f(2.6f, 10.0f);
    glEnd();
    glColor3f(0.82f, 0.88f, 0.92f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-5.0f, 8.0f); glVertex2f(-21.0f, 0.0f); glVertex2f(-7.0f, 3.0f);
    glVertex2f(5.0f, 8.0f); glVertex2f(21.0f, 0.0f); glVertex2f(7.0f, 3.0f);
    glEnd();
    glColor3f(0.88f, 0.2f, 0.16f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-2.0f, -13.0f); glVertex2f(0.0f, -16.0f); glVertex2f(2.0f, -13.0f);
    glEnd();
    glPopMatrix();
}

std::vector<Projectile>& Player::GetProjectiles() { return projectiles_; }
float Player::GetX() const { return x_; }
float Player::GetY() const { return y_; }
float Player::GetHalfWidth() const { return Config::PLAYER_WIDTH * 0.5f; }
float Player::GetHalfHeight() const { return Config::PLAYER_HEIGHT * 0.5f; }

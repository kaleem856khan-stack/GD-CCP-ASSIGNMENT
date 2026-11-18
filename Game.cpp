#include "Game.h"
#include "Config.h"
#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

Game* Game::instance_ = 0;

Game::Game()
    : score_(0), lives_(Config::INITIAL_LIVES), gameOver_(false), spawnTimer_(0.0f),
      lastUpdateTime_(0.0f), windowWidth_(Config::SCREEN_WIDTH), windowHeight_(Config::SCREEN_HEIGHT)
{
}

void Game::Run(int argc, char** argv)
{
    instance_ = this;
    srand((unsigned int)time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("SpiderGame - Spider vs Honey Bees");
    glClearColor(Config::BACKGROUND_RED, Config::BACKGROUND_GREEN, Config::BACKGROUND_BLUE, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glutSpecialFunc(SpecialDownCallback);
    glutSpecialUpFunc(SpecialUpCallback);
    glutKeyboardFunc(KeyDownCallback);
    glutKeyboardUpFunc(KeyUpCallback);
    lastUpdateTime_ = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    glutTimerFunc(Config::TIMER_INTERVAL_MS, TimerCallback, 0);
    glutMainLoop();
}

void Game::DisplayCallback() { if (instance_ != 0) instance_->Display(); }
void Game::TimerCallback(int value)
{
    (void)value;
    if (instance_ != 0) instance_->Update();
    glutTimerFunc(Config::TIMER_INTERVAL_MS, TimerCallback, 0);
}
void Game::ReshapeCallback(int width, int height) { if (instance_ != 0) instance_->Reshape(width, height); }
void Game::SpecialDownCallback(int key, int x, int y)
{ (void)x; (void)y; if (instance_ != 0) instance_->SpecialKeyDown(key); }
void Game::SpecialUpCallback(int key, int x, int y)
{ (void)x; (void)y; if (instance_ != 0) instance_->SpecialKeyUp(key); }
void Game::KeyDownCallback(unsigned char key, int x, int y)
{ (void)x; (void)y; if (instance_ != 0) instance_->KeyDown(key); }
void Game::KeyUpCallback(unsigned char key, int x, int y)
{ (void)x; (void)y; if (instance_ != 0) instance_->KeyUp(key); }

void Game::Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.35f, 0.38f, 0.43f);
    glBegin(GL_LINES);
    glVertex2f(Config::WORLD_LEFT, Config::WORLD_BOTTOM + 18.0f);
    glVertex2f(Config::WORLD_RIGHT, Config::WORLD_BOTTOM + 18.0f);
    glEnd();
    player_.Draw();
    const std::vector<Projectile>& shots = player_.GetProjectiles();
    for (std::vector<Projectile>::const_iterator shot = shots.begin(); shot != shots.end(); ++shot) shot->Draw();
    for (std::vector<Enemy>::const_iterator enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy) enemy->Draw();
    char status[80];
    sprintf_s(status, "Score: %d     Lives: %d", score_, lives_);
    glColor3f(0.92f, 0.94f, 1.0f);
    DrawText(Config::WORLD_LEFT + 12.0f, Config::WORLD_TOP - 22.0f, status);
    DrawText(Config::WORLD_LEFT + 12.0f, Config::WORLD_BOTTOM + 8.0f,
             "Move: Left/Right arrows     Fire: Space or Up");
    if (gameOver_)
    {
        DrawText(-46.0f, 20.0f, "GAME OVER");
        DrawText(-81.0f, 0.0f, "Press R to play again");
    }
    glutSwapBuffers();
}

void Game::Update()
{
    float now = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float elapsed = now - lastUpdateTime_;
    lastUpdateTime_ = now;
    if (elapsed < 0.0f) elapsed = 0.0f;
    if (elapsed > 0.05f) elapsed = 0.05f;
    if (!gameOver_)
    {
        player_.Update(elapsed);
        spawnTimer_ += elapsed;
        if (spawnTimer_ >= Config::ENEMY_SPAWN_INTERVAL)
        {
            spawnTimer_ -= Config::ENEMY_SPAWN_INTERVAL;
            SpawnEnemy();
        }
        for (std::vector<Enemy>::iterator enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy)
            enemy->Update(elapsed);
        CheckCollisions();
    }
    glutPostRedisplay();
}

void Game::Reshape(int width, int height)
{
    if (width < 1) width = 1;
    if (height < 1) height = 1;
    windowWidth_ = width;
    windowHeight_ = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Config::WORLD_LEFT, Config::WORLD_RIGHT, Config::WORLD_BOTTOM, Config::WORLD_TOP);
    glMatrixMode(GL_MODELVIEW);
}

void Game::SpecialKeyDown(int key)
{
    if (key == GLUT_KEY_LEFT) player_.SetMovingLeft(true);
    if (key == GLUT_KEY_RIGHT) player_.SetMovingRight(true);
    if (key == GLUT_KEY_UP) player_.SetFiring(true);
}
void Game::SpecialKeyUp(int key)
{
    if (key == GLUT_KEY_LEFT) player_.SetMovingLeft(false);
    if (key == GLUT_KEY_RIGHT) player_.SetMovingRight(false);
    if (key == GLUT_KEY_UP) player_.SetFiring(false);
}
void Game::KeyDown(unsigned char key)
{
    if (key == 27) exit(0);
    if (key == ' ' && !gameOver_) player_.SetFiring(true);
    if ((key == 'r' || key == 'R') && gameOver_) Reset();
}
void Game::KeyUp(unsigned char key) { if (key == ' ') player_.SetFiring(false); }

void Game::Reset()
{
    player_.Reset();
    enemies_.clear();
    score_ = 0;
    lives_ = Config::INITIAL_LIVES;
    gameOver_ = false;
    spawnTimer_ = 0.0f;
}

void Game::SpawnEnemy()
{
    float x = Config::WORLD_LEFT + 20.0f + (float)(rand() % (Config::SCREEN_WIDTH - 40));
    float speed = Config::ENEMY_BASE_SPEED + (float)(score_ / 50) * 2.0f;
    if (speed > 125.0f) speed = 125.0f;
    enemies_.push_back(Enemy(x, Config::WORLD_TOP - 28.0f, speed));
}

bool Game::CirclesOverlap(float ax, float ay, float ar,
                          float bx, float by, float br) const
{
    float dx = ax - bx;
    float dy = ay - by;
    float radius = ar + br;
    return dx * dx + dy * dy <= radius * radius;
}

void Game::CheckCollisions()
{
    std::vector<Projectile>& shots = player_.GetProjectiles();
    for (std::vector<Projectile>::iterator shot = shots.begin(); shot != shots.end(); ++shot)
    {
        if (!shot->IsActive()) continue;
        for (std::vector<Enemy>::iterator enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy)
        {
            if (!enemy->IsActive()) continue;
            if (CirclesOverlap(shot->GetX(), shot->GetY(), 7.0f,
                               enemy->GetX(), enemy->GetY(), enemy->GetRadius()))
            {
                shot->Deactivate();
                enemy->Deactivate();
                score_ += 10;
                break;
            }
        }
    }
    for (std::vector<Enemy>::iterator enemy = enemies_.begin(); enemy != enemies_.end(); ++enemy)
    {
        if (!enemy->IsActive()) continue;
        if (CirclesOverlap(player_.GetX(), player_.GetY(), 15.0f,
                           enemy->GetX(), enemy->GetY(), enemy->GetRadius()))
        {
            enemy->Deactivate();
            --lives_;
            if (lives_ <= 0) { lives_ = 0; gameOver_ = true; break; }
        }
        else if (enemy->GetY() < Config::WORLD_BOTTOM + 14.0f)
        {
            enemy->Deactivate();
            --lives_;
            if (lives_ <= 0) { lives_ = 0; gameOver_ = true; break; }
        }
    }
    for (std::vector<Projectile>::iterator shot = shots.begin(); shot != shots.end(); )
    {
        if (!shot->IsActive()) shot = shots.erase(shot); else ++shot;
    }
    for (std::vector<Enemy>::iterator enemy = enemies_.begin(); enemy != enemies_.end(); )
    {
        if (!enemy->IsActive()) enemy = enemies_.erase(enemy); else ++enemy;
    }
}

void Game::DrawText(float x, float y, const char* text) const
{
    glRasterPos2f(x, y);
    for (const char* character = text; *character != '\0'; ++character)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *character);
}

#ifndef SPIDERGAME_GAME_H
#define SPIDERGAME_GAME_H

#include <vector>
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
    Game();
    void Run(int argc, char** argv);
    void Display();
    void Update();
    void Reshape(int width, int height);
    void SpecialKeyDown(int key);
    void SpecialKeyUp(int key);
    void KeyDown(unsigned char key);
    void KeyUp(unsigned char key);

private:
    void Reset();
    void SpawnEnemy();
    void CheckCollisions();
    void DrawText(float x, float y, const char* text) const;
    bool CirclesOverlap(float ax, float ay, float ar,
                        float bx, float by, float br) const;

    Player player_;
    std::vector<Enemy> enemies_;
    int score_;
    int lives_;
    bool gameOver_;
    float spawnTimer_;
    float lastUpdateTime_;
    int windowWidth_;
    int windowHeight_;
    static Game* instance_;
    static void DisplayCallback();
    static void TimerCallback(int value);
    static void ReshapeCallback(int width, int height);
    static void SpecialDownCallback(int key, int x, int y);
    static void SpecialUpCallback(int key, int x, int y);
    static void KeyDownCallback(unsigned char key, int x, int y);
    static void KeyUpCallback(unsigned char key, int x, int y);
};

#endif

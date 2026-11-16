#ifndef SPIDERGAME_CONFIG_H
#define SPIDERGAME_CONFIG_H

namespace Config
{
    static const int SCREEN_WIDTH = 400;
    static const int SCREEN_HEIGHT = 400;
    static const int TIMER_INTERVAL_MS = 16;
    static const int INITIAL_LIVES = 3;
    static const float BACKGROUND_RED = 0.94f;
    static const float BACKGROUND_GREEN = 0.96f;
    static const float BACKGROUND_BLUE = 1.0f;
    static const int PLAYER_WIDTH = 38;
    static const int PLAYER_HEIGHT = 34;
    static const int ENEMY_RADIUS = 12;
    static const int PROJECTILE_WIDTH = 5;
    static const int PROJECTILE_HEIGHT = 14;
    static const float PLAYER_SPEED = 240.0f;
    static const float PROJECTILE_SPEED = 430.0f;
    static const float PROJECTILE_COOLDOWN = 0.28f;
    static const float ENEMY_BASE_SPEED = 55.0f;
    static const float ENEMY_SPAWN_INTERVAL = 1.15f;
    static const float WORLD_LEFT = -200.0f;
    static const float WORLD_RIGHT = 200.0f;
    static const float WORLD_BOTTOM = -200.0f;
    static const float WORLD_TOP = 200.0f;
}

#endif

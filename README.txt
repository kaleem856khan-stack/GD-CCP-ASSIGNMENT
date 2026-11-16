Jet Fighter - Visual Studio 2013 / v120 / C++11
================================================

Framework
---------
This game follows the supplied skeleton's 2D OpenGL and GLUT callback design.
The fighter jet and enemies are animated with immediate-mode OpenGL shapes, so
the project does not depend on external sprite images.

Files
-----
Config.h                 Window, movement and gameplay settings
Player.h / Player.cpp    Jet movement, animation and firing cooldown
Projectile.h / .cpp      Cannon round movement and drawing
Enemy.h / Enemy.cpp      Chasing enemies and animation
Game.h / Game.cpp        GLUT callbacks, timer, collisions, score and lives
main.cpp                 Program entry point

Build in Visual Studio 2013
---------------------------
1. Install Visual Studio 2013 with the Visual C++ desktop tools.
2. The VS2013 C++ installation includes the classic 32-bit GLUT header and
   library used by this project (GL\glut.h and glut32.lib). If they are absent,
   install a compatible 32-bit GLUT or FreeGLUT development package.
3. Open SpiderGame.sln. The project targets Win32 and the v120 toolset.
4. Build the Debug|Win32 or Release|Win32 configuration.
5. Copy glut32.dll from the VS2013 VC\include\GL folder beside the produced
   SpiderGame.exe (or make sure that DLL is on PATH),
   then run the program.

Controls
--------
Left / Right arrows: move the fighter jet
Space or Up arrow:   fire cannon rounds (hold to fire at the cooldown rate)
R:                   restart after game over
Escape:              quit

Each bug caught is worth 10 points. Bugs that hit the jet or pass the
bottom edge cost one life. The game ends at zero lives.

#ifndef BLOCKSGAME_H
#define BLOCKSGAME_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "world.h"
#include "block.h"
#include "camera.h"

class BlocksGame
{
    public:
        BlocksGame();
        ~BlocksGame();

        void go();

    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        std::string savesDir;

        bool m_running;

        sf::RenderWindow *m_window;
        sf::ContextSettings *m_settings;

        Camera *m_cam;
        World *m_world;
        sf::Clock m_gameClock;

        // to be moved to a texture manager class
        sf::Texture m_terrainTex;
        //sf::Texture m_crosshairTex;
        //sf::Sprite m_crosshair;

        bool init();
        void run();
        void quit();

        void render(float dT);
        //void update();
        void handleInput(float dT);

        void drawSphereAt(sf::Vector3<float> position);
        void drawBlockLines(sf::Vector3<float> pos);

        sf::Vector3<int> getBlockPosFromCam();
        sf::Vector3<float> getWorldCoordsAtScrenPos(int x, int y);
        bool file_exists(const char *filename);
        void takeScreenShot();

};

#endif
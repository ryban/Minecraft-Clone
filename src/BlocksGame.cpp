#include "BlocksGame.h"

#include "tostr.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>

const float DEG_TO_RAD = M_PI / 180;
const float RAD_90 = M_PI / 2;

BlocksGame::BlocksGame()
{
    SCREEN_WIDTH = 1366;
    SCREEN_HEIGHT = SCREEN_WIDTH * 9/16;
    savesDir = "save";
}

BlocksGame::~BlocksGame()
{
    delete m_cam;
    delete m_world;
    delete m_settings;
    m_window->close();
    delete m_window;
}

void BlocksGame::go()
{
    if(init())
        run();
}

bool BlocksGame::init()
{
    m_running = true;

    m_settings = new sf::ContextSettings;
    m_settings->antialiasingLevel = 4;

     m_window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blocks", sf::Style::Close, *m_settings);

    sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), *m_window);
    m_window->setFramerateLimit(60);
    m_window->setMouseCursorVisible(false);

    //initialize openGL
    glClearDepth(1.f);
    glClearColor(0.f, 148.f/255.f, 1.f, 0.f);
    // Enable Z-buffer read and write
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE); // define quads counter-clockwise!
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 1.f, 120000.f);

    m_cam = new Camera(sf::Vector3<float>(1600, 40000, 1600));
    m_cam->lookAt(0, 0, 0);
    sf::Clock Clock;
    Clock.restart();

    m_world = new World;//(19028734L);//(time(0), savesDir);

    std::cout << Clock.getElapsedTime().asSeconds() << " seconds to generate/load terrain\n";

    m_terrainTex;
    if(m_terrainTex.loadFromFile("res/tiles.png"))
    {
        m_terrainTex.setSmooth(false);
        m_terrainTex.setRepeated(false);
        m_terrainTex.bind();
    }
    else
    {
        std::cerr << "Could not open image: res/tiles.png\n";
        return false;
    }

    return true;
}

void BlocksGame::quit()
{
    m_running = false;
    m_window->close();
}

void BlocksGame::run()
{
    while(m_window->isOpen() && m_running)
    {
        float dT = m_gameClock.getElapsedTime().asSeconds();
        m_gameClock.restart();

        handleInput(dT);
        render(dT);
    }
}

void BlocksGame::render(float dT)
{

        m_window->clear(sf::Color(0, 81, 255));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // move camera
        m_cam->render();
        // render world
        m_world->render(*m_cam);

        // draw the lines around the slected block
        sf::Vector3<int> blockPosi = getBlockPosFromCam();
        
        sf::Vector3<float> blockPosf;
        blockPosf.x = (float)blockPosi.x*200.0;
        blockPosf.y = (float)blockPosi.y*200.0;
        blockPosf.z = (float)blockPosi.z*200.0;

        blockPosf -= m_cam->getPosition();

        sf::Vector3<float> worldPos = getWorldCoordsAtScrenPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        if(sqrt(worldPos.x * worldPos.x + worldPos.y * worldPos.y + worldPos.z * worldPos.z) < 1000.0) // 1000.0 = 5 blocks
            drawBlockLines(blockPosf);
        drawSphereAt(worldPos);

        // preserve opengl states
        // render text and 2d sprites here
        // doesn't work properly for some reason
        /*
        m_window->pushGLStates();
        m_window->resetGLStates();
            // Draw fps and debug info
            fpsArray[fpsIndex] = 1 / dT;
            fpsIndex++;
            fpsIndex %= FPS_BUFFER_SIZE;
            if(fpsIndex == FPS_BUFFER_SIZE-1)
            {
                int i_fps = 0;
                for(int i = 0; i < FPS_BUFFER_SIZE; i++)
                    i_fps += fpsArray[i];

                i_fps /= FPS_BUFFER;
                fps.setString("FPS: " + toString(i_fps));
            }
            pos_strx.setString("x: " + toString(m_cam->getPosition().x/200.0));
            pos_stry.setString("y: " + toString(m_cam->getPosition().y/200.0));
            pos_strz.setString("z: " + toString(m_cam->getPosition().z/200.0));
            m_window->draw(fps);
            m_window->draw(pos_strx);
            m_window->draw(pos_stry);
            m_window->draw(pos_strz);

            m_window->draw(crosshair);

        // restore opengl states
        m_window->popGLStates();
        */
        m_window->display();
}

void BlocksGame::handleInput(float dT)
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                quit();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    quit();
                if(event.key.code == sf::Keyboard::F2)
                    takeScreenShot();
                if(event.key.code == sf::Keyboard::F5)
                    m_world->saveWorld(savesDir);
                break;
        }
    }

    sf::Vector3<float> angles = m_cam->getAngles();

    const float speed = 2000.0; // 10 blocks / sec

    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    float dX = mousePos.x - SCREEN_WIDTH / 2;
    float dY = mousePos.y - SCREEN_HEIGHT / 2;
    //dX /= 1-0.5; // sensitivity
    //dY /= 1-0.5;
    dX *= RAD_90 * dT;
    dY *= -RAD_90 * dT;
    
    m_cam->rotate(dY, dX, 0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        std::cout << m_cam->getPosition().y / 200.0 << std::endl;
    }

    // forward
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        float zspd = speed * dT * sin((angles.y));
        float xspd = speed * dT * cos((angles.y));
        float yspd = 0;//speed * window.GetFrameTime() * sin(angles.x);
        m_cam->move(sf::Vector3<float>(xspd, yspd, zspd));
    }
    // backwards
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        float zspd = speed * dT * sin((angles.y));
        float xspd = speed * dT * cos((angles.y));
        float yspd = 0;//-speed * window.GetFrameTime() * sin(angles.x);
        m_cam->move(sf::Vector3<float>(-xspd, yspd, -zspd));
    }
    // left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        float zspd = -speed * dT * sin(angles.y + RAD_90);
        float xspd = -speed * dT * cos(angles.y + RAD_90);
        m_cam->move(sf::Vector3<float>(xspd, 0, zspd));
    }
    // right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        float zspd = -speed * dT * sin(angles.y + RAD_90);
        float xspd = -speed * dT * cos(angles.y + RAD_90);
        m_cam->move(sf::Vector3<float>(-xspd, 0, -zspd));
    }
    // up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        m_cam->move(sf::Vector3<float>(0, speed * dT, 0));
    // down
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        m_cam->move(sf::Vector3<float>(0, -speed * dT, 0));

    sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), *m_window);

    // mouse clicks
    static bool leftMouseDown = false;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftMouseDown)
    {
        leftMouseDown = true;
        sf::Vector3<int> blockPos = getBlockPosFromCam();
        sf::Vector3<float> worldPos = getWorldCoordsAtScrenPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
        if(worldPos.x * worldPos.x + worldPos.y * worldPos.y + worldPos.z * worldPos.z < (1000.0 * 1000.0))
        {
            //std::cout << "Close enough to remove" << std::endl;
            int id = m_world->getBlockId(blockPos.x, blockPos.y, blockPos.z);
            if(id != 0)
            {
                std::cout << "removing block\n";
                m_world->setBlockId(blockPos.x, blockPos.y, blockPos.z, 0);
            }
        }
    }else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        leftMouseDown = false;
}

void BlocksGame::drawSphereAt(sf::Vector3<float> position)
{
    // draws a sphere of radius 10 at the give position
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(position.x, position.y , position.z);
        gluSphere(quadric, 10.0, 12, 12);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

void BlocksGame::drawBlockLines(sf::Vector3<float> pos)
{
    glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(pos.x, pos.y, pos.z);
        glLineWidth(3.0);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(200, 0, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(0, 200, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 200);

            glVertex3f(200, 0, 0);
            glVertex3f(200, 0, 200);

            glVertex3f(200, 0, 0);
            glVertex3f(200, 200, 0);

            glVertex3f(200, 0, 200);
            glVertex3f(0, 0, 200);

            glVertex3f(200, 0, 200);
            glVertex3f(200, 200, 200);

            glVertex3f(0, 0, 200);
            glVertex3f(0, 200, 200);

            glVertex3f(0, 200, 0);
            glVertex3f(200, 200, 0);

            glVertex3f(0, 200, 0);
            glVertex3f(0, 200, 200);

            glVertex3f(200, 200, 200);
            glVertex3f(200, 200, 0);

            glVertex3f(200, 200, 200);
            glVertex3f(0, 200, 200);
        glEnd();
    glPopMatrix();
}

sf::Vector3<int> BlocksGame::getBlockPosFromCam()
{
    sf::Vector3<float> worldPos = getWorldCoordsAtScrenPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    sf::Vector3<float> cpos = m_cam->getPosition();

    worldPos += cpos;

    worldPos = worldPos / 200.f;

    sf::Vector3<int> blockPos;

    blockPos.x = floor(worldPos.x);
    blockPos.y = floor(worldPos.y);
    blockPos.z = floor(worldPos.z);

    return blockPos;
}

sf::Vector3<float> BlocksGame::getWorldCoordsAtScrenPos(int x, int y)
{
    // to many calls to this in a single frame might slow things down
    // best to get once and store
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    // get the depthbuffer for the current frame
    glReadPixels( winX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return sf::Vector3<float>(posX, posY, posZ);
}

bool BlocksGame::file_exists(const char *filename)
{
    // is this a good idea?
    std::ifstream ifile(filename);
    return ifile;
}

void BlocksGame::takeScreenShot()
{
    sf::Image screen = m_window->capture();
    std::string filename = "screenshots/screenshot_" + toString((int)time(0) % 32000) + ".png";
    while(file_exists(filename.c_str()))
    {
        filename = "screenshots/screenshot_" + toString((int)time(0) % 32000) + ".png";
    }
    if(!screen.saveToFile(filename))
        std::cerr << "couldn't save screen\n";
    else
        std::cout << "screen saved as " << filename << std::endl;
}
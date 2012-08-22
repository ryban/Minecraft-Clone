#ifndef CAMERA_H
#define CAMERA_H

// Class for manipulating and keeping track of the cameras psotion in the world
// the camera is always at the OpenGL origin, so when rendered most objects need the camera position
// to render properly
// also handles frustum culling

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include "vectormath.h"
#include "AABB.h"

class Plane
{
    public:
        Plane(sf::Vector3<float> &vec1, sf::Vector3<float> &vec2, sf::Vector3<float> &vec3);
        Plane();

        void set3Points(sf::Vector3<float> &vec1, sf::Vector3<float> &vec2, sf::Vector3<float> &vec3);
        void setNormalAndPoint(sf::Vector3<float> &n, sf::Vector3<float> &p);
        void setCoefficients(float a, float b, float c, float d);
        float distance(sf::Vector3<float> &point);

        sf::Vector3<float> normal;
        sf::Vector3<float> point;
        float d;
};

class Camera
{
    public:
        Camera(sf::Vector3<float> pos);
        void setPitch(float angle);
        void setYaw(float angle);
        void setRoll(float angle);
        void setPosition(sf::Vector3<float> new_pos);
        void rotate(float p_angle, float y_angle, float r_angle);
        void move(sf::Vector3<float> velocity);
        void lookAt(float x, float y, float z);

        bool isSpereInFrustum(sf::Vector3<float> &point, float radius);
        bool isBoxInFrustum(AABB &box);

        void render();

        sf::Vector3<float> getPosition() { return m_position; }
        sf::Vector3<float> getAngles() { return sf::Vector3<float>(m_pitch, m_yaw, m_roll); }
    private:
        void updateFrustum();
        sf::Vector3<float> m_position;
        // angles in radians
        float m_pitch;
        float m_yaw;
        float m_roll;

        enum { A = 0, B, C, D };
        enum { NEAR = 0, FAR, LEFT, RIGHT, TOP, BOTTOM };

        GLfloat planes[6][4];
};

#endif
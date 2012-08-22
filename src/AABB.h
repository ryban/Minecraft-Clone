#ifndef AABB_H
#define AABB_H

#include <SFML/System/Vector3.hpp>

class AABB 
{
    public:
        sf::Vector3<float> corner;
        float x, y, z;

        AABB(sf::Vector3<float> &corn, float xx, float yy, float zz);
        AABB();
        ~AABB();

        void setBox(sf::Vector3<float> &corn, float xx, float yy, float zz);

        // for use in frustum computations
        sf::Vector3<float> getVertexP(sf::Vector3<float> &normal);
        sf::Vector3<float> getVertexN(sf::Vector3<float> &normal);
        void getCorners(sf::Vector3<float> verts[]);
};

#endif
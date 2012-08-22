#include "AABB.h"

AABB::AABB( sf::Vector3<float> &corner,  float x, float y, float z)
{
    setBox(corner,x,y,z);
}

AABB::AABB()
{
    corner.x = 0; corner.y = 0; corner.z = 0;
    x = 1.0f;
    y = 1.0f;
    z = 1.0f;
}

AABB::~AABB() {}

void AABB::setBox( sf::Vector3<float> &corn,  float xx, float yy, float zz)
{
    corner = corn;
    if (xx < 0.0)
    {
        xx = -xx;
        corner.x -= xx;
    }
    if (yy < 0.0)
    {
        yy = -yy;
        corner.y -= yy;
    }
    if (zz < 0.0)
    {
        zz = -zz;
        corner.z -= zz;
    }
    x = xx;
    y = yy;
    z = zz;
}

sf::Vector3<float> AABB::getVertexP(sf::Vector3<float> &normal)
{
    sf::Vector3<float> res = corner;

    if (normal.x > 0)
        res.x += x;
    if (normal.y > 0)
        res.y += y;
    if (normal.z > 0)
        res.z += z;
    return res;
}

sf::Vector3<float> AABB::getVertexN(sf::Vector3<float> &normal)
{
    sf::Vector3<float> res = corner;
    if (normal.x < 0)
        res.x += x;
    if (normal.y < 0)
        res.y += y;
    if (normal.z < 0)
        res.z += z;
    return res;
}
void AABB::getCorners(sf::Vector3<float> verts[])
{
    verts[0] = corner;

    verts[1] = sf::Vector3<float>(x, y, z) + corner;

    verts[2] = corner;
    verts[2].x += x;

    verts[3] = corner;
    verts[3].z += z;

    verts[4] = corner;
    verts[4].y += y;
    verts[4].x += x;

    verts[5] = corner;
    verts[5].y += y;
    verts[5].x += x;

    verts[6] = corner;
    verts[6].x += x;
    verts[6].z += z;

    verts[7] = corner;
    verts[7].y += y;
}
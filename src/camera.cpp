#include "camera.h"
#include <iostream>

////////////////
//// Camera ////
////////////////

#define RAD_90 M_PI / 2.0
#define RAD_89 89.99 * M_PI / 180

Camera::Camera(sf::Vector3<float> pos)
{
    m_position = pos;
    m_pitch = m_yaw = m_roll = 0;
}
void Camera::setPosition(sf::Vector3<float> new_pos)
{
    m_position = new_pos;
}
void Camera::rotate(float p_angle, float y_angle, float r_angle)
{
    m_pitch += p_angle;
    if(m_pitch > RAD_90)
        m_pitch = RAD_89;
    else if(m_pitch < -RAD_90)
        m_pitch = -RAD_89;

    m_yaw += y_angle;
    if(m_yaw > M_PI)
        m_yaw -= M_PI * 2;
    else if(m_yaw < -M_PI)
        m_yaw += M_PI * 2;

    m_roll += r_angle;
}
void Camera::move(sf::Vector3<float> velocity)
{
    m_position += velocity;
}
void Camera::setPitch(float angle)
{
    m_pitch = angle;
}
void Camera::setYaw(float angle)
{
    m_yaw = angle;
}
void Camera::setRoll(float angle)
{
    m_roll = angle;
}
void Camera::lookAt(float x, float y, float z)
{
    float new_yaw = atan((x - m_position.x) / (z - m_position.z));
    float d = sqrt((x - m_position.x) * (x - m_position.x) + (z - m_position.z) * (z - m_position.z));
    float new_pitch = atan((y - m_position.y) / d);
    setYaw(new_yaw);
    setPitch(new_pitch);
}
// rotates the OpenGL scene and updates the frustum
void Camera::render()
{
    float lx = cos(m_yaw);
    float lz = sin(m_yaw);
    float ly = tan(m_pitch);
    gluLookAt(  0.0, 0.0, 0.0, // camera is always at the origin, everything else moves
                lx, ly, lz,
                sin(m_roll), cos(m_roll), 0.0);

    updateFrustum();    
}
// updates the frustum to the current OpenGL view
void Camera::updateFrustum()
{
    GLfloat modelViewMatrix[16];
    GLfloat MVPMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);

    // get the modelviewmatrix
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glMultMatrixf(modelViewMatrix);
        glGetFloatv(GL_PROJECTION_MATRIX, MVPMatrix);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW); // return to model view

    planes[LEFT][A] = MVPMatrix[3]  + MVPMatrix[0];
    planes[LEFT][B] = MVPMatrix[7]  + MVPMatrix[4];
    planes[LEFT][C] = MVPMatrix[11] + MVPMatrix[8];
    planes[LEFT][D] = MVPMatrix[15] + MVPMatrix[12];

    GLfloat length = sqrt(planes[LEFT][A] * planes[LEFT][A] + planes[LEFT][B] * planes[LEFT][B] + planes[LEFT][C] * planes[LEFT][C]);
    planes[LEFT][A] /= length;
    planes[LEFT][B] /= length;
    planes[LEFT][C] /= length;
    planes[LEFT][D] /= length;

    planes[RIGHT][A] = MVPMatrix[3]  - MVPMatrix[0];
    planes[RIGHT][B] = MVPMatrix[7]  - MVPMatrix[4];
    planes[RIGHT][C] = MVPMatrix[11] - MVPMatrix[8];
    planes[RIGHT][D] = MVPMatrix[15] - MVPMatrix[12];
    
    length = sqrt(planes[RIGHT][A] * planes[RIGHT][A] + planes[RIGHT][B] * planes[RIGHT][B] + planes[RIGHT][C] * planes[RIGHT][C]);
    planes[RIGHT][A] /= length;
    planes[RIGHT][B] /= length;
    planes[RIGHT][C] /= length;
    planes[RIGHT][D] /= length;

    planes[BOTTOM][A] = MVPMatrix[3]  + MVPMatrix[1];
    planes[BOTTOM][B] = MVPMatrix[7]  + MVPMatrix[5];
    planes[BOTTOM][C] = MVPMatrix[11] + MVPMatrix[9];
    planes[BOTTOM][D] = MVPMatrix[15] + MVPMatrix[13];
    
    length = sqrt(planes[BOTTOM][A] * planes[BOTTOM][A] + planes[BOTTOM][B] * planes[BOTTOM][B] + planes[BOTTOM][C] * planes[BOTTOM][C]);
    planes[BOTTOM][A] /= length;
    planes[BOTTOM][B] /= length;
    planes[BOTTOM][C] /= length;
    planes[BOTTOM][D] /= length;

    planes[TOP][A] = MVPMatrix[3]  - MVPMatrix[1];
    planes[TOP][B] = MVPMatrix[7]  - MVPMatrix[5];
    planes[TOP][C] = MVPMatrix[11] - MVPMatrix[9];
    planes[TOP][D] = MVPMatrix[15] - MVPMatrix[13];
    
    length = sqrt(planes[TOP][A] * planes[TOP][A] + planes[TOP][B] * planes[TOP][B] + planes[TOP][C] * planes[TOP][C]);
    planes[TOP][A] /= length;
    planes[TOP][B] /= length;
    planes[TOP][C] /= length;
    planes[TOP][D] /= length;

    planes[NEAR][A] = MVPMatrix[3]  + MVPMatrix[2];
    planes[NEAR][B] = MVPMatrix[7]  + MVPMatrix[6];
    planes[NEAR][C] = MVPMatrix[11] + MVPMatrix[10];
    planes[NEAR][D] = MVPMatrix[15] + MVPMatrix[14];
    
    length = sqrt(planes[NEAR][A] * planes[NEAR][A] + planes[NEAR][B] * planes[NEAR][B] + planes[NEAR][C] * planes[NEAR][C]);
    planes[NEAR][A] /= length;
    planes[NEAR][B] /= length;
    planes[NEAR][C] /= length;
    planes[NEAR][D] /= length;

    planes[FAR][A] = MVPMatrix[3]  - MVPMatrix[2];
    planes[FAR][B] = MVPMatrix[7]  - MVPMatrix[6];
    planes[FAR][C] = MVPMatrix[11] - MVPMatrix[10];
    planes[FAR][D] = MVPMatrix[15] - MVPMatrix[14];
    
    length = sqrt(planes[FAR][A] * planes[FAR][A] + planes[FAR][B] * planes[FAR][B] + planes[FAR][C] * planes[FAR][C]);
    planes[FAR][A] /= length;
    planes[FAR][B] /= length;
    planes[FAR][C] /= length;
    planes[FAR][D] /= length;
}
// checks if a sphere is inside or touches the side of the view frustum
bool Camera::isSpereInFrustum(sf::Vector3<float> &point, float radius)
{
    GLfloat distance;
    for(int i = 0; i < 6; i++)
    {
        distance = planes[i][A] * point.x + planes[i][B] * point.y + planes[i][C] * point.z + planes[i][D];
        if (distance <= -radius)
            return false;
    }
    return true;
}
// checks if a AABB is inside or touches the side of the view frustum
// does not work properly
bool Camera::isBoxInFrustum(AABB &box)
{
    // not accurate
    Plane plane;
    //sf::Vector3<float> verts[8];
    //box.GetCorners(verts);
    sf::Vector3<float> pVert;
    for(int i = 0; i < 6; i++)
    {
        plane.setCoefficients(planes[i][A], planes[i][B], planes[i][C], planes[i][D]);
        pVert = box.getVertexP(plane.normal);
        if(plane.distance(pVert) < 0)
            return false;
    }
    return true;
}

///////////////
//// Plane ////
///////////////

Plane::Plane() {}

Plane::Plane(sf::Vector3<float> &vec1, sf::Vector3<float> &vec2, sf::Vector3<float> &vec3)
{
    set3Points(vec1, vec2, vec3);
}

void Plane::set3Points(sf::Vector3<float> &vec1, sf::Vector3<float> &vec2, sf::Vector3<float> &vec3)
{
    sf::Vector3<float> aux1;
    sf::Vector3<float> aux2;

    aux1 = vec1 - vec2;
    aux2 = vec3 - vec2;

    normal = sfm::Cross(aux2, aux1);
    sfm::Normalize(normal);

    point = vec2;
    d = (sfm::InnerProduct(normal, point));
}

void Plane::setNormalAndPoint(sf::Vector3<float> &n, sf::Vector3<float> &p)
{
    normal = n;
    point = p;
    d = -(sfm::InnerProduct(normal, point));
}

void Plane::setCoefficients(float a_, float b_, float c_, float d_)
{
    // set the normal vector
    normal = sf::Vector3<float> (a_, b_, c_);
    //compute the lenght of the vector
    float l = sfm::Length(normal);
    sfm::Normalize(normal);
    // and divide d by th length as well
    d = d_ / l;
}

float Plane::distance(sf::Vector3<float> &point)
{
    return d + sfm::InnerProduct(normal, point);
}
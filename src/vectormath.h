//Author : Stefan Woskowiak
//www.rixcode.com
//
//Distrubuted freely for use within sfml
#ifndef SFMATH_H
#define SFMATH_H

//include only the headers we need 
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
const float PI = 3.14159f;

namespace sfm
{
    //Zero out a vector
    template <class T>
    void Zero(sf::Vector3<T> &vec) { vec.x = vec.y = vec.z = 0; }

    template <class T>
    void Zero(sf::Vector2<T> &vec) { vec.x = vec.y = 0; }

    //Negate a vectors values
    template <class T>
    void Negate(sf::Vector3<T> &vec) { vec.x = -vec.x; vec.y = -vec.y; vec.z = -vec.z; }

    template <class T>
    void Negate(sf::Vector2<T> &vec) { vec.x = -vec.x; vec.y = -vec.y; }

    //Get the length of a vector
    template <class T>
    float Length(const sf::Vector3<T> &vec){    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }

    template <class T>
    float Length(const sf::Vector2<T> &vec){    return sqrt(vec.x * vec.x + vec.y * vec.y); }

    //Normalize the length of a vector
    template <class T>
    void Normalize(sf::Vector3<T> &vec){ float len = Length(vec);   vec/=(len); }

    template <class T>
    void Normalize(sf::Vector2<T> &vec){ float len = Length(vec);   vec/=(len); }

    template <class T>
    void Invert(sf::Vector3<T> &v) { v.x *= -1.0; v.y *= -1.0; v.z *= -1.0; }

    //Calculate dot product of two 3D vectors
    template <class T>
    float Dot(const sf::Vector3<T> &v1, const sf::Vector3<T> &v2){
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <class T>
    float Dot(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2){
        return v1.x * v2.x + v1.y * v2.y;
    }

    //Calculate the cross product of two 3D vectors
    template <class T>
    sf::Vector3<T> Cross(const sf::Vector3<T> &v1, const sf::Vector3<T> &v2)
    {
        sf::Vector3<T> vResult;
        vResult.x = v1.y * v2.z - v1.z * v2.y;
        vResult.y = v1.z * v2.x - v1.x * v2.z;
        vResult.z = v1.x * v2.y - v1.y * v2.x;
        return vResult;
    }

    template <class T>
    float Cross(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2)
    {
        return((v1.x * v2.y) - ( v1.y * v2.x ));
    }

    //Convert a 2D vector to a 3D vector ( nothing fancy just for a time saver )
    template <class T>
    sf::Vector3<T> Convert2Dto3D(const sf::Vector2<T> &vec) { return sf::Vector3<T>(vec.x, vec.y, 0); }

    // compute the inner product of a 2 3d vectors
    template <class T>
    float InnerProduct(sf::Vector3<T> &v1, sf::Vector3<T> &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z + v2.z;
    }

    template <class T>
    float InnerProduct(sf::Vector2<T> &v1, sf::Vector2<T> &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
}// namespace sfMath

#endif
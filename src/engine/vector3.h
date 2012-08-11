/* 
 * File:   vector3.h
 * Author: lzuercher
 *
 * Created on 17 July 2012, 21:52
 */

#ifndef VECTOR3_H
#define	VECTOR3_H

#include <math.h>

#pragma once

class Vector3
{
public:
    // Variablen
    union
    {
        struct
        {
            float x;	// Koordinaten
            float y;
            float z;
        };

        /*struct
        {
            float u;	// Texturkoordinaten
            float v;
            float w;
        };**/

        //float	c[3];	// Array der Koordinaten
    };

    // Konstruktoren
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z){}
    Vector3(const float f) : x(f), y(f), z(f) {}
    Vector3(const float _x, const float _y, const float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const float* pfComponent) : x(pfComponent[0]), y(pfComponent[1]), z(pfComponent[2])	{}

    // Zuweisungsoperatoren
    Vector3& operator = (const Vector3& v) {x = v.x; y = v.y; z = v.z; return *this;}
    Vector3& operator += (const Vector3& v) {x += v.x; y += v.y; z += v.z; return *this;}
    Vector3& operator -= (const Vector3& v) {x -= v.x; y -= v.y; z -= v.z; return *this;}
    Vector3& operator *= (const Vector3& v) {x *= v.x; y *= v.y; z *= v.z; return *this;}
    Vector3& operator *= (const float f) {x *= f; y *= f; z *= f; return *this;}
    Vector3& operator /= (const Vector3& v) {x /= v.x; y /= v.y; z /= v.z; return *this;}
    Vector3& operator /= (const float f) {x /= f; y /= f; z /= f; return *this;}
};

#endif	/* VECTOR3_H */


// Arithmetische Operatoren
inline Vector3 operator + (const Vector3& a, const Vector3& b)	{return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);}
inline Vector3 operator - (const Vector3& a, const Vector3& b)	{return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);}
inline Vector3 operator - (const Vector3& v)			{return Vector3(-v.x, -v.y, -v.z);}
inline Vector3 operator * (const Vector3& a, const Vector3& b)	{return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);}
inline Vector3 operator * (const Vector3& v, const float f)     {return Vector3(v.x * f, v.y * f, v.z * f);}
inline Vector3 operator * (const float f, const Vector3& v)     {return Vector3(v.x * f, v.y * f, v.z * f);}
inline Vector3 operator / (const Vector3& a, const Vector3& b)  {return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);}
inline Vector3 operator / (const Vector3& v, const float f)     {return Vector3(v.x / f, v.y / f, v.z / f);}

// Vergleichsoperatoren
inline bool operator == (const Vector3& a, const Vector3& b) {if(a.x != b.x) return false; if(a.y != b.y) return false; return a.z == b.z;}
inline bool operator != (const Vector3& a, const Vector3& b) {if(a.x != b.x) return true; if(a.y != b.y) return true; return a.z != b.z;}

// ******************************************************************
// Funktionen deklarieren
inline float	Vector3Length(const Vector3& v)	{return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);}
inline float	Vector3LengthSq(const Vector3& v) {return v.x * v.x + v.y * v.y + v.z * v.z;}
inline Vector3	Vector3Normalize(const Vector3& v) {return v / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);}
inline Vector3	Vector3NormalizeEx(const Vector3& v) {return v / (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z) + 0.0001f);}
inline Vector3	Vector3Cross(const Vector3& v1, const Vector3& v2){return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);}
inline float	Vector3Dot(const Vector3& v1, const Vector3& v2) {return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}
inline float	Vector3Angle(const Vector3& v1, const Vector3& v2) {return acosf((v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) / sqrtf((v1.x * v1.x + v1.y * v1.y + v1.z * v1.z) * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z)));}
inline Vector3	Vector3InterpolateCoords(const Vector3& v1, const Vector3& v2, const float p)	{return v1 + p * (v2 - v1);}
inline Vector3	Vector3InterpolateNormal(const Vector3& v1, const Vector3& v2, const float p)	{return Vector3NormalizeEx(v1 + p * (v2 - v1));}

// ******************************************************************
#ifndef MATH_HPP
#define MATH_HPP

// Std includes
#include <string>

// Local includes
#include "types.h"

struct Vec3 {
    float32 x, y, z;
    Vec3();
    Vec3(float32 f);
    Vec3(float32 x, float32 y, float32 z);
    Vec3 neg();
    Vec3 add(Vec3 v);
    Vec3 sub(Vec3 v);
    Vec3 mul(Vec3 v);
    Vec3 div(Vec3 v);
    Vec3 add(float32 f);
    Vec3 sub(float32 f);
    Vec3 mul(float32 f);
    Vec3 div(float32 f);
    float32 dot(Vec3 v);
    Vec3 cross(Vec3 v);
    float32 len();
    float32 lenSq();
    Vec3 normalize();
    void copy(Vec3 other);
    std::string toString();
};

Vec3 neg(Vec3 v);
Vec3 add(Vec3 v0, Vec3 v1);
Vec3 sub(Vec3 v0, Vec3 v1);
Vec3 mul(Vec3 v0, Vec3 v1);
Vec3 div(Vec3 v0, Vec3 v1);
Vec3 add(Vec3 v, float32 f);
Vec3 add(float32 f, Vec3 v);
Vec3 sub(Vec3 v, float32 f);
Vec3 sub(float32 f, Vec3 v);
Vec3 mul(Vec3 v, float32 f);
Vec3 mul(float32 f, Vec3 v);
Vec3 div(Vec3 v, float32 f);
Vec3 div(float32 f, Vec3 v);
float32 dot(Vec3 v0, Vec3 v1);
Vec3 cross(Vec3 v0, Vec3 v1);
float32 len(Vec3 v);
float32 lenSq(Vec3 v);
Vec3 normalize(Vec3 v);
std::string toString(Vec3 v);

// Overloaded ops
Vec3 operator-(Vec3 v);
Vec3 operator+(Vec3 v0, Vec3 v1);
Vec3 operator-(Vec3 v0, Vec3 v1);
Vec3 operator*(Vec3 v0, Vec3 v1);
Vec3 operator/(Vec3 v0, Vec3 v1);
Vec3 operator+(Vec3 v, float32 f);
Vec3 operator+(float32 f, Vec3 v);
Vec3 operator-(Vec3 v, float32 f);
Vec3 operator-(float32 f, Vec3 v);
Vec3 operator*(Vec3 v, float32 f);
Vec3 operator*(float32 f, Vec3 v);
Vec3 operator/(Vec3 v, float32 f);
Vec3 operator/(float32 f, Vec3 v);

#endif // MATH_HPP
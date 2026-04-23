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
    Vec3 neg() const;
    Vec3 add(const Vec3& v) const;
    Vec3 sub(const Vec3& v) const;
    Vec3 mul(const Vec3& v) const;
    Vec3 div(const Vec3& v) const;
    Vec3 add(float32 f) const;
    Vec3 sub(float32 f) const;
    Vec3 mul(float32 f) const;
    Vec3 div(float32 f) const;
    float32 dot(const Vec3& v) const;
    Vec3 cross(const Vec3& v) const;
    float32 len() const;
    float32 lenSq() const;
    Vec3 normalize() const;
    void copy(Vec3 other);
    std::string toString() const;
};

Vec3 neg(const Vec3& v);
Vec3 add(const Vec3& v0, const Vec3& v1);
Vec3 sub(const Vec3& v0, const Vec3& v1);
Vec3 mul(const Vec3& v0, const Vec3& v1);
Vec3 div(const Vec3& v0, const Vec3& v1);
Vec3 add(const Vec3& v, float32 f);
Vec3 add(float32 f, const Vec3& v);
Vec3 sub(const Vec3& v, float32 f);
Vec3 sub(float32 f, const Vec3& v);
Vec3 mul(const Vec3& v, float32 f);
Vec3 mul(float32 f, const Vec3& v);
Vec3 div(const Vec3& v, float32 f);
Vec3 div(float32 f, const Vec3& v);
float32 dot(const Vec3& v0, const Vec3& v1);
Vec3 cross(const Vec3& v0, const Vec3& v1);
float32 len(const Vec3& v);
float32 lenSq(const Vec3& v);
Vec3 normalize(const Vec3& v);
std::string toString(const Vec3& v);

// Overloaded ops
Vec3 operator-(const Vec3& v);
Vec3 operator+(const Vec3& v0, const Vec3& v1);
Vec3 operator-(const Vec3& v0, const Vec3& v1);
Vec3 operator*(const Vec3& v0, const Vec3& v1);
Vec3 operator/(const Vec3& v0, const Vec3& v1);
Vec3 operator+(const Vec3& v, float32 f);
Vec3 operator+(float32 f, const Vec3& v);
Vec3 operator-(const Vec3& v, float32 f);
Vec3 operator-(float32 f, const Vec3& v);
Vec3 operator*(const Vec3& v, float32 f);
Vec3 operator*(float32 f, const Vec3& v);
Vec3 operator/(const Vec3& v, float32 f);
Vec3 operator/(float32 f, const Vec3& v);
void operator+=(Vec3& v0, const Vec3& v1);
void operator-=(Vec3& v0, const Vec3& v1);
void operator*=(Vec3& v0, const Vec3& v1);
void operator/=(Vec3& v0, const Vec3& v1);
void operator+=(Vec3& v, float32 f);
void operator-=(Vec3& v, float32 f);
void operator*=(Vec3& v, float32 f);
void operator/=(Vec3& v, float32 f);
std::ostream& operator<<(std::ostream& out, const Vec3& v);

#endif // MATH_HPP
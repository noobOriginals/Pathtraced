#include "math.hpp"

// Std includes
#include <iostream>
#include <cmath>

// Vec3

Vec3::Vec3() {
    x = y = z = 0.0f;
}

Vec3::Vec3(float32 f) {
    x = y = z = f;
}

Vec3::Vec3(float32 x, float32 y, float32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::neg() const {
    return Vec3(-x, -y, -z);
}

Vec3 Vec3::inv() const {
    return Vec3(1.0 / x, 1.0 / y, 1.0 / z);
}

Vec3 Vec3::add(const Vec3& v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::sub(const Vec3& v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::mul(const Vec3& v) const {
    return Vec3(x * v.x, y * v.y, z * v.z);
}

Vec3 Vec3::div(const Vec3& v) const {
    return Vec3(x / v.x, y / v.y, z / v.z);
}

Vec3 Vec3::add(float32 f) const {
    return Vec3(x + f, y + f, z + f);
}

Vec3 Vec3::sub(float32 f) const {
    return Vec3(x - f, y - f, z - f);
}

Vec3 Vec3::mul(float32 f) const {
    return Vec3(x * f, y * f, z * f);
}

Vec3 Vec3::div(float32 f) const {
    return Vec3(x / f, y / f, z / f);
}

float32 Vec3::dot(const Vec3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::cross(const Vec3& v) const {
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float32 Vec3::len() const {
    return std::sqrt(x * x + y * y + z * z);
}

float32 Vec3::lenSq() const {
    return x * x + y * y + z * z;
}

Vec3 Vec3::normalize() const {
    float length = len();
    if (length == 0) {
        return Vec3(0.0f);
    } else {
        return Vec3(x / length, y / length, z / length);
    }
}

void Vec3::copy(Vec3 other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

std::string Vec3::toString() const {
    return "Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// Ops

Vec3 neg(const Vec3& v) {
    return v.neg();
}

Vec3 inv(const Vec3& v) {
    return v.inv();
}

Vec3 add(const Vec3& v0, const Vec3& v1) {
    return v0.add(v1);
}

Vec3 sub(const Vec3& v0, const Vec3& v1) {
    return v0.sub(v1);
}

Vec3 mul(const Vec3& v0, const Vec3& v1) {
    return v0.mul(v1);
}

Vec3 div(const Vec3& v0, const Vec3& v1) {
    return v0.div(v1);
}

Vec3 add(const Vec3& v, float32 f) {
    return v.add(f);
}

Vec3 add(float32 f, const Vec3& v) {
    return v.add(f);
}

Vec3 sub(const Vec3& v, float32 f) {
    return v.sub(f);
}

Vec3 sub(float32 f, const Vec3& v) {
    return Vec3(f - v.x, f - v.y, f - v.z);
}

Vec3 mul(const Vec3& v, float32 f) {
    return v.mul(f);
}

Vec3 mul(float32 f, const Vec3& v) {
    return v.mul(f);
}

Vec3 div(const Vec3& v, float32 f) {
    return v.div(f);
}

Vec3 div(float32 f, const Vec3& v) {
    return Vec3(f / v.x, f / v.y, f / v.z);
}

float32 dot(const Vec3& v0, const Vec3& v1) {
    return v0.dot(v1);
}

Vec3 cross(const Vec3& v0, const Vec3& v1) {
    return v0.cross(v1);
}

float32 len(const Vec3& v) {
    return v.len();
}

float32 lenSq(const Vec3& v) {
    return v.lenSq();
}

Vec3 normalize(const Vec3& v) {
    return v.normalize();
}

std::string toString(const Vec3& v) {
    return v.toString();
}

// Overloaded ops

Vec3 operator-(const Vec3& v) {
    return neg(v);
}

Vec3 operator+(const Vec3& v0, const Vec3& v1) {
    return add(v0, v1);
}

Vec3 operator-(const Vec3& v0, const Vec3& v1) {
    return sub(v0, v1);
}

Vec3 operator*(const Vec3& v0, const Vec3& v1) {
    return mul(v0, v1);
}

Vec3 operator/(const Vec3& v0, const Vec3& v1) {
    return div(v0, v1);
}

Vec3 operator+(const Vec3& v, float32 f) {
    return add(v, f);
}

Vec3 operator+(float32 f, const Vec3& v) {
    return add(f, v);
}

Vec3 operator-(const Vec3& v, float32 f) {
    return sub(v, f);
}

Vec3 operator-(float32 f, const Vec3& v) {
    return sub(f, v);
}

Vec3 operator*(const Vec3& v, float32 f) {
    return mul(v, f);
}

Vec3 operator*(float32 f, const Vec3& v) {
    return mul(f, v);
}

Vec3 operator/(const Vec3& v, float32 f) {
    return div(v, f);
}

Vec3 operator/(float32 f, const Vec3& v) {
    return div(f, v);
}

void operator+=(Vec3& v0, const Vec3& v1) {
    v0 = v0 + v1;
}

void operator-=(Vec3& v0, const Vec3& v1) {
    v0 = v0 - v1;
}

void operator*=(Vec3& v0, const Vec3& v1) {
    v0 = v0 * v1;
}

void operator/=(Vec3& v0, const Vec3& v1) {
    v0 = v0 / v1;
}

void operator+=(Vec3& v, float32 f) {
    v = v + f;
}

void operator-=(Vec3& v, float32 f) {
    v = v - f;
}

void operator*=(Vec3& v, float32 f) {
    v = v * f;
}

void operator/=(Vec3& v, float32 f) {
    v = v / f;
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    out << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}

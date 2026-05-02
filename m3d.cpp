#include "m3d.hpp"
#include <cmath>

namespace m3d {

float64 degToRad(float64 deg) {
    return deg * PI / 180.0;
}
float64 radToDeg(float64 rad) {
    return rad * 180.0 / PI;
}

// --- vec2 ---

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float32 s) : x(s), y(s) {}
vec2::vec2(float32 x, float32 y) : x(x), y(y) {}
vec2::vec2(const vec3& v) : x(v.x), y(v.y) {}
vec2::vec2(const vec4& v) : x(v.x), y(v.y) {}

vec2 vec2::neg() const {
    return vec2(-x, -y);
}
vec2 vec2::inv() const {
    return vec2(1.0f / x, 1.0f / y);
}

vec2 vec2::add(const vec2& o) const {
    return vec2(x + o.x, y + o.y);
}
vec2 vec2::add(float32 s) const {
    return vec2(x + s, y + s);
}
vec2 vec2::sub(const vec2& o) const {
    return vec2(x - o.x, y - o.y);
}
vec2 vec2::sub(float32 s) const {
    return vec2(x - s, y - s);
}
vec2 vec2::mul(const vec2& o) const {
    return vec2(x * o.x, y * o.y);
}
vec2 vec2::mul(float32 s) const {
    return vec2(x * s, y * s);
}
vec2 vec2::div(const vec2& o) const {
    return vec2(x / o.x, y / o.y);
}
vec2 vec2::div(float32 s) const {
    return vec2(x / s, y / s);
}

vec2& vec2::operator+=(const vec2& o) {
    x += o.x;
    y += o.y;
    return *this;
}
vec2& vec2::operator+=(float32 s) {
    x += s;
    y += s;
    return *this;
}
vec2& vec2::operator-=(const vec2& o) {
    x -= o.x;
    y -= o.y;
    return *this;
}
vec2& vec2::operator-=(float32 s) {
    x -= s;
    y -= s;
    return *this;
}
vec2& vec2::operator*=(const vec2& o) {
    x *= o.x;
    y *= o.y;
    return *this;
}
vec2& vec2::operator*=(float32 s) {
    x *= s;
    y *= s;
    return *this;
}
vec2& vec2::operator/=(const vec2& o) {
    x /= o.x;
    y /= o.y;
    return *this;
}
vec2& vec2::operator/=(float32 s) {
    x /= s;
    y /= s;
    return *this;
}

float32 vec2::lenSq() const {
    return x * x + y * y;
}
float32 vec2::len() const {
    return std::sqrt(lenSq());
}

// returns zero vector if length is below EPSILON to avoid division by zero
vec2 vec2::normalize() const {
    float32 l = len();
    if (l < EPSILON) {
        return vec2(0.0f);
    }
    return vec2(x / l, y / l);
}

float32 vec2::dot(const vec2& o) const {
    return x * o.x + y * o.y;
}
float32 vec2::cross(const vec2& o) const {
    return x * o.y - y * o.x;
}

vec2 add(const vec2& a, const vec2& b) {
    return a.add(b);
}
vec2 add(const vec2& v, float32 s) {
    return v.add(s);
}
vec2 add(float32 s, const vec2& v) {
    return v.add(s);
}
vec2 sub(const vec2& a, const vec2& b) {
    return a.sub(b);
}
vec2 sub(const vec2& v, float32 s) {
    return v.sub(s);
}
vec2 sub(float32 s, const vec2& v) {
    return vec2(s - v.x, s - v.y);
}
vec2 mul(const vec2& a, const vec2& b) {
    return a.mul(b);
}
vec2 mul(const vec2& v, float32 s) {
    return v.mul(s);
}
vec2 mul(float32 s, const vec2& v) {
    return v.mul(s);
}
vec2 div(const vec2& a, const vec2& b) {
    return a.div(b);
}
vec2 div(const vec2& v, float32 s) {
    return v.div(s);
}
vec2 div(float32 s, const vec2& v) {
    return vec2(s / v.x, s / v.y);
}

vec2 operator-(const vec2& v) {
    return v.neg();
}

vec2 operator+(const vec2& a, const vec2& b) {
    return a.add(b);
}
vec2 operator+(const vec2& v, float32 s) {
    return v.add(s);
}
vec2 operator+(float32 s, const vec2& v) {
    return v.add(s);
}
vec2 operator-(const vec2& a, const vec2& b) {
    return a.sub(b);
}
vec2 operator-(const vec2& v, float32 s) {
    return v.sub(s);
}
vec2 operator-(float32 s, const vec2& v) {
    return vec2(s - v.x, s - v.y);
}
vec2 operator*(const vec2& a, const vec2& b) {
    return a.mul(b);
}
vec2 operator*(const vec2& v, float32 s) {
    return v.mul(s);
}
vec2 operator*(float32 s, const vec2& v) {
    return v.mul(s);
}
vec2 operator/(const vec2& a, const vec2& b) {
    return a.div(b);
}
vec2 operator/(const vec2& v, float32 s) {
    return v.div(s);
}
vec2 operator/(float32 s, const vec2& v) {
    return vec2(s / v.x, s / v.y);
}

float32 dot(const vec2& a, const vec2& b) {
    return a.dot(b);
}
float32 cross(const vec2& a, const vec2& b) {
    return a.cross(b);
}
float32 lenSq(const vec2& v) {
    return v.lenSq();
}
float32 len(const vec2& v) {
    return v.len();
}
vec2 normalize(const vec2& v) {
    return v.normalize();
}

vec2 neg(const vec2& v) {
    return v.neg();
}
vec2 inv(const vec2& v) {
    return v.inv();
}

// --- vec3 ---

vec3::vec3() : x(0.0f), y(0.0f), z(0.0f) {}
vec3::vec3(float32 s) : x(s), y(s), z(s) {}
vec3::vec3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {}
vec3::vec3(const vec2& v, float32 z) : x(v.x), y(v.y), z(z) {}
vec3::vec3(const vec4& v) : x(v.x), y(v.y), z(v.z) {}

vec3 vec3::neg() const {
    return vec3(-x, -y, -z);
}
vec3 vec3::inv() const {
    return vec3(1.0f / x, 1.0f / y, 1.0f / z);
}

vec3 vec3::add(const vec3& o) const {
    return vec3(x + o.x, y + o.y, z + o.z);
}
vec3 vec3::add(float32 s) const {
    return vec3(x + s, y + s, z + s);
}
vec3 vec3::sub(const vec3& o) const {
    return vec3(x - o.x, y - o.y, z - o.z);
}
vec3 vec3::sub(float32 s) const {
    return vec3(x - s, y - s, z - s);
}
vec3 vec3::mul(const vec3& o) const {
    return vec3(x * o.x, y * o.y, z * o.z);
}
vec3 vec3::mul(float32 s) const {
    return vec3(x * s, y * s, z * s);
}
vec3 vec3::div(const vec3& o) const {
    return vec3(x / o.x, y / o.y, z / o.z);
}
vec3 vec3::div(float32 s) const {
    return vec3(x / s, y / s, z / s);
}

vec3& vec3::operator+=(const vec3& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}
vec3& vec3::operator+=(float32 s) {
    x += s;
    y += s;
    z += s;
    return *this;
}
vec3& vec3::operator-=(const vec3& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    return *this;
}
vec3& vec3::operator-=(float32 s) {
    x -= s;
    y -= s;
    z -= s;
    return *this;
}
vec3& vec3::operator*=(const vec3& o) {
    x *= o.x;
    y *= o.y;
    z *= o.z;
    return *this;
}
vec3& vec3::operator*=(float32 s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}
vec3& vec3::operator/=(const vec3& o) {
    x /= o.x;
    y /= o.y;
    z /= o.z;
    return *this;
}
vec3& vec3::operator/=(float32 s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

float32 vec3::lenSq() const {
    return x * x + y * y + z * z;
}
float32 vec3::len() const {
    return std::sqrt(lenSq());
}

// returns zero vector if length is below EPSILON to avoid division by zero
vec3 vec3::normalize() const {
    float32 l = len();
    if (l < EPSILON) {
        return vec3(0.0f);
    }
    return vec3(x / l, y / l, z / l);
}

float32 vec3::dot(const vec3& o) const {
    return x * o.x + y * o.y + z * o.z;
}

vec3 vec3::cross(const vec3& o) const {
    return vec3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
}

vec3 add(const vec3& a, const vec3& b) {
    return a.add(b);
}
vec3 add(const vec3& v, float32 s) {
    return v.add(s);
}
vec3 add(float32 s, const vec3& v) {
    return v.add(s);
}
vec3 sub(const vec3& a, const vec3& b) {
    return a.sub(b);
}
vec3 sub(const vec3& v, float32 s) {
    return v.sub(s);
}
vec3 sub(float32 s, const vec3& v) {
    return vec3(s - v.x, s - v.y, s - v.z);
}
vec3 mul(const vec3& a, const vec3& b) {
    return a.mul(b);
}
vec3 mul(const vec3& v, float32 s) {
    return v.mul(s);
}
vec3 mul(float32 s, const vec3& v) {
    return v.mul(s);
}
vec3 div(const vec3& a, const vec3& b) {
    return a.div(b);
}
vec3 div(const vec3& v, float32 s) {
    return v.div(s);
}
vec3 div(float32 s, const vec3& v) {
    return vec3(s / v.x, s / v.y, s / v.z);
}

vec3 operator-(const vec3& v) {
    return v.neg();
}

vec3 operator+(const vec3& a, const vec3& b) {
    return a.add(b);
}
vec3 operator+(const vec3& v, float32 s) {
    return v.add(s);
}
vec3 operator+(float32 s, const vec3& v) {
    return v.add(s);
}
vec3 operator-(const vec3& a, const vec3& b) {
    return a.sub(b);
}
vec3 operator-(const vec3& v, float32 s) {
    return v.sub(s);
}
vec3 operator-(float32 s, const vec3& v) {
    return vec3(s - v.x, s - v.y, s - v.z);
}
vec3 operator*(const vec3& a, const vec3& b) {
    return a.mul(b);
}
vec3 operator*(const vec3& v, float32 s) {
    return v.mul(s);
}
vec3 operator*(float32 s, const vec3& v) {
    return v.mul(s);
}
vec3 operator/(const vec3& a, const vec3& b) {
    return a.div(b);
}
vec3 operator/(const vec3& v, float32 s) {
    return v.div(s);
}
vec3 operator/(float32 s, const vec3& v) {
    return vec3(s / v.x, s / v.y, s / v.z);
}

float32 dot(const vec3& a, const vec3& b) {
    return a.dot(b);
}
vec3 cross(const vec3& a, const vec3& b) {
    return a.cross(b);
}
float32 lenSq(const vec3& v) {
    return v.lenSq();
}
float32 len(const vec3& v) {
    return v.len();
}
vec3 normalize(const vec3& v) {
    return v.normalize();
}

vec3 neg(const vec3& v) {
    return v.neg();
}
vec3 inv(const vec3& v) {
    return v.inv();
}

// --- vec4 ---

vec4::vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
vec4::vec4(float32 s) : x(s), y(s), z(s), w(s) {}
vec4::vec4(float32 x, float32 y, float32 z, float32 w) : x(x), y(y), z(z), w(w) {}
vec4::vec4(const vec3& v, float32 w) : x(v.x), y(v.y), z(v.z), w(w) {}
vec4::vec4(const vec2& v, float32 z, float32 w) : x(v.x), y(v.y), z(z), w(w) {}

vec4 vec4::neg() const {
    return vec4(-x, -y, -z, -w);
}
vec4 vec4::inv() const {
    return vec4(1.0f / x, 1.0f / y, 1.0f / z, 1.0f / w);
}

vec4 vec4::add(const vec4& o) const {
    return vec4(x + o.x, y + o.y, z + o.z, w + o.w);
}
vec4 vec4::add(float32 s) const {
    return vec4(x + s, y + s, z + s, w + s);
}
vec4 vec4::sub(const vec4& o) const {
    return vec4(x - o.x, y - o.y, z - o.z, w - o.w);
}
vec4 vec4::sub(float32 s) const {
    return vec4(x - s, y - s, z - s, w - s);
}
vec4 vec4::mul(const vec4& o) const {
    return vec4(x * o.x, y * o.y, z * o.z, w * o.w);
}
vec4 vec4::mul(float32 s) const {
    return vec4(x * s, y * s, z * s, w * s);
}
vec4 vec4::div(const vec4& o) const {
    return vec4(x / o.x, y / o.y, z / o.z, w / o.w);
}
vec4 vec4::div(float32 s) const {
    return vec4(x / s, y / s, z / s, w / s);
}

vec4& vec4::operator+=(const vec4& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    w += o.w;
    return *this;
}
vec4& vec4::operator+=(float32 s) {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
}
vec4& vec4::operator-=(const vec4& o) {
    x -= o.x;
    y -= o.y;
    z -= o.z;
    w -= o.w;
    return *this;
}
vec4& vec4::operator-=(float32 s) {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
}
vec4& vec4::operator*=(const vec4& o) {
    x *= o.x;
    y *= o.y;
    z *= o.z;
    w *= o.w;
    return *this;
}
vec4& vec4::operator*=(float32 s) {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
}
vec4& vec4::operator/=(const vec4& o) {
    x /= o.x;
    y /= o.y;
    z /= o.z;
    w /= o.w;
    return *this;
}
vec4& vec4::operator/=(float32 s) {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
}

float32 vec4::lenSq() const {
    return x * x + y * y + z * z + w * w;
}
float32 vec4::len() const {
    return std::sqrt(lenSq());
}

// returns zero vector if length is below EPSILON to avoid division by zero
vec4 vec4::normalize() const {
    float32 l = len();
    if (l < EPSILON) {
        return vec4(0.0f);
    }
    return vec4(x / l, y / l, z / l, w / l);
}

vec4 add(const vec4& a, const vec4& b) {
    return a.add(b);
}
vec4 add(const vec4& v, float32 s) {
    return v.add(s);
}
vec4 add(float32 s, const vec4& v) {
    return v.add(s);
}
vec4 sub(const vec4& a, const vec4& b) {
    return a.sub(b);
}
vec4 sub(const vec4& v, float32 s) {
    return v.sub(s);
}
vec4 sub(float32 s, const vec4& v) {
    return vec4(s - v.x, s - v.y, s - v.z, s - v.w);
}
vec4 mul(const vec4& a, const vec4& b) {
    return a.mul(b);
}
vec4 mul(const vec4& v, float32 s) {
    return v.mul(s);
}
vec4 mul(float32 s, const vec4& v) {
    return v.mul(s);
}
vec4 div(const vec4& a, const vec4& b) {
    return a.div(b);
}
vec4 div(const vec4& v, float32 s) {
    return v.div(s);
}
vec4 div(float32 s, const vec4& v) {
    return vec4(s / v.x, s / v.y, s / v.z, s / v.w);
}

vec4 operator-(const vec4& v) {
    return v.neg();
}

vec4 operator+(const vec4& a, const vec4& b) {
    return a.add(b);
}
vec4 operator+(const vec4& v, float32 s) {
    return v.add(s);
}
vec4 operator+(float32 s, const vec4& v) {
    return v.add(s);
}
vec4 operator-(const vec4& a, const vec4& b) {
    return a.sub(b);
}
vec4 operator-(const vec4& v, float32 s) {
    return v.sub(s);
}
vec4 operator-(float32 s, const vec4& v) {
    return vec4(s - v.x, s - v.y, s - v.z, s - v.w);
}
vec4 operator*(const vec4& a, const vec4& b) {
    return a.mul(b);
}
vec4 operator*(const vec4& v, float32 s) {
    return v.mul(s);
}
vec4 operator*(float32 s, const vec4& v) {
    return v.mul(s);
}
vec4 operator/(const vec4& a, const vec4& b) {
    return a.div(b);
}
vec4 operator/(const vec4& v, float32 s) {
    return v.div(s);
}
vec4 operator/(float32 s, const vec4& v) {
    return vec4(s / v.x, s / v.y, s / v.z, s / v.w);
}

float32 lenSq(const vec4& v) {
    return v.lenSq();
}
float32 len(const vec4& v) {
    return v.len();
}
vec4 normalize(const vec4& v) {
    return v.normalize();
}

vec4 neg(const vec4& v) {
    return v.neg();
}
vec4 inv(const vec4& v) {
    return v.inv();
}

// --- mat3 ---

mat3::mat3() : e{} {}
mat3::mat3(float32 d) : e{d, 0, 0, 0, d, 0, 0, 0, d} {}
mat3::mat3(const mat4& m) : e{m.e[0], m.e[1], m.e[2], m.e[4], m.e[5], m.e[6], m.e[8], m.e[9], m.e[10]} {}

mat3 mat3::add(const mat3& o) const {
    mat3 r;
    r.e[0] = e[0] + o.e[0];
    r.e[1] = e[1] + o.e[1];
    r.e[2] = e[2] + o.e[2];
    r.e[3] = e[3] + o.e[3];
    r.e[4] = e[4] + o.e[4];
    r.e[5] = e[5] + o.e[5];
    r.e[6] = e[6] + o.e[6];
    r.e[7] = e[7] + o.e[7];
    r.e[8] = e[8] + o.e[8];
    return r;
}
mat3 mat3::add(float32 s) const {
    mat3 r;
    r.e[0] = e[0] + s;
    r.e[1] = e[1] + s;
    r.e[2] = e[2] + s;
    r.e[3] = e[3] + s;
    r.e[4] = e[4] + s;
    r.e[5] = e[5] + s;
    r.e[6] = e[6] + s;
    r.e[7] = e[7] + s;
    r.e[8] = e[8] + s;
    return r;
}
mat3 mat3::sub(const mat3& o) const {
    mat3 r;
    r.e[0] = e[0] - o.e[0];
    r.e[1] = e[1] - o.e[1];
    r.e[2] = e[2] - o.e[2];
    r.e[3] = e[3] - o.e[3];
    r.e[4] = e[4] - o.e[4];
    r.e[5] = e[5] - o.e[5];
    r.e[6] = e[6] - o.e[6];
    r.e[7] = e[7] - o.e[7];
    r.e[8] = e[8] - o.e[8];
    return r;
}
mat3 mat3::sub(float32 s) const {
    mat3 r;
    r.e[0] = e[0] - s;
    r.e[1] = e[1] - s;
    r.e[2] = e[2] - s;
    r.e[3] = e[3] - s;
    r.e[4] = e[4] - s;
    r.e[5] = e[5] - s;
    r.e[6] = e[6] - s;
    r.e[7] = e[7] - s;
    r.e[8] = e[8] - s;
    return r;
}
mat3 mat3::mul(const mat3& o) const {
    mat3 r;
    r.e[0] = e[0] * o.e[0] + e[3] * o.e[1] + e[6] * o.e[2];
    r.e[1] = e[1] * o.e[0] + e[4] * o.e[1] + e[7] * o.e[2];
    r.e[2] = e[2] * o.e[0] + e[5] * o.e[1] + e[8] * o.e[2];
    r.e[3] = e[0] * o.e[3] + e[3] * o.e[4] + e[6] * o.e[5];
    r.e[4] = e[1] * o.e[3] + e[4] * o.e[4] + e[7] * o.e[5];
    r.e[5] = e[2] * o.e[3] + e[5] * o.e[4] + e[8] * o.e[5];
    r.e[6] = e[0] * o.e[6] + e[3] * o.e[7] + e[6] * o.e[8];
    r.e[7] = e[1] * o.e[6] + e[4] * o.e[7] + e[7] * o.e[8];
    r.e[8] = e[2] * o.e[6] + e[5] * o.e[7] + e[8] * o.e[8];
    return r;
}
mat3 mat3::mul(float32 s) const {
    mat3 r;
    r.e[0] = e[0] * s;
    r.e[1] = e[1] * s;
    r.e[2] = e[2] * s;
    r.e[3] = e[3] * s;
    r.e[4] = e[4] * s;
    r.e[5] = e[5] * s;
    r.e[6] = e[6] * s;
    r.e[7] = e[7] * s;
    r.e[8] = e[8] * s;
    return r;
}
vec3 mat3::mul(const vec3& v) const {
    return vec3(
        e[0] * v.x + e[3] * v.y + e[6] * v.z,
        e[1] * v.x + e[4] * v.y + e[7] * v.z,
        e[2] * v.x + e[5] * v.y + e[8] * v.z
    );
}
mat3 mat3::div(const mat3& o) const {
    mat3 r;
    r.e[0] = e[0] / o.e[0];
    r.e[1] = e[1] / o.e[1];
    r.e[2] = e[2] / o.e[2];
    r.e[3] = e[3] / o.e[3];
    r.e[4] = e[4] / o.e[4];
    r.e[5] = e[5] / o.e[5];
    r.e[6] = e[6] / o.e[6];
    r.e[7] = e[7] / o.e[7];
    r.e[8] = e[8] / o.e[8];
    return r;
}
mat3 mat3::div(float32 s) const {
    mat3 r;
    r.e[0] = e[0] / s;
    r.e[1] = e[1] / s;
    r.e[2] = e[2] / s;
    r.e[3] = e[3] / s;
    r.e[4] = e[4] / s;
    r.e[5] = e[5] / s;
    r.e[6] = e[6] / s;
    r.e[7] = e[7] / s;
    r.e[8] = e[8] / s;
    return r;
}

mat3& mat3::operator+=(const mat3& o) {
    e[0] += o.e[0];
    e[1] += o.e[1];
    e[2] += o.e[2];
    e[3] += o.e[3];
    e[4] += o.e[4];
    e[5] += o.e[5];
    e[6] += o.e[6];
    e[7] += o.e[7];
    e[8] += o.e[8];
    return *this;
}
mat3& mat3::operator+=(float32 s) {
    e[0] += s;
    e[1] += s;
    e[2] += s;
    e[3] += s;
    e[4] += s;
    e[5] += s;
    e[6] += s;
    e[7] += s;
    e[8] += s;
    return *this;
}
mat3& mat3::operator-=(const mat3& o) {
    e[0] -= o.e[0];
    e[1] -= o.e[1];
    e[2] -= o.e[2];
    e[3] -= o.e[3];
    e[4] -= o.e[4];
    e[5] -= o.e[5];
    e[6] -= o.e[6];
    e[7] -= o.e[7];
    e[8] -= o.e[8];
    return *this;
}
mat3& mat3::operator-=(float32 s) {
    e[0] -= s;
    e[1] -= s;
    e[2] -= s;
    e[3] -= s;
    e[4] -= s;
    e[5] -= s;
    e[6] -= s;
    e[7] -= s;
    e[8] -= s;
    return *this;
}
mat3& mat3::operator*=(const mat3& o) {
    *this = mul(o);
    return *this;
}
mat3& mat3::operator*=(float32 s) {
    e[0] *= s;
    e[1] *= s;
    e[2] *= s;
    e[3] *= s;
    e[4] *= s;
    e[5] *= s;
    e[6] *= s;
    e[7] *= s;
    e[8] *= s;
    return *this;
}
mat3& mat3::operator/=(const mat3& o) {
    e[0] /= o.e[0];
    e[1] /= o.e[1];
    e[2] /= o.e[2];
    e[3] /= o.e[3];
    e[4] /= o.e[4];
    e[5] /= o.e[5];
    e[6] /= o.e[6];
    e[7] /= o.e[7];
    e[8] /= o.e[8];
    return *this;
}
mat3& mat3::operator/=(float32 s) {
    e[0] /= s;
    e[1] /= s;
    e[2] /= s;
    e[3] /= s;
    e[4] /= s;
    e[5] /= s;
    e[6] /= s;
    e[7] /= s;
    e[8] /= s;
    return *this;
}

float32 mat3::determinant() const {
    return e[0] * (e[4] * e[8] - e[7] * e[5]) - e[3] * (e[1] * e[8] - e[7] * e[2]) + e[6] * (e[1] * e[5] - e[4] * e[2]);
}
mat3 mat3::transpose() const {
    mat3 r;
    r.e[0] = e[0];
    r.e[1] = e[3];
    r.e[2] = e[6];
    r.e[3] = e[1];
    r.e[4] = e[4];
    r.e[5] = e[7];
    r.e[6] = e[2];
    r.e[7] = e[5];
    r.e[8] = e[8];
    return r;
}
// returns zero matrix if singular
mat3 mat3::inverse() const {
    float32 d = determinant();
    if (std::abs(d) < EPSILON) {
        return mat3(0.0f);
    }
    float32 inv = 1.0f / d;
    mat3 r;
    r.e[0] = (e[4] * e[8] - e[7] * e[5]) * inv;
    r.e[1] = (-e[1] * e[8] + e[7] * e[2]) * inv;
    r.e[2] = (e[1] * e[5] - e[4] * e[2]) * inv;
    r.e[3] = (-e[3] * e[8] + e[6] * e[5]) * inv;
    r.e[4] = (e[0] * e[8] - e[6] * e[2]) * inv;
    r.e[5] = (-e[0] * e[5] + e[3] * e[2]) * inv;
    r.e[6] = (e[3] * e[7] - e[6] * e[4]) * inv;
    r.e[7] = (-e[0] * e[7] + e[6] * e[1]) * inv;
    r.e[8] = (e[0] * e[4] - e[3] * e[1]) * inv;
    return r;
}
float32 mat3::trace() const {
    return e[0] + e[4] + e[8];
}

mat3 add(const mat3& a, const mat3& b) {
    return a.add(b);
}
mat3 add(const mat3& m, float32 s) {
    return m.add(s);
}
mat3 add(float32 s, const mat3& m) {
    return m.add(s);
}
mat3 sub(const mat3& a, const mat3& b) {
    return a.sub(b);
}
mat3 sub(const mat3& m, float32 s) {
    return m.sub(s);
}
mat3 sub(float32 s, const mat3& m) {
    mat3 r;
    r.e[0] = s - m.e[0];
    r.e[1] = s - m.e[1];
    r.e[2] = s - m.e[2];
    r.e[3] = s - m.e[3];
    r.e[4] = s - m.e[4];
    r.e[5] = s - m.e[5];
    r.e[6] = s - m.e[6];
    r.e[7] = s - m.e[7];
    r.e[8] = s - m.e[8];
    return r;
}
mat3 mul(const mat3& a, const mat3& b) {
    return a.mul(b);
}
mat3 mul(const mat3& m, float32 s) {
    return m.mul(s);
}
mat3 mul(float32 s, const mat3& m) {
    return m.mul(s);
}
vec3 mul(const mat3& m, const vec3& v) {
    return m.mul(v);
}
mat3 div(const mat3& a, const mat3& b) {
    return a.div(b);
}
mat3 div(const mat3& m, float32 s) {
    return m.div(s);
}
mat3 div(float32 s, const mat3& m) {
    mat3 r;
    r.e[0] = s / m.e[0];
    r.e[1] = s / m.e[1];
    r.e[2] = s / m.e[2];
    r.e[3] = s / m.e[3];
    r.e[4] = s / m.e[4];
    r.e[5] = s / m.e[5];
    r.e[6] = s / m.e[6];
    r.e[7] = s / m.e[7];
    r.e[8] = s / m.e[8];
    return r;
}

mat3 operator+(const mat3& a, const mat3& b) {
    return a.add(b);
}
mat3 operator+(const mat3& m, float32 s) {
    return m.add(s);
}
mat3 operator+(float32 s, const mat3& m) {
    return m.add(s);
}
mat3 operator-(const mat3& a, const mat3& b) {
    return a.sub(b);
}
mat3 operator-(const mat3& m, float32 s) {
    return m.sub(s);
}
mat3 operator-(float32 s, const mat3& m) {
    return sub(s, m);
}
mat3 operator*(const mat3& a, const mat3& b) {
    return a.mul(b);
}
mat3 operator*(const mat3& m, float32 s) {
    return m.mul(s);
}
mat3 operator*(float32 s, const mat3& m) {
    return m.mul(s);
}
vec3 operator*(const mat3& m, const vec3& v) {
    return m.mul(v);
}
mat3 operator/(const mat3& a, const mat3& b) {
    return a.div(b);
}
mat3 operator/(const mat3& m, float32 s) {
    return m.div(s);
}
mat3 operator/(float32 s, const mat3& m) {
    return div(s, m);
}

float32 determinant(const mat3& m) {
    return m.determinant();
}
mat3 transpose(const mat3& m) {
    return m.transpose();
}
mat3 inverse(const mat3& m) {
    return m.inverse();
}
float32 trace(const mat3& m) {
    return m.trace();
}

mat3 mat3::translate(const vec2& t) const {
    return mul(m3d::translate(t));
}
mat3 mat3::rotate(float32 a) const {
    return mul(m3d::rotate(a));
}
mat3 mat3::scale(const vec2& sv) const {
    return mul(m3d::scale(sv));
}

mat3 translate(const vec2& t) {
    mat3 T;
    T.e[0] = 1.0f;
    T.e[3] = 0.0f;
    T.e[6] = t.x;
    T.e[1] = 0.0f;
    T.e[4] = 1.0f;
    T.e[7] = t.y;
    T.e[2] = 0.0f;
    T.e[5] = 0.0f;
    T.e[8] = 1.0f;
    return T;
}
mat3 translate(const mat3& m, const vec2& t) {
    return m.mul(translate(t));
}
mat3 rotate(float32 angle) {
    float32 c = std::cos(angle), s = std::sin(angle);
    mat3 R;
    R.e[0] = c;
    R.e[3] = -s;
    R.e[6] = 0.0f;
    R.e[1] = s;
    R.e[4] = c;
    R.e[7] = 0.0f;
    R.e[2] = 0.0f;
    R.e[5] = 0.0f;
    R.e[8] = 1.0f;
    return R;
}
mat3 rotate(const mat3& m, float32 angle) {
    return m.mul(rotate(angle));
}
mat3 scale(const vec2& sv) {
    mat3 S;
    S.e[0] = sv.x;
    S.e[3] = 0.0f;
    S.e[6] = 0.0f;
    S.e[1] = 0.0f;
    S.e[4] = sv.y;
    S.e[7] = 0.0f;
    S.e[2] = 0.0f;
    S.e[5] = 0.0f;
    S.e[8] = 1.0f;
    return S;
}
mat3 scale(const mat3& m, const vec2& sv) {
    return m.mul(scale(sv));
}

// --- mat4 ---

mat4::mat4() : e{} {}
mat4::mat4(float32 d) : e{d, 0, 0, 0, 0, d, 0, 0, 0, 0, d, 0, 0, 0, 0, d} {}
mat4::mat4(const mat3& m, float32 d) : e{m.e[0], m.e[1], m.e[2], 0.0f, m.e[3], m.e[4], m.e[5], 0.0f, m.e[6], m.e[7], m.e[8], 0.0f, 0.0f, 0.0f, 0.0f, d} {}

mat4 mat4::add(const mat4& o) const {
    mat4 r;
    r.e[0] = e[0] + o.e[0];
    r.e[1] = e[1] + o.e[1];
    r.e[2] = e[2] + o.e[2];
    r.e[3] = e[3] + o.e[3];
    r.e[4] = e[4] + o.e[4];
    r.e[5] = e[5] + o.e[5];
    r.e[6] = e[6] + o.e[6];
    r.e[7] = e[7] + o.e[7];
    r.e[8] = e[8] + o.e[8];
    r.e[9] = e[9] + o.e[9];
    r.e[10] = e[10] + o.e[10];
    r.e[11] = e[11] + o.e[11];
    r.e[12] = e[12] + o.e[12];
    r.e[13] = e[13] + o.e[13];
    r.e[14] = e[14] + o.e[14];
    r.e[15] = e[15] + o.e[15];
    return r;
}
mat4 mat4::add(float32 s) const {
    mat4 r;
    r.e[0] = e[0] + s;
    r.e[1] = e[1] + s;
    r.e[2] = e[2] + s;
    r.e[3] = e[3] + s;
    r.e[4] = e[4] + s;
    r.e[5] = e[5] + s;
    r.e[6] = e[6] + s;
    r.e[7] = e[7] + s;
    r.e[8] = e[8] + s;
    r.e[9] = e[9] + s;
    r.e[10] = e[10] + s;
    r.e[11] = e[11] + s;
    r.e[12] = e[12] + s;
    r.e[13] = e[13] + s;
    r.e[14] = e[14] + s;
    r.e[15] = e[15] + s;
    return r;
}
mat4 mat4::sub(const mat4& o) const {
    mat4 r;
    r.e[0] = e[0] - o.e[0];
    r.e[1] = e[1] - o.e[1];
    r.e[2] = e[2] - o.e[2];
    r.e[3] = e[3] - o.e[3];
    r.e[4] = e[4] - o.e[4];
    r.e[5] = e[5] - o.e[5];
    r.e[6] = e[6] - o.e[6];
    r.e[7] = e[7] - o.e[7];
    r.e[8] = e[8] - o.e[8];
    r.e[9] = e[9] - o.e[9];
    r.e[10] = e[10] - o.e[10];
    r.e[11] = e[11] - o.e[11];
    r.e[12] = e[12] - o.e[12];
    r.e[13] = e[13] - o.e[13];
    r.e[14] = e[14] - o.e[14];
    r.e[15] = e[15] - o.e[15];
    return r;
}
mat4 mat4::sub(float32 s) const {
    mat4 r;
    r.e[0] = e[0] - s;
    r.e[1] = e[1] - s;
    r.e[2] = e[2] - s;
    r.e[3] = e[3] - s;
    r.e[4] = e[4] - s;
    r.e[5] = e[5] - s;
    r.e[6] = e[6] - s;
    r.e[7] = e[7] - s;
    r.e[8] = e[8] - s;
    r.e[9] = e[9] - s;
    r.e[10] = e[10] - s;
    r.e[11] = e[11] - s;
    r.e[12] = e[12] - s;
    r.e[13] = e[13] - s;
    r.e[14] = e[14] - s;
    r.e[15] = e[15] - s;
    return r;
}
mat4 mat4::mul(const mat4& o) const {
    mat4 r;
    r.e[0] = e[0] * o.e[0] + e[4] * o.e[1] + e[8] * o.e[2] + e[12] * o.e[3];
    r.e[1] = e[1] * o.e[0] + e[5] * o.e[1] + e[9] * o.e[2] + e[13] * o.e[3];
    r.e[2] = e[2] * o.e[0] + e[6] * o.e[1] + e[10] * o.e[2] + e[14] * o.e[3];
    r.e[3] = e[3] * o.e[0] + e[7] * o.e[1] + e[11] * o.e[2] + e[15] * o.e[3];
    r.e[4] = e[0] * o.e[4] + e[4] * o.e[5] + e[8] * o.e[6] + e[12] * o.e[7];
    r.e[5] = e[1] * o.e[4] + e[5] * o.e[5] + e[9] * o.e[6] + e[13] * o.e[7];
    r.e[6] = e[2] * o.e[4] + e[6] * o.e[5] + e[10] * o.e[6] + e[14] * o.e[7];
    r.e[7] = e[3] * o.e[4] + e[7] * o.e[5] + e[11] * o.e[6] + e[15] * o.e[7];
    r.e[8] = e[0] * o.e[8] + e[4] * o.e[9] + e[8] * o.e[10] + e[12] * o.e[11];
    r.e[9] = e[1] * o.e[8] + e[5] * o.e[9] + e[9] * o.e[10] + e[13] * o.e[11];
    r.e[10] = e[2] * o.e[8] + e[6] * o.e[9] + e[10] * o.e[10] + e[14] * o.e[11];
    r.e[11] = e[3] * o.e[8] + e[7] * o.e[9] + e[11] * o.e[10] + e[15] * o.e[11];
    r.e[12] = e[0] * o.e[12] + e[4] * o.e[13] + e[8] * o.e[14] + e[12] * o.e[15];
    r.e[13] = e[1] * o.e[12] + e[5] * o.e[13] + e[9] * o.e[14] + e[13] * o.e[15];
    r.e[14] = e[2] * o.e[12] + e[6] * o.e[13] + e[10] * o.e[14] + e[14] * o.e[15];
    r.e[15] = e[3] * o.e[12] + e[7] * o.e[13] + e[11] * o.e[14] + e[15] * o.e[15];
    return r;
}
mat4 mat4::mul(float32 s) const {
    mat4 r;
    r.e[0] = e[0] * s;
    r.e[1] = e[1] * s;
    r.e[2] = e[2] * s;
    r.e[3] = e[3] * s;
    r.e[4] = e[4] * s;
    r.e[5] = e[5] * s;
    r.e[6] = e[6] * s;
    r.e[7] = e[7] * s;
    r.e[8] = e[8] * s;
    r.e[9] = e[9] * s;
    r.e[10] = e[10] * s;
    r.e[11] = e[11] * s;
    r.e[12] = e[12] * s;
    r.e[13] = e[13] * s;
    r.e[14] = e[14] * s;
    r.e[15] = e[15] * s;
    return r;
}
vec4 mat4::mul(const vec4& v) const {
    return vec4(
        e[0] * v.x + e[4] * v.y + e[8] * v.z + e[12] * v.w,
        e[1] * v.x + e[5] * v.y + e[9] * v.z + e[13] * v.w,
        e[2] * v.x + e[6] * v.y + e[10] * v.z + e[14] * v.w,
        e[3] * v.x + e[7] * v.y + e[11] * v.z + e[15] * v.w
    );
}
mat4 mat4::div(const mat4& o) const {
    mat4 r;
    r.e[0] = e[0] / o.e[0];
    r.e[1] = e[1] / o.e[1];
    r.e[2] = e[2] / o.e[2];
    r.e[3] = e[3] / o.e[3];
    r.e[4] = e[4] / o.e[4];
    r.e[5] = e[5] / o.e[5];
    r.e[6] = e[6] / o.e[6];
    r.e[7] = e[7] / o.e[7];
    r.e[8] = e[8] / o.e[8];
    r.e[9] = e[9] / o.e[9];
    r.e[10] = e[10] / o.e[10];
    r.e[11] = e[11] / o.e[11];
    r.e[12] = e[12] / o.e[12];
    r.e[13] = e[13] / o.e[13];
    r.e[14] = e[14] / o.e[14];
    r.e[15] = e[15] / o.e[15];
    return r;
}
mat4 mat4::div(float32 s) const {
    mat4 r;
    r.e[0] = e[0] / s;
    r.e[1] = e[1] / s;
    r.e[2] = e[2] / s;
    r.e[3] = e[3] / s;
    r.e[4] = e[4] / s;
    r.e[5] = e[5] / s;
    r.e[6] = e[6] / s;
    r.e[7] = e[7] / s;
    r.e[8] = e[8] / s;
    r.e[9] = e[9] / s;
    r.e[10] = e[10] / s;
    r.e[11] = e[11] / s;
    r.e[12] = e[12] / s;
    r.e[13] = e[13] / s;
    r.e[14] = e[14] / s;
    r.e[15] = e[15] / s;
    return r;
}

mat4& mat4::operator+=(const mat4& o) {
    e[0] += o.e[0];
    e[1] += o.e[1];
    e[2] += o.e[2];
    e[3] += o.e[3];
    e[4] += o.e[4];
    e[5] += o.e[5];
    e[6] += o.e[6];
    e[7] += o.e[7];
    e[8] += o.e[8];
    e[9] += o.e[9];
    e[10] += o.e[10];
    e[11] += o.e[11];
    e[12] += o.e[12];
    e[13] += o.e[13];
    e[14] += o.e[14];
    e[15] += o.e[15];
    return *this;
}
mat4& mat4::operator+=(float32 s) {
    e[0] += s;
    e[1] += s;
    e[2] += s;
    e[3] += s;
    e[4] += s;
    e[5] += s;
    e[6] += s;
    e[7] += s;
    e[8] += s;
    e[9] += s;
    e[10] += s;
    e[11] += s;
    e[12] += s;
    e[13] += s;
    e[14] += s;
    e[15] += s;
    return *this;
}
mat4& mat4::operator-=(const mat4& o) {
    e[0] -= o.e[0];
    e[1] -= o.e[1];
    e[2] -= o.e[2];
    e[3] -= o.e[3];
    e[4] -= o.e[4];
    e[5] -= o.e[5];
    e[6] -= o.e[6];
    e[7] -= o.e[7];
    e[8] -= o.e[8];
    e[9] -= o.e[9];
    e[10] -= o.e[10];
    e[11] -= o.e[11];
    e[12] -= o.e[12];
    e[13] -= o.e[13];
    e[14] -= o.e[14];
    e[15] -= o.e[15];
    return *this;
}
mat4& mat4::operator-=(float32 s) {
    e[0] -= s;
    e[1] -= s;
    e[2] -= s;
    e[3] -= s;
    e[4] -= s;
    e[5] -= s;
    e[6] -= s;
    e[7] -= s;
    e[8] -= s;
    e[9] -= s;
    e[10] -= s;
    e[11] -= s;
    e[12] -= s;
    e[13] -= s;
    e[14] -= s;
    e[15] -= s;
    return *this;
}
mat4& mat4::operator*=(const mat4& o) {
    *this = mul(o);
    return *this;
}
mat4& mat4::operator*=(float32 s) {
    e[0] *= s;
    e[1] *= s;
    e[2] *= s;
    e[3] *= s;
    e[4] *= s;
    e[5] *= s;
    e[6] *= s;
    e[7] *= s;
    e[8] *= s;
    e[9] *= s;
    e[10] *= s;
    e[11] *= s;
    e[12] *= s;
    e[13] *= s;
    e[14] *= s;
    e[15] *= s;
    return *this;
}
mat4& mat4::operator/=(const mat4& o) {
    e[0] /= o.e[0];
    e[1] /= o.e[1];
    e[2] /= o.e[2];
    e[3] /= o.e[3];
    e[4] /= o.e[4];
    e[5] /= o.e[5];
    e[6] /= o.e[6];
    e[7] /= o.e[7];
    e[8] /= o.e[8];
    e[9] /= o.e[9];
    e[10] /= o.e[10];
    e[11] /= o.e[11];
    e[12] /= o.e[12];
    e[13] /= o.e[13];
    e[14] /= o.e[14];
    e[15] /= o.e[15];
    return *this;
}
mat4& mat4::operator/=(float32 s) {
    e[0] /= s;
    e[1] /= s;
    e[2] /= s;
    e[3] /= s;
    e[4] /= s;
    e[5] /= s;
    e[6] /= s;
    e[7] /= s;
    e[8] /= s;
    e[9] /= s;
    e[10] /= s;
    e[11] /= s;
    e[12] /= s;
    e[13] /= s;
    e[14] /= s;
    e[15] /= s;
    return *this;
}

float32 mat4::determinant() const {
    float32 a0 = e[0] * e[5] - e[4] * e[1];
    float32 a1 = e[0] * e[9] - e[8] * e[1];
    float32 a2 = e[0] * e[13] - e[12] * e[1];
    float32 a3 = e[4] * e[9] - e[8] * e[5];
    float32 a4 = e[4] * e[13] - e[12] * e[5];
    float32 a5 = e[8] * e[13] - e[12] * e[9];
    float32 b0 = e[2] * e[7] - e[6] * e[3];
    float32 b1 = e[2] * e[11] - e[10] * e[3];
    float32 b2 = e[2] * e[15] - e[14] * e[3];
    float32 b3 = e[6] * e[11] - e[10] * e[7];
    float32 b4 = e[6] * e[15] - e[14] * e[7];
    float32 b5 = e[10] * e[15] - e[14] * e[11];
    return a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
}
mat4 mat4::transpose() const {
    mat4 r;
    r.e[0] = e[0];
    r.e[1] = e[4];
    r.e[2] = e[8];
    r.e[3] = e[12];
    r.e[4] = e[1];
    r.e[5] = e[5];
    r.e[6] = e[9];
    r.e[7] = e[13];
    r.e[8] = e[2];
    r.e[9] = e[6];
    r.e[10] = e[10];
    r.e[11] = e[14];
    r.e[12] = e[3];
    r.e[13] = e[7];
    r.e[14] = e[11];
    r.e[15] = e[15];
    return r;
}
// returns zero matrix if singular
mat4 mat4::inverse() const {
    float32 a0 = e[0] * e[5] - e[4] * e[1];
    float32 a1 = e[0] * e[9] - e[8] * e[1];
    float32 a2 = e[0] * e[13] - e[12] * e[1];
    float32 a3 = e[4] * e[9] - e[8] * e[5];
    float32 a4 = e[4] * e[13] - e[12] * e[5];
    float32 a5 = e[8] * e[13] - e[12] * e[9];
    float32 b0 = e[2] * e[7] - e[6] * e[3];
    float32 b1 = e[2] * e[11] - e[10] * e[3];
    float32 b2 = e[2] * e[15] - e[14] * e[3];
    float32 b3 = e[6] * e[11] - e[10] * e[7];
    float32 b4 = e[6] * e[15] - e[14] * e[7];
    float32 b5 = e[10] * e[15] - e[14] * e[11];
    float32 d = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    if (std::abs(d) < EPSILON) {
        return mat4(0.0f);
    }
    float32 inv = 1.0f / d;
    mat4 r;
    r.e[0] = (e[5] * b5 - e[9] * b4 + e[13] * b3) * inv;
    r.e[1] = (-e[1] * b5 + e[9] * b2 - e[13] * b1) * inv;
    r.e[2] = (e[1] * b4 - e[5] * b2 + e[13] * b0) * inv;
    r.e[3] = (-e[1] * b3 + e[5] * b1 - e[9] * b0) * inv;
    r.e[4] = (-e[4] * b5 + e[8] * b4 - e[12] * b3) * inv;
    r.e[5] = (e[0] * b5 - e[8] * b2 + e[12] * b1) * inv;
    r.e[6] = (-e[0] * b4 + e[4] * b2 - e[12] * b0) * inv;
    r.e[7] = (e[0] * b3 - e[4] * b1 + e[8] * b0) * inv;
    r.e[8] = (e[7] * a5 - e[11] * a4 + e[15] * a3) * inv;
    r.e[9] = (-e[3] * a5 + e[11] * a2 - e[15] * a1) * inv;
    r.e[10] = (e[3] * a4 - e[7] * a2 + e[15] * a0) * inv;
    r.e[11] = (-e[3] * a3 + e[7] * a1 - e[11] * a0) * inv;
    r.e[12] = (-e[6] * a5 + e[10] * a4 - e[14] * a3) * inv;
    r.e[13] = (e[2] * a5 - e[10] * a2 + e[14] * a1) * inv;
    r.e[14] = (-e[2] * a4 + e[6] * a2 - e[14] * a0) * inv;
    r.e[15] = (e[2] * a3 - e[6] * a1 + e[10] * a0) * inv;
    return r;
}
float32 mat4::trace() const {
    return e[0] + e[5] + e[10] + e[15];
}

mat4 add(const mat4& a, const mat4& b) {
    return a.add(b);
}
mat4 add(const mat4& m, float32 s) {
    return m.add(s);
}
mat4 add(float32 s, const mat4& m) {
    return m.add(s);
}
mat4 sub(const mat4& a, const mat4& b) {
    return a.sub(b);
}
mat4 sub(const mat4& m, float32 s) {
    return m.sub(s);
}
mat4 sub(float32 s, const mat4& m) {
    mat4 r;
    r.e[0] = s - m.e[0];
    r.e[1] = s - m.e[1];
    r.e[2] = s - m.e[2];
    r.e[3] = s - m.e[3];
    r.e[4] = s - m.e[4];
    r.e[5] = s - m.e[5];
    r.e[6] = s - m.e[6];
    r.e[7] = s - m.e[7];
    r.e[8] = s - m.e[8];
    r.e[9] = s - m.e[9];
    r.e[10] = s - m.e[10];
    r.e[11] = s - m.e[11];
    r.e[12] = s - m.e[12];
    r.e[13] = s - m.e[13];
    r.e[14] = s - m.e[14];
    r.e[15] = s - m.e[15];
    return r;
}
mat4 mul(const mat4& a, const mat4& b) {
    return a.mul(b);
}
mat4 mul(const mat4& m, float32 s) {
    return m.mul(s);
}
mat4 mul(float32 s, const mat4& m) {
    return m.mul(s);
}
vec4 mul(const mat4& m, const vec4& v) {
    return m.mul(v);
}
mat4 div(const mat4& a, const mat4& b) {
    return a.div(b);
}
mat4 div(const mat4& m, float32 s) {
    return m.div(s);
}
mat4 div(float32 s, const mat4& m) {
    mat4 r;
    r.e[0] = s / m.e[0];
    r.e[1] = s / m.e[1];
    r.e[2] = s / m.e[2];
    r.e[3] = s / m.e[3];
    r.e[4] = s / m.e[4];
    r.e[5] = s / m.e[5];
    r.e[6] = s / m.e[6];
    r.e[7] = s / m.e[7];
    r.e[8] = s / m.e[8];
    r.e[9] = s / m.e[9];
    r.e[10] = s / m.e[10];
    r.e[11] = s / m.e[11];
    r.e[12] = s / m.e[12];
    r.e[13] = s / m.e[13];
    r.e[14] = s / m.e[14];
    r.e[15] = s / m.e[15];
    return r;
}

mat4 operator+(const mat4& a, const mat4& b) {
    return a.add(b);
}
mat4 operator+(const mat4& m, float32 s) {
    return m.add(s);
}
mat4 operator+(float32 s, const mat4& m) {
    return m.add(s);
}
mat4 operator-(const mat4& a, const mat4& b) {
    return a.sub(b);
}
mat4 operator-(const mat4& m, float32 s) {
    return m.sub(s);
}
mat4 operator-(float32 s, const mat4& m) {
    return sub(s, m);
}
mat4 operator*(const mat4& a, const mat4& b) {
    return a.mul(b);
}
mat4 operator*(const mat4& m, float32 s) {
    return m.mul(s);
}
mat4 operator*(float32 s, const mat4& m) {
    return m.mul(s);
}
vec4 operator*(const mat4& m, const vec4& v) {
    return m.mul(v);
}
mat4 operator/(const mat4& a, const mat4& b) {
    return a.div(b);
}
mat4 operator/(const mat4& m, float32 s) {
    return m.div(s);
}
mat4 operator/(float32 s, const mat4& m) {
    return div(s, m);
}

float32 determinant(const mat4& m) {
    return m.determinant();
}
mat4 transpose(const mat4& m) {
    return m.transpose();
}
mat4 inverse(const mat4& m) {
    return m.inverse();
}
float32 trace(const mat4& m) {
    return m.trace();
}

mat4 mat4::translate(const vec3& t) const {
    return mul(m3d::translate(t));
}
mat4 mat4::rotate(float32 a, const vec3& axis) const {
    return mul(m3d::rotate(a, axis));
}
mat4 mat4::scale(const vec3& sv) const {
    return mul(m3d::scale(sv));
}
mat4 mat4::perspective(float32 fovy, float32 aspect, float32 zNear, float32 zFar) const {
    return mul(m3d::perspective(fovy, aspect, zNear, zFar));
}
mat4 mat4::ortho(float32 l, float32 r, float32 b, float32 t, float32 zNear, float32 zFar) const {
    return mul(m3d::ortho(l, r, b, t, zNear, zFar));
}
mat4 mat4::lookAt(const vec3& eye, const vec3& center, const vec3& up) const {
    return mul(m3d::lookAt(eye, center, up));
}

mat4 translate(const vec3& t) {
    mat4 T(1.0f);
    T.e[12] = t.x;
    T.e[13] = t.y;
    T.e[14] = t.z;
    return T;
}
mat4 translate(const mat4& m, const vec3& t) {
    return m.mul(translate(t));
}
mat4 rotate(float32 angle, const vec3& axis) {
    vec3 n = axis.normalize();
    float32 c = std::cos(angle), s = std::sin(angle), tc = 1.0f - c;
    float32 x = n.x, y = n.y, z = n.z;
    mat4 R;
    R.e[0] = tc * x * x + c;
    R.e[4] = tc * x * y - s * z;
    R.e[8] = tc * x * z + s * y;
    R.e[12] = 0.0f;
    R.e[1] = tc * x * y + s * z;
    R.e[5] = tc * y * y + c;
    R.e[9] = tc * y * z - s * x;
    R.e[13] = 0.0f;
    R.e[2] = tc * x * z - s * y;
    R.e[6] = tc * y * z + s * x;
    R.e[10] = tc * z * z + c;
    R.e[14] = 0.0f;
    R.e[3] = 0.0f;
    R.e[7] = 0.0f;
    R.e[11] = 0.0f;
    R.e[15] = 1.0f;
    return R;
}
mat4 rotate(const mat4& m, float32 angle, const vec3& axis) {
    return m.mul(rotate(angle, axis));
}
mat4 scale(const vec3& sv) {
    mat4 S;
    S.e[0] = sv.x;
    S.e[4] = 0.0f;
    S.e[8] = 0.0f;
    S.e[12] = 0.0f;
    S.e[1] = 0.0f;
    S.e[5] = sv.y;
    S.e[9] = 0.0f;
    S.e[13] = 0.0f;
    S.e[2] = 0.0f;
    S.e[6] = 0.0f;
    S.e[10] = sv.z;
    S.e[14] = 0.0f;
    S.e[3] = 0.0f;
    S.e[7] = 0.0f;
    S.e[11] = 0.0f;
    S.e[15] = 1.0f;
    return S;
}
mat4 scale(const mat4& m, const vec3& sv) {
    return m.mul(scale(sv));
}
mat4 perspective(float32 fovy, float32 aspect, float32 zNear, float32 zFar) {
    float32 f = 1.0f / std::tan(fovy * 0.5f);
    mat4 P;
    P.e[0] = f / aspect;
    P.e[4] = 0.0f;
    P.e[8] = 0.0f;
    P.e[12] = 0.0f;
    P.e[1] = 0.0f;
    P.e[5] = f;
    P.e[9] = 0.0f;
    P.e[13] = 0.0f;
    P.e[2] = 0.0f;
    P.e[6] = 0.0f;
    P.e[10] = (zNear + zFar) / (zNear - zFar);
    P.e[14] = (2.0f * zNear * zFar) / (zNear - zFar);
    P.e[3] = 0.0f;
    P.e[7] = 0.0f;
    P.e[11] = -1.0f;
    P.e[15] = 0.0f;
    return P;
}
mat4 perspective(const mat4& m, float32 fovy, float32 aspect, float32 zNear, float32 zFar) {
    return m.mul(perspective(fovy, aspect, zNear, zFar));
}
mat4 ortho(float32 l, float32 r, float32 b, float32 t, float32 zNear, float32 zFar) {
    mat4 O;
    O.e[0] = 2.0f / (r - l);
    O.e[4] = 0.0f;
    O.e[8] = 0.0f;
    O.e[12] = -(r + l) / (r - l);
    O.e[1] = 0.0f;
    O.e[5] = 2.0f / (t - b);
    O.e[9] = 0.0f;
    O.e[13] = -(t + b) / (t - b);
    O.e[2] = 0.0f;
    O.e[6] = 0.0f;
    O.e[10] = -2.0f / (zFar - zNear);
    O.e[14] = -(zFar + zNear) / (zFar - zNear);
    O.e[3] = 0.0f;
    O.e[7] = 0.0f;
    O.e[11] = 0.0f;
    O.e[15] = 1.0f;
    return O;
}
mat4 ortho(const mat4& m, float32 l, float32 r, float32 b, float32 t, float32 zNear, float32 zFar) {
    return m.mul(ortho(l, r, b, t, zNear, zFar));
}
mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    vec3 f = (center - eye).normalize();
    vec3 r = f.cross(up).normalize();
    vec3 u = r.cross(f);
    mat4 V;
    V.e[0] = r.x;
    V.e[4] = r.y;
    V.e[8] = r.z;
    V.e[12] = -r.dot(eye);
    V.e[1] = u.x;
    V.e[5] = u.y;
    V.e[9] = u.z;
    V.e[13] = -u.dot(eye);
    V.e[2] = -f.x;
    V.e[6] = -f.y;
    V.e[10] = -f.z;
    V.e[14] = f.dot(eye);
    V.e[3] = 0.0f;
    V.e[7] = 0.0f;
    V.e[11] = 0.0f;
    V.e[15] = 1.0f;
    return V;
}
mat4 lookAt(const mat4& m, const vec3& eye, const vec3& center, const vec3& up) {
    return m.mul(lookAt(eye, center, up));
}

}  // namespace m3d

#ifndef M3D_HPP
#define M3D_HPP

namespace m3d {

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef float float32;
typedef double float64;

const float64 PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
const float32 EPSILON = 1e-6f;

float64 degToRad(float64 deg);
float64 radToDeg(float64 rad);

struct vec2;
struct vec3;
struct vec4;
struct mat3;
struct mat4;

// --- vec2 ---

struct vec2 {
    float32 x, y;

    vec2();
    vec2(float32 s);
    vec2(float32 x, float32 y);
    explicit vec2(const vec3& v);
    explicit vec2(const vec4& v);

    vec2 add(const vec2& other) const;
    vec2 add(float32 s) const;
    vec2 sub(const vec2& other) const;
    vec2 sub(float32 s) const;
    vec2 mul(const vec2& other) const;
    vec2 mul(float32 s) const;
    vec2 div(const vec2& other) const;
    vec2 div(float32 s) const;

    vec2& operator+=(const vec2& other);
    vec2& operator+=(float32 s);
    vec2& operator-=(const vec2& other);
    vec2& operator-=(float32 s);
    vec2& operator*=(const vec2& other);
    vec2& operator*=(float32 s);
    vec2& operator/=(const vec2& other);
    vec2& operator/=(float32 s);

    float32 lenSq() const;
    float32 len() const;
    vec2 normalize() const;

    float32 dot(const vec2& other) const;
    float32 cross(const vec2& other) const;
};

vec2 add(const vec2& a, const vec2& b);
vec2 add(const vec2& v, float32 s);
vec2 add(float32 s, const vec2& v);
vec2 sub(const vec2& a, const vec2& b);
vec2 sub(const vec2& v, float32 s);
vec2 sub(float32 s, const vec2& v);
vec2 mul(const vec2& a, const vec2& b);
vec2 mul(const vec2& v, float32 s);
vec2 mul(float32 s, const vec2& v);
vec2 div(const vec2& a, const vec2& b);
vec2 div(const vec2& v, float32 s);
vec2 div(float32 s, const vec2& v);

vec2 operator+(const vec2& a, const vec2& b);
vec2 operator+(const vec2& v, float32 s);
vec2 operator+(float32 s, const vec2& v);
vec2 operator-(const vec2& a, const vec2& b);
vec2 operator-(const vec2& v, float32 s);
vec2 operator-(float32 s, const vec2& v);
vec2 operator*(const vec2& a, const vec2& b);
vec2 operator*(const vec2& v, float32 s);
vec2 operator*(float32 s, const vec2& v);
vec2 operator/(const vec2& a, const vec2& b);
vec2 operator/(const vec2& v, float32 s);
vec2 operator/(float32 s, const vec2& v);

float32 dot(const vec2& a, const vec2& b);
float32 cross(const vec2& a, const vec2& b);
float32 lenSq(const vec2& v);
float32 len(const vec2& v);
vec2 normalize(const vec2& v);

// --- vec3 ---

struct vec3 {
    float32 x, y, z;

    vec3();
    vec3(float32 s);
    vec3(float32 x, float32 y, float32 z);
    vec3(const vec2& v, float32 z = 0.0f);
    explicit vec3(const vec4& v);

    vec3 add(const vec3& other) const;
    vec3 add(float32 s) const;
    vec3 sub(const vec3& other) const;
    vec3 sub(float32 s) const;
    vec3 mul(const vec3& other) const;
    vec3 mul(float32 s) const;
    vec3 div(const vec3& other) const;
    vec3 div(float32 s) const;

    vec3& operator+=(const vec3& other);
    vec3& operator+=(float32 s);
    vec3& operator-=(const vec3& other);
    vec3& operator-=(float32 s);
    vec3& operator*=(const vec3& other);
    vec3& operator*=(float32 s);
    vec3& operator/=(const vec3& other);
    vec3& operator/=(float32 s);

    float32 lenSq() const;
    float32 len() const;
    vec3 normalize() const;

    float32 dot(const vec3& other) const;
    vec3 cross(const vec3& other) const;
};

vec3 add(const vec3& a, const vec3& b);
vec3 add(const vec3& v, float32 s);
vec3 add(float32 s, const vec3& v);
vec3 sub(const vec3& a, const vec3& b);
vec3 sub(const vec3& v, float32 s);
vec3 sub(float32 s, const vec3& v);
vec3 mul(const vec3& a, const vec3& b);
vec3 mul(const vec3& v, float32 s);
vec3 mul(float32 s, const vec3& v);
vec3 div(const vec3& a, const vec3& b);
vec3 div(const vec3& v, float32 s);
vec3 div(float32 s, const vec3& v);

vec3 operator+(const vec3& a, const vec3& b);
vec3 operator+(const vec3& v, float32 s);
vec3 operator+(float32 s, const vec3& v);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator-(const vec3& v, float32 s);
vec3 operator-(float32 s, const vec3& v);
vec3 operator*(const vec3& a, const vec3& b);
vec3 operator*(const vec3& v, float32 s);
vec3 operator*(float32 s, const vec3& v);
vec3 operator/(const vec3& a, const vec3& b);
vec3 operator/(const vec3& v, float32 s);
vec3 operator/(float32 s, const vec3& v);

float32 dot(const vec3& a, const vec3& b);
vec3 cross(const vec3& a, const vec3& b);
float32 lenSq(const vec3& v);
float32 len(const vec3& v);
vec3 normalize(const vec3& v);

// --- vec4 ---

struct vec4 {
    float32 x, y, z, w;

    vec4();
    vec4(float32 s);
    vec4(float32 x, float32 y, float32 z, float32 w);
    vec4(const vec3& v, float32 w = 0.0f);
    vec4(const vec2& v, float32 z = 0.0f, float32 w = 0.0f);

    vec4 add(const vec4& other) const;
    vec4 add(float32 s) const;
    vec4 sub(const vec4& other) const;
    vec4 sub(float32 s) const;
    vec4 mul(const vec4& other) const;
    vec4 mul(float32 s) const;
    vec4 div(const vec4& other) const;
    vec4 div(float32 s) const;

    vec4& operator+=(const vec4& other);
    vec4& operator+=(float32 s);
    vec4& operator-=(const vec4& other);
    vec4& operator-=(float32 s);
    vec4& operator*=(const vec4& other);
    vec4& operator*=(float32 s);
    vec4& operator/=(const vec4& other);
    vec4& operator/=(float32 s);

    float32 lenSq() const;
    float32 len() const;
    vec4 normalize() const;
};

vec4 add(const vec4& a, const vec4& b);
vec4 add(const vec4& v, float32 s);
vec4 add(float32 s, const vec4& v);
vec4 sub(const vec4& a, const vec4& b);
vec4 sub(const vec4& v, float32 s);
vec4 sub(float32 s, const vec4& v);
vec4 mul(const vec4& a, const vec4& b);
vec4 mul(const vec4& v, float32 s);
vec4 mul(float32 s, const vec4& v);
vec4 div(const vec4& a, const vec4& b);
vec4 div(const vec4& v, float32 s);
vec4 div(float32 s, const vec4& v);

vec4 operator+(const vec4& a, const vec4& b);
vec4 operator+(const vec4& v, float32 s);
vec4 operator+(float32 s, const vec4& v);
vec4 operator-(const vec4& a, const vec4& b);
vec4 operator-(const vec4& v, float32 s);
vec4 operator-(float32 s, const vec4& v);
vec4 operator*(const vec4& a, const vec4& b);
vec4 operator*(const vec4& v, float32 s);
vec4 operator*(float32 s, const vec4& v);
vec4 operator/(const vec4& a, const vec4& b);
vec4 operator/(const vec4& v, float32 s);
vec4 operator/(float32 s, const vec4& v);

float32 lenSq(const vec4& v);
float32 len(const vec4& v);
vec4 normalize(const vec4& v);

// --- mat3 ---

struct mat3 {
    float32 e[9];  // column-major: e[col * 3 + row]

    mat3();
    mat3(float32 diagonal);
    explicit mat3(const mat4& m);

    mat3 add(const mat3& o) const;
    mat3 add(float32 s) const;
    mat3 sub(const mat3& o) const;
    mat3 sub(float32 s) const;
    mat3 mul(const mat3& o) const;
    mat3 mul(float32 s) const;
    vec3 mul(const vec3& v) const;
    mat3 div(const mat3& o) const;
    mat3 div(float32 s) const;

    mat3& operator+=(const mat3& o);
    mat3& operator+=(float32 s);
    mat3& operator-=(const mat3& o);
    mat3& operator-=(float32 s);
    mat3& operator*=(const mat3& o);
    mat3& operator*=(float32 s);
    mat3& operator/=(const mat3& o);
    mat3& operator/=(float32 s);

    float32 determinant() const;
    mat3 transpose() const;
    mat3 inverse() const;
    float32 trace() const;

    mat3 translate(const vec2& t) const;
    mat3 rotate(float32 angle) const;
    mat3 scale(const vec2& s) const;
};

mat3 add(const mat3& a, const mat3& b);
mat3 add(const mat3& m, float32 s);
mat3 add(float32 s, const mat3& m);
mat3 sub(const mat3& a, const mat3& b);
mat3 sub(const mat3& m, float32 s);
mat3 sub(float32 s, const mat3& m);
mat3 mul(const mat3& a, const mat3& b);
mat3 mul(const mat3& m, float32 s);
mat3 mul(float32 s, const mat3& m);
vec3 mul(const mat3& m, const vec3& v);
mat3 div(const mat3& a, const mat3& b);
mat3 div(const mat3& m, float32 s);
mat3 div(float32 s, const mat3& m);

mat3 operator+(const mat3& a, const mat3& b);
mat3 operator+(const mat3& m, float32 s);
mat3 operator+(float32 s, const mat3& m);
mat3 operator-(const mat3& a, const mat3& b);
mat3 operator-(const mat3& m, float32 s);
mat3 operator-(float32 s, const mat3& m);
mat3 operator*(const mat3& a, const mat3& b);
mat3 operator*(const mat3& m, float32 s);
mat3 operator*(float32 s, const mat3& m);
vec3 operator*(const mat3& m, const vec3& v);
mat3 operator/(const mat3& a, const mat3& b);
mat3 operator/(const mat3& m, float32 s);
mat3 operator/(float32 s, const mat3& m);

float32 determinant(const mat3& m);
mat3 transpose(const mat3& m);
mat3 inverse(const mat3& m);
float32 trace(const mat3& m);

mat3 translate(const vec2& t);
mat3 translate(const mat3& m, const vec2& t);
mat3 rotate(float32 angle);
mat3 rotate(const mat3& m, float32 angle);
mat3 scale(const vec2& s);
mat3 scale(const mat3& m, const vec2& s);

// --- mat4 ---

struct mat4 {
    float32 e[16];  // column-major: e[col * 4 + row]

    mat4();
    mat4(float32 diagonal);
    mat4(const mat3& m, float32 d = 0.0f);

    mat4 add(const mat4& o) const;
    mat4 add(float32 s) const;
    mat4 sub(const mat4& o) const;
    mat4 sub(float32 s) const;
    mat4 mul(const mat4& o) const;
    mat4 mul(float32 s) const;
    vec4 mul(const vec4& v) const;
    mat4 div(const mat4& o) const;
    mat4 div(float32 s) const;

    mat4& operator+=(const mat4& o);
    mat4& operator+=(float32 s);
    mat4& operator-=(const mat4& o);
    mat4& operator-=(float32 s);
    mat4& operator*=(const mat4& o);
    mat4& operator*=(float32 s);
    mat4& operator/=(const mat4& o);
    mat4& operator/=(float32 s);

    float32 determinant() const;
    mat4 transpose() const;
    mat4 inverse() const;
    float32 trace() const;

    mat4 translate(const vec3& t) const;
    mat4 rotate(float32 angle, const vec3& axis) const;
    mat4 scale(const vec3& s) const;
    mat4 perspective(float32 fovy, float32 aspect, float32 zNear, float32 zFar) const;
    mat4 ortho(float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar) const;
    mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) const;
};

mat4 add(const mat4& a, const mat4& b);
mat4 add(const mat4& m, float32 s);
mat4 add(float32 s, const mat4& m);
mat4 sub(const mat4& a, const mat4& b);
mat4 sub(const mat4& m, float32 s);
mat4 sub(float32 s, const mat4& m);
mat4 mul(const mat4& a, const mat4& b);
mat4 mul(const mat4& m, float32 s);
mat4 mul(float32 s, const mat4& m);
vec4 mul(const mat4& m, const vec4& v);
mat4 div(const mat4& a, const mat4& b);
mat4 div(const mat4& m, float32 s);
mat4 div(float32 s, const mat4& m);

mat4 operator+(const mat4& a, const mat4& b);
mat4 operator+(const mat4& m, float32 s);
mat4 operator+(float32 s, const mat4& m);
mat4 operator-(const mat4& a, const mat4& b);
mat4 operator-(const mat4& m, float32 s);
mat4 operator-(float32 s, const mat4& m);
mat4 operator*(const mat4& a, const mat4& b);
mat4 operator*(const mat4& m, float32 s);
mat4 operator*(float32 s, const mat4& m);
vec4 operator*(const mat4& m, const vec4& v);
mat4 operator/(const mat4& a, const mat4& b);
mat4 operator/(const mat4& m, float32 s);
mat4 operator/(float32 s, const mat4& m);

float32 determinant(const mat4& m);
mat4 transpose(const mat4& m);
mat4 inverse(const mat4& m);
float32 trace(const mat4& m);

mat4 translate(const vec3& t);
mat4 translate(const mat4& m, const vec3& t);
mat4 rotate(float32 angle, const vec3& axis);
mat4 rotate(const mat4& m, float32 angle, const vec3& axis);
mat4 scale(const vec3& s);
mat4 scale(const mat4& m, const vec3& s);
mat4 perspective(float32 fovy, float32 aspect, float32 zNear, float32 zFar);
mat4 perspective(const mat4& m, float32 fovy, float32 aspect, float32 zNear, float32 zFar);
mat4 ortho(float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);
mat4 ortho(const mat4& m, float32 left, float32 right, float32 bottom, float32 top, float32 zNear, float32 zFar);
mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4 lookAt(const mat4& m, const vec3& eye, const vec3& center, const vec3& up);

}  // namespace m3d

#endif  // M3D_HPP

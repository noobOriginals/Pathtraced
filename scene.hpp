#ifndef SCENE_HPP
#define SCENE_HPP

// Std includes
#include <cstdlib>
#include <vector>
#include <limits>
#include <string>
#include <fstream>

// Local includes
#include "m3d.hpp"
#include "materials.hpp"
#include "geometry.hpp"

struct Object {
    Hittable* obj;
    Material* mat;

    Object(Hittable* obj, Material* mat) : obj(obj), mat(mat) {}

    bool hitRay(const Ray& ray, Hitpoint* hp, float32 minT, float32 maxT) const {
        return obj->hitRay(ray, hp, minT, maxT);
    }
};

typedef std::vector<Object> Scene;

Material* traceScene(const Scene& scene, const Ray& ray, Hitpoint* hp) {
    Material* mat = nullptr;
    m3d::float32 closestT = std::numeric_limits<float32>::max();
    for (const Object& o : scene) {
        if (o.hitRay(ray, hp, m3d::EPSILON, closestT)) {
            mat = o.mat;
            closestT = hp->t;
        }
    }
    return mat;
}

Scene loadSceneFromFile(std::string filename) {
    Scene scene;
    std::fstream file(filename, std::ios::in);



    file.close();
    return scene;
}

void saveVec3(const m3d::vec3& v, std::ostream& file) {
    file << v.x << " " << v.y << " " << v.z;
}

void saveHittable(Hittable* obj, std::ostream& file) {
    m3d::int32 type = obj->type();
    switch (type) {
    case SPHERE: {
        Sphere* sphere = (Sphere*)obj;
        m3d::vec3 origin = sphere->getOrigin();
        file << "SPH : ";
        saveVec3(sphere->getOrigin(), file);
        file << " " << sphere->getRadius();
        break;
    }

    case TRIANGLE: {
        Triangle* triangle = (Triangle*)obj;
        file << "TRI : ";
        saveVec3(triangle->getA(), file);
        file << " ";
        saveVec3(triangle->getB(), file);
        file << " ";
        saveVec3(triangle->getC(), file);
        break;
    }

    case QUAD: {
        Quad* quad = (Quad*)obj;
        file << "QUD : ";
        saveVec3(quad->getCenter(), file);
        file << " ";
        saveVec3(quad->getU(), file);
        file << " ";
        saveVec3(quad->getV(), file);
        break;
    }

    default: {
        break;
    }
    }
}

void saveMaterial(Material* mat, std::ostream& file) {
    m3d::int32 type = mat->type;
    switch (type) {
    case LAMBERTIAN: {
        file << "LMB : ";
        saveVec3(mat->color, file);
        break;
    }

    case METAL: {
        file << "MTL : ";
        saveVec3(mat->color, file);
        file << " " << mat->fuzz;
        break;
    }

    case DIELECTRIC: {
        file << "DIE : ";
        saveVec3(mat->color, file);
        file << " " << mat->refIdx;
        break;
    }

    default: {
        break;
    }
    }
}

void saveScene(const Scene& s, std::string filename) {
    std::fstream file(filename, std::ios::out);

    for (const Object& o : s) {
        saveHittable(o.obj, file);
        file << "\n";
        saveMaterial(o.mat, file);
        file << "\n\n";
    }

    file.close();
}

#endif // SCENE_HPP
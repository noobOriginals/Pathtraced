#include <scene/scene.hpp>

// Std includes
#include <iostream>
#include <fstream>

// Local includes
#include <lib/m3d.hpp>
#include <geometry/hittable.hpp>
#include <geometry/sphere.hpp>
#include <geometry/triangle.hpp>
#include <geometry/quad.hpp>
#include <material/material.hpp>

#define handleReadError(x) if (!x) { std::cout << "Invalid format for \"" << filepath << "\" scene file!"; return; }

using namespace m3d;

namespace scene {

// Scene

Scene::Scene(std::string filepath) {
    numLoaded = 0;
    std::fstream file(filepath, std::ios::in);
    std::string type;
    while ((file >> type)) {
        geo::Hittable* h = nullptr;
        if (type == "Sphere") {
            float32 x, y, z, r;
            handleReadError((file >> x >> y >> z >> r))
            h = new geo::Sphere(vec3(x, y, z), r);
        }
        if (type == "Triangle") {
            float32 ax, ay, az, bx, by, bz, cx, cy, cz;
            handleReadError((file >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz))
            h = new geo::Triangle(vec3(ax, ay, az), vec3(bx, by, bz), vec3(cx, cy, cz));
        }
        if (type == "Quad") {
            float32 cx, cy, cz, ax, ay, az, bx, by, bz;
            handleReadError((file >> cx >> cy >> cz >> ax >> ay >> az >> bx >> by >> bz))
            h = new geo::Quad(vec3(cx, cy, cz), vec3(ax, ay, az), vec3(bx, by, bz));
        }
        handleReadError(h)
        handleReadError((file >> type))
        mat::Material* m = nullptr;
        if (type == "Diffuse") {
            float32 r, g, b;
            handleReadError((file >> r >> g >> b))
            m = new mat::Material(mat::DIFFUSE, vec3(r, g, b), 0.0f);
        }
        if (type == "Metal") {
            float32 r, g, b, f;
            handleReadError((file >> r >> g >> b >> f))
            m = new mat::Material(mat::METAL, vec3(r, g, b), f);
        }
        if (type == "Dielectric") {
            float32 r, g, b, i;
            handleReadError((file >> r >> g >> b >> i))
            m = new mat::Material(mat::DIELECTRIC, vec3(r, g, b), i);
        }
        handleReadError(m)
        objects.push_back(Object(h, m));
        numLoaded++;
    }
    file.close();
    loadedFromFile = true;
    std::cout << "Loaded \"" << filepath << "\" successfully!\n";
}

Scene::~Scene() {
    if (!loadedFromFile) {
        return;
    }
    for (int32 i = 0; i < numLoaded; i++) {
        delete objects[i].h;
        delete objects[i].m;
    }
}

void Scene::add(const Object& obj) {
    objects.push_back(obj);
}

mat::Material* Scene::getClosestHit(const Ray& ray, Hitpoint& hp) const {
    mat::Material* mat = nullptr;
    float32 closestT = std::numeric_limits<float32>::max();
    for (const Object& obj : objects) {
        if (obj.hit(ray, hp, 1e-4f, closestT)) {
            mat = obj.m;
            closestT = hp.t;
        }
    }
    return mat;
}

void Scene::save(std::string filepath) const {
    std::fstream file(filepath, std::ios::out);
    for (const Object& obj : objects) {
        file << obj.h->toString() << "\n" << obj.m->toString() << "\n";
    }
    file.close();
}

} // namespace scene
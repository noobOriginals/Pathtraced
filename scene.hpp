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
#include "camera.hpp"
#include "render.hpp"

struct Object {
    Hittable* obj;
    Material* mat;

    Object(Hittable* obj, Material* mat) : obj(obj), mat(mat) {}

    bool hitRay(const Ray& ray, Hitpoint* hp, m3d::float32 minT, m3d::float32 maxT) const {
        return obj->hitRay(ray, hp, minT, maxT);
    }
};

void saveVec3(const m3d::vec3& v, std::ostream& file);
void saveHittable(Hittable* obj, std::ostream& file);
void saveMaterial(Material* mat, std::ostream& file);

class Scene;
typedef m3d::vec3 (*SceneRaytraceCallback)(const Scene* scene, const Ray& ray, m3d::int32 depth);

class Scene {
public:
    Scene();
    Scene(m3d::int32 imgWidth, m3d::int32 imgHeight, m3d::float32 vfov);
    Scene(m3d::int32 imgWidth, m3d::int32 imgHeight, m3d::float32 vfov, m3d::vec3 camPos, m3d::vec3 camLookat);
    Scene(std::string filepath);

    void add(const Object& o);

    void renderScene();
    Material* trace(const Ray& ray, Hitpoint* hp) const;
    void saveRender(std::string filepath) const;
    void saveScene(std::string filepath) const;
    void loadScene(std::string filepath);

    const std::vector<Object>& getObjects();
    Render& getRender();

    void setRaytraceCallback(SceneRaytraceCallback rt);
    SceneRaytraceCallback getRaytraceCallback();

private:
    std::vector<Object> objects;
    Render render;
    SceneRaytraceCallback rt;
};

#endif // SCENE_HPP
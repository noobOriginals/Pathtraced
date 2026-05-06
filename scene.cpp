#include "scene.hpp"

// Local includes
#include "util.hpp"

using namespace m3d;

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

vec3 defaultSceneRaytraceCalback(const Scene* scene, const Ray& ray, int32 depth) {
    if (depth < 1) {
        return vec3(0.0f);
    }
    vec3 color = skyColor(ray);
    Hitpoint hp;
    Material* mat;
    if ((mat = scene->trace(ray, &hp))) {
        ScatterResult r = mat->scatter(ray, hp);
        color = r.color;
        if (r.scattered) {
            color *= defaultSceneRaytraceCalback(scene, r.ray, depth - 1);
        } else {
            color = vec3(0.0f);
        }
    }
    return color;
}

vec3 sceneRenderRaytraceCallback(const Render* render, const Ray& ray, int32 depth) {
    Scene* scene = (Scene*)render->getUserPtr();
    if (!scene) {
        return vec3(-1.0f);
    }
    return scene->getRaytraceCallback()(scene, ray, depth);
}

void saveVec3(const vec3& v, std::ostream& file) {
    file << v.x << " " << v.y << " " << v.z;
}

void saveHittable(Hittable* obj, std::ostream& file) {
    int32 type = obj->type();
    switch (type) {
    case SPHERE: {
        Sphere* sphere = (Sphere*)obj;
        vec3 origin = sphere->getOrigin();
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
    int32 type = mat->type;
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

Scene::Scene() : render(800, 600, 25.0f) {
    render.setCameraPosAndLookat(vec3(0.0f, 2.0f, 5.0f), vec3(0.0f));
    render.setUserPtr(this);
    render.setRaytraceCallback(sceneRenderRaytraceCallback);
    rt = defaultSceneRaytraceCalback;
}

Scene::Scene(int32 imgWidth, int32 imgHeight, float32 vfov) : render(imgWidth, imgHeight, vfov) {
    render.setUserPtr(this);
    render.setRaytraceCallback(sceneRenderRaytraceCallback);
    rt = defaultSceneRaytraceCalback;
}

Scene::Scene(int32 imgWidth, int32 imgHeight, float32 vfov, vec3 camPos, vec3 camLookat) : render(imgWidth, imgHeight, vfov) {
    render.setCameraPosAndLookat(camPos, camLookat);
    render.setUserPtr(this);
    render.setRaytraceCallback(sceneRenderRaytraceCallback);
    rt = defaultSceneRaytraceCalback;
}

Scene::Scene(std::string filepath) {
    loadScene(filepath);
    render.setUserPtr(this);
    render.setRaytraceCallback(sceneRenderRaytraceCallback);
    rt = defaultSceneRaytraceCalback;
}

void Scene::add(const Object& o) {
    objects.push_back(o);
}

void Scene::renderScene() {
    render.render();
}

Material* Scene::trace(const Ray& ray, Hitpoint* hp) const {
    Material* mat = nullptr;
    float32 closestT = std::numeric_limits<float32>::max();
    for (const Object& o : objects) {
        if (o.hitRay(ray, hp, EPSILON, closestT)) {
            mat = o.mat;
            closestT = hp->t;
        }
    }
    return mat;
}

void Scene::saveRender(std::string filepath) const {
    render.save(filepath);
}

void Scene::saveScene(std::string filepath) const {
    std::fstream file(filepath, std::ios::out);
    for (const Object& o : objects) {
        saveHittable(o.obj, file);
        file << "\n";
        saveMaterial(o.mat, file);
        file << "\n\n";
    }
    file << "PARAM : ";
    file << render.getViewport().getScreenWidth() << " " << render.getViewport().getScreenHeight() << " " << radToDeg(render.getViewport().getVerticalFOV()) << " ";
    saveVec3(render.getCamera().getPos(), file);
    file << " ";
    saveVec3(render.getCamera().getLookat(), file);
    file << "\n";
    file.close();
}

void Scene::loadScene(std::string filepath) {
    std::fstream file(filepath, std::ios::in);



    file.close();
}

const std::vector<Object>& Scene::getObjects() {
    return objects;
}

Render& Scene::getRender() {
    return render;
}

void Scene::setRaytraceCallback(SceneRaytraceCallback rt) {
    this->rt = rt;
}

SceneRaytraceCallback Scene::getRaytraceCallback() {
    return rt;
}

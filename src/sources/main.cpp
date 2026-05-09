// Std includes
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

// Local includes
#include <lib/m3d.hpp>
#include <util.hpp>
#include <ray.hpp>
#include <hitpoint.hpp>
#include <material/scatter_result.hpp>
#include <material/material.hpp>
#include <scene/scene.hpp>
#include <render.hpp>
#include <geometry_maker.hpp>

using namespace m3d;

int32 pickOneOfN(int32 n) {
    return (int32) (n * randomUnit());
}

scene::Scene scn;

geo::Quad ground = makeQuad(vec3(0), vec3(0, 0, -10), vec3(-10, 0, 0));
geo::Sphere s1 = makeSphere(vec3(1.5, 0.5, 0), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 0.8, 7));
geo::Sphere s2 = makeSphere(vec3(-3, 0.5, 0.2), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 6.8, 7));
geo::Sphere s3 = makeSphere(vec3(-0.5, 0.5, -4), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(5, 0.8, 7));
geo::Sphere s4 = makeSphere(vec3(1, 0.5, 2), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 7.8, 7));
geo::Sphere s5 = makeSphere(vec3(1.5, 0.5, 0), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 6.8, 7));
geo::Sphere s6 = makeSphere(vec3(-3, 0.5, 0.2), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(6, 5.8, 7));
geo::Sphere s7 = makeSphere(vec3(-0.5, 0.5, -4), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(5, 5.8, 5));
geo::Sphere s8 = makeSphere(vec3(1, 0.5, 2), 0.5, vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(2, 0.8, 2));
geo::Triangle t1 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));
geo::Triangle t2 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));
geo::Triangle t3 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));
geo::Triangle t4 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));
geo::Triangle t5 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));
geo::Triangle t6 = makeTriangle(vec3(-0.5, 0.0, 0.0), vec3(0.5, 0.0, 0.0), vec3(0.0, 0.866, 0.0), vec3(randomUnit() - 0.5, randomUnit(), randomUnit() - 0.5) * vec3(7, 3.8, 7), randomUnit() * 360.0, vec3(0, 1, 0));

mat::Material groundMat(mat::DIFFUSE, vec3(0.086, 0.439, 0), 0.0);

mat::Material d1(mat::DIFFUSE, vec3(0, 0.686, 1), 0.0);
mat::Material d2(mat::DIFFUSE, vec3(0.922, 0.29, 0.545), 0.0);
mat::Material d3(mat::DIFFUSE, vec3(0.663, 0.922, 0.29), 0.0);
mat::Material d4(mat::DIFFUSE, vec3(0.643, 0.506, 0.91), 0.0);

mat::Material m1(mat::METAL, vec3(0.8, 0.702, 1), randomUnit() * 0.3);
mat::Material m2(mat::METAL, vec3(0.91, 0.91, 0.91), randomUnit() * 0.3);
mat::Material m3(mat::METAL, vec3(0.333, 1, 1), randomUnit() * 0.3);

float32 indices[] = {1.33, 1.5, 2.4};
mat::Material g1(mat::DIELECTRIC, vec3(1, 1, 1), indices[pickOneOfN(3)]);
mat::Material g2(mat::DIELECTRIC, vec3(0.808, 0.91, 0.91), indices[pickOneOfN(3)]);
mat::Material g3(mat::DIELECTRIC, vec3(0.671, 0.97, 0.831), indices[pickOneOfN(3)]);
mat::Material g4(mat::DIELECTRIC, vec3(0.902, 0.8, 0.949), indices[pickOneOfN(3)]);

vec3 skyColor(const Ray& ray) {
    float32 a = 0.5 * (ray.dir.y + 1.0);
    return (1.0 - a) * vec3(1.0) + a * vec3(0.5, 0.7, 1);
}

vec3 raytrace(const Ray& ray, int32 maxDepth) {
    Ray r = ray;
    Hitpoint h;
    mat::Material* m;
    vec3 color = vec3(1.0f);
    for (int32 i = 0; i < maxDepth; i++) {
        if ((m = scn.getClosestHit(r, h))) {
            mat::ScatterResult res = m->scatter(r, h);
            if (res.scattered) {
                color *= res.color;
                r = res.ray;
            } else {
                return vec3();
            }
        } else {
            return color * skyColor(r);
        }
    }
    return vec3();
}

int main() {
    std::vector<mat::Material> materials;
    materials.push_back(d1);
    materials.push_back(d2);
    materials.push_back(d3);
    materials.push_back(d4);
    materials.push_back(m1);
    materials.push_back(m2);
    materials.push_back(m3);
    materials.push_back(g1);
    materials.push_back(g2);
    materials.push_back(g3);
    materials.push_back(g4);

    scn.add(scene::Object(&s1, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s2, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s3, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s4, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s5, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s6, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s7, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&s8, &materials[pickOneOfN(materials.size())]));
    scn.add(scene::Object(&t1, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&t2, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&t3, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&t4, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&t5, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&t6, &materials[pickOneOfN(materials.size() - 4)]));
    scn.add(scene::Object(&ground, &groundMat));
    scn.save("random_scene1.scn");

    RenderParameters renderParameters;

    renderParameters.screenWidth = 1920;
    renderParameters.screenHeight = 1080;
    renderParameters.vfov = 34.0f;

    renderParameters.worldUp = vec3(0, 1, 0);
    renderParameters.cameraPos = vec3(-9.0f, 7.5f, 9.0f);
    renderParameters.cameraLookAt = vec3(0.0f, 0.5f, 0.0f);

    renderParameters.samplesPerPixel = 10;
    renderParameters.maxBounces = 50;

    renderParameters.enableSupersampling = true;
    renderParameters.enableGammaCorrection = true;
    renderParameters.enableMultiThreading = true;

    renderParameters.raytraceCallback = raytrace;

    Render render(renderParameters);
    render.render();
    render.save("render.bmp");
    return 0;
}

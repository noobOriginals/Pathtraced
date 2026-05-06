/**
    As this is also a project that's being worked on from school, the following message is meant for
    anyone who may stumble onto this project (on the coputers at school):

    The goal of this project is to create a CPU pathtracer from scratch. Being a large project and
    containing many files, it's rather hard to import/export to/from Code::Blocks. So I kindly ask of you to take care of
    this project, in the event that you need to delete it. You could upload it to drive or anything
    like that, but please consider not rendering all of this work pointless.

    Repository of this project: https://github.com/noobOriginals/Pathtraced
 */

// Std includes

// Local includes
#include "scene.hpp"

void setSceneRenderingParameters(Scene& scene) {
    scene.getRender().setSupersamples(15, 15);
    scene.getRender().enableSupersamling();
    scene.getRender().enableGammaCorrection();
    scene.getRender().enableMultithreading();
    scene.getRender().setMaxDepth(100);
}

int main() {
    Scene scene("scenes/default_scene.sc");
    setSceneRenderingParameters(scene);
    scene.renderScene();
    scene.saveRender("render.bmp");
    scene.saveScene("current_scene.sc");
    return 0;
}

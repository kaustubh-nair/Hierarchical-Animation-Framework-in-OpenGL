#ifndef SETTINGS_H
#define SETTINGS_H

#include "../include/definitions.h"

struct Settings
{
    int textureRenderingStyle;
    int currentScene = SCENE_1;
    int selectedMesh = -1;
    bool normalColoring;
    bool splats;
    int splatMultipler;
};

#endif

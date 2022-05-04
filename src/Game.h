#pragma once

#include "pgr.h"

class Game {
public:
    static float time;

    static bool drawDebugNormals;
    static float normalDebugShaderMagnitude;

    static float windStrength;
    static float animSpeed;

    static bool fogEnabled;
    static glm::vec3 fogColor;
    static float fogNear;
    static float fogFar;
};

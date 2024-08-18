#pragma once

#include "Scene.h"
#include "RGBImage.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer();

    RGBImage Render(const Scene& scene) const;
};

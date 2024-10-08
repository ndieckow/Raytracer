#pragma once

#include <vector>
#include "Light.h"

class Scene {
private:
    std::vector<SceneObject*> m_Objects;
    std::vector<Light*> m_Lights;
    Vector3d m_BackgroundColor;

public:
    Scene();

    Scene(double bgX, double bgY, double bgZ);

    ~Scene();

    Vector3d getBackgroundColor() const;

    Scene &AddObject(SceneObject *object);

    void Clear();

    Scene &AddLight(Light *light);

    const std::vector<Light*> &getLights() const;

    std::vector<SceneObject*>::const_iterator iter_begin() const;

    std::vector<SceneObject*>::const_iterator iter_end() const;
};

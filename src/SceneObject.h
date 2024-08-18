#pragma once

#include "Ray.h"
#include "Material.h"

class SceneObject {
private:
    Vector3d m_Pos;
    const Material &m_Mat;

public:
    SceneObject() : m_Pos(0, 0, 0), m_Mat(stone) {
    } // is the default constructor of Vector3d called?
    SceneObject(Vector3d pos, const Material &m) : m_Pos(pos), m_Mat(m) {
    }

    virtual ~SceneObject() {
    }

    Vector3d getPosition() const {
        return m_Pos;
    }

    void setPosition(Vector3d pos) {
        m_Pos = pos;
    }

    const Material &getMaterial() const {
        return m_Mat;
    }

    virtual Vector3d getNormal(Vector3d point) = 0;

    virtual double Intersect(const Ray &r) = 0;
};

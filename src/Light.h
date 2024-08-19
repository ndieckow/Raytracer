#pragma once

#include <iostream>
#include <random>
#include "SceneObject.h"

// A point light source
class Light {
private:
    Vector3d m_Pos;
    double m_Intensity;
    int m_Samples; // no. of required samples
public:
    virtual ~Light() = default;

    Light(Vector3d pos, double intensity) : m_Pos(pos), m_Intensity(intensity), m_Samples(1) {}
    Light(Vector3d pos, double intensity, int samples) : m_Pos(pos), m_Intensity(intensity), m_Samples(samples) {}

    double getIntensity() const { return m_Intensity; }
    Vector3d getPosition() const { return m_Pos; }
    int getSamples() const { return m_Samples; }

    virtual Vector3d Sample() { return m_Pos; }
};

// A cicrular light source
class CircularLight : public Light {
private:
    Vector3d m_Normal;
    Vector3d m_Span1;
    Vector3d m_Span2;
    double m_Radius;
    std::mt19937 m_RNG;

public:
    CircularLight(Vector3d pos, double intensity, Vector3d normal, double radius) : Light(pos, intensity, 20), // samples should probably depend on radius
                                                                                    m_Normal(normal.normalized()),
                                                                                    m_Radius(radius), m_RNG(std::random_device()()) {
        Vector3d helper = {1, 0, 0};
        if (helper == m_Normal) helper = {0, 1, 0};
        m_Span1 = m_Normal.cross(helper);
        m_Span2 = m_Normal.cross(m_Span1);
    }

    double getRadius() const { return m_Radius; }

    Vector3d Sample() override {
        // Sample a random point on the light.
        std::uniform_real_distribution<> dist(0, 1);
        double r = dist(m_RNG) * m_Radius;
        double theta = 2 * M_PI * dist(m_RNG);
        double x = sqrt(r) * cos(theta);
        double y = sqrt(r) * sin(theta);
        return getPosition() + Vector3d{m_Span1.x * x + m_Span2.x * y, m_Span1.y * x + m_Span2.y * y, m_Span1.z * x + m_Span2.z * y};
    }
};

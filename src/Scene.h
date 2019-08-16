#pragma once

#include <vector>
#include <memory>
#include "Light.h"
#include "RGBImage.h"

class Scene
{
private:
	std::vector<SceneObject*> m_Objects;
	std::vector<Light*> m_Lights;
	Vector3d m_Viewpoint;
public:
	Scene();
	~Scene();
	Vector3d getViewpoint() const;
	Scene& AddObject(SceneObject* object);
	void Clear();
	Scene& AddLight(Light* light);
	const std::vector<Light*>& getLights() const;
	std::vector<SceneObject*>::const_iterator iter_begin() const;
	std::vector<SceneObject*>::const_iterator iter_end() const;
};


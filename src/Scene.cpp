#include "Scene.h"

Scene::Scene() : m_Viewpoint(0, 0, 0)
{
}

Scene::~Scene()
{
}

Vector3d Scene::getViewpoint() const
{
	return m_Viewpoint;
}

Scene& Scene::AddObject(SceneObject* object)
{
	m_Objects.push_back(object);
	return *this;
}

void Scene::Clear()
{
	m_Objects.clear();
}

Scene& Scene::AddLight(Light* light)
{
	m_Lights.push_back(light);
	return *this;
}

const std::vector<Light*>& Scene::getLights() const
{
	return m_Lights;
}

std::vector<SceneObject*>::const_iterator Scene::iter_begin() const
{
	return m_Objects.begin();
}
std::vector<SceneObject*>::const_iterator Scene::iter_end() const
{
	return m_Objects.end();
}
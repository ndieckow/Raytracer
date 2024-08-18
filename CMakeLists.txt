cmake_minimum_required(VERSION 3.29)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/stb)

add_executable(Raytracer
    src/stb/stb_image_write.h
    src/Light.h
    src/Main.cpp
    src/Material.cpp
    src/Material.h
    src/Plane.h
    src/Ray.h
    src/RGBImage.cpp
    src/RGBImage.h
    src/Scene.cpp
    src/Scene.h
    src/SceneObject.h
    src/Sphere.h
    src/Vector3d.h
        src/Renderer.cpp
        src/Renderer.h)

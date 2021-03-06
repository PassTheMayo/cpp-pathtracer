#include <math.h>
#include <thread>
#include <chrono>
#include <time.h>
#include <png++/png.hpp>
#include "scene.h"
#include "camera.h"
#include "renderer.h"
#include "sphere.h"
#include "triangle.h"
#include "plane.h"
#include "ray.h"
#include "rotation.h"
#include "color.h"
#include "vector.h"
#include "object.h"
#include "skybox.h"
#include "util.h"

const int renderWidth = 500;
const int renderHeight = 500;
const double antialiasJitter = 0.0;
const int sampleCount = 10;
const int maxBounces = 5;
const double threadCount = std::thread::hardware_concurrency();

void setupScene(Scene *scene)
{
    Material floorMaterial(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, Color(255.0, 255.0, 255.0), nullptr);
    Material lightMaterial(0.0, 0.0, 0.0, 2.0, 0.0, 1.0, Color(255.0, 255.0, 255.0), nullptr);
    Material frontLeftCubeMaterial(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, Color(0.0, 0.0, 255.0), nullptr);
    Material frontRightCubeMaterial(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, Color(255.0, 255.0, 0.0), nullptr);
    Material backLeftCubeMaterial(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, Color(255.0, 0.0, 0.0), nullptr);
    Material backRightCubeMaterial(0.0, 1.0, 0.0, 0.0, 0.0, 1.0, Color(0.0, 255.0, 0.0), nullptr);
    Material middleCubeMaterial(0.0, 0.0, 0.0, 0.0, 1.0, 1.325, Color(255.0, 255.0, 255.0), nullptr);

    // Floor
    createCube(scene, Vector3(-5.0, 0.0, -5.0), Vector3(5.0, 0.0, -5.0), Vector3(-5.0, 0.0, 5.0), Vector3(5.0, 0.0, 5.0), Vector3(-5.0, -100.0, -5.0), Vector3(5.0, -100.0, -5.0), Vector3(-5.0, -100.0, 5.0), Vector3(5.0, -100.0, 5.0), floorMaterial);

    // Light
    createCube(scene, Vector3(-5.0, 10.0, -5.0), Vector3(5.0, 10.0, -5.0), Vector3(-5.0, 10.0, 5.0), Vector3(5.0, 10.0, 5.0), Vector3(-5.0, 20.0, -5.0), Vector3(5.0, 20.0, -5.0), Vector3(-5.0, 20.0, 5.0), Vector3(5.0, 20.0, 5.0), lightMaterial);

    // Front Left Cube
    createCube(scene, Vector3(-5.0, 2.0, 3.0), Vector3(-3.0, 2.0, 3.0), Vector3(-5.0, 2.0, 5.0), Vector3(-3.0, 2.0, 5.0), Vector3(-5.0, 0.0, 3.0), Vector3(-3.0, 0.0, 3.0), Vector3(-5.0, 0.0, 5.0), Vector3(-3.0, 0.0, 5.0), frontLeftCubeMaterial);

    // Front Right Cube
    createCube(scene, Vector3(3.0, 2.0, 3.0), Vector3(5.0, 2.0, 3.0), Vector3(3.0, 2.0, 5.0), Vector3(5.0, 2.0, 5.0), Vector3(3.0, 0.0, 3.0), Vector3(5.0, 0.0, 3.0), Vector3(3.0, 0.0, 5.0), Vector3(5.0, 0.0, 5.0), frontRightCubeMaterial);

    // Back Left Cube
    createCube(scene, Vector3(-5.0, 2.0, -3.0), Vector3(-3.0, 2.0, -3.0), Vector3(-5.0, 2.0, -5.0), Vector3(-3.0, 2.0, -5.0), Vector3(-5.0, 0.0, -3.0), Vector3(-3.0, 0.0, -3.0), Vector3(-5.0, 0.0, -5.0), Vector3(-3.0, 0.0, -5.0), backLeftCubeMaterial);

    // Back Right Cube
    createCube(scene, Vector3(3.0, 2.0, -3.0), Vector3(5.0, 2.0, -3.0), Vector3(3.0, 2.0, -5.0), Vector3(5.0, 2.0, -5.0), Vector3(3.0, 0.0, -3.0), Vector3(5.0, 0.0, -3.0), Vector3(3.0, 0.0, -5.0), Vector3(5.0, 0.0, -5.0), backRightCubeMaterial);

    // Middle Cube
    createCube(scene, Vector3(-1.0, 3.0, -1.0), Vector3(1.0, 3.0, -1.0), Vector3(-1.0, 3.0, 1.0), Vector3(1.0, 3.0, 1.0), Vector3(-1.0, 1.0, -1.0), Vector3(1.0, 1.0, -1.0), Vector3(-1.0, 1.0, 1.0), Vector3(1.0, 1.0, 1.0), middleCubeMaterial);
}

void renderRegion(int x0, int y0, int x1, int y1, Camera camera, Scene *scene, Renderer renderer, png::image<png::rgba_pixel> *image)
{
    double width = renderer.width;
    double height = renderer.height;
    double samples = renderer.samples;

    for (double x = x0; x < x1; x++)
    {
        for (double y = y0; y < y1; y++)
        {
            Color color;

            for (double s = 0; s < samples; s++)
            {
                color = color + renderer.traceRay(camera.getRay((x + (randomDouble() - 0.5) * antialiasJitter * 2) / width, (y + (randomDouble() - 0.5) * antialiasJitter * 2) / height), scene, camera, 0);
            }

            image->set_pixel(x, y, (color / samples).clamp().toRGBAPixel());
        }
    }
}

int main()
{
    Scene scene;
    Renderer renderer(renderWidth, renderHeight, sampleCount, 0, 0.0);
    Camera camera(Vector3(0.0, 5.0, 35.0), Rotation(M_PI, 0.0, 0.0), double(renderer.height) / double(renderer.width), 90.0, maxBounces + 1);

    Skybox skybox(Color(38.0, 77.0, 153.0), Color(19.0, 39.0, 77.0), Color(0.0, 0.0, 0.0), 1.0);
    scene.setSkybox(&skybox);

    setupScene(&scene);

    png::image<png::rgba_pixel> image(renderer.width, renderer.height);

    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    std::vector<std::thread> threads;

    printf("Render started...\n    - %.0f threads\n    - %d samples\n    - %d max bounces\n    - %dx%d\n", threadCount, sampleCount, maxBounces, renderer.width, renderer.height);

    for (int i = 0; i < threadCount; i++)
    {
        int width = ceil(double(renderer.width) / threadCount);

        int x0 = i * width;
        int y0 = 0;
        int x1 = (i + 1) * width;
        int y1 = renderer.height;

        threads.emplace_back(renderRegion, std::max(x0, 0), std::max(y0, 0), std::min(x1, renderer.width), std::min(y1, renderer.height), camera, &scene, renderer, &image);
    }

    for (int i = 0; i < threadCount; i++)
    {
        threads[i].join();
    }

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    printf("Rendered in %.2f seconds\n", (double(end) - double(start)) / 1000);

    image.write("output.png");
}
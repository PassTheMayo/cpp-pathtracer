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

const int width = 256;
const int height = 256;
const double antialiasJitter = 1.0;
const int sampleCount = 5;
const int maxBounces = 20;
const double threadCount = std::thread::hardware_concurrency();

void setupScene(Scene *scene)
{
    Texture sphereTexture("sphere.png");
    Material leftWallMaterial = Material(0, 1, 0, 0, 0, Color(255.0, 0.0, 0.0), nullptr);
    Material rightWallMaterial = Material(0, 1, 0, 0, 0, Color(0.0, 255.0, 0.0), nullptr);
    Material otherWallMaterial = Material(0, 1, 0, 0, 0, Color(255.0, 255.0, 255.0), nullptr);
    Material lightMaterial = Material(0, 0, 2.5, 0, 0, Color(255.0, 255.0, 255.0), nullptr);

    Triangle leftWall1 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(-5.1, 0.0, 5.0), Vector3(-5.1, 10.0, 5.0), leftWallMaterial);
    Triangle leftWall2 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(-5.1, 10.0, -5.1), Vector3(-5.1, 10.0, 5.0), leftWallMaterial);
    scene->addObject(std::make_unique<Triangle>(leftWall1));
    scene->addObject(std::make_unique<Triangle>(leftWall2));

    Triangle rightWall1 = Triangle(Vector3(5.1, 0.0, -5.1), Vector3(5.1, 0.0, 5.0), Vector3(5.1, 10.0, 5.0), rightWallMaterial);
    Triangle rightWall2 = Triangle(Vector3(5.1, 0.0, -5.1), Vector3(5.1, 10.0, -5.1), Vector3(5.1, 10.0, 5.0), rightWallMaterial);
    scene->addObject(std::make_unique<Triangle>(rightWall1));
    scene->addObject(std::make_unique<Triangle>(rightWall2));

    Triangle topWall1 = Triangle(Vector3(-5.1, 10.0, -5.1), Vector3(5.1, 10.0, -5.1), Vector3(5.1, 10.0, 5.0), otherWallMaterial);
    Triangle topWall2 = Triangle(Vector3(-5.1, 10.0, -5.1), Vector3(-5.1, 10.0, 5.0), Vector3(5.1, 10.0, 5.0), otherWallMaterial);
    scene->addObject(std::make_unique<Triangle>(topWall1));
    scene->addObject(std::make_unique<Triangle>(topWall2));

    Triangle bottomWall1 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(5.1, 0.0, -5.1), Vector3(5.1, 0.0, 5.0), otherWallMaterial);
    Triangle bottomWall2 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(-5.1, 0.0, 5.0), Vector3(5.1, 0.0, 5.0), otherWallMaterial);
    scene->addObject(std::make_unique<Triangle>(bottomWall1));
    scene->addObject(std::make_unique<Triangle>(bottomWall2));

    Triangle backWall1 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(-5.1, 10.0, -5.1), Vector3(5.1, 10.0, -5.1), otherWallMaterial);
    Triangle backWall2 = Triangle(Vector3(-5.1, 0.0, -5.1), Vector3(5.1, 0.0, -5.1), Vector3(5.1, 10.0, -5.1), otherWallMaterial);
    scene->addObject(std::make_unique<Triangle>(backWall1));
    scene->addObject(std::make_unique<Triangle>(backWall2));

    Triangle light1 = Triangle(Vector3(-3.0, 9.99, -3.0), Vector3(3.0, 9.99, -3.0), Vector3(3.0, 9.99, 3.0), lightMaterial);
    Triangle light2 = Triangle(Vector3(-3.0, 9.99, -3.0), Vector3(-3.0, 9.99, 3.0), Vector3(3, 9.99, 3.0), lightMaterial);
    scene->addObject(std::make_unique<Triangle>(light1));
    scene->addObject(std::make_unique<Triangle>(light2));

    Sphere sphere1 = Sphere(Vector3(-2, 2.5, -2), 2.5, Material(1.0, 0.0, 0.0, 0.0, 1.0, Color(0.0, 0.0, 0.0), &sphereTexture));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere3 = Sphere(Vector3(2.25, 1.75, 0.0), 1.75, Material(0.0, 1.0, 0.0, 0.0, 1.45, Color(255.0, 0.0, 0.0), &sphereTexture));
    scene->addObject(std::make_unique<Sphere>(sphere3));

    Sphere sphere2 = Sphere(Vector3(-0.5, 1.25, 2.0), 1.25, Material(0.0, 0.0, 0.0, 1.0, 1.45, Color(0.0, 0.0, 0.0), &sphereTexture));
    scene->addObject(std::make_unique<Sphere>(sphere2));
}

void renderRegion(int x0, int y0, int x1, int y1, Camera *camera, Scene *scene, Renderer *renderer, png::image<png::rgba_pixel> *image)
{
    for (int x = x0; x < x1; x++)
    {
        for (int y = y0; y < y1; y++)
        {
            Color finalColor;

            for (int s = 0; s < renderer->samples; s++)
            {
                Ray ray = camera->getRay((double(x) + randomDouble() * antialiasJitter) / double(renderer->width), (double(y) + randomDouble() * antialiasJitter) / double(renderer->height));

                finalColor = finalColor + renderer->traceRay(&ray, scene, camera, 0);
            }

            finalColor = (finalColor / double(renderer->samples)).clamp();

            image->set_pixel(x, y, png::rgba_pixel(finalColor.r, finalColor.g, finalColor.b, 255));
        }
    }
}

int main()
{
    Scene scene;
    Renderer renderer(width, height, sampleCount);
    Camera camera(Vector3(0.0, 5.0, 14.9), Rotation(M_PI, 0.0, 0.0), double(renderer.height) / double(renderer.width), 180.0, maxBounces + 2);

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

        threads.emplace_back(renderRegion, std::max(x0, 0), std::max(y0, 0), std::min(x1, renderer.width), std::min(y1, renderer.height), &camera, &scene, &renderer, &image);
    }

    for (int i = 0; i < threadCount; i++)
    {
        threads[i].join();
    }

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    printf("Rendered in %.2f seconds\n", (double(end) - double(start)) / 1000);

    image.write("output.png");
}
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

const double antialiasJitter = 1.0;
const int sampleCount = 50;
const int maxBounces = 5;
const double threadCount = 16.0;

void setupScene(Scene *scene)
{
    Sphere sphere1 = Sphere(Vector3(-2.5, 1.25, 0.0), 1.25, Material(1.0, 0.0, 0.0, 1.0, 1.25, Color(255.0, 50.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere2 = Sphere(Vector3(0.0, 1.25, 0.0), 1.25, Material(0.0, 1.0, 0.0, 0.0, 1.0, Color(255.0, 50.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere2));

    Sphere sphere3 = Sphere(Vector3(2.5, 1.25, 0.0), 1.25, Material(1.0, 0.4, 0.0, 0.0, 1.0, Color(255.0, 50.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere3));

    Sphere light = Sphere(Vector3(0.0, 30.0, 0.0), 20, Material(0.0, 0.0, 1.0, 0.0, 1.0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(light));

    Plane floor = Plane(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 1.0, 0.0), Material(1.0, 0.75, 0.0, 0.0, 1.0, Color(0.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Plane>(floor));
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

                finalColor = finalColor + renderer->traceRay(&ray, scene, camera, 0).clamp();
            }

            finalColor = (finalColor / double(renderer->samples)).clamp();

            image->set_pixel(x, y, png::rgba_pixel(finalColor.r, finalColor.g, finalColor.b, 255));
        }
    }
}

int main()
{
    Scene scene;
    Renderer renderer(3840.0, 2160.0, sampleCount);
    Camera camera(Vector3(0.0, 1.5, 13.5), Rotation(M_PI, 0.0, 0.0), double(renderer.height) / double(renderer.width), 180.0, maxBounces + 2);

    setupScene(&scene);

    png::image<png::rgba_pixel> image(renderer.width, renderer.height);

    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t lastUpdate = start;

    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++)
    {
        int width = double(renderer.width) / threadCount;

        threads.emplace_back(renderRegion, i * width, 0, i * width + width, renderer.height, &camera, &scene, &renderer, &image);
    }

    for (int i = 0; i < threadCount; i++)
    {
        threads[i].join();
    }

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    printf("Rendered in %.2f seconds\n", (double(end) - double(start)) / 1000);

    image.write("output.png");
}
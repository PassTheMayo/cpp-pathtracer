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
#include "ray.h"
#include "rotation.h"
#include "color.h"
#include "vector.h"
#include "object.h"
#include "skybox.h"
#include "util.h"

const double antialiasJitter = 1.0;
const int sampleCount = 10;
const int maxBounces = 2;
const double threadCount = 2.0;

void setupScene(Scene *scene)
{
    Sphere sphere1 = Sphere(Vector3(0.0, 1.0, 0.0), 1, Material(0.65, 0.25, 0, Color(255.0, 50.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere2 = Sphere(Vector3(-2.0, 1.0, 0.0), 1, Material(1.0, 0.0, 0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(sphere2));

    Sphere sphere3 = Sphere(Vector3(2.0, 1.0, 0.0), 1, Material(0.85, 0.5, 0, Color(50.0, 255.0, 50.0)));
    scene->addObject(std::make_unique<Sphere>(sphere3));

    Sphere light = Sphere(Vector3(0.0, 7.0, 0.0), 2, Material(0.0, 0.0, 1.0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(light));

    Triangle floor1 = Triangle(Vector3(25.0, 0.0, 25.0), Vector3(25.0, 0.0, -25.0), Vector3(-25.0, 0.0, -25.0), Material(0.75, 0.5, 0.0, Color(0.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Triangle>(floor1));

    Triangle floor2 = Triangle(Vector3(-25.0, 0.0, -25.0), Vector3(-25.0, 0.0, 25.0), Vector3(25.0, 0.0, 25.0), Material(0.75, 0.5, 0.0, Color(0.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Triangle>(floor2));
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
    srand(time(NULL));

    Scene scene;
    Renderer renderer(1920.0 * 2.0, 1080.0 * 2.0, sampleCount);
    Camera camera(Vector3(0.0, 1.5, 10.0), Rotation(M_PI, 0.0, 0.0), double(renderer.height) / double(renderer.width), 180.0, maxBounces + 2);
    Skybox skybox(Color(63.0, 178.0, 232.0), Color(225.0, 244.0, 252.0), Color(225.0, 244.0, 252.0), 1.0);

    // scene.setSkybox(&skybox);

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

    printf("\nRendered in %.2f seconds\n", (double(end) - double(start)) / 1000);

    image.write("output.png");
}
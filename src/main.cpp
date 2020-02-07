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

void setupScene(Scene *scene)
{
    Sphere sphere1 = Sphere(Vector3(0.0, 1.0, 0.0), 1, Material(1.0, 0.25, 0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(sphere1));

    Sphere sphere2 = Sphere(Vector3(-2.0, 1.0, 0.0), 1, Material(1.0, 0.0, 0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(sphere2));

    Sphere sphere3 = Sphere(Vector3(2.0, 1.0, 0.0), 1, Material(1.0, 0.5, 0, Color(255.0, 255.0, 255.0)));
    scene->addObject(std::make_unique<Sphere>(sphere3));

    Triangle floor1 = Triangle(Vector3(-5.0, 0.0, -5.0), Vector3(5.0, 0.0, -5.0), Vector3(5.0, 0.0, 5.0), Material(1.0, 0.5, 0.0, Color(255.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Triangle>(floor1));

    Triangle floor2 = Triangle(Vector3(-5.0, 0.0, -5.0), Vector3(-5.0, 0.0, 5.0), Vector3(5.0, 0.0, 5.0), Material(1.0, 0.5, 0.0, Color(255.0, 0.0, 0.0)));
    scene->addObject(std::make_unique<Triangle>(floor2));
}

void renderRegion(int x0, int y0, int x1, int y1, Camera *camera, Scene *scene, Renderer *renderer, png::image<png::rgba_pixel> *image)
{
    double aspectRatio = double(renderer->height) / double(renderer->width);

    for (int x = x0; x < x1; x++)
    {
        for (int y = y0; y < y1; y++)
        {
            Color finalColor;

            for (int s = 0; s < renderer->samples; s++)
            {
                Ray ray = camera->getRay(double(x) / double(renderer->width), double(y) / double(renderer->height), aspectRatio);

                finalColor = finalColor + renderer->traceRay(&ray, scene, camera, 0);
            }

            finalColor = (finalColor / double(renderer->samples)).clamp();

            image->set_pixel(x, y, png::rgba_pixel(finalColor.r, finalColor.g, finalColor.b, 255));
        }
    }
}

const double threadCount = 16.0;

int main()
{
    srand(time(NULL));

    Scene scene;
    Camera camera(Vector3(0.0, 2.5, 15.0), Rotation(M_PI, 0.0, 0.0), 180.0, 4);
    Renderer renderer(1920, 1080, 10);
    Skybox skybox(Color(63.0, 178.0, 232.0), Color(225.0, 244.0, 252.0), Color(225.0, 244.0, 252.0), 1.0);

    scene.setSkybox(&skybox);

    setupScene(&scene);

    png::image<png::rgba_pixel> image(renderer.width, renderer.height);

    int64_t start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int64_t lastUpdate = start;

    std::vector<std::thread> threads;

    for (int i = 0; i < threadCount; i++)
    {
        int width = double(renderer.width) / threadCount;

        std::thread renderThread(renderRegion, i * width, 0, i * width + width, renderer.height, &camera, &scene, &renderer, &image);

        threads.emplace_back(renderThread);
    }

    for (int i = 0; i < threadCount; i++)
    {
        threads[i].join();
    }

    int64_t end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    printf("\nRendered in %.2f seconds\n", (double(end) - double(start)) / 1000);

    image.write("output.png");
}
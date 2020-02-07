#include <math.h>
#include <png++/png.hpp>
#include "scene.h"
#include "camera.h"
#include "renderer.h"
#include "sphere.h"
#include "ray.h"
#include "rotation.h"
#include "color.h"
#include "vector.h"
#include "object.h"

void setupScene(Scene *scene)
{
    Sphere sphere1 = Sphere(Vector3(0.0, 0.0, 15.0), 5, Material(0, 1, 0, Color(255.0, 255.0, 255.0)));

    scene->addObject(std::make_unique<Sphere>(sphere1));
}

int main()
{
    Scene scene;
    Camera camera(Vector3(0.0, 0.0, 0.0), Rotation(M_PI, 0.0, 0.0), 60.0);
    Renderer renderer(1920 / 4, 1080 / 4);

    setupScene(&scene);

    png::image<png::rgba_pixel> image(renderer.width, renderer.height);

    const double aspectRatio = double(renderer.height) / double(renderer.width);

    for (int x = 0; x < renderer.width; x++)
    {
        for (int y = 0; y < renderer.height; y++)
        {
            Ray ray = camera.getRay(double(x) / double(renderer.width), double(y) / double(renderer.height), aspectRatio);

            Color color = renderer.traceRay(&ray, &scene, &camera);

            image.set_pixel(x, y, png::rgba_pixel(color.r, color.g, color.b, 255));
        }
    }

    image.write("output.png");
}
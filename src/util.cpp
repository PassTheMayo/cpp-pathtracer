#include <random>
#include <regex>
#include <fstream>
#include "util.h"

struct xorshift_engine
{
    using result_type = uint32_t;

    uint32_t state;

    xorshift_engine()
    {
        state = 0x1234567;
    }

    xorshift_engine(uint32_t seed)
    {
        if (seed == 0)
            seed++;
        state = seed;
    }

    const uint32_t min()
    {
        return 1;
    }

    const uint32_t max()
    {
        return 0xffffffff;
    }

    uint32_t operator()()
    {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }
};

thread_local std::uniform_real_distribution<double> dist(0.0f, 1.0f);
thread_local std::random_device rd;
thread_local xorshift_engine eng(rd());

double randomDouble()
{
    return dist(eng);
}

Vector3 randomDirection()
{
    return Vector3(randomDouble() - 0.5, randomDouble() - 0.5, randomDouble() - 0.5).normalize();
}

void loadObjectFile(std::string filename, Scene *scene, Material material, Vector3 translate, Vector3 scale)
{
    std::ifstream f(filename);

    int vertexCount = 0;
    int faceCount = 0;

    std::vector<Vector3> vertices;

    std::string line;

    while (getline(f, line))
    {
        line = std::regex_replace(std::regex_replace(line, std::regex(" +"), " "), std::regex("^ *| *$"), "");

        if (line.rfind("#", 0) == 0)
        {
            continue;
        }

        if (line.rfind("g ", 0) == 0)
        {
            vertices.empty();
        }

        if (line.rfind("v ", 0) == 0)
        {
            float x, y, z;

            sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);

            vertices.emplace_back(x, y, z);

            vertexCount++;
        }

        if (line.rfind("f ", 0) == 0)
        {
            if (std::regex_match(line, std::regex(R"(f( [0-9]+){3})", std::regex_constants::extended)))
            {
                int i0, i1, i2;

                sscanf(line.c_str(), "f %d %d %d", &i0, &i1, &i2);

                if (i0 > int(vertices.size()))
                {
                    std::cerr << i0 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (i1 > int(vertices.size()))
                {
                    std::cerr << i1 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (i2 > int(vertices.size()))
                {
                    std::cerr << i2 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                scene->addObject(std::make_unique<Triangle>(Triangle(vertices[i0 - 1] * scale + translate, vertices[i1 - 1] * scale + translate, vertices[i2 - 1] * scale + translate, material)));

                faceCount++;
            }
            else if (std::regex_match(line, std::regex(R"(f( [0-9]+\/[0-9]+\/[0-9]+){3})", std::regex_constants::extended)))
            {
                int v0, v1, v2, vn0, vn1, vn2, vt0, vt1, vt2;

                sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &vn0, &vt0, &v1, &vn1, &vt1, &v2, &vn2, &vt2);

                if (v0 > int(vertices.size()))
                {
                    std::cerr << v0 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (v1 > int(vertices.size()))
                {
                    std::cerr << v1 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (v2 > int(vertices.size()))
                {
                    std::cerr << v2 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                scene->addObject(std::make_unique<Triangle>(Triangle(vertices[v0 - 1] * scale + translate, vertices[v1 - 1] * scale + translate, vertices[v2 - 1] * scale + translate, material)));

                faceCount++;
            }
            else if (std::regex_match(line, std::regex(R"(f( [0-9]+\/\/[0-9]+){3})", std::regex_constants::extended)))
            {
                int v0, v1, v2, vt0, vt1, vt2;

                sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v0, &vt0, &v1, &vt1, &v2, &vt2);

                if (v0 > int(vertices.size()))
                {
                    std::cerr << v0 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (v1 > int(vertices.size()))
                {
                    std::cerr << v1 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                if (v2 > int(vertices.size()))
                {
                    std::cerr << v2 << " is out of range for .obj vertex index" << std::endl;

                    std::cout << line << std::endl;

                    continue;
                }

                scene->addObject(std::make_unique<Triangle>(Triangle(vertices[v0 - 1] * scale + translate, vertices[v1 - 1] * scale + translate, vertices[v2 - 1] * scale + translate, material)));

                faceCount++;
            }
            else
            {
                std::cerr << "Face does not match known format: " << line << std::endl;
            }
        }
    }

    std::cout << "Successfully imported OBJ with " << faceCount << " faces and " << vertexCount << " vertices" << std::endl;
}

double interpolate(double a, double b, double s)
{
    return a + (b - a) * s;
}

void createCube(Scene *scene, Vector3 a, Vector3 b, Vector3 c, Vector3 d, Vector3 e, Vector3 f, Vector3 g, Vector3 h, Material material)
{
    Triangle triangle1 = Triangle(a, b, d, material);
    scene->addObject(std::make_unique<Triangle>(triangle1)); // Top

    Triangle triangle2 = Triangle(a, c, d, material);
    scene->addObject(std::make_unique<Triangle>(triangle2)); // Top

    Triangle triangle3 = Triangle(e, f, h, material);
    scene->addObject(std::make_unique<Triangle>(triangle3)); // Bottom

    Triangle triangle4 = Triangle(e, g, h, material);
    scene->addObject(std::make_unique<Triangle>(triangle4)); // Bottom

    Triangle triangle5 = Triangle(c, d, h, material);
    scene->addObject(std::make_unique<Triangle>(triangle5)); // Side 1

    Triangle triangle6 = Triangle(c, g, h, material);
    scene->addObject(std::make_unique<Triangle>(triangle6)); // Side 1

    Triangle triangle7 = Triangle(a, b, f, material);
    scene->addObject(std::make_unique<Triangle>(triangle7)); // Side 2

    Triangle triangle8 = Triangle(a, e, f, material);
    scene->addObject(std::make_unique<Triangle>(triangle8)); // Side 2

    Triangle triangle9 = Triangle(d, b, f, material);
    scene->addObject(std::make_unique<Triangle>(triangle9)); // Side 3

    Triangle triangle10 = Triangle(d, h, f, material);
    scene->addObject(std::make_unique<Triangle>(triangle10)); // Side 3

    Triangle triangle11 = Triangle(a, e, g, material);
    scene->addObject(std::make_unique<Triangle>(triangle11)); // Side 4

    Triangle triangle12 = Triangle(a, c, g, material);
    scene->addObject(std::make_unique<Triangle>(triangle12)); // Side 4
}
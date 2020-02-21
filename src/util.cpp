#include <random>
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
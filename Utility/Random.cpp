#include "Random.h"

using namespace pong;

Random::Random()
{
    std::random_device device;

    engine.seed(device());
}

Random::Random(long seed) {engine.seed(seed);}

void Random::setSeed(long seed) {engine.seed(seed);}

bool Random::getBool()
{
    std::uniform_int_distribution<> distribution(0, 1);

    return distribution(engine) == 0;
}

unsigned char Random::getByte()
{
    std::uniform_int_distribution<> distribution(0, 255);

    return distribution(engine);
}

int Random::getInt() {return engine();}

int Random::getInt(int max) {return engine() % max;}

int Random::randomRange(int min, int max)
{
    return getInt((max) - min) + min;
}

int Random::iRandomRange(int min, int max)
{
    return getInt((max + 1) - min) + min;
}

long Random::getLong() {return engine();}

float Random::getFloat()
{
    std::uniform_real_distribution<float> distribution(0.f, 1.f);

    return distribution(engine);
}

double Random::getDouble()
{
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(engine);
}
#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace pong {

class Random
{
    std::default_random_engine engine;

public:
    Random();
    Random(long seed);

    void setSeed(long seed);

    bool getBool();

    //[0, 255]
    unsigned char getByte();

    int getInt();
    int getInt(int max);

    //[min, max)
    int randomRange(int min, int max);

    //[min, max]
    int iRandomRange(int min, int max);

    long getLong();
    
    //[0, 1]
    float getFloat();

    //[0, 1]
    double getDouble();
};

}


#endif
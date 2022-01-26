#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <ctime>
#include <cstdlib>
#include <random>

class RNG{
    public :

    RNG();
    static void setSeed(long int*);
    static double random(double max);
};

#endif
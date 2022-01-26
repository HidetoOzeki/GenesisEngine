#include <Genesis/RNG.h>

RNG::RNG(){

}

void RNG::setSeed(long int* seed){
    std::srand(std::time(seed));
}

double RNG::random(double max){
    double rndval = ((double)rand()/RAND_MAX)*max;
    return rndval;
}
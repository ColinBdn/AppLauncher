#include "utils_include.h"

#include <random>

float genRandomFloat(const float& a, const float& b)
{
    static std::mt19937 rng(std::random_device{}());
    //static std::mt19937 rng(1);
    std::uniform_real_distribution<float> dist(a, b); 
    return dist(rng);
}
int genRandomInt(int a, int b) {
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    return a + rand() % (b - a + 1);
}

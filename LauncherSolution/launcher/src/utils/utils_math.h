#pragma once

#include "utils_vector.h"

#include <vector>


/**
 * Calculates the mean value of a vector.
 *
 * @param vec The vector for which to calculate the mean.
 * @return The mean value of the vector.
 */
template<typename T>
float vectorMean(const std::vector<T>& vec)
{
    double mean = 0;
    int size = vec.size();
    for (int i = 0; i < size; ++i)
        mean += vec[i];
    return mean / size;
}

/**
 * Finds the maximum value in a 1D vector.
 *
 * @param vec The vector for which to find the maximum value.
 * @return The maximum value in the vector.
 */
template<typename T>
T vectorMax(const std::vector<T>& vec)
{
    T max = 0;
    for (T ele : vec)
    {
        if (ele > max) max = ele;
    }
    return max;
}

/**
 * Finds the maximum value in a 2D vector.
 *
 * @param vec The vector for which to find the maximum value.
 * @return The maximum value in the vector.
 */
template<typename T>
T vectorMax(const std::vector<std::vector<T>>& vec)
{
    T max= 0;
    for (std::vector<T> row : vec)
    {
        for (T ele : row)
        {
            if (ele > max) max = ele;
        }
    }
    return max;
}


float distance(const Vec3& a, const Vec3& b);
float distance(const Vec2& a, const Vec2& b);
float distanceSquared(const Vec3& a, const Vec3& b);
float distanceSquared(const Vec2& a, const Vec2& b);
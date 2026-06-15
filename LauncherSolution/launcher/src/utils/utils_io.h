#pragma once

#include <iostream>
#include <vector>



/**
 * Clear the console input buffer (if there was some input before std::cin for example)
 */
void clearConsoleInputBuffer();

/**
 * Inputs a value of type T from the standard input stream.
 * Clears the input buffer before reading and resets the stream state after reading.
 *
 * @param var The variable to store the input value.
 * @return True if input operation fails, otherwise false.
 */
template<typename T> bool input(T& var)
{
    clearConsoleInputBuffer();
    std::cin >> var;
    bool fail = std::cin.fail();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return fail;
}





/**
 * Prints the elements of a 1D vector to the standard output stream.
 *
 * @param data The vector containing the elements to print.
 */
template<typename T>
void printVector(std::vector<T>data, bool newLine=true)
{
    std::cout << '{';
    for (T& ele : data)
    {
        std::cout << ele;
        if (&ele != &data.end()) std::cout << " ";
    }
    std::cout << "}";
    if (newLine) std::cout << "\n";
}
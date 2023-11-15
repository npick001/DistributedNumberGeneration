#pragma once

#define USE_DEBUG 0

#if USE_DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif // USE_DEBUG

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/***************************************

This file denotes completed functions that may be useful later.
All functions should be COMPLETE and tested before addition.

***************************************/

// Differential equation callback function
typedef double (*callback_function_DBL)(double, double);

// Define the start of the Runge Kutta family numerical integrators.
// works but apparently not for what I needed it for. I cry.
std::vector<double> RungeKutta4(callback_function_DBL pdf, double x_init, double upperbound, int steps);

// Iteratively compute the factorial
unsigned long long factorial(unsigned int n);

// GAMMA FUNCTION
// CONSTRAINED x > 0 for x = 1,2,3,...,n
double GammaFunction(unsigned int n);

// CHI-SQUARE DISTRIBUTION
// returns vector of points in the chi-square distribution
// also can write the results to a file, determined by last param
std::vector<double> Chi_Square_Distribution(int dof, int numPoints, bool writeToFile);

/**
 * @brief Writes the given data to a file.
 *
 * This template function writes a single item of any type to a specified file, with two possible write modes:
 * - Append mode (openMode=0): appends the given data to the end of the file if it exists; creates the file if it does not exist.
 * - Truncate mode (openMode=1): overwrites the file with the given data if the file exists; creates the file if it does not exist.
 *
 * @tparam T The type of the data to write to the file. The type must support the insertion operator (operator<<).
 * @param filename The name of the file (with path if needed) where the data is to be written.
 * @param data The data item to write to the file.
 * @param openMode The mode to open the file. 0 represents append mode, and 1 represents truncate mode.
 */
template <typename T>
void WriteToFile(std::string filename, T data, int openMode) {

	std::ofstream outfile;

	switch (openMode) {
	case 0:
		outfile.open(filename, std::ios_base::app);
		break;
	case 1:
		outfile.open(filename, std::ios_base::trunc);
		break;
	}

	if (!outfile.is_open()) {
		std::cout << filename << " WAS UNABLE TO OPEN. " << std::endl;
	}

	outfile << data << '\n';
	outfile.close();
}
#ifndef UTILITIES_H
#define UTILITIES_H

#include <map>
#include <string>
#include <vector>
#include "typed_array.h"

// Sort a vector of doubles by magnitude
void sort_by_magnititude(std::vector<double>& vec);

// Read a matrix from a CSV file
TypedArray<TypedArray<double>> read_matrix_csv(const std::string path);

// Write a matrix to a CSV file
void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const std::string path);

// reads in an ascii text file and returns an assocation where each key is a
// word in the text file, and each value is the number of occurences of that
// word
std::map<std::string, int> occurrence_map(const std::string path);

#endif  // UTILITIES_H

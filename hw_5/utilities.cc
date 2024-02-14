#include "utilities.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "typed_array.h"

void sort_by_magnititude(std::vector<double>& vec) {
    sort(vec.begin(), vec.end(),
         [](double a, double b) { return abs(a) < abs(b); });
}

TypedArray<TypedArray<double>> read_matrix_csv(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    TypedArray<TypedArray<double>> matrix;
    std::string line;
    int rowCount = 0;

    while (getline(file, line)) {
        TypedArray<double> row;
        std::stringstream ss(line);
        std::string cell;
        int columnCount = 0;

        while (getline(ss, cell, ',')) {
            // Trim spaces and tabs from the beginning and end of the item
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);

            if (cell.empty()) {
                throw std::runtime_error("Missing value in matrix at row " +
                                         std::to_string(rowCount) +
                                         ", column " +
                                         std::to_string(columnCount));
            }

            // Convert item to double and add to the current row
            try {
                double value = stod(cell);
                row.set(columnCount, value);
            } catch (const std::invalid_argument& ia) {
                throw std::runtime_error(
                    "Invalid number format in matrix at row " +
                    std::to_string(rowCount) + ", column " +
                    std::to_string(columnCount));
            }
            columnCount++;
        }
        matrix.set(rowCount, row);
        rowCount++;
        // check if all rows have the same number of columns
        if (rowCount > 0 && row.size() != matrix.get(0).size()) {
            // std::cout << "row count: " << rowCount << std::endl;
            // std::cout << "row: " << row << std::endl;
            throw std::runtime_error("Row " + std::to_string(rowCount) +
                                        " has a different number of columns");
        }

    }

    
    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix,
                      const std::string path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.safe_get(i).size(); j++) {
            file << matrix.safe_get(i).safe_get(j);
            if (j < matrix.safe_get(i).size() - 1) {
                file << ",";
            }
        }
        file << std::endl;
    }
    file.close();
}

std::map<std::string, int> occurrence_map(const std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    auto isValidChar = [](char c) { return isalnum(c) || c == '\''; };

    std::map<std::string, int> wordCount;
    std::string word;
    while (file >> word) {
        std::string filteredWord;

        // remove non-alphanumeric characters and convert to lowercase
        copy_if(word.begin(), word.end(), back_inserter(filteredWord),
                isValidChar);
        transform(filteredWord.begin(), filteredWord.end(),
                  filteredWord.begin(),
                  [](unsigned char c) -> char { return tolower(c); });

        // add word to map
        if (!filteredWord.empty()) {
            wordCount[filteredWord]++;
        }
    }

    return wordCount;
}